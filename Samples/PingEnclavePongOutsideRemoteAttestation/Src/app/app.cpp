#include <stdio.h>
#include <iostream>
#include <assert.h>
#include "enclave_u.h"
#include "sgx_urts.h"
#include "sgx_utils/sgx_utils.h"
#include "network_ra.h"
#include "PingPong.h"
#include <pthread.h> 
#include "pong_enclave_attestation.h"

/* Global EID shared by multiple threads */
sgx_enclave_id_t global_eid = 0;

static PRT_BOOLEAN cooperative = PRT_FALSE;
static int threads = 1;

static PRT_BOOLEAN perf = PRT_FALSE;
static long steps = 0;
static long startTime = 0;
static long perfEndTime = 0;
static const char* parg = NULL;
static const char* workspaceConfig;

extern char secure_message[8];

PRT_PROCESS *process;

void ErrorHandler(PRT_STATUS status, PRT_MACHINEINST *ptr)
{
    if (status == PRT_STATUS_ASSERT)
    {
        ocall_print("exiting with PRT_STATUS_ASSERT (assertion failure)\n");
        // exit(1);
    }
    else if (status == PRT_STATUS_EVENT_OVERFLOW)
    {
        ocall_print("exiting with PRT_STATUS_EVENT_OVERFLOW\n");
        // exit(1);
    }
    else if (status == PRT_STATUS_EVENT_UNHANDLED)
    {
        ocall_print("exiting with PRT_STATUS_EVENT_UNHANDLED\n");
        // exit(1);
    }
    else if (status == PRT_STATUS_QUEUE_OVERFLOW)
    {
        ocall_print("exiting with PRT_STATUS_QUEUE_OVERFLOW \n");
        // exit(1);
    }
    else if (status == PRT_STATUS_ILLEGAL_SEND)
    {
        ocall_print("exiting with PRT_STATUS_ILLEGAL_SEND \n");
        // exit(1);
    }
    else
    {
        ocall_print("unexpected PRT_STATUS in ErrorHandler: \n");
        // exit(2);
    }

}


void Log(PRT_STEP step, PRT_MACHINESTATE* senderState, PRT_MACHINEINST *receiver, PRT_VALUE* event, PRT_VALUE* payload)
{ 
    PrtPrintStep(step, senderState, receiver, event, payload);
}

void MyAssert(PRT_INT32 condition, PRT_CSTRING message)
{
	if (condition != 0)
	{
		return;
	}
	else if (message == NULL)
	{
		ocall_print("ASSERT");
	}
	else
	{
		ocall_print("ASSERT: ");
        ocall_print(message);
	}
	// exit(1);
}


static void RunToIdle(void* process)
{
    // In the tester we run the state machines until there is no more work to do then we exit
    // instead of blocking indefinitely.  This is then equivalent of the non-cooperative case
    // where we PrtRunStateMachine once (inside PrtMkMachine).  So we do NOT call PrtWaitForWork.
    
    PRT_PROCESS_PRIV* privateProcess = (PRT_PROCESS_PRIV*)process;
	while (privateProcess->terminating == PRT_FALSE)
	{
		PRT_STEP_RESULT result = PrtStepProcess((PRT_PROCESS*) process);
		switch (result) {
		case PRT_STEP_TERMINATING:
			break;
		case PRT_STEP_IDLE:
			PrtWaitForWork((PRT_PROCESS*)process);
			break;
		case PRT_STEP_MORE:
			PrtYieldThread();
			break;
		}
	}
}

struct Enclave_start_attestation_wrapper_arguments {
    char* machineName;
    int receive_message;
};
//TODO move this to pong_enclave_attesation as well as methdod below
void* attestation_thread(void* parameters) { //receive_message should be true when the enclave is receiving the message
                                                  //false when the enclave wants to send a message
    struct Enclave_start_attestation_wrapper_arguments* p = (struct Enclave_start_attestation_wrapper_arguments*)parameters;
    //*((int*)(&receive_message))
    return (void*) enclave_start_attestation(p->machineName,  p->receive_message);
}

int ocall_pong_enclave_attestation_in_thread(char* other_machine_name, uint32_t size, int receive_message) {
    struct Enclave_start_attestation_wrapper_arguments parameters = {other_machine_name, receive_message};
    void* thread_ret;
    pthread_t thread_id; 
    printf("\n Calling Attestation Thread\n"); 
    pthread_create(&thread_id, NULL, attestation_thread, (void*) &parameters);
    //TODO look into not calling pthread_join but actually let this run asynchoronous
    pthread_join(thread_id, &thread_ret); 
    printf("\n Finished Attestation Thread\n"); 

    return 0;

}

extern "C" void P_SecureSend_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    //TODO Make Secure Send take in a parameter that is the receiving machine's name
    char* receiving_machine_name = "PongMachine";

    //TODO Enclave should be intialized and ready to go before SecureSend is called
    if (initialize_enclave(&global_eid, "enclave.token", "enclave.signed.so") < 0) {
        std::cout << "Fail to initialize enclave." << std::endl;
    }
    int ptr;
    sgx_status_t status = enclave_main(global_eid, &ptr); //Start up PrtTrusted inside enclave
    std::cout << status << std::endl;
    if (status != SGX_SUCCESS) {
        std::cout << "noob" << std::endl;
    }
    int ret_status;

    strcpy(secure_message, "PING"); //Make secure payload to be "PING"

    //Request the enclave to start the attestation and secure channel process so that
    // we can send the enclave a secure message
    if (ra_network_send_receive(receiving_machine_name, NULL, NULL) == 0) {
        printf("\nAttestation Succesful! Ping Event has been Sent!\n");

    } else {
        printf("\nERROR IN ATTESTATION. Message not sent!\n");

    }
    
}

// OCall implementations
void ocall_print(const char* str) {
    printf("[o] %s\n", str);
}

void ocall_send_pong(void) {
    PRT_VALUE* pongEvent = PrtMkEventValue(PrtPrimGetEvent(&P_EVENT_Pong.value));
    PRT_MACHINEID pingId;
    pingId.machineId = 1;

    PRT_MACHINEINST* pingMachine = PrtGetMachine(process, PrtMkMachineValue(pingId));
    PrtSend(NULL, pingMachine, pongEvent, 0);

}

int main(int argc, char const *argv[]) {

		PRT_GUID processGuid;
		PRT_VALUE *payload;
        PRT_VALUE *payload2;

		processGuid.data1 = 1;
		processGuid.data2 = 0;
		processGuid.data3 = 0;
		processGuid.data4 = 0;
		process = PrtStartProcess(processGuid, &P_GEND_IMPL_DefaultImpl, ErrorHandler, Log);
        ocall_print("after start process!\n");
        if (cooperative)
        {
            PrtSetSchedulingPolicy(process, PRT_SCHEDULINGPOLICY_COOPERATIVE);
        }
		if (parg == NULL)
		{
			payload = PrtMkNullValue();
            payload2 = PrtMkNullValue();

		}
		else
		{
			int i = atoi(parg);
			payload = PrtMkIntValue(i);
            payload2 = PrtMkIntValue(i);

            
		}

		PrtUpdateAssertFn(MyAssert);
        ocall_print("after update assert fn!\n");

        PRT_UINT32 mainMachine = 1; //TODO NOTE: I'm not able to send messages to machines unless they have id of 1. Otherwise I receive 
        // id out of bounds when I call PRT_MACHINEINST* pingMachine = PrtGetMachine(process, PrtMkMachineValue(pingId));
		PRT_BOOLEAN foundMachine = PrtLookupMachineByName("Ping", &mainMachine);
		PrtAssert(foundMachine, "No 'Ping' machine found!");
		PRT_MACHINEINST* pingMachine = PrtMkMachine(process, mainMachine, 1, &payload);    
        
        printf("after mk machine!\n");

        if (cooperative)
        {
            // test some multithreading across state machines.
            /*
            typedef void *(*start_routine) (void *);
            pthread_t tid[threads];
            for (int i = 0; i < threads; i++)
            {
                pthread_create(&tid[i], NULL, (start_routine)RunToIdle, (void*)process);
            }
            for (int i = 0; i < threads; i++)
            {
                pthread_join(tid[i], NULL);
            }
            */
        }
    
    return 0;
}