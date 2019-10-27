/*
 * Copyright (C) 2011-2019 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "network_ra.h"
#include "ping_attestation.h"
#include "enclave_u.h"
#include "sgx_urts.h"
#include "sgx_utils/sgx_utils.h"

extern sgx_enclave_id_t global_eid;


// Used to send requests to the service provider sample.  It
// simulates network communication between the ISV app and the
// ISV service provider.  This would be modified in a real
// product to use the proper IP communication.
//
// @param receiving_machine_name String name of the server URL
// @param p_req Pointer to the message to be sent.
// @param p_resp Pointer to a pointer of the response message.

// @return int

int ra_network_send_receive(const char *sending_machine_name, 
    const char *receiving_machine_name,
    const ra_samp_request_header_t *p_req,
    ra_samp_response_header_t **p_resp,
    Encrypted_Message optional_Message)
{
    //Request to PingMachine to initialize attestation channel
    if (strcmp(receiving_machine_name, "PingMachine") == 0 && optional_Message.secret_size == 0) {
        int ret = 0;
        ra_samp_response_header_t* p_resp_msg;

        if((NULL == receiving_machine_name) ||
            (NULL == p_req) ||
            (NULL == p_resp))
        {
            return -1;
        }

        switch(p_req->type)
        {

        case TYPE_RA_MSG0:
            ret = sp_ra_proc_msg0_req((const sample_ra_msg0_t*)((size_t)p_req
                + sizeof(ra_samp_request_header_t)),
                p_req->size);
            if (0 != ret)
            {
                fprintf(stderr, "\nError, call sp_ra_proc_msg1_req fail [%s].",
                    __FUNCTION__);
            }
            break;

        case TYPE_RA_MSG1:
            ret = sp_ra_proc_msg1_req((const sample_ra_msg1_t*)((size_t)p_req
                + sizeof(ra_samp_request_header_t)),
                p_req->size,
                &p_resp_msg);
            if(0 != ret)
            {
                fprintf(stderr, "\nError, call sp_ra_proc_msg1_req fail [%s].",
                    __FUNCTION__);
            }
            else
            {
                *p_resp = p_resp_msg;
            }
            break;

        case TYPE_RA_MSG3:
            ret =sp_ra_proc_msg3_req((const sample_ra_msg3_t*)((size_t)p_req +
                sizeof(ra_samp_request_header_t)),
                p_req->size,
                &p_resp_msg,
                0);
            if(0 != ret)
            {
                fprintf(stderr, "\nError, call sp_ra_proc_msg3_req fail [%s].",
                    __FUNCTION__);
            }
            else
            {
                *p_resp = p_resp_msg;
            }
            break;

        default:
            ret = -1;
            fprintf(stderr, "\nError, unknown ra message type. Type = %d [%s].",
                p_req->type, __FUNCTION__);
            break;
        }

        return ret;

     //Request to PingMachine to send encrypted data based on previous secure channel
     } else if (strcmp(receiving_machine_name, "PingMachine") == 0 && optional_Message.secret_size > 0) {
         ocall_ping_machine_receive_encrypted_message(
                                (uint8_t*)optional_Message.encrypted_message, 
                                optional_Message.secret_size,
                                 optional_Message.payload_tag);

    //Request to PongMachine to initialize a secure attestation channel
    } else if (strcmp(receiving_machine_name, "PongMachine") == 0) {
        int ptr;
        sgx_status_t status = pong_enclave_request_attestation(global_eid, &ptr, sending_machine_name);
        if (status == SGX_SUCCESS && ptr == 0) {
            return ptr;
        } else {
            printf("\nEnclave Request Attestation SGX Error!\n");
        }
    } else if (strcmp(receiving_machine_name, "KPS") == 0) {
        createCapabilityKey("", "");

    } else {
        return -1;
    }
}

// Used to free the response messages.  In the sample code, the
// response messages are allocated by the SP code.
//
//
// @param resp Pointer to the response buffer to be freed.

void ra_free_network_response_buffer(ra_samp_response_header_t *resp)
{
    if(resp!=NULL)
    {
        free(resp);
    }
}

char* network_request(char* request) {
    char* split = strtok(request, ":");
    if (strcmp(split, "Create") == 0) {
        return "Create Message found!";
    } else {
        return "Command Not Found";
    }
}
