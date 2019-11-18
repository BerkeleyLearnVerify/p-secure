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



#ifndef _NETWORK_RA_H

#define _NETWORK_RA_H

const int SIZE_OF_IDENTITY_STRING = 20;
const int SIZE_OF_CAPABILITYKEY = 20;
const int SIZE_OF_SESSION_KEY = 20;
const int SIZE_OF_MAX_MESSAGE = 20;

const int SIZE_OF_MAX_EVENT_NAME = 20;
const int SIZE_OF_MAX_EVENT_PAYLOAD = 100;



struct Encrypted_Message{
    uint8_t* encrypted_message;
    uint32_t secret_size;
    uint8_t* payload_tag;
};

static const Encrypted_Message default_Encrypted_Message = {NULL, 0, NULL};

/* Enum for all possible message types between the ISV app and
 * the ISV SP. Requests and responses in the remote attestation
 * sample.
 */
typedef enum _ra_msg_type_t
{
     TYPE_RA_MSG0,
     TYPE_RA_MSG1,
     TYPE_RA_MSG2,
     TYPE_RA_MSG3,
     TYPE_RA_ATT_RESULT,
}ra_msg_type_t;

/* Enum for all possible message types between the SP and IAS.
 * Network communication is not simulated in the remote
 * attestation sample.  Currently these aren't used.
 */
typedef enum _ias_msg_type_t
{
     TYPE_IAS_ENROLL,
     TYPE_IAS_GET_SIGRL,
     TYPE_IAS_SIGRL,
     TYPE_IAS_ATT_EVIDENCE,
     TYPE_IAS_ATT_RESULT,
}ias_msg_type_t;

#pragma pack(1)
typedef struct _ra_samp_request_header_t{
    uint8_t  type;     /* set to one of ra_msg_type_t*/
    uint32_t size;     /*size of request body*/
    uint8_t  align[3];
    uint8_t body[];
}ra_samp_request_header_t;

typedef struct _ra_samp_response_header_t{
    uint8_t  type;      /* set to one of ra_msg_type_t*/
    uint8_t  status[2];
    uint32_t size;      /*size of the response body*/
    uint8_t  align[1];
    uint8_t  body[];
}ra_samp_response_header_t;

#pragma pack()

#ifdef  __cplusplus
extern "C" {
#endif

int ra_network_send_receive(const char *sending_machine_name, 
                            const char *receiving_machine_name,
                            const ra_samp_request_header_t *req,
                            ra_samp_response_header_t **p_resp,
                            Encrypted_Message optional_Message = default_Encrypted_Message,
                            char* plain_text_message = NULL);
void ra_free_network_response_buffer(ra_samp_response_header_t *resp);
char* send_network_request_API(char* request);
void* network_request_thread_wrapper(void* request);
char* network_request_logic(char* request);

#ifdef  __cplusplus
}
#endif

#endif
