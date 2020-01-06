#include <stdio.h>
#include <iostream>
#include <assert.h>
#include "PingPongEnclave.h"
#include <unordered_map> 
#include <map>

using namespace std;

char* itoa(int num, char* str, int base);
int atoi(char *p);
void reverse(char str[], int length);

//NOTE all typedefs are also defined in enclave.cpp and constants.cpp
typedef tuple <string,string> PublicMachineChildPair; //parentMachineID, childPublicKey
typedef tuple <string,string> identityKeyPair; //public, private


int handle_incoming_events_ping_machine(PRT_UINT32 eventIdentifier);

int handle_incoming_event(PRT_UINT32 eventIdentifier, PRT_MACHINEID receivingMachinePID, int numArgs, int payloadType, char* payload);
char* serializePrtValueToString(PRT_VALUE* value);

void generateIdentity(string& publicID, string& privateID, string prefix);

char* receiveNetworkRequest(char* request);

void startPrtProcessIfNotStarted();

int getNextPID();

string createString(char* str);

int createMachine(char* machineType, int numArgs, int payloadType, char* payload);

int machineTypeIsSecure(char* machineType);

char* createUSMMachineAPI(char* machineType, int numArgs, int payloadType, char* payload);

char* registerMachineWithNetwork(char* newMachineID);

char* generateCStringFromFormat(char* format_string, char* strings_to_print[], int num_strings);

char* USMinitializeCommunicationAPI(char* requestingMachineIDKey, char* receivingMachineIDKey);

void generateSessionKey(string& newSessionKey);

char* USMsendMessageAPI(char* receivingMachineIDKey, char* eventNum, int numArgs, int payloadType, char* payload);

PRT_VALUE* sendCreateMachineNetworkRequest(PRT_MACHINEINST* context, PRT_VALUE*** argRefs, char* createTypeCommand, bool isSecureCreate);

extern "C" PRT_VALUE* P_UntrustedCreateCoordinator_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);

extern "C" PRT_VALUE* P_CreateSecureMachineRequest_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);

char* receiveNetworkRequestHelper(char* request, bool isEnclaveUntrustedHost);

void safe_free(void* ptr);

