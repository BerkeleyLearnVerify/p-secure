#include "string.h"
#include <string>
#include "constants.h"
#include <tuple>
#include <unordered_map> 
#include <unordered_set> 
#include <map> 
#include <iostream>

#ifdef ENCLAVE_STD_ALT
#include "enclave_t.h"
#endif

#ifndef ENCLAVE_STD_ALT
#include "enclave_u.h"
#include "sample_libcrypto.h"
#include "sgx_tcrypto.h"
extern sgx_enclave_id_t global_app_eid;
#endif

using namespace std;

#ifndef ENCLAVE_STD_ALT
extern unordered_map<string, int> USMPublicIdentityKeyToMachinePIDDictionary; 
#endif

extern PRT_PROCESS *process;
extern PRT_PROGRAMDECL* program;

//NOTE all typedefs are also defined in enclave.cpp and app.cpp
typedef tuple <string,string> identityKeyPair; //public, private
extern unordered_map<int, identityKeyPair> MachinePIDToIdentityDictionary;
typedef tuple <uint32_t,string> PMachineChildPair; //parentMachineID, childPublicKey
extern map<PMachineChildPair, string> PMachineToChildCapabilityKey;
extern unordered_map<string, sgx_enclave_id_t> PublicIdentityKeyToEidDictionary;

typedef tuple <string,string> PublicMachineChildPair; //parentMachineID, childPublicKey
extern map<PublicMachineChildPair, string> PublicIdentityKeyToChildSessionKey;
extern map<tuple<string, string>, int> ChildSessionKeyToNonce;
extern unordered_map<string, int> PublicIdentityKeyToMachinePIDDictionary;
extern unordered_map<int, string> MachinePIDtoCapabilityKeyDictionary;
extern unordered_map<string, string> PublicIdentityKeyToPublicSigningKey;
extern unordered_map<string, string> PrivateIdentityKeyToPrivateSigningKey;


extern bool verifySignature(char* message, int message_size, sgx_rsa3072_signature_t* signature, sgx_rsa3072_public_key_t* public_key);
extern int sendMessageAPI(char* requestingMachineIDKey, char* receivingMachineIDKey, char* event, int numArgs, int payloadType, char* payload, int payloadSize);


extern unordered_set<string> USMAuthorizedTypes;

extern int CURRENT_ENCLAVE_EID_NUM;

extern int initialize_enclave(sgx_enclave_id_t* eid, const std::string& launch_token_path, const std::string& enclave_name);

extern char* createUSMMachineAPI(char* machineType, int numArgs, int payloadType, char* payload, int payloadSize);
extern char* USMinitializeCommunicationAPI(char* requestingMachineIDKey, char* receivingMachineIDKey, char* newSessionKey);


extern char* untrusted_enclave1_receiveNetworkRequest(char* request, size_t requestSize);

extern char* USMSendMessageAPI(char* requestingMachineIDKey, char* receivingMachineIDKey, char* iv, char* mac, char* encryptedMessage, char* response);

extern char* retrieveCapabilityKeyForChildFromKPS(char* currentMachinePublicIDKey, char* childPublicIDKey, char* requestedMachineTypeToCreate);
extern char* send_network_request_API(char* request);

int handle_incoming_event(PRT_UINT32 eventIdentifier, PRT_MACHINEID receivingMachinePID, int numArgs, int payloadType, char* payload, int payloadSize, bool isSecureSend);

extern sgx_rsa3072_signature_t* signStringMessage(char* message, int size, sgx_rsa3072_key_t *private_key);

void safe_free(void* ptr) {
    if (ptr != NULL) {
        free(ptr);
        ptr = NULL;
    }
}

void printSessionKey(char* key) {
    char* keyCopy = (char*) malloc(SIZE_OF_REAL_SESSION_KEY);
    memcpy(keyCopy, key, SIZE_OF_REAL_SESSION_KEY);
    ocall_print("session key:");
    char* temp = keyCopy;
    for (int i = 0; i < SIZE_OF_REAL_SESSION_KEY; i++) {
        if (temp[i] == '\0') {
            temp[i] = 'D';
        }
    }
    keyCopy[SIZE_OF_REAL_SESSION_KEY - 1] = '\0';
    
    ocall_print(keyCopy);
    safe_free(keyCopy);
}
void printPayload(char* payload, int size) {
    char* keyCopy = (char*) malloc(size);
    memcpy(keyCopy, payload, size);
    ocall_print("payload:");
    char* temp = keyCopy;
    for (int i = 0; i < size; i++) {
        if (temp[i] == '\0') {
            temp[i] = 'D';
        }
    }
    keyCopy[size - 1] = '\0';
    
    ocall_print(keyCopy);
    safe_free(keyCopy);
}

void printRSAKey(char* key) {
    char* keyCopy = (char*) malloc(SGX_RSA3072_KEY_SIZE);
    memcpy(keyCopy, key, SGX_RSA3072_KEY_SIZE);
    ocall_print("key:");
    char* temp = keyCopy;
    for (int i = 0; i < SGX_RSA3072_KEY_SIZE; i++) {
        if (temp[i] == '\0') {
            temp[i] = 'D';
        }
    }
    keyCopy[SGX_RSA3072_KEY_SIZE - 1] = '\0';
    
    ocall_print(keyCopy);
    safe_free(keyCopy);
}

void printPublicCapabilityKey(char* key) {
    char* keyCopy = (char*) malloc(SIZE_OF_PUBLIC_CAPABILITY_KEY);
    memcpy(keyCopy, key, SIZE_OF_PUBLIC_CAPABILITY_KEY);
    ocall_print("public capability key:");
    char* temp = keyCopy;
    for (int i = 0; i < SIZE_OF_PUBLIC_CAPABILITY_KEY; i++) {
        if (temp[i] == '\0') {
            temp[i] = 'D';
        }
    }
    keyCopy[SIZE_OF_PUBLIC_CAPABILITY_KEY - 1] = '\0';
    
    ocall_print(keyCopy);
    safe_free(keyCopy);
}

void printPrivateCapabilityKey(char* key) {
    char* keyCopy = (char*) malloc(SIZE_OF_PRIVATE_CAPABILITY_KEY);
    memcpy(keyCopy, key, SIZE_OF_PRIVATE_CAPABILITY_KEY);
    ocall_print("private capability key:");
    char* temp = keyCopy;
    for (int i = 0; i < SIZE_OF_PRIVATE_CAPABILITY_KEY; i++) {
        if (temp[i] == '\0') {
            temp[i] = 'D';
        }
    }
    keyCopy[SIZE_OF_PRIVATE_CAPABILITY_KEY - 1] = '\0';
    
    ocall_print(keyCopy);
    safe_free(keyCopy);
}

//Responsiblity of caller to free
char* retrievePublicCapabilityKey(char* capabilityPayload) {
    char* publicKey = (char*) malloc(sizeof(sgx_rsa3072_public_key_t));
    memcpy(publicKey, capabilityPayload, sizeof(sgx_rsa3072_public_key_t));
    return publicKey;
}

//Responsiblity of caller to free
char* retrievePrivateCapabilityKey(char* capabilityPayload) {
    char* privateKey = (char*) malloc(sizeof(sgx_rsa3072_key_t));
    memcpy(privateKey, capabilityPayload + sizeof(sgx_rsa3072_public_key_t) + 1, sizeof(sgx_rsa3072_key_t));
    return privateKey;
}

//Responsiblity of caller to free return
char* createStringLiteralMalloced(char* stringLiteral) {
    //TODO if modifying here, modify in network_ra.cpp
    char* malloced = (char*) malloc(strlen(stringLiteral));
    strncpy(malloced, stringLiteral, strlen(stringLiteral) + 1);
    return malloced;

}

int atoi(char *p) {
    int k = 0;
    while (*p) {
        k = (k << 3) + (k << 1) + (*p) - '0';
        p++;
     }
     return k;
}

void reverse(char str[], int length) 
{ 
    int start = 0; 
    int end = length -1; 
    while (start < end) 
    { 
        char temp = *(str+start);
        *(str+start) = *(str+end);
        *(str+end) = temp;
        //swap(*(str+start), *(str+end)); 
        start++; 
        end--; 
    } 
} 

// Implementation of itoa() 
char* itoa(int num, char* str, int base) 
{ 
    int i = 0; 
    bool isNegative = false; 
  
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0) 
    { 
        str[i++] = '0'; 
        str[i] = '\0'; 
        return str; 
    } 
  
    // In standard itoa(), negative numbers are handled only with  
    // base 10. Otherwise numbers are considered unsigned. 
    if (num < 0 && base == 10) 
    { 
        isNegative = true; 
        num = -num; 
    } 
  
    // Process individual digits 
    while (num != 0) 
    { 
        int rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/base; 
    } 
  
    // If number is negative, append '-' 
    if (isNegative) 
        str[i++] = '-'; 
  
    str[i] = '\0'; // Append string terminator 
  
    // Reverse the string 
    reverse(str, i); 
  
    return str; 
} 

//Responsibility of caller to free result
char* concat(char* str1, char* str2) {
    char* retString = (char*) malloc(strlen(str1) + strlen(str2) + 2);
    strncpy(retString, str1, strlen(str1) + 1);
    strncat(retString, str2, strlen(str2) + 1);
    retString[strlen(str1) + strlen(str2)] = '\0';
    return retString;
}

PRT_TYPE_KIND convertKindToType(int kind) {
    if (kind == PRT_VALUE_KIND_INT) {
        return PRT_KIND_INT;
    } else if (kind == PRT_VALUE_KIND_FOREIGN) {
        return PRT_KIND_FOREIGN;
    } else if (kind == PRT_VALUE_KIND_BOOL) {
        return PRT_KIND_BOOL;
    } else {
        return PRT_TYPE_KIND_CANARY; //unsupported type
    }
}

int returnSizeOfForeignType(int type_tag) {
    if (type_tag == P_TYPEDEF_StringType->typeUnion.foreignType->declIndex || type_tag == P_TYPEDEF_secure_StringType->typeUnion.foreignType->declIndex) { 
        return SIZE_OF_PRT_STRING_SERIALIZED;
    }  else if (type_tag == P_TYPEDEF_machine_handle->typeUnion.foreignType->declIndex) {        
        return SIZE_OF_MACHINE_HANDLE;
    } else if (type_tag == P_TYPEDEF_capability->typeUnion.foreignType->declIndex) {
        return SIZE_OF_P_CAPABILITY_FOREIGN_TYPE;
    } else if (type_tag == P_TYPEDEF_secure_machine_handle->typeUnion.foreignType->declIndex) {
        return SIZE_OF_SECURE_MACHINE_HANDLE;
    } else {
        return -1;
    }
}

//Responsibility of Caller to free return
char* serializePrtValueToString(PRT_VALUE* value, int& final_size) {
    //TODO code the rest of the types
    if (value->discriminator == PRT_VALUE_KIND_INT || value->discriminator == PRT_VALUE_KIND_SECURE_INT) {
        char* integer = (char*) malloc(SIZE_OF_MAX_INTEGER_SERIALIZED);
        itoa(value->valueUnion.nt, integer, 10);
        final_size += strlen(integer);
        return integer;
    } else if (value->discriminator == PRT_VALUE_KIND_FOREIGN) {
        int size_of_type_tag_foreign_type = returnSizeOfForeignType(value->valueUnion.frgn->typeTag);
        char* string = (char*) malloc(10 + 1 + size_of_type_tag_foreign_type);
        char* foreignTypeTagString = (char*) malloc(10);
        itoa(value->valueUnion.frgn->typeTag, foreignTypeTagString, 10);
        memcpy(string, foreignTypeTagString, strlen(foreignTypeTagString));
        memcpy(string + strlen(foreignTypeTagString), ":", 1);
        memcpy(string + strlen(foreignTypeTagString) + 1, (char*) value->valueUnion.frgn->value, size_of_type_tag_foreign_type);
        ocall_print("the actual PRT value is");
        ocall_print((char*)value->valueUnion.frgn->value);
        //string[SIZE_OF_PRT_STRING_SERIALIZED] = '\0';
        if (value->valueUnion.frgn->typeTag == 2) {
            ocall_print("serializing capability");
            ocall_print("length added is");
            ocall_print_int(strlen(foreignTypeTagString) + 1 + size_of_type_tag_foreign_type);
        }
        final_size += strlen(foreignTypeTagString) + 1 + size_of_type_tag_foreign_type;
        return string;
    } else if (value->discriminator == PRT_VALUE_KIND_BOOL || value->discriminator == PRT_VALUE_KIND_SECURE_BOOL) {
        if (value->valueUnion.bl == PRT_TRUE) {
            final_size += 4;
            return createStringLiteralMalloced("true");
        } else if (value->valueUnion.bl == PRT_FALSE) {
            final_size += 5;
            return createStringLiteralMalloced("false");
        } else {
            final_size += 24;
            return createStringLiteralMalloced("ERROR: Boolean not found");
        }
    } else if (value->discriminator == PRT_VALUE_KIND_TUPLE) {
        char* tupleString = (char*) malloc(SIZE_OF_MAX_SERIALIZED_TUPLE);
        int currIndex = 0;
        PRT_TUPVALUE* tupPtr = value->valueUnion.tuple;
        for (int i = 0; i < tupPtr->size; i++) {
            PRT_VALUE* currValue = tupPtr->values[i];
            int currValueType = tupPtr->values[i]->discriminator;
            char* typeString = (char*) malloc(10);
            itoa(currValueType, typeString, 10);
            memcpy(tupleString + currIndex, typeString, strlen(typeString) + 1);
            currIndex += strlen(typeString);
            safe_free(typeString);
            tupleString[currIndex] = ':';
            currIndex++;
            int szSerializedStr = 0;
            char* serializedStr = serializePrtValueToString(currValue, szSerializedStr);
            memcpy(tupleString + currIndex, serializedStr, szSerializedStr + 1);
            currIndex += szSerializedStr;
            safe_free(serializedStr);
            if (i < tupPtr->size - 1) {
                tupleString[currIndex] = ':';
                currIndex++;
            }
        }
        // strncat(tupleString, ":END_TUP", 10);
        memcpy(tupleString + currIndex, ":END_TUP", 8);
        currIndex += 8;
        tupleString[currIndex] = '\0';
        final_size = currIndex;
        return tupleString;
    } else if (value->discriminator == PRT_VALUE_KIND_MAP) {
        char* mapString = (char*) malloc(SIZE_OF_MAX_SERIALIZED_MAP);
        int currIndex = 0;

        PRT_VALUE* mapValues = PrtMapGetValues(value);
        PRT_VALUE* mapKeys = PrtMapGetKeys(value);
        int size = mapValues->valueUnion.seq->size;

        for (int i = 0; i < size; i++) {
            PRT_VALUE* mapKey = mapKeys->valueUnion.seq->values[i];
            int currValueType = mapKey->discriminator;
            char* typeString = (char*) malloc(10);
            itoa(currValueType, typeString, 10);
            memcpy(mapString + currIndex, typeString, strlen(typeString) + 1);
            currIndex += strlen(typeString);
            safe_free(typeString);
            mapString[currIndex] = ':';
            currIndex++;
            int serializedKeySz = 0;
            char* serializedKey = serializePrtValueToString(mapKey, serializedKeySz);
            memcpy(mapString + currIndex, serializedKey, serializedKeySz + 1);
            currIndex += serializedKeySz;
            safe_free(serializedKey);
            mapString[currIndex] = ':';
            currIndex++;
            PRT_VALUE* mapValue = mapValues->valueUnion.seq->values[i];
            currValueType = mapValue->discriminator;
            typeString = (char*) malloc(10);
            itoa(currValueType, typeString, 10);
            memcpy(mapString + currIndex, typeString, strlen(typeString) + 1);
            currIndex += strlen(typeString);
            safe_free(typeString);
            mapString[currIndex] = ':';
            currIndex++;
            int serializedValueSz = 0;
            char* serializedValue = serializePrtValueToString(mapValue, serializedValueSz);
            memcpy(mapString + currIndex, serializedValue, serializedValueSz + 1);
            currIndex += serializedValueSz;
            safe_free(serializedValue);
            if (i < size - 1) {
                mapString[currIndex] = ':';
                currIndex++;
            }
        }
        // strncat(mapString, ":END_MAP", 10);
        memcpy(mapString + currIndex, ":END_MAP", 8);
        currIndex += 8;
        mapString[currIndex] = '\0';
        final_size = currIndex;
        return mapString;
    } else if (value->discriminator == PRT_VALUE_KIND_SEQ) {
        char* seqString = (char*) malloc(SIZE_OF_MAX_SERIALIZED_SEQ);
        int currIndex = 0;

        int size = PrtSeqSizeOf(value);

        PrtPrintValue(value);

        for (int i = 0; i < size; i++) {

            PRT_VALUE* seqValue = PrtSeqGet(value, PrtMkIntValue(i));
            int currValueType = seqValue->discriminator;
            char* typeString = (char*) malloc(10);
            itoa(currValueType, typeString, 10);
            memcpy(seqString + currIndex, typeString, strlen(typeString) + 1);
            currIndex += strlen(typeString);
            safe_free(typeString);
            seqString[currIndex] = ':';
            currIndex++;
            int serializedValueSz = 0;
            char* serializedValue = serializePrtValueToString(seqValue, serializedValueSz);
            memcpy(seqString + currIndex, serializedValue, serializedValueSz + 1);
            currIndex += serializedValueSz;
            safe_free(serializedValue);
            if (i < size - 1) {
                seqString[currIndex] = ':';
                currIndex++;
            }
        }
        // strncat(seqString, ":END_SEQ", 10);
        ocall_print("sequence so far");
        ocall_print(seqString);
        ocall_print("checking location of currIndex");
        ocall_print_int(currIndex);
        memcpy(seqString + currIndex, ":END_SEQ", 9);
        ocall_print("new seq");
        ocall_print(seqString);
        currIndex += 8;
        seqString[currIndex] = '\0';
        final_size = currIndex;
        return seqString;
    }
    
    
     else {
        return createStringLiteralMalloced("UNSUPPORTED_TYPE");
    }

}

PRT_VALUE* deserializeHelper(char* payloadOriginal, int* numCharactersProcessed) { //assumes only 1 non-recursive element
    char* payload = (char*) malloc(strlen(payloadOriginal) + 1);
    strncpy(payload, payloadOriginal, strlen(payloadOriginal) + 1);
    char* reentrant = NULL; 
    char* payloadTypeString = strtok_r(payload, ":", &reentrant);
    int payloadType = atoi(payloadTypeString);
    char* str = strtok_r(NULL, ":", &reentrant);
    *numCharactersProcessed = strlen(payloadTypeString) + 1 + strlen(str);
    PRT_VALUE* newPrtValue = (PRT_VALUE*)PrtMalloc(sizeof(PRT_VALUE));
    newPrtValue->discriminator = (PRT_VALUE_KIND) payloadType;
    if (payloadType == PRT_VALUE_KIND_INT || payloadType == PRT_VALUE_KIND_SECURE_INT) {
        if (payloadType == PRT_VALUE_KIND_SECURE_INT) {
            ocall_print("Creating secure int!");
        }
        ocall_print("Make Prt Int with Value:");
        ocall_print(str);
        newPrtValue->valueUnion.nt = atoi(str);
    } else if (payloadType == PRT_VALUE_KIND_FOREIGN) {
        ocall_print("Make Prt String with Value:");
        // ocall_print(str);
        char* typeTagString = str;
        int size_of_foreign_type = returnSizeOfForeignType(atoi(typeTagString));
        newPrtValue->valueUnion.frgn = (PRT_FOREIGNVALUE*) PrtMalloc(sizeof(PRT_FOREIGNVALUE));
       //  = 0; //TODO hardcoded for StringType
        PRT_STRING prtStr = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (size_of_foreign_type));
        // sprintf_s(prtStr, size_of_foreign_type, str);
        
        newPrtValue->valueUnion.frgn->typeTag = atoi(typeTagString);
        str = payloadOriginal + strlen(payloadTypeString) + 1 + strlen(typeTagString) + 1;
        printRSAKey(str);
        memcpy(prtStr, str, size_of_foreign_type);
        newPrtValue->valueUnion.frgn->value = (PRT_UINT64) prtStr; //TODO do we need to memcpy?
        *numCharactersProcessed = strlen(payloadTypeString) + 1 + strlen(typeTagString) + 1 + size_of_foreign_type;
    } else if (payloadType == PRT_VALUE_KIND_BOOL || payloadType == PRT_VALUE_KIND_SECURE_BOOL) {
        if (strcmp(str, "true") == 0) {
            newPrtValue->valueUnion.bl = PRT_TRUE;
        } else if (strcmp(str, "false") == 0){
            newPrtValue->valueUnion.bl = PRT_FALSE;
        } 
    } 
    safe_free(payload);
    return newPrtValue;

}

PRT_VALUE** deserializeStringToPrtValue(int numArgs, char* strOriginal, int payloadSize, int* numCharactersProcessed) { //TODO shiv add string size (payload size) here
    //TODO code the rest of the types (only int is coded for now)
    ocall_print("Deserialized called!");
    ocall_print(strOriginal);
    ocall_print_int(payloadSize + 2);
    *numCharactersProcessed = 0;
    char* str = (char*) malloc(payloadSize + 3);
    memcpy(str, strOriginal, payloadSize + 3);
    char* strCopy = (char*) malloc(payloadSize + 3);
    memcpy(strCopy, strOriginal, payloadSize + 3);

    // char* str = (char*) malloc(strlen(strOriginal) + 1);
    // strncpy(str, strOriginal, strlen(strOriginal) + 1);
    // char* strCopy = (char*) malloc(strlen(strOriginal) + 1);
    // strncpy(strCopy, strOriginal, strlen(strOriginal) + 1);

    PRT_VALUE** values = (PRT_VALUE**) PrtCalloc(numArgs, sizeof(PRT_VALUE*));
    char* reentrant = NULL;
    char* temp = str;
    char* split = strtok_r(str, ":", &reentrant);
    *numCharactersProcessed = *numCharactersProcessed + strlen(split) + 1; //+ 1 for ":"
    int payloadType = atoi(split);
    for (int i = 0; i < numArgs; i++) {
        
        if (payloadType == PRT_VALUE_KIND_INT || payloadType == PRT_VALUE_KIND_SECURE_INT || payloadType == PRT_VALUE_KIND_FOREIGN || payloadType == PRT_VALUE_KIND_BOOL || payloadType == PRT_VALUE_KIND_SECURE_BOOL) {
            ocall_print("Processing Primitative Type:");
            printRSAKey(strOriginal);
            int numProcessedInHelper;
            values[i] = deserializeHelper(strOriginal, &numProcessedInHelper);
            *numCharactersProcessed = numProcessedInHelper;
        }
        else if (payloadType == PRT_VALUE_KIND_TUPLE) {
            ocall_print("Deserializing Tuple:");
            values[i] = (PRT_VALUE*) PrtMalloc(sizeof(PRT_VALUE));
            PRT_TUPVALUE* tupPtr = (PRT_TUPVALUE*) PrtMalloc(sizeof(PRT_TUPVALUE));
            values[i]->discriminator = PRT_VALUE_KIND_TUPLE;
            values[i]->valueUnion.tuple = tupPtr;            
            tupPtr->size = 0;
            char* nextTupleElementToProcess = strCopy + strlen(split) + 1; // + 1 for ":"
            char* nextTupleElementToProcessOriginal = nextTupleElementToProcess;
            tupPtr->values = (PRT_VALUE **)PrtCalloc(MAX_TUPLE_ELEMENT_LENGTH, sizeof(PRT_VALUE*));
            while (strncmp(nextTupleElementToProcess, "END_TUP", 7) != 0) {
                //char* payload = strtok_r(NULL, ":", &reentrant); //TODO make this safe?
                ocall_print("Processing Element String:");
                ocall_print(nextTupleElementToProcess);
                int i = tupPtr->size;
                tupPtr->size++;
                int numProcessedInHelper;
                tupPtr->values[i] = *deserializeStringToPrtValue(1, nextTupleElementToProcess, payloadSize - (nextTupleElementToProcess - strCopy), &numProcessedInHelper);// deserializeStringToPrtValue(1, );
                ocall_print("Element Processed.");
                ocall_print("Number of characters in helper is ");
                ocall_print_int(numProcessedInHelper);
                // *numCharactersProcessed =  *numCharactersProcessed + numProcessedInHelper + 1; //+1 for ":"
                nextTupleElementToProcess = nextTupleElementToProcess + numProcessedInHelper + 1;
            }
            *numCharactersProcessed =  *numCharactersProcessed + (nextTupleElementToProcess - nextTupleElementToProcessOriginal) + 7; //+7 for "END_TUP"

        } else if (payloadType == PRT_VALUE_KIND_MAP) {

            char* nextMapKeyValuePairToProcess = strCopy + strlen(split) + 1; // + 1 for ":"
            char* nextMapKeyValuePairToProcessOriginal = nextMapKeyValuePairToProcess;

           
            // PrtMkDefaultValue()
            // values[i]->discriminator = PRT_VALUE_KIND_MAP;
            // values[i]->valueUnion.map = map;

            // map->size = 0;
            // map->capNum = 0;
            // map->buckets = (PRT_MAPNODE **)PrtCalloc(PrtHashtableCapacities[0], sizeof(PRT_MAPNODE *));
            // map->first = NULL;
            // map->last = NULL;

            while (strncmp(nextMapKeyValuePairToProcess, "END_MAP", 7) != 0) {
                int numProcessedInHelper;
                PRT_VALUE* key = *deserializeStringToPrtValue(1, nextMapKeyValuePairToProcess, payloadSize - (nextMapKeyValuePairToProcess - strCopy), &numProcessedInHelper);
                char* dataType = (char*) malloc(strlen(nextMapKeyValuePairToProcess) + 1);
                strncpy(dataType, nextMapKeyValuePairToProcess, strlen(nextMapKeyValuePairToProcess) + 1);
                char* reentrant = NULL;
                strtok_r(dataType, ":", &reentrant);
                int dType = atoi(dataType);
                safe_free(dataType);
                nextMapKeyValuePairToProcess = nextMapKeyValuePairToProcess + numProcessedInHelper + 1;

                PRT_VALUE* value = *deserializeStringToPrtValue(1, nextMapKeyValuePairToProcess, payloadSize - (nextMapKeyValuePairToProcess - strCopy), &numProcessedInHelper);
                char* dataType2 = (char*) malloc(strlen(nextMapKeyValuePairToProcess) + 1);
                strncpy(dataType2, nextMapKeyValuePairToProcess, strlen(nextMapKeyValuePairToProcess) + 1);
                char* reentrant2 = NULL;
                strtok_r(dataType2, ":", &reentrant2);
                int dType2 = atoi(dataType2);
                safe_free(dataType2);
                nextMapKeyValuePairToProcess = nextMapKeyValuePairToProcess + numProcessedInHelper + 1;

                if (values[i] == NULL) {

                    PRT_TYPE* mapType = PrtMkMapType(PrtMkPrimitiveType(convertKindToType(dType)), PrtMkPrimitiveType(convertKindToType(dType2)));
                    // PRT_TYPE* mapType = (PRT_TYPE*) PrtMalloc(sizeof(PRT_TYPE));
                    // mapType->typeKind = PRT_KIND_MAP;
                    // mapType->typeUnion.map = 
                    values[i] = PrtMkDefaultValue(mapType);

                }

                PrtMapUpdate(values[i], key, value);
            }

            ocall_print("Map created");
            *numCharactersProcessed =  *numCharactersProcessed + (nextMapKeyValuePairToProcess - nextMapKeyValuePairToProcessOriginal) + 7; //+7 for "END_MAP"


        } else if (payloadType == PRT_VALUE_KIND_SEQ) {

            char* nextSeqElementToProcess = strCopy + strlen(split) + 1; // + 1 for ":"
            char* nextSeqElementToProcessOriginal = nextSeqElementToProcess;

            int index = 0;
            while (strncmp(nextSeqElementToProcess, "END_SEQ", 7) != 0) {
                // char* payload = strtok_r(NULL, ":", &reentrant); //TODO make this safe?
                // int dType = atoi(dataType);
                int numProcessedInHelper;
                PRT_VALUE* value = *deserializeStringToPrtValue(1, nextSeqElementToProcess, payloadSize - (nextSeqElementToProcess - strCopy), &numProcessedInHelper);
                //*numCharactersProcessed =  *numCharactersProcessed + numProcessedInHelper + 1; //+1 for ":"

                char* dataType = (char*) malloc(strlen(nextSeqElementToProcess) + 1);
                strncpy(dataType, nextSeqElementToProcess, strlen(nextSeqElementToProcess) + 1);
                char* reentrant = NULL;
                strtok_r(dataType, ":", &reentrant);
                int dType = atoi(dataType);
                safe_free(dataType);

                if (values[i] == NULL) {

                    PRT_TYPE* seqType = PrtMkSeqType(PrtMkPrimitiveType(convertKindToType(dType)));
                    values[i] = PrtMkDefaultValue(seqType);

                }

                PrtSeqInsert(values[i], PrtMkIntValue(index), value);
                nextSeqElementToProcess = nextSeqElementToProcess + numProcessedInHelper + 1;
                
            }
            ocall_print("Seq created");
            *numCharactersProcessed =  *numCharactersProcessed + (nextSeqElementToProcess - nextSeqElementToProcessOriginal) + 7; //+7 for "END_SEQ"

        }
    }
    safe_free(str);
    safe_free(strCopy);
    return values;
}
//Responsbility of caller to free return
char* generateCStringFromFormat(char* format_string, char* strings_to_print[], int num_strings) {
    if (num_strings > 5) {
        ocall_print("Too many strings passed to generateCStringFromFormat!");
        return "ERROR!";
    }
    char* returnString = (char*) malloc(1600);

    char* str1 = strings_to_print[0];
    char* str2 = strings_to_print[1];
    char* str3 = strings_to_print[2];
    char* str4 = strings_to_print[3];
    char* str5 = strings_to_print[4];

    snprintf(returnString, 1600, format_string, str1, str2, str3, str4, str5);
    //ocall_print("Return string is");
    //ocall_print(returnString);
    return returnString;

}

int returnTotalSizeofLengthArray(int lengths[], int length){
    int total_size = 0;
    for (int i = 0; i < length; i++) {
        total_size += lengths[i];
    }
    return total_size;
}

//Responsbility of caller to free return
char* concatMutipleStringsWithLength(char* strings_to_concat[], int lengths[], int size_array) {
        //NOTE make changes in app.cpp as well
    int total_size = returnTotalSizeofLengthArray(lengths, size_array);
    ocall_print("Total size of concat is ");
    ocall_print_int(total_size);
    

    char* returnString = (char*) malloc(total_size + 1);
    char* ptr = returnString;
    for (int i = 0; i < size_array; i++) {
        memcpy(ptr, strings_to_concat[i], lengths[i]);
        ptr = ptr + lengths[i];
    }
    returnString[total_size] = '\0';

    ocall_print("Concat return string is");
    ocall_print(returnString);
    return returnString;

}

void parseIPAddressPortString(char* serializedString, string& ipAddress, int& port) {
    char* split = strtok(serializedString, ":");
    ipAddress = string(split);
    split = strtok(NULL, ":");
    port = atoi(split);
}

//Responbility of caller to free return
char* receiveNetworkRequestHelper(char* request, size_t requestSize, bool isEnclaveUntrustedHost) {
    // ocall_print("helllo");
    // ocall_print_int(strlen(request));
    //char requestCopy[250];
    char* requestCopy = (char*) malloc(requestSize);
    // ocall_print("malloc init");
    memcpy(requestCopy, request, requestSize);
    // requestCopy[strlen(request)] = '\0';
    // ocall_print("malloc yeeee");


    #ifdef ENCLAVE_STD_ALT   
    return createStringLiteralMalloced("empty");
    #else
    char* split = strtok(requestCopy, ":");
    if (strcmp(split, "Create") == 0) {
        char* newMachineID;
        char* parentTrustedMachinePublicIDKey;
        char* machineType;
        int numArgs;
        int payloadType;
        char* payload;

        newMachineID = (char* ) malloc(SIZE_OF_RETURN_ID_AFTER_CREATE_REQUEST);

        parentTrustedMachinePublicIDKey = (char*) malloc(SGX_RSA3072_KEY_SIZE);
        memcpy(parentTrustedMachinePublicIDKey, request + strlen(split) + 1, SGX_RSA3072_KEY_SIZE);
        char* nextIndex = requestCopy + strlen(split) + 1 + SGX_RSA3072_KEY_SIZE + 1; //TODO using requestcopy here might be an issue

        // char* newTokenizerString = (char*) malloc(strlen(nextIndex) + 1);
        // strncpy(newTokenizerString, nextIndex, strlen(nextIndex) + 1);
        char* newTokenizerString = (char*) malloc(SIZE_OF_MAX_EVENT_PAYLOAD);
        memcpy(newTokenizerString, nextIndex, SIZE_OF_MAX_EVENT_PAYLOAD);
        ocall_print("New tokenizer is ");
        ocall_print(newTokenizerString);

        split = strtok(newTokenizerString, ":");
        machineType = split;
        split = strtok(NULL, ":");
        numArgs = atoi(split);
        payloadType = -1;
        payload = (char*) malloc(10);
        payload[0] = '\0';
        int payloadSize;
        if (numArgs > 0) {
            split = strtok(NULL, ":");
            payloadType = atoi(split);
            split = strtok(NULL, ":");
            payloadSize = atoi(split);
            safe_free(payload);
            payload = split + strlen(split) + 1;

        } else {
            safe_free(payload);
        }        

        if (isEnclaveUntrustedHost) {
        
            sgx_enclave_id_t new_enclave_eid = 0;
            string token = "enclave" + to_string((int)CURRENT_ENCLAVE_EID_NUM) + ".token";
            CURRENT_ENCLAVE_EID_NUM += 1;


            if (initialize_enclave(&new_enclave_eid, token, "enclave.signed.so") < 0) { //TODO figure out how to initialize all enclaves. Maybe network_ra should do that as a setup step?
                ocall_print("Fail to initialize enclave.");
            }    

            int ptr;

            ocall_print("at helper.cpp level");
            printRSAKey(parentTrustedMachinePublicIDKey);
            sgx_status_t status = enclave_createMachineAPI(new_enclave_eid, &ptr, new_enclave_eid, machineType, parentTrustedMachinePublicIDKey, newMachineID, numArgs, payloadType, payload, payloadSize, SIZE_OF_RETURN_ID_AFTER_CREATE_REQUEST, SIZE_OF_MAX_EVENT_PAYLOAD, new_enclave_eid);
            
            safe_free(requestCopy);
            return newMachineID;

        } else {
            if (USMAuthorizedTypes.count(machineType) > 0) {
                char* ret = createUSMMachineAPI(machineType, numArgs, payloadType, payload, payloadSize);
                safe_free(requestCopy);
                return ret;
            } else {
                safe_free(requestCopy);
                return untrusted_enclave1_receiveNetworkRequest(request, requestSize);
            }
        }
    
    }  else if (strcmp(split, "UntrustedCreate") == 0) {

        char* newMachineID = (char* ) malloc(SIZE_OF_RETURN_ID_AFTER_CREATE_REQUEST);
        split = strtok(NULL, ":");
        char* machineType = split;
        split = strtok(NULL, ":");
        int numArgs = atoi(split);
        int payloadType = -1;
        char* payload = (char*) malloc(10);
        payload[0] = '\0';
        int payloadSize;
        if (numArgs > 0) {
            split = strtok(NULL, ":");
            payloadType = atoi(split);
            split = strtok(NULL, ":");
            payloadSize = atoi(split);
            safe_free(payload);
            payload = split + strlen(split) + 1;

        } else {
            safe_free(payload);
        }

        if (isEnclaveUntrustedHost) {

            sgx_enclave_id_t new_enclave_eid = 0;
            string token = "enclave" + to_string((int)CURRENT_ENCLAVE_EID_NUM) + ".token";
            CURRENT_ENCLAVE_EID_NUM += 1;

            if (initialize_enclave(&new_enclave_eid, token, "enclave.signed.so") < 0) { //TODO figure out how to initialize all enclaves. Maybe network_ra should do that as a setup step?
                ocall_print("Fail to initialize enclave.");
            }   

            
            sgx_status_t status = enclave_UntrustedCreateMachineAPI(new_enclave_eid, new_enclave_eid, machineType, 30, newMachineID, numArgs, payloadType, payload, payloadSize, SIZE_OF_RETURN_ID_AFTER_CREATE_REQUEST, SIZE_OF_MAX_MESSAGE, new_enclave_eid);
            
            safe_free(requestCopy);
            return newMachineID;


        } else {
            if (USMAuthorizedTypes.count(machineType) > 0) {
                char* ret = createUSMMachineAPI(machineType, numArgs, payloadType, payload, payloadSize);
                safe_free(requestCopy);
                return ret;
            } else {
                safe_free(requestCopy);
                return untrusted_enclave1_receiveNetworkRequest(request, requestSize);
            }
        }

    
    } else if (strcmp(split, "InitComm") == 0) {

        char* encryptedSessionKey;
        //newSessionKey[0] = '\0';

        char* machineInitializingComm;
        char* machineReceivingComm;

        machineInitializingComm = (char*) malloc(SIZE_OF_RETURN_ID_AFTER_CREATE_REQUEST);
        memcpy(machineInitializingComm, request + strlen(split) + 1, SIZE_OF_RETURN_ID_AFTER_CREATE_REQUEST);
        machineReceivingComm = (char*) malloc(SGX_RSA3072_KEY_SIZE);
        memcpy(machineReceivingComm, request + strlen(split) + 1 + SIZE_OF_RETURN_ID_AFTER_CREATE_REQUEST + 1, SGX_RSA3072_KEY_SIZE);
        encryptedSessionKey = (char* ) malloc(SGX_RSA3072_KEY_SIZE);
        memcpy(encryptedSessionKey, request + strlen(split) + 1 + SIZE_OF_RETURN_ID_AFTER_CREATE_REQUEST + 1 + SGX_RSA3072_KEY_SIZE + 1, SGX_RSA3072_KEY_SIZE);
            
        // machineInitializingComm = (char*) malloc(SIZE_OF_RETURN_ID_AFTER_CREATE_REQUEST);
        // memcpy(machineInitializingComm, request + strlen(split) + 1, SGX_RSA3072_KEY_SIZE + 2);
        // machineReceivingComm = (char*) malloc(SGX_RSA3072_KEY_SIZE);
        // memcpy(machineReceivingComm, request + strlen(split) + 1 + SGX_RSA3072_KEY_SIZE + 1, SGX_RSA3072_KEY_SIZE);
        // encryptedSessionKey = (char* ) malloc(SGX_RSA3072_KEY_SIZE);
        // memcpy(encryptedSessionKey, request + strlen(split) + 1 + SGX_RSA3072_KEY_SIZE + 1 + SGX_RSA3072_KEY_SIZE + 1, SGX_RSA3072_KEY_SIZE);
            
        
        if (isEnclaveUntrustedHost) {

            if (PublicIdentityKeyToEidDictionary.count(string(machineReceivingComm, SGX_RSA3072_KEY_SIZE)) == 0) {
                ocall_print("\n No Enclave Eid Found!\n");
            }
            
            sgx_enclave_id_t enclave_eid = PublicIdentityKeyToEidDictionary[string(machineReceivingComm, SGX_RSA3072_KEY_SIZE)]; //TODO add check here in case its not in dictionary
            char* returnMessage = (char*) malloc(100);
            int ptr;
            //TODO actually make this call a method in untrusted host (enclave_untrusted_host.cpp)
            sgx_status_t status = enclave_initializeCommunicationAPI(enclave_eid, &ptr, machineInitializingComm,machineReceivingComm, encryptedSessionKey, returnMessage, SIZE_OF_RETURN_ID_AFTER_CREATE_REQUEST, SGX_RSA3072_KEY_SIZE);
            if (status != SGX_SUCCESS) {
                printf("Sgx Error Code: %x\n", status);
            }
        
            
            safe_free(requestCopy);
            return returnMessage;

        } else {
            // ocall_print("checking the following");
            // printPayload(machineReceivingComm, SGX_RSA3072_KEY_SIZE);
            if (USMPublicIdentityKeyToMachinePIDDictionary.count(string(machineReceivingComm, SGX_RSA3072_KEY_SIZE)) > 0) {
                // ocall_print("YEEEEEET");
                char* ret = USMinitializeCommunicationAPI(machineInitializingComm, machineReceivingComm, encryptedSessionKey);
                safe_free(requestCopy);
                return ret;
            
            } else {
                safe_free(requestCopy);
                return untrusted_enclave1_receiveNetworkRequest(request, requestSize);
            }
        }

    
    }  else if (strcmp(split, "UntrustedSend") == 0) {
        char* machineSendingMessage;
        char* machineReceivingMessage;
        char* iv;
        char* mac;
        char* encryptedMessage;
        char* temp;

 
        machineSendingMessage = (char*) malloc(SGX_RSA3072_KEY_SIZE);
        memcpy(machineSendingMessage, request + strlen(split) + 1, SGX_RSA3072_KEY_SIZE);
        machineReceivingMessage = (char*) malloc(SGX_RSA3072_KEY_SIZE);
        memcpy(machineReceivingMessage, request + strlen(split) + 1 + SGX_RSA3072_KEY_SIZE + 1, SGX_RSA3072_KEY_SIZE);
        iv = requestCopy + strlen("UntrustedSend") + 1 + SGX_RSA3072_KEY_SIZE + 1 + SGX_RSA3072_KEY_SIZE + 1;
        mac = requestCopy + strlen("UntrustedSend") + 1 + SGX_RSA3072_KEY_SIZE + 1 + SGX_RSA3072_KEY_SIZE + 1 + SIZE_OF_IV + 1;
        encryptedMessage = requestCopy + strlen("UntrustedSend") + 1 + SGX_RSA3072_KEY_SIZE + 1 + SGX_RSA3072_KEY_SIZE + 1 + SIZE_OF_IV + 1 + SIZE_OF_MAC + 1;

        
        ocall_print("encrypted message is helper");
        ocall_print(encryptedMessage);

        if (isEnclaveUntrustedHost) {

            int count;
            int ptr;
            sgx_enclave_id_t enclave_eid;
            count = PublicIdentityKeyToEidDictionary.count(string(machineReceivingMessage, SGX_RSA3072_KEY_SIZE));
            enclave_eid = PublicIdentityKeyToEidDictionary[string(machineReceivingMessage, SGX_RSA3072_KEY_SIZE)];
            char* split = strtok(encryptedMessage, ":");
            int encryptedMessageSize = atoi(split) + strlen(split) + 1;
            printPayload(encryptedMessage, 9);
            encryptedMessage[strlen(split)] = ':'; //undoing effect of strtok
            int RESPONSE_SZ = 100;
            char* responseBuffer = (char*) malloc(RESPONSE_SZ);
            sgx_status_t status = enclave_decryptAndSendMessageAPI(enclave_eid, &ptr, machineSendingMessage,machineReceivingMessage, iv, mac, encryptedMessage, responseBuffer, 0, SGX_RSA3072_KEY_SIZE, encryptedMessageSize, RESPONSE_SZ);
            

            if (count == 0) {
                ocall_print("\n No Enclave Eid Found!");
            }
            
            safe_free(requestCopy);
            temp = responseBuffer;
            return temp;

        } else {
            int count;
           
            count = USMPublicIdentityKeyToMachinePIDDictionary.count(string(machineReceivingMessage, SGX_RSA3072_KEY_SIZE));
            
            if (count > 0) {
                int RESPONSE_SZ = 100;
                char* responseBuffer = (char*) malloc(RESPONSE_SZ);
                char* ret = USMSendMessageAPI(machineSendingMessage, machineReceivingMessage, iv, mac, encryptedMessage, responseBuffer);
                safe_free(requestCopy);
                ret = responseBuffer;
                return ret;
                
            } else {
                safe_free(requestCopy);
                return untrusted_enclave1_receiveNetworkRequest(request, requestSize);
            }
        }

    } else if (strcmp(split, "Send") == 0) {

        char* machineSendingMessage;
        char* machineReceivingMessage;
        char* iv;
        char* mac;
        char* encryptedMessage;
        char* temp;

 
        machineSendingMessage = (char*) malloc(SGX_RSA3072_KEY_SIZE);
        memcpy(machineSendingMessage, request + strlen(split) + 1, SGX_RSA3072_KEY_SIZE);
        machineReceivingMessage = (char*) malloc(SGX_RSA3072_KEY_SIZE);
        memcpy(machineReceivingMessage, request + strlen(split) + 1 + SGX_RSA3072_KEY_SIZE + 1, SGX_RSA3072_KEY_SIZE);
        iv = requestCopy + strlen("Send") + 1 + SGX_RSA3072_KEY_SIZE + 1 + SGX_RSA3072_KEY_SIZE + 1;
        mac = requestCopy + strlen("Send") + 1 + SGX_RSA3072_KEY_SIZE + 1 + SGX_RSA3072_KEY_SIZE + 1 + SIZE_OF_IV + 1;
        encryptedMessage = requestCopy + strlen("Send") + 1 + SGX_RSA3072_KEY_SIZE + 1 + SGX_RSA3072_KEY_SIZE + 1 + SIZE_OF_IV + 1 + SIZE_OF_MAC + 1;

        
        ocall_print("encrypted message is");
        ocall_print(encryptedMessage);

        if (isEnclaveUntrustedHost) {

            int count;
            int ptr;
            sgx_enclave_id_t enclave_eid;
            count = PublicIdentityKeyToEidDictionary.count(string(machineReceivingMessage, SGX_RSA3072_KEY_SIZE));
            enclave_eid = PublicIdentityKeyToEidDictionary[string(machineReceivingMessage, SGX_RSA3072_KEY_SIZE)];
            char* split = strtok(encryptedMessage, ":");
            int encryptedMessageSize = atoi(split) + strlen(split) + 1;
            printPayload(encryptedMessage, 9);
            encryptedMessage[strlen(split)] = ':'; //undoing effect of strtok
            int RESPONSE_SZ = 100;
            char* responseBuffer = (char*) malloc(RESPONSE_SZ);
            sgx_status_t status = enclave_decryptAndSendMessageAPI(enclave_eid, &ptr, machineSendingMessage,machineReceivingMessage, iv, mac, encryptedMessage, responseBuffer, 1, SGX_RSA3072_KEY_SIZE, encryptedMessageSize, RESPONSE_SZ);
            

            if (count == 0) {
                ocall_print("\n No Enclave Eid Found!");
            }
            
            safe_free(requestCopy);
            temp = createStringLiteralMalloced("SecureSendReturn");
            return responseBuffer;

        } else {
            int count;
            count = USMPublicIdentityKeyToMachinePIDDictionary.count(string(machineReceivingMessage, SGX_RSA3072_KEY_SIZE));

            if (count > 0) {
                safe_free(requestCopy);
                //TODO need to implement
                return createStringLiteralMalloced("TODO");
                
            } else {
                safe_free(requestCopy);
                return untrusted_enclave1_receiveNetworkRequest(request, requestSize);
            }
        }


    } else {
        safe_free(requestCopy);
        return createStringLiteralMalloced("Command Not Found");
    }
    #endif
}

PRT_VALUE* sendCreateMachineNetworkRequest(PRT_MACHINEINST* context, PRT_VALUE*** argRefs, char* createTypeCommand, bool isSecureCreate) {
    //If making changes here, make relevant changes in app.cpp
    uint32_t currentMachinePID = context->id->valueUnion.mid->machineId;
    char* requestedNewMachineTypeToCreate = (char*) argRefs[0];

    string ipAddress;
    int port = 0;
    
    //Query the KPS to determine the target IP address of this type of machine
    char* ipAddressOfRequestedMachine = (char*) malloc(IP_ADDRESS_AND_PORT_STRING_SIZE);
    char* ipAddressOfKPSMachine = (char*) malloc(IP_ADDRESS_AND_PORT_STRING_SIZE);
    ocall_get_ip_address_of_kps(ipAddressOfKPSMachine, IP_ADDRESS_AND_PORT_STRING_SIZE);
    #ifdef ENCLAVE_STD_ALT
    ocall_get_generic_port_of_kps(&port);
    #else 
    port = ocall_get_generic_port_of_kps();
    #endif
    

    char* constructString[] = {"KPS", ":", "IPRequestMachineType", ":", requestedNewMachineTypeToCreate};
    int constructStringLengths[] = {strlen("KPS"), 1, strlen("IPRequestMachineType"), 1, strlen(requestedNewMachineTypeToCreate)};
    char* kpsIpRequest = concatMutipleStringsWithLength(constructString, constructStringLengths, 5);
    int requestLength = returnTotalSizeofLengthArray(constructStringLengths, 5) + 1;
    int ret_value; 

    

    #ifdef ENCLAVE_STD_ALT   
    ocall_network_request(&ret_value, kpsIpRequest, ipAddressOfRequestedMachine, requestLength, IP_ADDRESS_AND_PORT_STRING_SIZE, ipAddressOfKPSMachine, strlen(ipAddressOfKPSMachine) + 1, port);
    #else
    ocall_network_request(kpsIpRequest, ipAddressOfRequestedMachine, requestLength, IP_ADDRESS_AND_PORT_STRING_SIZE, ipAddressOfKPSMachine, strlen(ipAddressOfKPSMachine) + 1, port);
    // newMachinePublicIDKey = send_network_request_API(createMachineRequest);
    #endif
    ocall_print("Received IP Address of target machine from KPS:");
    ocall_print(ipAddressOfRequestedMachine);

    parseIPAddressPortString(ipAddressOfRequestedMachine, ipAddress, port);


    ocall_print("Requesting to create this new type of machine");
    ocall_print(requestedNewMachineTypeToCreate);

    char* currentMachineIDPublicKey;

   
    currentMachineIDPublicKey = (char*) malloc(SGX_RSA3072_KEY_SIZE);
    memcpy(currentMachineIDPublicKey, (char*)(get<0>(MachinePIDToIdentityDictionary[currentMachinePID]).c_str()), SGX_RSA3072_KEY_SIZE);
    
    int numArgs = atoi((char*) argRefs[1]);

    PRT_VALUE* payloadPrtValue;
    char* payloadString = NULL;  
    int payloadType;
    int payloadStringSize;

    if (numArgs == 1) {
        payloadPrtValue = *(argRefs[2]);
        payloadType = payloadPrtValue->discriminator;
        payloadStringSize = 0;
        payloadString = (char*) malloc(SIZE_OF_MAX_EVENT_PAYLOAD);
        char* temp = serializePrtValueToString(payloadPrtValue, payloadStringSize);
        memcpy(payloadString, temp, payloadStringSize + 1);
        payloadString[payloadStringSize] = '\0';
        ocall_print("EVENT MESSAGE PAYLOAD IS");
        printPayload(payloadString, payloadStringSize);
        ocall_print("Length is");
        ocall_print_int(payloadStringSize);
        safe_free(temp);        

    }

    char* payloadStringSizeString = (char*) malloc(10);
    itoa(payloadStringSize, payloadStringSizeString, 10);

    char* newMachinePublicIDKey = (char*) malloc(SIZE_OF_RETURN_ID_AFTER_CREATE_REQUEST);
    int requestSize = -1;
    char* createMachineRequest = (char*) malloc(requestSize);
    char* numArgsString = (char*) argRefs[1];
    char* payloadTypeString = (char*) malloc(10);
    itoa(payloadType, payloadTypeString, 10);
         if (isSecureCreate) {
            if (numArgs == 0) {
                char* constructString[] = {createTypeCommand, ":", currentMachineIDPublicKey, ":", requestedNewMachineTypeToCreate, ":0"};
                int constructStringLengths[] = {strlen(createTypeCommand), 1, SGX_RSA3072_KEY_SIZE, 1, strlen(requestedNewMachineTypeToCreate), 2};
                safe_free(createMachineRequest);
                createMachineRequest = concatMutipleStringsWithLength(constructString, constructStringLengths, 6);
                requestLength = returnTotalSizeofLengthArray(constructStringLengths, 6) + 1;

            } else {
                ocall_print("requested new type of machine to create is");
                ocall_print(requestedNewMachineTypeToCreate);
                ocall_print("current RSA key is");
                printRSAKey(currentMachineIDPublicKey);
                
                char* constructString[] = {createTypeCommand, ":", currentMachineIDPublicKey, ":", requestedNewMachineTypeToCreate, ":", numArgsString, ":", payloadTypeString, ":", payloadStringSizeString, ":", payloadString};
                int constructStringLengths[] = {strlen(createTypeCommand), 1, SGX_RSA3072_KEY_SIZE, 1, strlen(requestedNewMachineTypeToCreate), 1, strlen(numArgsString), 1, strlen(payloadTypeString), 1, strlen(payloadStringSizeString), 1, payloadStringSize};
                safe_free(createMachineRequest);
                createMachineRequest = concatMutipleStringsWithLength(constructString, constructStringLengths, 13);
                requestLength = returnTotalSizeofLengthArray(constructStringLengths, 13) + 1;
                safe_free(payloadTypeString);

                ocall_print("KURUT");
                ocall_print(createMachineRequest);
            }
        
        } else {
            if (numArgs == 0) {
                char* constructString[] = {createTypeCommand, ":", requestedNewMachineTypeToCreate, ":0"};
                int constructStringLengths[] = {strlen(createTypeCommand), 1, strlen(requestedNewMachineTypeToCreate), 2};
                safe_free(createMachineRequest);
                createMachineRequest = concatMutipleStringsWithLength(constructString, constructStringLengths, 4);
                requestLength = returnTotalSizeofLengthArray(constructStringLengths, 4) + 1;

                // snprintf(createMachineRequest, requestSize, "%s:%s:0", createTypeCommand, requestedNewMachineTypeToCreate);
            } else {
                char* constructString[] = {createTypeCommand, ":", requestedNewMachineTypeToCreate, ":", numArgsString, ":", payloadTypeString, ":", payloadStringSizeString, ":", payloadString};
                int constructStringLengths[] = {strlen(createTypeCommand), 1, strlen(requestedNewMachineTypeToCreate), 1, strlen(numArgsString), 1, strlen(payloadTypeString), 1, strlen(payloadStringSizeString), 1, payloadStringSize};
                safe_free(createMachineRequest);
                createMachineRequest = concatMutipleStringsWithLength(constructString, constructStringLengths, 11);
                requestLength = returnTotalSizeofLengthArray(constructStringLengths, 11) + 1;

                // snprintf(createMachineRequest, requestSize, "%s:%s:%d:%d:", createTypeCommand, requestedNewMachineTypeToCreate, numArgs, payloadType);
                // memcpy(createMachineRequest + strlen(createMachineRequest), payloadString, payloadStringSize);

            }
            // requestLength = strlen(createMachineRequest) + 1;
        }
    
   
    safe_free(payloadString);
    
    
    char* machineNameWrapper[] = {currentMachineIDPublicKey};
    char* printStr = generateCStringFromFormat("%s machine is sending out the following network request:", machineNameWrapper, 1);
    ocall_print(printStr); //TODO use this method for all future ocall_prints
    safe_free(printStr);
    ocall_print(createMachineRequest);

    int response_size = SIZE_OF_RETURN_ID_AFTER_CREATE_REQUEST;//SIZE_OF_RETURN_ID_AFTER_CREATE_REQUEST;// + 1 + SIZE_OF_CAPABILITYKEY;

    #ifdef ENCLAVE_STD_ALT   
    ocall_network_request(&ret_value, createMachineRequest, newMachinePublicIDKey, requestLength, response_size, (char*)ipAddress.c_str(), strlen((char*)ipAddress.c_str()) + 1, port);
    #else
    ocall_network_request(createMachineRequest, newMachinePublicIDKey, requestLength, response_size, (char*)ipAddress.c_str(), strlen((char*)ipAddress.c_str()) + 1, port);
    // newMachinePublicIDKey = send_network_request_API(createMachineRequest);
    #endif
    safe_free(createMachineRequest);
    
    char* machineNameWrapper2[] = {currentMachineIDPublicKey};
    printStr = generateCStringFromFormat("%s machine has created a new machine with Identity Public Key as:", machineNameWrapper2, 1);
    ocall_print(printStr); //TODO use this method for all future ocall_prints
    safe_free(printStr);

    // if (NETWORK_DEBUG) {
    //     ocall_print(newMachinePublicIDKey);
    // } else {
        printPayload(newMachinePublicIDKey, response_size);
    // }
    
    #ifdef ENCLAVE_STD_ALT

    string capabilityKeyPayloadString;

    if (isSecureCreate) {

        //Now, need to retrieve capabilityKey for this newMachinePublicIDKey and store (thisMachineID, newMachinePublicIDKey) -> capabilityKey
        string request;
        // if (NETWORK_DEBUG) {
        //     request = "GetKey:" + string(currentMachineIDPublicKey) + ":" + string(newMachinePublicIDKey);//TODO unhardcode current Machine name
        // } else {
            request = "GetKey:" + string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE) + ":" + string(newMachinePublicIDKey, SGX_RSA3072_KEY_SIZE);//TODO unhardcode current Machine name
        // }
        //TODO replace above line with snprintf as did with createMachineRequest, and do this everywhere in code
        char* getChildMachineIDRequest = (char*) request.c_str(); 
        char* capabilityKeyPayload = retrieveCapabilityKeyForChildFromKPS(currentMachineIDPublicKey, newMachinePublicIDKey, requestedNewMachineTypeToCreate);//(char*) malloc(SIZE_OF_CAPABILITYKEY); 
        //ocall_network_request(&ret_value, getChildMachineIDRequest, capabilityKeyPayload, SIZE_OF_CAPABILITYKEY);        
        

        char* machineNameWrapper3[] = {currentMachineIDPublicKey};
        printStr = generateCStringFromFormat("%s machine has received capability key for secure child:", machineNameWrapper3, 1);
        ocall_print(printStr);
        safe_free(printStr);
        char* publicCapabilityKey = retrievePublicCapabilityKey(capabilityKeyPayload);
        char* privateCapabilityKey = retrievePrivateCapabilityKey(capabilityKeyPayload);
        // printRSAKey(publicCapabilityKey);
        // printRSAKey(privateCapabilityKey);

        capabilityKeyPayloadString =  string(capabilityKeyPayload, SIZE_OF_CAPABILITYKEY);
        ocall_print("Saving capability as");
        ocall_print("currentMachinePID");
        ocall_print_int(currentMachinePID);
        printRSAKey(newMachinePublicIDKey);
        ocall_print("capabilityKey");
        ocall_print(capabilityKeyPayload);
        safe_free(publicCapabilityKey);
        safe_free(privateCapabilityKey);
        safe_free(capabilityKeyPayload);
    }

    #endif
    safe_free(currentMachineIDPublicKey);

    //Return the newMachinePublicIDKey and it is the responsibility of the P Secure machine to save it and use it to send messages later
    // if (NETWORK_DEBUG) {
    //     sprintf_s(str, SIZE_OF_PRT_STRING_SERIALIZED, newMachinePublicIDKey);
    // } else {
    // }

    char* portString = (char*) malloc(IP_ADDRESS_AND_PORT_STRING_SIZE);
    itoa(port, portString, 10);

    char* concatStringss[] = {(char*)ipAddress.c_str(), ":", portString};
    int concatLengthss[] = {strlen((char*)ipAddress.c_str()), 1, strlen(portString)};
    char* ipAddressAndPortSerialized = concatMutipleStringsWithLength(concatStringss, concatLengthss, 3);
    int ipAddressAndPortSerializedSize = returnTotalSizeofLengthArray(concatLengthss, 3);
    

	
    #ifdef ENCLAVE_STD_ALT
    if (isSecureCreate) {
        // string capabilityKeyPayloadString = PMachineToChildCapabilityKey[make_tuple(currentMachinePID, string(newMachinePublicIDKey, SGX_RSA3072_KEY_SIZE))];
        PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_SECURE_MACHINE_HANDLE));
        char* finalString;
        int finalStringSize;
        char* newMachinePublicSigningKey = newMachinePublicIDKey + SGX_RSA3072_KEY_SIZE + 1;
        char* concatStrings[] = {newMachinePublicIDKey, ":", newMachinePublicSigningKey, ":", (char*)capabilityKeyPayloadString.c_str(), ":", ipAddressAndPortSerialized};
        int concatLengths[] = {SGX_RSA3072_KEY_SIZE, 1, sizeof(sgx_rsa3072_public_key_t), 1, SIZE_OF_CAPABILITYKEY, 1, ipAddressAndPortSerializedSize};
        finalString = concatMutipleStringsWithLength(concatStrings, concatLengths, 7);
        finalStringSize = returnTotalSizeofLengthArray(concatLengths, 7) + 1;

        memcpy(str, finalString, finalStringSize);
        safe_free(finalString);
        safe_free(newMachinePublicIDKey);
        return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_secure_machine_handle);

    } else {
        PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_MACHINE_HANDLE));
        char* finalString;
        int finalStringSize;
        char* concatStrings[] = {newMachinePublicIDKey, ":", ipAddressAndPortSerialized};
        int concatLengths[] = {SIZE_OF_KEY_IDENTITY_IN_HANDLE, 1, ipAddressAndPortSerializedSize};
        finalString = concatMutipleStringsWithLength(concatStrings, concatLengths, 3);
        finalStringSize = returnTotalSizeofLengthArray(concatLengths, 3) + 1;

        if (finalStringSize >= SIZE_OF_MACHINE_HANDLE) {
            ocall_print("ERROR: Overwriting machine handle");
        }

        memcpy(str, finalString, finalStringSize);
        safe_free(newMachinePublicIDKey);
        safe_free(finalString);
        // ocall_print("check check");
        // printPayload((char*)str, SIZE_OF_MACHINE_HANDLE);
        return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_machine_handle);
    }
    
    #else 

    PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_MACHINE_HANDLE));
    char* finalString;
    int finalStringSize;
    char* concatStrings[] = {newMachinePublicIDKey, ":", ipAddressAndPortSerialized};
    int concatLengths[] = {SIZE_OF_KEY_IDENTITY_IN_HANDLE, 1, ipAddressAndPortSerializedSize};
    finalString = concatMutipleStringsWithLength(concatStrings, concatLengths, 3);
    finalStringSize = returnTotalSizeofLengthArray(concatLengths, 3) + 1;

    if (finalStringSize >= SIZE_OF_MACHINE_HANDLE) {
        ocall_print("ERROR: Overwriting machine handle");
    }

    memcpy(str, finalString, finalStringSize);
    safe_free(newMachinePublicIDKey);
    safe_free(finalString);
    // ocall_print("check check");
    // printPayload((char*)str, SIZE_OF_MACHINE_HANDLE);
    return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_machine_handle);
    #endif

}

//Responsibilty of caller to free return
char* generateIV() {
    char* ivKey = (char*) malloc(SIZE_OF_IV);
    #ifdef ENCLAVE_STD_ALT
    sgx_read_rand((unsigned char*)ivKey, SIZE_OF_IV);
    #endif
    // sessionKey[98] = '!';
    // sessionKey[99] = '\0';
    // for (int i = 0; i < 99; i ++) {
    //     if (sessionKey[i] == '\0') {
    //         sessionKey[i] ='0';
    //     }
    // }
    return ivKey;
}

void generateSessionKey(string& newSessionKey) {
    //TODO Make this generate a random key
    if (NETWORK_DEBUG) {
        uint32_t val; 
        #ifdef ENCLAVE_STD_ALT
        sgx_read_rand((unsigned char *) &val, 4);
        #endif
        newSessionKey = string("GenSessionKeyREA", SIZE_OF_REAL_SESSION_KEY);
    } else {
        char* sessionKey = (char*) malloc(SIZE_OF_REAL_SESSION_KEY);
        #ifdef ENCLAVE_STD_ALT
        sgx_read_rand((unsigned char*)sessionKey, SIZE_OF_REAL_SESSION_KEY);
        #else
        sgx_status_t status = enclave_sgx_read_rand_ecall(global_app_eid, sessionKey, SIZE_OF_REAL_SESSION_KEY);
        // ocall_print("Generating random session key!");
        #endif
        newSessionKey = string(sessionKey, SIZE_OF_REAL_SESSION_KEY);
    }
    
} 

char* encryptMessageExternalPublicKey(char* message, size_t message_length_with_null_byte, void* other_party_public_key_raw, int& output_encrypted_message_length, void* other_party_public_key) {
    #ifdef ENCLAVE_STD_ALT
    // ocall_print("Pub key received is");
    // ocall_print((char*) other_party_public_key_raw);

    size_t encrypted_data_length;
    char* encrypted_data = (char*) malloc(SGX_RSA3072_KEY_SIZE); //TODO note if message is bigger than this size, then we can run into issues
    

    ocall_print("encrypting with this key");
    printPayload((char*) other_party_public_key_raw, SGX_RSA3072_KEY_SIZE);
    ocall_print("message is");
    printPayload(message, message_length_with_null_byte);

    sgx_status_t status = SGX_ERROR_AE_SESSION_INVALID;
    void* public_key_raw = NULL;
    ocall_print("pk is");
    printPayload((char*)other_party_public_key, sizeof(sgx_rsa3072_public_key_t));
    sgx_rsa3072_public_key_t *public_key = (sgx_rsa3072_public_key_t*) other_party_public_key;
    // status = sgx_create_rsa_pub1_key(
    //                    SGX_RSA3072_KEY_SIZE,
    //                    SGX_RSA3072_PUB_EXP_SIZE,
    //                    (const unsigned char*)public_key->mod,
    //                    (const unsigned char*)public_key->exp,
    //                    &public_key_raw);
    // if (status == SGX_SUCCESS) {
    //     ocall_print("Yeet");
    //     printPayload((char*) public_key_raw, SGX_RSA3072_KEY_SIZE);
    // } else {
    //     ocall_print("neep");
    // }

    const int n_byte_size = SGX_RSA3072_KEY_SIZE;



    int e_byte_size = SGX_RSA3072_PUB_EXP_SIZE;
    unsigned char *p_n = (unsigned char *)malloc(n_byte_size);
    unsigned char *p_d = (unsigned char *)malloc(SGX_RSA3072_PRI_EXP_SIZE);
    // unsigned char p_e[] = {0x01, 0x00, 0x01, 0x00}; //65537
    unsigned char *p_p = (unsigned char *)malloc(n_byte_size);
    unsigned char *p_q = (unsigned char *)malloc(n_byte_size);
    unsigned char *p_dmp1 = (unsigned char *)malloc(n_byte_size);
    unsigned char *p_dmq1 = (unsigned char *)malloc(n_byte_size);
    unsigned char *p_iqmp = (unsigned char *)malloc(n_byte_size);
    

    status = SGX_SUCCESS;
    status = sgx_create_rsa_key_pair(
        n_byte_size,
        e_byte_size,
        p_n,
        p_d,
        public_key->exp,
        p_p,
        p_q,
        p_dmp1,
        p_dmq1,
        p_iqmp
    );
    if (status != SGX_SUCCESS) {
        ocall_print("Rsa Key Pair creation error!");
    } else {
        ocall_print("RSA Generated Succesfully!");
    }

    // memcpy(private_key->mod, p_n, n_byte_size);
    // memcpy(private_key->d, p_d, n_byte_size);
	// memcpy(private_key->e, p_e, e_byte_size);

	// memcpy(public_key->mod, p_n, n_byte_size);
	// memcpy(public_key->exp, p_e, e_byte_size);

    status = sgx_create_rsa_pub1_key(
                       SGX_RSA3072_KEY_SIZE,
                       SGX_RSA3072_PUB_EXP_SIZE,
                       (const unsigned char*)public_key->mod,
                       (const unsigned char*)public_key->exp,
                       &public_key_raw);
    if (status == SGX_SUCCESS) {
        ocall_print("Yeet");
        printPayload((char*) public_key_raw, SGX_RSA3072_KEY_SIZE);
    } else {
        ocall_print("neep");
    }




    status = sgx_rsa_pub_encrypt_sha256(public_key_raw, NULL, &encrypted_data_length, (unsigned char*) message, message_length_with_null_byte);

    if (status != SGX_SUCCESS) {
        ocall_print("Error in encrypting using public key!");
        // ocall_print((char*)**other_party_public_key_raw);
        if (status == SGX_ERROR_UNEXPECTED) {
            ocall_print("unexpected error :(");
        } else if (status == SGX_ERROR_INVALID_PARAMETER) {
            ocall_print("invalid parameters");
        }
    } else {
        ocall_print("Encrypted data length will be");
        ocall_print_int(encrypted_data_length);
    }

    // encrypted_data_length = 384*2;

    status = sgx_rsa_pub_encrypt_sha256(public_key_raw, (unsigned char*) encrypted_data, &encrypted_data_length, (unsigned char*) message, message_length_with_null_byte);

    if (status != SGX_SUCCESS) {
        ocall_print("Error in encrypting using public key!");
        // ocall_print((char*)**other_party_public_key_raw);
        if (status == SGX_ERROR_UNEXPECTED) {
            ocall_print("unexpected error :(");
        } else if (status == SGX_ERROR_INVALID_PARAMETER) {
            ocall_print("invalid parameters");
        }
    } else {
        ocall_print("Able to encrypt using public key!");
    }
    // ocall_print_int(strlen(message) + 1);
    // ocall_print_int(encrypted_data_length);
    // encrypted_data[encrypted_data_length] = '\0';
    output_encrypted_message_length = encrypted_data_length;
    return encrypted_data;
    #endif
}

char* decryptMessageInteralPrivateKey(char* encryptedData, size_t encryptedDataSize, void* private_key) {
    #ifdef ENCLAVE_STD_ALT
    size_t decrypted_data_length;
    char* decrypted_data = (char*) malloc(MAX_NETWORK_MESSAGE); //TODO note if message is bigger than this size, then we can run into issues

    sgx_status_t status = sgx_rsa_priv_decrypt_sha256(private_key, NULL, &decrypted_data_length, (unsigned char*) encryptedData, encryptedDataSize);

    status = sgx_rsa_priv_decrypt_sha256(private_key, (unsigned char*)decrypted_data, &decrypted_data_length, (unsigned char*) encryptedData, encryptedDataSize);

    if (status != SGX_SUCCESS) {
        ocall_print("Error in decrypting using private key!");
        // ocall_print((char*)**other_party_public_key_raw);
    } else {
        ocall_print("Able to decrytp using private key!");
    }
    // ocall_print_int(strlen(message) + 1);
    // ocall_print_int(encrypted_data_length);
    //decrypted_data[decrypted_data_length] = '\0';
    // ocall_print("Decrypted data is");
    // ocall_print(decrypted_data);
    return decrypted_data;
    #endif
}

void sendSendNetworkRequest(PRT_MACHINEINST* context, PRT_VALUE*** argRefs, char* sendTypeCommand, bool isSecureSend, bool isEnclave) {
    //TODO if making changes in this protocol, make changes in app.cpp
    uint32_t currentMachinePID = context->id->valueUnion.mid->machineId;

    ocall_print("Entered Secure Send");

    string ipAddress;
    int port = 0;

    char* currentMachineIDPublicKey;
    currentMachineIDPublicKey = (char*) malloc(SGX_RSA3072_KEY_SIZE);
    memcpy(currentMachineIDPublicKey, (char*)(get<0>(MachinePIDToIdentityDictionary[currentMachinePID]).c_str()), SGX_RSA3072_KEY_SIZE);

    ocall_print("Inside machine");
    printRSAKey(currentMachineIDPublicKey);
    // PRT_MACHINEINST* mch = PrtGetMachine((PRT_PROCESS*)program, context->id);
    // ocall_print(program->machines[context->id->valueUnion.mid->machineId]->name); //This gives incorrect machine name

    PRT_VALUE** P_ToMachine_Payload = argRefs[0];
    PRT_UINT64 sendingToMachinePublicIDPValue = (*P_ToMachine_Payload)->valueUnion.frgn->value;
    char* sendingToMachinePublicID = (char*) sendingToMachinePublicIDPValue;

    ocall_print("Parsed IP address/Port Info from handle as");
    if (isSecureSend) {
        char* ipAddressAndPortFromSecureHandle = sendingToMachinePublicID + SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1 + SIZE_OF_CAPABILITYKEY + 1;
        ocall_print(ipAddressAndPortFromSecureHandle);
        parseIPAddressPortString(ipAddressAndPortFromSecureHandle, ipAddress, port);
    } else {
        char* ipAddressAndPortFromSecureHandle = sendingToMachinePublicID + SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1;
        ocall_print(ipAddressAndPortFromSecureHandle);
        parseIPAddressPortString(ipAddressAndPortFromSecureHandle, ipAddress, port);
    }

    
    PublicIdentityKeyToPublicSigningKey[string(sendingToMachinePublicID, SGX_RSA3072_KEY_SIZE)] = string(sendingToMachinePublicID + SGX_RSA3072_KEY_SIZE + 1, sizeof(sgx_rsa3072_public_key_t));

    // ocall_print("saving following signing key:");
    // printPayload(sendingToMachinePublicID + SGX_RSA3072_KEY_SIZE + 1, sizeof(sgx_rsa3072_public_key_t));
    // ocall_print("for public identity");
    // printPayload(sendingToMachinePublicID, SGX_RSA3072_KEY_SIZE);

    ocall_print("Need to send to machine (received via P argument)");
    printRSAKey(sendingToMachinePublicID);
    

    // if (isSecureSend) {
        //Check if we don't have a pre-existing session key with the other machine, if so 
        //we need to intialize communications and establish a session key
       
        if (PublicIdentityKeyToChildSessionKey.count(make_tuple(string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE), string(sendingToMachinePublicID, SGX_RSA3072_KEY_SIZE))) == 0) {
                string newSessionKey;
                generateSessionKey(newSessionKey);

                printSessionKey((char*)newSessionKey.c_str());

                int encryptedMessageSize;
                char* encryptedSessionKeyMessage = (char*) malloc(SGX_RSA3072_KEY_SIZE);
                #ifdef ENCLAVE_STD_ALT
                safe_free(encryptedSessionKeyMessage);
                encryptedSessionKeyMessage = encryptMessageExternalPublicKey((char*)newSessionKey.c_str(), SIZE_OF_REAL_SESSION_KEY, sendingToMachinePublicID, encryptedMessageSize, sendingToMachinePublicID + SGX_RSA3072_KEY_SIZE + 1);
                #else
                sgx_status_t sgx_st = enclave_encryptMessageExternalPublicKeyEcall(global_app_eid ,(char*)newSessionKey.c_str(), SIZE_OF_REAL_SESSION_KEY, sendingToMachinePublicID, encryptedSessionKeyMessage, sendingToMachinePublicID + SGX_RSA3072_KEY_SIZE + 1, SGX_RSA3072_KEY_SIZE, sizeof(sgx_rsa3072_public_key_t));
                #endif
                // char* encryptedSessionKeyMessage = encryptMessageExternalPublicKey((char*)newSessionKey.c_str(), SIZE_OF_REAL_SESSION_KEY, currentMachineIDPublicKey, encryptedMessageSize);
                ocall_print("SS:Encrypted Message size is");
                ocall_print_int(encryptedMessageSize);
                printPayload(encryptedSessionKeyMessage, SGX_RSA3072_KEY_SIZE);

                // char* receivingMachinePrivateID = (char*)get<1>(MachinePIDToIdentityDictionary[PublicIdentityKeyToMachinePIDDictionary[string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE)]]).c_str();
                // char* decryptedMessage = decryptMessageInteralPrivateKey(encryptedSessionKeyMessage, SGX_RSA3072_KEY_SIZE, receivingMachinePrivateID);
                // ocall_print("Decrypted message is");
                // printSessionKey(decryptedMessage);

                char* concatStrings[] = {"InitComm:", currentMachineIDPublicKey, ":", (char*)PublicIdentityKeyToPublicSigningKey[string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE)].c_str(), ":", sendingToMachinePublicID, ":", encryptedSessionKeyMessage};
                int concatLenghts[] = {9, SGX_RSA3072_KEY_SIZE, 1, sizeof(sgx_rsa3072_public_key_t), 1, SGX_RSA3072_KEY_SIZE, 1, SGX_RSA3072_KEY_SIZE};
                char* initComRequest = concatMutipleStringsWithLength(concatStrings, concatLenghts, 8);
                int requestSize = returnTotalSizeofLengthArray(concatLenghts, 8) + 1;

                // char* concatStrings[] = {"InitComm:", currentMachineIDPublicKey, ";", sendingToMachinePublicID, ":", encryptedSessionKeyMessage};
                // int concatLenghts[] = {9, SGX_RSA3072_KEY_SIZE, 1, SGX_RSA3072_KEY_SIZE, 1, SGX_RSA3072_KEY_SIZE};
                // char* initComRequest = concatMutipleStringsWithLength(concatStrings, concatLenghts, 6);
                // int requestSize = returnTotalSizeofLengthArray(concatLenghts, 6) + 1;
                
                char* machineNameWrapper[] = {currentMachineIDPublicKey};
                char* printStr = generateCStringFromFormat("%s machine is sending out following network request:", machineNameWrapper, 1);
                ocall_print(printStr);
                safe_free(printStr);
                ocall_print(initComRequest);
                char* returnMessage = (char*) malloc(100);
                int ret_value;

                #ifdef ENCLAVE_STD_ALT
                ocall_network_request(&ret_value, initComRequest, returnMessage, requestSize, SIZE_OF_SESSION_KEY, (char*)ipAddress.c_str(), strlen((char*)ipAddress.c_str()) + 1, port);
                #else
                // ocall_print("Init comm untrusted! 1");
                ocall_network_request(initComRequest, returnMessage, requestSize, SIZE_OF_SESSION_KEY, (char*)ipAddress.c_str(), strlen((char*)ipAddress.c_str()) + 1, port); 
                #endif
                safe_free(initComRequest);
                char* machineNameWrapper2[] = {currentMachineIDPublicKey};
                printStr = generateCStringFromFormat("%s machine has received session key request message:", machineNameWrapper2, 1);
                ocall_print(printStr);
                safe_free(printStr);       
                ocall_print(returnMessage);
                PublicIdentityKeyToChildSessionKey[make_tuple(string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE), string(sendingToMachinePublicID, SGX_RSA3072_KEY_SIZE))] = newSessionKey;
                ChildSessionKeyToNonce[make_tuple(string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE), newSessionKey)] = 0;
                // safe_free(newSessionKey);
                safe_free(returnMessage);
            

        }  else {
            ocall_print("Already have session key!");
            printPayload((char*)PublicIdentityKeyToChildSessionKey[make_tuple(string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE), string(sendingToMachinePublicID, SGX_RSA3072_KEY_SIZE))].c_str(), 16);
        }      
    // }
    PRT_VALUE** P_Event_Payload = argRefs[1];
    char* event = (char*) malloc(SIZE_OF_MAX_EVENT_NAME);
    itoa((*P_Event_Payload)->valueUnion.ev , event, 10);

    char* eventName = program->events[PrtPrimGetEvent((*P_Event_Payload))]->name;
    ocall_print("About to send following event");
    ocall_print(eventName);

    const int size_of_max_num_args = 10; //TODO if modififying this, modify it in app.cpp

    PRT_VALUE** P_NumEventArgs_Payload = argRefs[2];
    int numArgs = (*P_NumEventArgs_Payload)->valueUnion.nt;
    char* numArgsPayload = (char*) malloc(size_of_max_num_args);
    itoa(numArgs, numArgsPayload, 10);

    char* eventMessagePayload = (char*) malloc(SIZE_OF_MAX_EVENT_PAYLOAD);


    PRT_VALUE** P_EventMessage_Payload;
    int eventPayloadType;
    char* eventPayloadTypeString = NULL;
    int eventMessagePayloadSize;
    char* eventMessagePayloadSizeString = NULL;

    if (numArgs > 0) {
        P_EventMessage_Payload = argRefs[3];
        eventPayloadType = (*P_EventMessage_Payload)->discriminator;
        eventPayloadTypeString = (char*) malloc(10);
        itoa(eventPayloadType, eventPayloadTypeString, 10);
        eventMessagePayloadSize = 0;
        char* temp = serializePrtValueToString(*P_EventMessage_Payload, eventMessagePayloadSize);
        memcpy(eventMessagePayload, temp, eventMessagePayloadSize + 1);
        eventMessagePayload[eventMessagePayloadSize] = '\0';
        ocall_print("EVENT MESSAGE PAYLOAD IS");
        printPayload(eventMessagePayload, eventMessagePayloadSize);
        ocall_print("Length is");
        ocall_print_int(eventMessagePayloadSize);
        // memcpy(eventMessagePayload, temp, strlen(temp) + 1); //TODO shividentity
        safe_free(temp);

        eventMessagePayloadSizeString = (char*) malloc(10);
        itoa(eventMessagePayloadSize, eventMessagePayloadSizeString, 10);

    }

    int requestSize = -1;// 4 + 1 + SIZE_OF_IDENTITY_STRING + 1 + SIZE_OF_IDENTITY_STRING + 1 + SIZE_OF_MAX_MESSAGE + 1 + size_of_max_num_args + 1 + SIZE_OF_MAX_EVENT_PAYLOAD + 1;
    char* sendRequest;

        char* colon = ":";
        char* zero = "0";
        if (isSecureSend) {
            char* iv = generateIV();
            char* mac = "1234567891234567";
            char* encryptedMessage;
            char* messageToEncrypt;
            int messageToEncryptSize;
            int encryptedMessageSize;
            char* encryptedMessageSizeString;

            if (numArgs > 0) {
                char* encryptStrings[] = {event, colon, numArgsPayload, colon, eventPayloadTypeString, colon, eventMessagePayloadSizeString, colon, eventMessagePayload};
                int encryptLenghts[] = {strlen(event), strlen(colon), strlen(numArgsPayload), strlen(colon), strlen(eventPayloadTypeString), strlen(colon), strlen(eventMessagePayloadSizeString), strlen(colon), eventMessagePayloadSize};
                messageToEncrypt = concatMutipleStringsWithLength(encryptStrings, encryptLenghts, 9);
                messageToEncryptSize = returnTotalSizeofLengthArray(encryptLenghts, 9);              
            } else  {
                char* encryptStrings[] = {event, colon, zero};
                int encryptLenghts[] = {strlen(event), strlen(colon), strlen(zero)};
                messageToEncrypt = concatMutipleStringsWithLength(encryptStrings, encryptLenghts, 3);
                messageToEncryptSize = returnTotalSizeofLengthArray(encryptLenghts, 3);
            }

            if (!NETWORK_DEBUG) {
                //add encryption logic here
                string sessionKey = PublicIdentityKeyToChildSessionKey[make_tuple(string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE), string(sendingToMachinePublicID, SGX_RSA3072_KEY_SIZE))];
                int nonce = ChildSessionKeyToNonce[make_tuple(string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE), sessionKey)];
                ChildSessionKeyToNonce[make_tuple(string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE), sessionKey)] = ChildSessionKeyToNonce[make_tuple(string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE), sessionKey)] + 1;
                char* nonceStr = (char*) malloc(10);
                itoa(nonce, nonceStr, 10);

                char* concatStrings[] = {sendingToMachinePublicID, colon, nonceStr, colon, messageToEncrypt};
                int concatLengths[] = {SGX_RSA3072_KEY_SIZE, strlen(colon), strlen(nonceStr), strlen(colon), messageToEncryptSize};
                char* M = concatMutipleStringsWithLength(concatStrings, concatLengths, 5);
                int MSize = returnTotalSizeofLengthArray(concatLengths, 5);

                safe_free(nonceStr);

                string sendingToMachineCapabilityKeyPayload = string(sendingToMachinePublicID + SGX_RSA3072_KEY_SIZE + 1 + sizeof(sgx_rsa3072_public_key_t) + 1, SIZE_OF_CAPABILITYKEY);//PMachineToChildCapabilityKey[make_tuple(currentMachinePID, string(sendingToMachinePublicID, SGX_RSA3072_KEY_SIZE))];
                char* privateCapabilityKeySendingToMachine = retrievePrivateCapabilityKey((char*)sendingToMachineCapabilityKeyPayload.c_str());
                ocall_print("Retrieving capability as");
                ocall_print("currentMachinePID");
                ocall_print_int(currentMachinePID);
                printRSAKey(sendingToMachinePublicID);
                // ocall_print("capabilityKey");
                printPublicCapabilityKey((char*)sendingToMachineCapabilityKeyPayload.c_str());
                printPrivateCapabilityKey((char*)sendingToMachineCapabilityKeyPayload.c_str());
                sgx_rsa3072_signature_t* signatureM;
                #ifdef ENCLAVE_STD_ALT
                signatureM = signStringMessage(M, MSize, (sgx_rsa3072_key_t*) privateCapabilityKeySendingToMachine);
                #endif
                int sizeOfSignature = SGX_RSA3072_KEY_SIZE;
                char* sigString[] = {M, colon, (char*)signatureM};
                int sigLengths[] = {MSize, strlen(colon), sizeOfSignature};
                char* trustedPayload = concatMutipleStringsWithLength(sigString, sigLengths, 3);
                int trustedPayloadLength = returnTotalSizeofLengthArray(sigLengths, 3);
                ocall_print("Printing Trusted Payload after public key");
                ocall_print(trustedPayload + SGX_RSA3072_KEY_SIZE);
                ocall_print("Printing Generated Signature");
                printRSAKey((char*)signatureM);
                ocall_print("Signature is over message");
                printRSAKey(M);
                ocall_print_int(MSize);
                ocall_print("Key needed to verify signature is");
                ocall_print((char*)sendingToMachineCapabilityKeyPayload.c_str());
                ocall_print("actual key is");
                printRSAKey(retrievePublicCapabilityKey((char*)sendingToMachineCapabilityKeyPayload.c_str()));

                // char* trustedPayload = M;
                // int trustedPayloadLength = MSize;

                ocall_print("Printing Generated Signature again");
                printRSAKey(trustedPayload + MSize + strlen(colon));
                // ocall_print("Printing length of encrypted message");
                // ocall_print(trustedPayloadLength);


                sgx_aes_ctr_128bit_key_t g_region_key;
                sgx_aes_gcm_128bit_tag_t g_mac;
                memcpy(g_region_key, (char*)sessionKey.c_str(), 16);

                encryptedMessageSize = trustedPayloadLength;
                encryptedMessage = (char*) malloc(encryptedMessageSize);
                #ifdef ENCLAVE_STD_ALT
                sgx_status_t status = sgx_rijndael128GCM_encrypt(&g_region_key, (const uint8_t*) trustedPayload, trustedPayloadLength, (uint8_t*)encryptedMessage, (const uint8_t*) iv, SIZE_OF_IV, NULL, 0, &g_mac);
                #endif
                // ocall_print("Encrypted Message is");
                // ocall_print(encryptedMessage);
                mac = (char*) malloc(SIZE_OF_MAC);
                memcpy(mac, (char*)g_mac, SIZE_OF_MAC);

                safe_free(M);
                safe_free(trustedPayload);
                
            } else {
                encryptedMessage = messageToEncrypt;
                encryptedMessageSize = messageToEncryptSize;
            }
            encryptedMessageSizeString = (char*) malloc(10);
            itoa(encryptedMessageSize, encryptedMessageSizeString, 10);

            char* concatStrings[] = {sendTypeCommand, colon, currentMachineIDPublicKey, colon, sendingToMachinePublicID, colon, iv, colon, mac, colon, encryptedMessageSizeString, colon, encryptedMessage};
            int concatLenghts[] = {strlen(sendTypeCommand), strlen(colon), SGX_RSA3072_KEY_SIZE, strlen(colon), SGX_RSA3072_KEY_SIZE, strlen(colon), SIZE_OF_IV, strlen(colon), SIZE_OF_MAC, strlen(colon), strlen(encryptedMessageSizeString), strlen(colon), encryptedMessageSize};
            sendRequest = concatMutipleStringsWithLength(concatStrings, concatLenghts, 13);
            requestSize = returnTotalSizeofLengthArray(concatLenghts, 13) + 1;

            
            safe_free(encryptedMessage);
            safe_free(encryptedMessageSizeString);

            if (!NETWORK_DEBUG) {
                safe_free(mac);    
            }

        } else { //!SecureSend 
            char* iv = generateIV();
            char* mac = "1234567891234567";
            char* encryptedMessage;
            char* messageToEncrypt;
            int messageToEncryptSize;
            int encryptedMessageSize;
            char* encryptedMessageSizeString;

            if (numArgs > 0) {
                char* encryptStrings[] = {event, colon, numArgsPayload, colon, eventPayloadTypeString, colon, eventMessagePayloadSizeString, colon, eventMessagePayload};
                int encryptLenghts[] = {strlen(event), strlen(colon), strlen(numArgsPayload), strlen(colon), strlen(eventPayloadTypeString), strlen(colon), strlen(eventMessagePayloadSizeString), strlen(colon), eventMessagePayloadSize};
                messageToEncrypt = concatMutipleStringsWithLength(encryptStrings, encryptLenghts, 9);
                messageToEncryptSize = returnTotalSizeofLengthArray(encryptLenghts, 9);              
            } else  {
                char* encryptStrings[] = {event, colon, zero};
                int encryptLenghts[] = {strlen(event), strlen(colon), strlen(zero)};
                messageToEncrypt = concatMutipleStringsWithLength(encryptStrings, encryptLenghts, 3);
                messageToEncryptSize = returnTotalSizeofLengthArray(encryptLenghts, 3);
            }

            if (!NETWORK_DEBUG) {
                //add encryption logic here
                string sessionKey = PublicIdentityKeyToChildSessionKey[make_tuple(string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE), string(sendingToMachinePublicID, SGX_RSA3072_KEY_SIZE))];
                int nonce = ChildSessionKeyToNonce[make_tuple(string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE), sessionKey)];
                ChildSessionKeyToNonce[make_tuple(string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE), sessionKey)] = ChildSessionKeyToNonce[make_tuple(string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE), sessionKey)] + 1;
                char* nonceStr = (char*) malloc(10);
                itoa(nonce, nonceStr, 10);

                char* concatStrings[] = {sendingToMachinePublicID, colon, nonceStr, colon, messageToEncrypt};
                int concatLengths[] = {SGX_RSA3072_KEY_SIZE, strlen(colon), strlen(nonceStr), strlen(colon), messageToEncryptSize};
                char* M = concatMutipleStringsWithLength(concatStrings, concatLengths, 5);
                int MSize = returnTotalSizeofLengthArray(concatLengths, 5);

                safe_free(nonceStr);

                char* currentMachineIDPrivateKey;
                #ifndef ENCLAVE_STD_ALT
                currentMachineIDPrivateKey = (char*)get<1>(MachinePIDToIdentityDictionary[USMPublicIdentityKeyToMachinePIDDictionary[string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE)]]).c_str();
                #else 
                currentMachineIDPrivateKey = (char*)get<1>(MachinePIDToIdentityDictionary[PublicIdentityKeyToMachinePIDDictionary[string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE)]]).c_str();
                #endif
                sgx_rsa3072_key_t* private_identity_key = (sgx_rsa3072_key_t*)PrivateIdentityKeyToPrivateSigningKey[string(currentMachineIDPrivateKey, SGX_RSA3072_KEY_SIZE)].c_str();//(sgx_rsa3072_key_t*) malloc(sizeof(sgx_rsa3072_key_t));
                // ocall_print("TEMPER: Signing the following key pair");
                // ocall_print("public signing");
                // printPayload((char*)PublicIdentityKeyToPublicSigningKey[string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE)].c_str(), sizeof(sgx_rsa3072_public_key_t));
                // ocall_print("public identity");
                // printPayload(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE);
                // printPayload();
                sgx_rsa3072_signature_t* signatureM;
                #ifdef ENCLAVE_STD_ALT
                signatureM = signStringMessage(M, MSize, (sgx_rsa3072_key_t*) private_identity_key);//(sgx_rsa3072_signature_t*) malloc(sizeof(sgx_rsa3072_signature_t));//
                #else
                signatureM = (sgx_rsa3072_signature_t*) malloc(sizeof(sgx_rsa3072_signature_t));
                sgx_status_t status = enclave_signStringMessageEcall(global_app_eid, M, MSize, (char*) private_identity_key, (char*)signatureM, sizeof(sgx_rsa3072_key_t), sizeof(sgx_rsa3072_signature_t));
                #endif
                int sizeOfSignature = SGX_RSA3072_KEY_SIZE;
                char* sigString[] = {M, colon, (char*)signatureM};
                int sigLengths[] = {MSize, strlen(colon), sizeOfSignature};
                char* trustedPayload = concatMutipleStringsWithLength(sigString, sigLengths, 3);
                int trustedPayloadLength = returnTotalSizeofLengthArray(sigLengths, 3);
                ocall_print("Printing Untrusted Payload after public key");
                ocall_print(trustedPayload + SGX_RSA3072_KEY_SIZE);
                // ocall_print("Printing Generated Signature");
                // printRSAKey((char*)signatureM);
                // ocall_print("Signature is over message");
                // printRSAKey(M);
                // ocall_print_int(MSize);
                // ocall_print("Key needed to verify signature is");
                // ocall_print((char*)sendingToMachineCapabilityKeyPayload.c_str());
                // ocall_print("actual key is");
                // printRSAKey(retrievePublicCapabilityKey((char*)sendingToMachineCapabilityKeyPayload.c_str()));

                sgx_aes_ctr_128bit_key_t g_region_key;
                sgx_aes_gcm_128bit_tag_t g_mac;
                memcpy(g_region_key, (char*)sessionKey.c_str(), 16);

                encryptedMessageSize = trustedPayloadLength;
                encryptedMessage = (char*) malloc(encryptedMessageSize);
                #ifdef ENCLAVE_STD_ALT
                sgx_status_t status = sgx_rijndael128GCM_encrypt(&g_region_key, (const uint8_t*) trustedPayload, trustedPayloadLength, (uint8_t*)encryptedMessage, (const uint8_t*) iv, SIZE_OF_IV, NULL, 0, &g_mac);
                #else 
                sample_rijndael128GCM_encrypt(&g_region_key, (const uint8_t*) trustedPayload, trustedPayloadLength, (uint8_t*)encryptedMessage, (const uint8_t*) iv, SIZE_OF_IV, NULL, 0, &g_mac);
                #endif
                ocall_print("Encrypted Message -DEBUG- is");
                printPayload(encryptedMessage, encryptedMessageSize);
                mac = (char*) malloc(SIZE_OF_MAC);
                memcpy(mac, (char*)g_mac, SIZE_OF_MAC);

                ocall_print("mac -DEBUG- is");
                printPayload(mac, SIZE_OF_MAC);

                safe_free(M);
                safe_free(trustedPayload);
                
            } else {
                encryptedMessage = messageToEncrypt;
                encryptedMessageSize = messageToEncryptSize;
            }
            encryptedMessageSizeString = (char*) malloc(10);
            itoa(encryptedMessageSize, encryptedMessageSizeString, 10);

            char* concatStrings[] = {sendTypeCommand, colon, currentMachineIDPublicKey, colon, sendingToMachinePublicID, colon, iv, colon, mac, colon, encryptedMessageSizeString, colon, encryptedMessage};
            int concatLenghts[] = {strlen(sendTypeCommand), strlen(colon), SGX_RSA3072_KEY_SIZE, strlen(colon), SGX_RSA3072_KEY_SIZE, strlen(colon), SIZE_OF_IV, strlen(colon), SIZE_OF_MAC, strlen(colon), strlen(encryptedMessageSizeString), strlen(colon), encryptedMessageSize};
            sendRequest = concatMutipleStringsWithLength(concatStrings, concatLenghts, 13);
            requestSize = returnTotalSizeofLengthArray(concatLenghts, 13) + 1;

            ocall_print("encryptedMessageSize is");
            ocall_print_int(encryptedMessageSize);
            ocall_print("helper encryptedMessageSizeString is");
            ocall_print(encryptedMessageSizeString);

            
            safe_free(encryptedMessage);
            safe_free(encryptedMessageSizeString);

            if (!NETWORK_DEBUG) {
                safe_free(mac);    
            }

                
            // requestSize = 130 + 1 + SIZE_OF_IDENTITY_STRING + 1 + SIZE_OF_MAX_MESSAGE + 1 + SIZE_OF_MAX_EVENT_PAYLOAD + 1;
            // sendRequest = (char*) malloc(requestSize);
            // if (numArgs > 0) {
            //     char* colon = ":";
            //     char* concatStrings[] = {sendTypeCommand, colon, sendingToMachinePublicID, colon, event, colon, numArgsPayload, colon, eventPayloadTypeString, colon, eventMessagePayloadSizeString, colon, eventMessagePayload};
            //     int concatLenghts[] = {strlen(sendTypeCommand), strlen(colon), SGX_RSA3072_KEY_SIZE, strlen(colon), strlen(event), strlen(colon), strlen(numArgsPayload), strlen(colon), strlen(eventPayloadTypeString), strlen(colon), strlen(eventMessagePayloadSizeString), strlen(colon), eventMessagePayloadSize};
            //     sendRequest = concatMutipleStringsWithLength(concatStrings, concatLenghts, 13);
            //     requestSize = returnTotalSizeofLengthArray(concatLenghts, 13) + 1;
            //     // snprintf(sendRequest, requestSize, "%s:%s:%s:%d:%d:%s", sendTypeCommand, sendingToMachinePublicID, event, numArgs, eventPayloadType, eventMessagePayload);
            // } else {
            //     char* colon = ":";
            //     char* zero = "0";
            //     char* concatStrings[] = {sendTypeCommand, colon, sendingToMachinePublicID, colon, event, colon, zero};
            //     int concatLenghts[] = {strlen(sendTypeCommand), strlen(colon), SGX_RSA3072_KEY_SIZE, strlen(colon), strlen(event), strlen(colon), strlen(zero)};
            //     sendRequest = concatMutipleStringsWithLength(concatStrings, concatLenghts, 7);
            //     requestSize = returnTotalSizeofLengthArray(concatLenghts, 7) + 1;
            //     // snprintf(sendRequest, requestSize, "%s:%s:%s:0", sendTypeCommand, sendingToMachinePublicID, event);
            // }
            
        }

    safe_free(eventPayloadTypeString);
    // safe_free(eventMessageSizeStr);
    
    
    char* machineNameWrapper[] = {currentMachineIDPublicKey};
    char* printStr = generateCStringFromFormat("%s machine is sending out following network request:", machineNameWrapper, 1);
    ocall_print(printStr);
    safe_free(printStr);      
    // ocall_print(sendRequest);
    // ocall_print_int(strlen(sendRequest) + 1);
    // ocall_print("KUUUURUT");
    char* sendReturn = (char*) malloc(100);
    int ret_value;

    

    ocall_print("-DEBUG- ENTIRE NETWORK REQUEST IS");
    printPayload(sendRequest, requestSize);

    ocall_print("Sending to ip address");
    ocall_print((char*)ipAddress.c_str());
    ocall_print("Sending to port");
    ocall_print_int(port);

    #ifdef ENCLAVE_STD_ALT
        sgx_status_t temppp = ocall_network_request(&ret_value, sendRequest, sendReturn, requestSize, 100, (char*)ipAddress.c_str(), strlen((char*)ipAddress.c_str()) + 1, port);
    #else
        ocall_network_request(sendRequest, sendReturn, requestSize, 100, (char*)ipAddress.c_str(), strlen((char*)ipAddress.c_str()) + 1, port); 
    #endif
    safe_free(sendRequest);
    ocall_print("Send/UntrustedSend Network call returned:");
    ocall_print(sendReturn);

    if (!NETWORK_DEBUG) {
        char* iv = (char*) malloc(SIZE_OF_IV);
        char* mac = (char*) malloc(SIZE_OF_MAC);
        memcpy(iv, sendReturn, SIZE_OF_IV);
        memcpy(mac, sendReturn + SIZE_OF_IV + 1, SIZE_OF_MAC);
        char* enc = sendReturn + SIZE_OF_IV + 1 + SIZE_OF_MAC + 1;
        char* encryptedStringSizeString = strtok(enc, ":");
        char* encryptedMessage = (char*)malloc(atoi(encryptedStringSizeString));
        memcpy(encryptedMessage, enc + strlen(encryptedStringSizeString) + 1, atoi(encryptedStringSizeString));

        string sessionKey = PublicIdentityKeyToChildSessionKey[make_tuple(string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE), string(sendingToMachinePublicID, SGX_RSA3072_KEY_SIZE))];
        sgx_aes_ctr_128bit_key_t g_region_key;
        sgx_aes_gcm_128bit_tag_t g_mac;
        memcpy(g_region_key, (char*)sessionKey.c_str(), 16);
        memcpy(g_mac, mac, SIZE_OF_MAC);

        char* decryptedMessage = (char*) malloc(atoi(encryptedStringSizeString));
        #ifdef ENCLAVE_STD_ALT
        sgx_status_t status = sgx_rijndael128GCM_decrypt(&g_region_key, (const uint8_t*) encryptedMessage, atoi(encryptedStringSizeString), (uint8_t*)decryptedMessage, (const uint8_t*) iv, SIZE_OF_IV, NULL, 0, &g_mac);
        #else 
        sample_rijndael128GCM_encrypt(&g_region_key, (const uint8_t*) encryptedMessage, atoi(encryptedStringSizeString), (uint8_t*)decryptedMessage, (const uint8_t*) iv, SIZE_OF_IV, NULL, 0, &g_mac);
        #endif

        ocall_print(decryptedMessage);
        decryptedMessage[atoi(encryptedStringSizeString)] = '\0';

        char* split = strtok(decryptedMessage, ":");
        char* msg = split;
        split = strtok(NULL, ":");
        char* nonceString = split;

        int expected_nonce = ChildSessionKeyToNonce[make_tuple(string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE), sessionKey)];
               

        if (atoi(nonceString) == expected_nonce) {
            ChildSessionKeyToNonce[make_tuple(string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE), sessionKey)] = ChildSessionKeyToNonce[make_tuple(string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE), sessionKey)] + 1;
        } else {
            ocall_print("Error: Replay attack! Nonce reused. Message not sent successfully!");
            ocall_print("expecting");
            ocall_print_int(ChildSessionKeyToNonce[make_tuple(string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE), sessionKey)]);
            ocall_print("received");
            ocall_print_int(atoi(nonceString));
        }



    }

    char* machineNameWrapper2[] = {currentMachineIDPublicKey};
    printStr = generateCStringFromFormat("%s machine has succesfully sent message", machineNameWrapper2, 1);
    ocall_print(printStr);
    safe_free(printStr);

    safe_free(event);
    safe_free(eventMessagePayload);
    safe_free(numArgsPayload);

    safe_free(currentMachineIDPublicKey);

}

void decryptAndSendInternalMessageHelper(char* requestingMachineIDKey, char* receivingMachineIDKey, char* iv, char* mac, char* encryptedMessage, char* response, bool isSecureSend) {
    ocall_print("entered decrypt fn");
    // ocall_print_int(MAX_ENCRYPTED_MESSAGE);
    printPayload(encryptedMessage, 9);
    char* split = strtok(encryptedMessage, ":");
    char* encryptedMessageSize = split;
    int encryptedMessageSizeInt = atoi(encryptedMessageSize);
    int encryptedMessageSizeIntString = strlen(encryptedMessageSize);
    char* eventNum;
    int numArgs;
    int payloadType;
    char* payload;
    int payloadSize;
    char* next = NULL;

    char* decryptedMessage = NULL;

    if (!NETWORK_DEBUG) {
        int machinePID;
        string sendingToMachineCapabilityKeyPayload;
        char* publicCapabilityKeySendingToMachine = NULL;
        #ifdef ENCLAVE_STD_ALT
        machinePID = PublicIdentityKeyToMachinePIDDictionary[string(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE)];
        sendingToMachineCapabilityKeyPayload = MachinePIDtoCapabilityKeyDictionary[machinePID];
        publicCapabilityKeySendingToMachine = retrievePublicCapabilityKey((char*)sendingToMachineCapabilityKeyPayload.c_str());
        #else
        machinePID = USMPublicIdentityKeyToMachinePIDDictionary[string(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE)];
        #endif
        
        string sessionKey = PublicIdentityKeyToChildSessionKey[make_tuple(string(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE), string(requestingMachineIDKey, SGX_RSA3072_KEY_SIZE))];

        sgx_aes_ctr_128bit_key_t g_region_key;
        sgx_aes_gcm_128bit_tag_t g_mac;
        memcpy(g_region_key, (char*)sessionKey.c_str(), 16);
        memcpy(g_mac, mac, SIZE_OF_MAC);

        char* actualEncryptedMessage = encryptedMessage + strlen(encryptedMessageSize) + 1;
        decryptedMessage = (char*) malloc(atoi(encryptedMessageSize));
        #ifdef ENCLAVE_STD_ALT
        sgx_status_t status = sgx_rijndael128GCM_decrypt(&g_region_key, (const uint8_t*) actualEncryptedMessage, atoi(encryptedMessageSize), (uint8_t*)decryptedMessage, (const uint8_t*) iv, SIZE_OF_IV, NULL, 0, &g_mac);
        #else
        sample_rijndael128GCM_encrypt(&g_region_key, (const uint8_t*) actualEncryptedMessage, encryptedMessageSizeInt, (uint8_t*)decryptedMessage, (const uint8_t*) iv, SIZE_OF_IV, NULL, 0, &g_mac);
        #endif
        char* checkMyPublicIdentity = (char*) malloc(SGX_RSA3072_KEY_SIZE);
        memcpy(checkMyPublicIdentity, decryptedMessage, SGX_RSA3072_KEY_SIZE);
        if (string(checkMyPublicIdentity, SGX_RSA3072_KEY_SIZE) != string(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE)) {
            ocall_print("ERROR: Checking Public Identity Key inside Message FAILED in Secure Send");
            ocall_print("Expected:");
            printPayload(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE);
            ocall_print("Received:");
            printPayload(checkMyPublicIdentity, SGX_RSA3072_KEY_SIZE);
            return;
        }

        sgx_rsa3072_signature_t* decryptedSignature = (sgx_rsa3072_signature_t*) malloc(SGX_RSA3072_KEY_SIZE);
        // char* message = (char*) malloc(atoi(encryptedMessageSize) - SGX_RSA3072_KEY_SIZE - 1); 
        // memcpy(message, decryptedMessage + SGX_RSA3072_KEY_SIZE + 1, atoi(encryptedMessageSize) - SGX_RSA3072_KEY_SIZE - 1);
        char* messageSignedOver = (char*) malloc(atoi(encryptedMessageSize) - SGX_RSA3072_KEY_SIZE - 1);
        memcpy(messageSignedOver, decryptedMessage, atoi(encryptedMessageSize) - SGX_RSA3072_KEY_SIZE - 1);
        memcpy(decryptedSignature, decryptedMessage + atoi(encryptedMessageSize) - SGX_RSA3072_KEY_SIZE, SGX_RSA3072_KEY_SIZE);
        // ocall_print("Lenght of encrypted message is ");
        // ocall_print(encryptedMessageSize);
        if (isSecureSend) {
            ocall_print("Received Signature:");
            printRSAKey((char*)decryptedSignature);
            ocall_print("Signature is over message");
            printRSAKey(messageSignedOver);
            ocall_print_int(atoi(encryptedMessageSize) - SGX_RSA3072_KEY_SIZE - 1);
            ocall_print("Key needed to verify signature is");
            ocall_print((char*)sendingToMachineCapabilityKeyPayload.c_str());
            ocall_print("actual key is");
            printPublicCapabilityKey(publicCapabilityKeySendingToMachine);
            // printPrivateCapabilityKey(retrievePrivateCapabilityKey((char*)sendingToMachineCapabilityKeyPayload.c_str()));
            #ifdef ENCLAVE_STD_ALT

            if (verifySignature(messageSignedOver, atoi(encryptedMessageSize) - SGX_RSA3072_KEY_SIZE - 1, decryptedSignature, (sgx_rsa3072_public_key_t*)publicCapabilityKeySendingToMachine)) {
                ocall_print("Secure Send Verifying Signature works!!!!");
            } else {
                ocall_print("Error: Secure Send Signature Verification Failed!");
                return;
            }

            #endif

        } else {
            // ocall_print("Received Signature:");
            // printRSAKey((char*)decryptedSignature);
            // ocall_print("Signature is over message");
            // printRSAKey(messageSignedOver);
            // ocall_print_int(atoi(encryptedMessageSize) - SGX_RSA3072_KEY_SIZE - 1);
            // ocall_print("Key needed to verify signature is");
            // ocall_print((char*)sendingToMachineCapabilityKeyPayload.c_str());
            // ocall_print("actual key is");
            // printPublicCapabilityKey(publicCapabilityKeySendingToMachine);
            // printPrivateCapabilityKey(retrievePrivateCapabilityKey((char*)sendingToMachineCapabilityKeyPayload.c_str()));
            if (PublicIdentityKeyToPublicSigningKey.count(string(requestingMachineIDKey, SGX_RSA3072_KEY_SIZE)) == 0) {
                ocall_print("ERROR: Cannot find signing key!");
                // ocall_print("cannot find init comm between");
                // printPayload(requestingMachineIDKey, SGX_RSA3072_KEY_SIZE);
                // printPayload(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE);
            }
            sgx_rsa3072_public_key_t* publicSigningKeyRequestingMachine = (sgx_rsa3072_public_key_t*) PublicIdentityKeyToPublicSigningKey[string(requestingMachineIDKey, SGX_RSA3072_KEY_SIZE)].c_str();
            // ocall_print("TEMPER:verifying signature using this public signing key");
            // printPayload((char*)publicSigningKeyRequestingMachine, sizeof(sgx_rsa3072_public_key_t));
            // ocall_print("public identity key");
            // printPayload(requestingMachineIDKey, SGX_RSA3072_KEY_SIZE);

            #ifndef ENCLAVE_STD_ALT
            int success;
            // ocall_print("OUTSIDE:");
            // ocall_print("message is");
            // printPayload(messageSignedOver, atoi(encryptedMessageSize) - SGX_RSA3072_KEY_SIZE - 1);
            // ocall_print_int(atoi(encryptedMessageSize) - SGX_RSA3072_KEY_SIZE - 1);
            // ocall_print("signature is");
            // printPayload((char*)decryptedSignature, SGX_RSA3072_KEY_SIZE);
            // ocall_print("signing key is");
            // printPayload((char*)publicSigningKeyRequestingMachine, sizeof(sgx_rsa3072_public_key_t));

            sgx_status_t status = enclave_verifySignatureEcall(global_app_eid , &success, messageSignedOver, atoi(encryptedMessageSize) - SGX_RSA3072_KEY_SIZE - 1, (char*)decryptedSignature, (char*)publicSigningKeyRequestingMachine, SGX_RSA3072_KEY_SIZE, (uint32_t) sizeof(sgx_rsa3072_public_key_t));
            if (status != SGX_SUCCESS) {
                ocall_print("sgx call failed!");
            }
            if (success == 1) {
                ocall_print("Untrusted Send Verifying Signature works!!!!");
            } else {
                ocall_print("Error: Untrusted Send Signature Verification Failed!");
                return;
            }

            #else 

            if (verifySignature(messageSignedOver, atoi(encryptedMessageSize) - SGX_RSA3072_KEY_SIZE - 1, decryptedSignature, (sgx_rsa3072_public_key_t*)publicSigningKeyRequestingMachine)) {
                ocall_print("Untrusted Send Verifying Signature works!!!!");
            } else {
                ocall_print("Error: Untrusted Send Enclave Signature Verification Failed!");
                return;
            }

            #endif

        }
        
        

        safe_free(checkMyPublicIdentity);
        char* nonce = strtok(decryptedMessage + SGX_RSA3072_KEY_SIZE + 1, ":");
        if (atoi(nonce) == ChildSessionKeyToNonce[make_tuple(string(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE), sessionKey)]) {
            ChildSessionKeyToNonce[make_tuple(string(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE), sessionKey)] = ChildSessionKeyToNonce[make_tuple(string(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE), sessionKey)] + 1;
        } else {
            ocall_print("Error: Replay attack! Nonce reused");
            ocall_print("expecting");
            ocall_print_int(ChildSessionKeyToNonce[make_tuple(string(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE), sessionKey)]);
            ocall_print("received");
            ocall_print_int(atoi(nonce));
        }
        char* message = (char*) malloc(atoi(encryptedMessageSize) - strlen(nonce) - 1); 
        memcpy(message, decryptedMessage + SGX_RSA3072_KEY_SIZE + 1 + strlen(nonce) + 1, atoi(encryptedMessageSize) - strlen(nonce) - 1);
        next = message;

    }

    split = strtok(next, ":");
    eventNum = split;
    split = strtok(NULL, ":");
    ocall_print("num args is");
    ocall_print(split);
    if (split[0] == '0') {
        numArgs = 0;
    } else {
        numArgs = atoi(split);
    }
    
    payloadType = -1;
    // ocall_print("MAC IS");
    // ocall_print(mac);
    payload = (char*) malloc(10);
    payloadSize;
    payload[0] = '\0';
    if (numArgs > 0) {
        split = strtok(NULL, ":");
        payloadType = atoi(split);
        split = strtok(NULL, ":");
        payloadSize = atoi(split);
        safe_free(payload);
        payload = split + strlen(split) + 1;

    } else {
        safe_free(payload);
    }

    #ifndef ENCLAVE_STD_ALT

    PRT_MACHINEID receivingMachinePID;
    char* temp = (char*) malloc(10);
    snprintf(temp, 5, "%d\n", USMPublicIdentityKeyToMachinePIDDictionary[string(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE)]);
    safe_free(temp);
    receivingMachinePID.machineId = USMPublicIdentityKeyToMachinePIDDictionary[string(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE)];

    handle_incoming_event(atoi(eventNum), receivingMachinePID, numArgs, payloadType, payload, payloadSize, isSecureSend); //TODO shividentity

    #else

    PRT_MACHINEID receivingMachinePID;
    ocall_print("SecureChildMachine has a PID of:");
    char* temp = (char*) malloc(10);
   
    if (PublicIdentityKeyToMachinePIDDictionary.count(string(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE)) == 0) {
        ocall_print("Key not found");
    }
    snprintf(temp, 5, "%d", PublicIdentityKeyToMachinePIDDictionary[string(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE)]);
    ocall_print(temp);
    safe_free(temp);
    receivingMachinePID.machineId = PublicIdentityKeyToMachinePIDDictionary[string(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE)];
    
    handle_incoming_event(atoi(eventNum), receivingMachinePID, numArgs, payloadType, payload, payloadSize, isSecureSend); //TODO update to untrusted send api

    // sendMessageAPI(requestingMachineIDKey, receivingMachineIDKey, eventNum, numArgs, payloadType, payload, payloadSize);
    #endif
    safe_free(decryptedMessage);


    if (!NETWORK_DEBUG) {
        //Return Success Messag with encryption
        string sessionKey = PublicIdentityKeyToChildSessionKey[make_tuple(string(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE), string(requestingMachineIDKey, SGX_RSA3072_KEY_SIZE))];
        int nonce = ChildSessionKeyToNonce[make_tuple(string(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE), sessionKey)];
        ChildSessionKeyToNonce[make_tuple(string(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE), sessionKey)] = ChildSessionKeyToNonce[make_tuple(string(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE), sessionKey)] + 1;
        char* nonceStr = (char*) malloc(10);
        itoa(nonce, nonceStr, 10);

        char* colon = ":";

        char* baseMessage = "Success";

        int encryptedMessageLength = strlen(baseMessage) + 1 + strlen(nonceStr);
        char* encryptedMessageLengthString = (char*) malloc(10);

        itoa(encryptedMessageLength, encryptedMessageLengthString, 10);

        char* iv = generateIV();
        char* mac = "1234567891234567";

        char* concatStrings[] = {baseMessage, colon, nonceStr};
        int concatLenghts[] = {strlen(baseMessage), strlen(colon), strlen(nonceStr)};
        char* toBeEncryptedMessage = concatMutipleStringsWithLength(concatStrings, concatLenghts, 3);
        int encryptedMessageSize = returnTotalSizeofLengthArray(concatLenghts, 3);

        sgx_aes_ctr_128bit_key_t g_region_key;
        sgx_aes_gcm_128bit_tag_t g_mac;
        memcpy(g_region_key, (char*)sessionKey.c_str(), 16);

        char* encryptedMessage = (char*) malloc(encryptedMessageSize);
        #ifdef ENCLAVE_STD_ALT
        sgx_status_t status = sgx_rijndael128GCM_encrypt(&g_region_key, (const uint8_t*) toBeEncryptedMessage, encryptedMessageSize, (uint8_t*)encryptedMessage, (const uint8_t*) iv, SIZE_OF_IV, NULL, 0, &g_mac);
        #else 
        sample_rijndael128GCM_encrypt(&g_region_key, (const uint8_t*) toBeEncryptedMessage, encryptedMessageSize, (uint8_t*)encryptedMessage, (const uint8_t*) iv, SIZE_OF_IV, NULL, 0, &g_mac);
        #endif
        // ocall_print("Encrypted Message is");
        // ocall_print(encryptedMessage);
        mac = (char*) malloc(SIZE_OF_MAC);
        memcpy(mac, (char*)g_mac, SIZE_OF_MAC);

        char* concatStrings2[] = {iv, colon, mac, colon, encryptedMessageLengthString, colon, encryptedMessage};
        int concatLenghts2[] = {SIZE_OF_IV, strlen(colon), SIZE_OF_MAC, strlen(colon), strlen(encryptedMessageLengthString), strlen(colon), encryptedMessageSize};
        char* returnString = concatMutipleStringsWithLength(concatStrings2, concatLenghts2, 7);
        int requestSize = returnTotalSizeofLengthArray(concatLenghts2, 7) + 1;
        memcpy(response, returnString, requestSize);

        safe_free(encryptedMessage);
        safe_free(returnString);


        // string sessionKey = PublicIdentityKeyToChildSessionKey[make_tuple(string(receivingMachineIDKey, SGX_RSA3072_KEY_SIZE), string(requestingMachineIDKey, SGX_RSA3072_KEY_SIZE))];

        // sgx_aes_ctr_128bit_key_t g_region_key;
        // sgx_aes_gcm_128bit_tag_t g_mac;
        // memcpy(g_region_key, (char*)sessionKey.c_str(), 16);
        // memcpy(g_mac, mac, SIZE_OF_MAC);


    }



}

int getNextPID() {
    return ((PRT_PROCESS_PRIV*)process)->numMachines + 1;
}

void PrintTuple(PRT_VALUE* tuple){
    ocall_print("Printing Tuple:");
    PRT_TUPVALUE* tupPtr = tuple->valueUnion.tuple;
    ocall_print("Tuple size:");
    ocall_print_int(tupPtr->size);
    for (int i = 0; i < tupPtr->size; i++) {
        PRT_VALUE* currValue = tupPtr->values[i];
        int currValueType = tupPtr->values[i]->discriminator;
        if (currValueType == PRT_VALUE_KIND_INT) {
            ocall_print("Int Value:");
            ocall_print_int(currValue->valueUnion.nt);
        } else if (currValueType == PRT_VALUE_KIND_FOREIGN) {
            ocall_print("String Value:");
            ocall_print( (char*)currValue->valueUnion.frgn->value);
        } else if (currValueType == PRT_VALUE_KIND_BOOL) {
            ocall_print("Bool Value:");
            ocall_print_int((int)currValue->valueUnion.bl);
        }
    }

}

int handle_incoming_event(PRT_UINT32 eventIdentifier, PRT_MACHINEID receivingMachinePID, int numArgs, int payloadType, char* payload, int payloadSize, bool isSecureSend) {
    ocall_print("About to enqueue event:");
    PRT_VALUE* event = PrtMkEventValue(eventIdentifier);
    char* eventName = program->events[PrtPrimGetEvent(event)]->name;
    ocall_print(eventName);
    if (isSecureSend) {
        if (program->events[PrtPrimGetEvent(event)]->isTrustedEvent == 0) {
            ocall_print("ERROR: UntrustedEvent was received through a secure send");
            return -1;
        }
    } else {
        if (program->events[PrtPrimGetEvent(event)]->isTrustedEvent == 1) {
            ocall_print("ERROR: TrustedEvent was received through a untrusted send");
            return -1;
        }
    }
    
    PRT_MACHINEINST* machine = PrtGetMachine(process, PrtMkMachineValue(receivingMachinePID));
    if (numArgs == 0) {
        PrtSend(NULL, machine, event, 0);
    } else {
        char* payloadConcat = (char*) malloc(SIZE_OF_MAX_MESSAGE);
        itoa(payloadType, payloadConcat, 10);
        strncat(payloadConcat, ":", SIZE_OF_MAX_MESSAGE + 1);
        int sizeSoFar = strlen(payloadConcat);
        memcpy(payloadConcat + sizeSoFar, payload, payloadSize);
        payloadConcat[sizeSoFar + payloadSize] = '\0';
        // strncat(payloadConcat, payload, SIZE_OF_MAX_MESSAGE + 1);
        int numCharactersProcessed;
        //print out what is being passed to the below method
        // ocall_print("payload key is ");
        // printRSAKey(payload);
        ocall_print("Passing In String To Deserialize:");
        ocall_print(payloadConcat);
        PRT_VALUE** prtPayload =  deserializeStringToPrtValue(numArgs, payloadConcat, payloadSize, &numCharactersProcessed);
        safe_free(payloadConcat);
        if (payloadType == PRT_VALUE_KIND_TUPLE) {
            PrintTuple(*prtPayload);
        } else if (payloadType == PRT_VALUE_KIND_MAP) {
            PrtPrintValue(event);
            PrtPrintValue(*prtPayload);
        }
        PrtSend(NULL, machine, event, numArgs, prtPayload);
    }
    return 0;
}

int createMachine(char* machineType, int numArgs, int payloadType, char* payload, int payloadSize) {
    PRT_VALUE* prtPayload;
    if (numArgs > 0) {
        ocall_print("Serialized the following payload");
        char* payloadConcat = (char*) malloc(SIZE_OF_MAX_MESSAGE);
        itoa(payloadType, payloadConcat, 10);
        strncat(payloadConcat, ":", SIZE_OF_MAX_MESSAGE + 1);
        int sizeSoFar = strlen(payloadConcat);
        memcpy(payloadConcat + sizeSoFar, payload, payloadSize);
        payloadConcat[sizeSoFar + payloadSize] = '\0';
        ocall_print(payloadConcat);
        int numCharactersProcessed;
        prtPayload = *(deserializeStringToPrtValue(numArgs, payloadConcat, payloadSize, &numCharactersProcessed));
        safe_free(payloadConcat);
    } else {
        prtPayload = PrtMkNullValue();
    }
    PRT_UINT32 newMachinePID;
	PRT_BOOLEAN foundMachine = PrtLookupMachineByName(machineType, &newMachinePID);
    // ocall_print_int(newMachinePID);
	PrtAssert(foundMachine, "No machine found!");
	PRT_MACHINEINST* pongMachine = PrtMkMachine(process, newMachinePID, 1, &prtPayload);
    return pongMachine->id->valueUnion.mid->machineId;
}

int machineTypeIsSecure(char* machineType) {
    PRT_UINT32 interfaceName;  
	PrtLookupMachineByName(machineType, &interfaceName);
    PRT_UINT32 instanceOf = program->interfaceDefMap[interfaceName];
    PRT_MACHINEDECL* curMachineDecl = program->machines[instanceOf];
    return curMachineDecl->isSecure;
}

//responsibility of caller to free string
string createString(char* str) {
    char* strCopy = (char*) malloc(strlen(str) + 1); //TODO shivfree
    memcpy(strCopy, str, strlen(str) + 1);
    return string(strCopy);
}

extern "C" PRT_VALUE* P_Hash_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE** P_VAR_payload = argRefs[0];
    PRT_UINT64 val = (*P_VAR_payload)->valueUnion.frgn->value;

    PRT_VALUE** P_VAR_payload2 = argRefs[1];
    PRT_UINT64 val2 = (*P_VAR_payload2)->valueUnion.frgn->value;

    strncat((char*) val, (char*) val2, SGX_RSA3072_KEY_SIZE + 1); //TODO shividentity
    strncat((char*) val, "hash", strlen("hash") + 1);
    // memcpy((char*)val, "HashedOutput", strlen("HashedOutput") + 1);

    PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED));
    memcpy(str, (char*)val, SIZE_OF_PRT_STRING_SERIALIZED);
	// sprintf_s(str, SIZE_OF_PRT_STRING_SERIALIZED, (char*)val);
    return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_StringType);
}

extern "C" PRT_VALUE* P_Concat_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE** P_VAR_payload = argRefs[0];
    PRT_UINT64 val = (*P_VAR_payload)->valueUnion.frgn->value;

    PRT_VALUE** P_VAR_payload2 = argRefs[1];
    PRT_UINT64 val2 = (*P_VAR_payload2)->valueUnion.frgn->value;

    strncat((char*) val, (char*) val2, SGX_RSA3072_KEY_SIZE + 1); //TODO shividentity

    PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED));
    memcpy(str, (char*)val, SIZE_OF_PRT_STRING_SERIALIZED);
	// sprintf_s(str, SIZE_OF_PRT_STRING_SERIALIZED, (char*)val);
    return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_StringType);
}

extern "C" PRT_VALUE* P_GetThis_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    char* ipAddressOfHostMachine = (char*) malloc(IP_ADDRESS_AND_PORT_STRING_SIZE);
    ocall_get_ip_address_of_current_host(ipAddressOfHostMachine, IP_ADDRESS_AND_PORT_STRING_SIZE);
    #ifdef ENCLAVE_STD_ALT
    int port;
    ocall_get_port_of_current_host(&port);
    char* portString = (char*) malloc(IP_ADDRESS_AND_PORT_STRING_SIZE);
    itoa(port, portString, 10);
    char* concatStringss[] = {ipAddressOfHostMachine, ":", portString};
    int concatLengthss[] = {strlen(ipAddressOfHostMachine), 1, strlen(portString)};
    char* ipAddressAndPortSerialized = concatMutipleStringsWithLength(concatStringss, concatLengthss, 3);
    int ipAddressAndPortSerializedSize = returnTotalSizeofLengthArray(concatLengthss, 3);
    

    uint32_t currentMachinePID = context->id->valueUnion.mid->machineId;
    char* currentMachineIDPublicKey;
 
    currentMachineIDPublicKey = (char*) malloc(SIZE_OF_IDENTITY_STRING);
    memcpy(currentMachineIDPublicKey,(char*)get<0>(MachinePIDToIdentityDictionary[currentMachinePID]).c_str(), SIZE_OF_IDENTITY_STRING);

    // ocall_print("Machine handle in get capability is:");
    // printRSAKey((char*) val);
    //TODO put check here before obtaining the value
    if ( PMachineToChildCapabilityKey.count(make_tuple(currentMachinePID, string((char*) currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE))) == 0){
        ocall_print("ERROR IN GETTING CAPABILITY FROM GetThis Secure P METHOD");
    }
    string capabilityKeyPayload = PMachineToChildCapabilityKey[make_tuple(currentMachinePID, string((char*) currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE))];
    PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_SECURE_MACHINE_HANDLE));
	char* finalString;
    int finalStringSize;
    char* currentMachinePublicSigningKey = (char*)PublicIdentityKeyToPublicSigningKey[string(currentMachineIDPublicKey, SGX_RSA3072_KEY_SIZE)].c_str();
    char* concatStrings[] = {(char*) currentMachineIDPublicKey, ":", currentMachinePublicSigningKey, ":", (char*)capabilityKeyPayload.c_str(), ":", ipAddressAndPortSerialized};
    int concatLengths[] = {SGX_RSA3072_KEY_SIZE, 1, sizeof(sgx_rsa3072_public_key_t), 1, SIZE_OF_CAPABILITYKEY, 1, ipAddressAndPortSerializedSize};
    finalString = concatMutipleStringsWithLength(concatStrings, concatLengths, 7);
    finalStringSize = returnTotalSizeofLengthArray(concatLengths, 7) + 1;

    memcpy(str, finalString, finalStringSize);
    safe_free(finalString);
    return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_secure_machine_handle);
    
    #else 
    int port = ocall_get_port_of_current_host();
    char* portString = (char*) malloc(IP_ADDRESS_AND_PORT_STRING_SIZE);
    itoa(port, portString, 10);
    char* concatStringss[] = {ipAddressOfHostMachine, ":", portString};
    int concatLengthss[] = {strlen(ipAddressOfHostMachine), 1, strlen(portString)};
    char* ipAddressAndPortSerialized = concatMutipleStringsWithLength(concatStringss, concatLengthss, 3);
    int ipAddressAndPortSerializedSize = returnTotalSizeofLengthArray(concatLengthss, 3);
    

    uint32_t currentMachinePID = context->id->valueUnion.mid->machineId;
    char* currentMachineIDPublicKey;
 
    currentMachineIDPublicKey = (char*) malloc(SIZE_OF_MACHINE_HANDLE);
    memcpy(currentMachineIDPublicKey,(char*)get<0>(MachinePIDToIdentityDictionary[currentMachinePID]).c_str(), SIZE_OF_IDENTITY_STRING);
    memcpy(currentMachineIDPublicKey + SGX_RSA3072_KEY_SIZE, ":", 1);
    memcpy(currentMachineIDPublicKey + SGX_RSA3072_KEY_SIZE + 1, (char*)PublicIdentityKeyToPublicSigningKey[get<0>(MachinePIDToIdentityDictionary[currentMachinePID])].c_str(), sizeof(sgx_rsa3072_public_key_t));
    //Return the currentMachineIDPublicKey and it is the responsibility of the P Secure machine to save it and use it to send messages later
    char* finalString;
    int finalStringSize;
    char* concatStrings[] = {currentMachineIDPublicKey, ":", ipAddressAndPortSerialized};
    int concatLengths[] = {SIZE_OF_KEY_IDENTITY_IN_HANDLE, 1, ipAddressAndPortSerializedSize};
    finalString = concatMutipleStringsWithLength(concatStrings, concatLengths, 3);
    finalStringSize = returnTotalSizeofLengthArray(concatLengths, 3) + 1;

    if (finalStringSize >= SIZE_OF_MACHINE_HANDLE) {
        ocall_print("ERROR: Overwriting machine handle");
    }

    PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_MACHINE_HANDLE));
    memcpy(str, finalString, finalStringSize);
    safe_free(currentMachineIDPublicKey);
    safe_free(finalString);
  
    return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_machine_handle);

    #endif
}

// extern "C" PRT_VALUE* P_GetThisSecure_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
// {
//     return P_GetThis_IMPL(context, argRefs);
// }

extern "C" void P_PrintString_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE** P_VAR_payload = argRefs[0];
    PRT_UINT64 val = (*P_VAR_payload)->valueUnion.frgn->value;
    ocall_print("String P value is:");
    ocall_print((char*) val);
    if ((*P_VAR_payload)->valueUnion.frgn->typeTag == P_TYPEDEF_secure_StringType->typeUnion.foreignType->declIndex) {
        ocall_print("secure StringType");
    } 
    if ((*P_VAR_payload)->valueUnion.frgn->typeTag == P_TYPEDEF_StringType->typeUnion.foreignType->declIndex) {
        ocall_print("StringType");
    } 
    (*P_VAR_payload)->valueUnion.frgn->typeTag = P_TYPEDEF_secure_StringType->typeUnion.foreignType->declIndex;
    
}

extern "C" void P_PrintKey_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE** P_VAR_payload = argRefs[0];
    PRT_UINT64 val = (*P_VAR_payload)->valueUnion.frgn->value;
    ocall_print("FOREIGN PRINT KEY IS:");
    printPayload((char*) val, SIZE_OF_MACHINE_HANDLE);
    // printRSAKey((char*) val);
    
}

extern "C" PRT_VALUE* P_CastSecureMachineHandleToMachineHandle_IMPL(PRT_VALUE* value)
{
    PRT_UINT64 val = value->valueUnion.frgn->value;

    PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_MACHINE_HANDLE));
    memcpy(str, (char*) val, SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1);
    memcpy(str + SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1, (char*) val + SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1 + SIZE_OF_CAPABILITYKEY + 1, IP_ADDRESS_AND_PORT_STRING_SIZE);
    // memcpy(str + SGX_RSA3072_KEY_SIZE, ":", 1);
    // ocall_print("checking temp fix");
    // if (PublicIdentityKeyToPublicSigningKey.count(string((char*)val, SGX_RSA3072_KEY_SIZE)) == 0) {
    //     ocall_print("TEMP FIX WONT WORK");
    // }
    // memcpy(str + SGX_RSA3072_KEY_SIZE + 1, (char*) , sizeof(sgx_rsa3072_public_key_t));
    ocall_print("Cast Secure Machine Handle to Regular preserves ip address and port information as");
    ocall_print(str + SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1);
    return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_machine_handle);
    
}

extern "C" PRT_VALUE* P_CastMachineHandleToSecureMachineHandle_IMPL(PRT_VALUE* value)
{
    PRT_UINT64 val = value->valueUnion.frgn->value;

    ocall_print("Cast Machine Handle to Secure initial port info");
    ocall_print(((char*)val) + SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1);

    PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_SECURE_MACHINE_HANDLE));
    memcpy(str, (char*) val, SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1);
    memcpy(str + SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1 + SIZE_OF_CAPABILITYKEY + 1, (char*) val + SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1, IP_ADDRESS_AND_PORT_STRING_SIZE);
    // memcpy(str + SGX_RSA3072_KEY_SIZE, ":", 1);
    // ocall_print("checking temp fix");
    // if (PublicIdentityKeyToPublicSigningKey.count(string((char*)val, SGX_RSA3072_KEY_SIZE)) == 0) {
    //     ocall_print("TEMP FIX WONT WORK");
    // }
    // memcpy(str + SGX_RSA3072_KEY_SIZE + 1, (char*) , sizeof(sgx_rsa3072_public_key_t));
    ocall_print("Cast Machine Handle to Secure preserves ip address and port information as");
    ocall_print(str + SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1 + SIZE_OF_CAPABILITYKEY + 1);
    return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_secure_machine_handle);
    
}

extern "C" PRT_VALUE* P_CastSecureStringTypeToStringType_IMPL(PRT_VALUE* value)
{
    
    value->valueUnion.frgn->typeTag = P_TYPEDEF_StringType->typeUnion.foreignType->declIndex;
    return value;
    // // ocall_print("debug inside");
    // PRT_UINT64 val = value->valueUnion.frgn->value;

    // PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED));
    // // ocall_print((char*)val);
    // memcpy(str, (char*) val, SIZE_OF_PRT_STRING_SERIALIZED);
    // // memcpy(str + SGX_RSA3072_KEY_SIZE, ":", 1);
    // // ocall_print("checking temp fix");
    // // if (PublicIdentityKeyToPublicSigningKey.count(string((char*)val, SGX_RSA3072_KEY_SIZE)) == 0) {
    // //     ocall_print("TEMP FIX WONT WORK");
    // // }
    // // memcpy(str + SGX_RSA3072_KEY_SIZE + 1, (char*) , sizeof(sgx_rsa3072_public_key_t));
    // PRT_VALUE* ret = PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_secure_StringType);
    // // ocall_print_int(ret->discriminator);
    // return ret;
    
}

extern "C" PRT_VALUE* P_CastStringTypeToSecureStringType_IMPL(PRT_VALUE* value)
{
    value->valueUnion.frgn->typeTag = P_TYPEDEF_secure_StringType->typeUnion.foreignType->declIndex;
    return value;
    // ocall_print("debug inside");
    // PRT_UINT64 val = value->valueUnion.frgn->value;

    // PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED));
    // // ocall_print((char*)val);
    // memcpy(str, (char*) val, SIZE_OF_PRT_STRING_SERIALIZED);
    // // memcpy(str + SGX_RSA3072_KEY_SIZE, ":", 1);
    // // ocall_print("checking temp fix");
    // // if (PublicIdentityKeyToPublicSigningKey.count(string((char*)val, SGX_RSA3072_KEY_SIZE)) == 0) {
    // //     ocall_print("TEMP FIX WONT WORK");
    // // }
    // // memcpy(str + SGX_RSA3072_KEY_SIZE + 1, (char*) , sizeof(sgx_rsa3072_public_key_t));
    // PRT_VALUE* ret = PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_StringType);
    // // ocall_print_int(ret->discriminator);
    // return ret;
    
}

extern "C" PRT_VALUE* P_DeclassifyHandle_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE** P_VAR_payload = argRefs[0];
    PRT_UINT64 val = (*P_VAR_payload)->valueUnion.frgn->value;

    PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_MACHINE_HANDLE));
    memcpy(str, (char*) val, SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1);
    memcpy(str + SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1, (char*) val + SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1 + SIZE_OF_CAPABILITYKEY + 1, IP_ADDRESS_AND_PORT_STRING_SIZE);
    // memcpy(str + SGX_RSA3072_KEY_SIZE, ":", 1);
    // ocall_print("checking temp fix");
    // if (PublicIdentityKeyToPublicSigningKey.count(string((char*)val, SGX_RSA3072_KEY_SIZE)) == 0) {
    //     ocall_print("TEMP FIX WONT WORK");
    // }
    // memcpy(str + SGX_RSA3072_KEY_SIZE + 1, (char*) , sizeof(sgx_rsa3072_public_key_t));
    ocall_print("Cast Secure Machine Handle preserves ip address and port information as");
    ocall_print(str + SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1);
    return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_machine_handle);
    
}

extern "C" PRT_VALUE* P_Declassify_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE** P_VAR_payload = argRefs[0];

    if ((*P_VAR_payload)->discriminator == PRT_VALUE_KIND_SECURE_BOOL) {
        return PrtMkBoolValue((*P_VAR_payload)->valueUnion.bl);

    } else if ((*P_VAR_payload)->discriminator == PRT_VALUE_KIND_SECURE_INT) {
        return PrtMkIntValue((*P_VAR_payload)->valueUnion.nt);

    } else if ((*P_VAR_payload)->discriminator == PRT_VALUE_KIND_FOREIGN) {

        if ((*P_VAR_payload)->valueUnion.frgn->typeTag == P_TYPEDEF_secure_StringType->typeUnion.foreignType->declIndex) {
            return P_CastSecureStringTypeToStringType_IMPL((*P_VAR_payload));
            // PRT_UINT64 val = (*P_VAR_payload)->valueUnion.frgn->value;
            // PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED));
            // memcpy(str, (char*) val, SIZE_OF_PRT_STRING_SERIALIZED);
            // return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_StringType);
        } else if ((*P_VAR_payload)->valueUnion.frgn->typeTag == P_TYPEDEF_secure_machine_handle->typeUnion.foreignType->declIndex) {
            return P_CastSecureMachineHandleToMachineHandle_IMPL((*P_VAR_payload));
            // PRT_UINT64 val = (*P_VAR_payload)->valueUnion.frgn->value;
            // PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_MACHINE_HANDLE));
            // memcpy(str, (char*) val, SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1);
            // memcpy(str + SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1, (char*) val + SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1 + SIZE_OF_CAPABILITYKEY + 1, IP_ADDRESS_AND_PORT_STRING_SIZE);
            // ocall_print("Cast Secure Machine Handle preserves ip address and port information as");
            // ocall_print(str + SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1);
            // return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_machine_handle);
        } 

    }

    ocall_print("ERROR: Declassify not found");
    return NULL;

}


extern "C" PRT_VALUE* P_Endorse_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE** P_VAR_payload = argRefs[0];
    PRT_VALUE* prtValue = *P_VAR_payload;

    if ((*P_VAR_payload)->discriminator == PRT_VALUE_KIND_BOOL) {
        PRT_VALUE* temp = PrtMkBoolValue((*P_VAR_payload)->valueUnion.bl);
		temp->discriminator = PRT_VALUE_KIND_SECURE_BOOL;
		return temp;

    } else if ((*P_VAR_payload)->discriminator == PRT_VALUE_KIND_INT) {
        PRT_VALUE* temp = PrtMkIntValue(prtValue->valueUnion.nt);
		temp->discriminator = PRT_VALUE_KIND_SECURE_INT;
		return temp;

    } else if ((*P_VAR_payload)->discriminator == PRT_VALUE_KIND_FOREIGN) {

        if ((*P_VAR_payload)->valueUnion.frgn->typeTag == P_TYPEDEF_StringType->typeUnion.foreignType->declIndex) {
            return P_CastStringTypeToSecureStringType_IMPL(prtValue);
            // PRT_UINT64 val = (*P_VAR_payload)->valueUnion.frgn->value;
            // PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED));
            // memcpy(str, (char*) val, SIZE_OF_PRT_STRING_SERIALIZED);
            // return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_StringType);
        } else if ((*P_VAR_payload)->valueUnion.frgn->typeTag == P_TYPEDEF_machine_handle->typeUnion.foreignType->declIndex) {
            return P_CastMachineHandleToSecureMachineHandle_IMPL(prtValue);
            // PRT_UINT64 val = (*P_VAR_payload)->valueUnion.frgn->value;

            // PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_MACHINE_HANDLE));
            // memcpy(str, (char*) val, SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1);
            // memcpy(str + SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1, (char*) val + SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1 + SIZE_OF_CAPABILITYKEY + 1, IP_ADDRESS_AND_PORT_STRING_SIZE);
            // ocall_print("Cast Secure Machine Handle preserves ip address and port information as");
            // ocall_print(str + SIZE_OF_KEY_IDENTITY_IN_HANDLE + 1);
            // return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_machine_handle);
        } 

    }

    ocall_print("ERROR: Declassify not found");
    return NULL;

}

extern "C" PRT_VALUE* P_Classify_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE** P_VAR_payload = argRefs[0];

    // if ((*P_VAR_payload)->discriminator == PRT_VALUE_KIND_BOOL) {
    //     return PrtMkBoolValue((*P_VAR_payload)->valueUnion.bl);

    // } else if ((*P_VAR_payload)->discriminator == PRT_VALUE_KIND_INT) {
    //     return PrtMkIntValue((*P_VAR_payload)->valueUnion.nt);

    // } else if ((*P_VAR_payload)->discriminator == PRT_VALUE_KIND_FOREIGN) {
    if ((*P_VAR_payload)->discriminator == PRT_VALUE_KIND_FOREIGN) {

        if ((*P_VAR_payload)->valueUnion.frgn->typeTag == P_TYPEDEF_secure_StringType->typeUnion.foreignType->declIndex || (*P_VAR_payload)->valueUnion.frgn->typeTag == P_TYPEDEF_StringType->typeUnion.foreignType->declIndex) {
            PRT_UINT64 val = (*P_VAR_payload)->valueUnion.frgn->value;
            PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED));
            memcpy(str, (char*) val, SIZE_OF_PRT_STRING_SERIALIZED);
            return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_secure_StringType);
        } else if ((*P_VAR_payload)->valueUnion.frgn->typeTag == P_TYPEDEF_secure_machine_handle->typeUnion.foreignType->declIndex || (*P_VAR_payload)->valueUnion.frgn->typeTag == P_TYPEDEF_machine_handle->typeUnion.foreignType->declIndex) {
            PRT_UINT64 val = (*P_VAR_payload)->valueUnion.frgn->value;
            PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_MACHINE_HANDLE));
            memcpy(str, (char*) val, SIZE_OF_MACHINE_HANDLE);
            return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_secure_machine_handle);
        } 

    }

    ocall_print("ERROR: Declassify not found");
    return NULL;
}

extern "C" void P_PrintPCapability_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE** P_VAR_payload = argRefs[0];
    PRT_UINT64 val = (*P_VAR_payload)->valueUnion.frgn->value;
    ocall_print("Capability of machine:");
    printRSAKey((char*) val);
    char* capabilityPayload = ((char*) val) + SGX_RSA3072_KEY_SIZE + 1;
    ocall_print("Public Capability:");
    printPublicCapabilityKey(retrievePublicCapabilityKey(capabilityPayload));
    ocall_print("Private Capability:");
    printPrivateCapabilityKey(retrievePrivateCapabilityKey(capabilityPayload));
    
}

extern "C" PRT_VALUE* P_GetCapability_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    #ifdef ENCLAVE_STD_ALT

    uint32_t currentMachinePID = context->id->valueUnion.mid->machineId;
    PRT_VALUE** P_VAR_payload = argRefs[0];
    PRT_UINT64 val = (*P_VAR_payload)->valueUnion.frgn->value;
    // ocall_print("Machine handle in get capability is:");
    // printRSAKey((char*) val);
    //TODO put check here before obtaining the value
    if ( PMachineToChildCapabilityKey.count(make_tuple(currentMachinePID, string((char*) val, SGX_RSA3072_KEY_SIZE))) == 0){
        ocall_print("ERROR IN GETTING CAPABILITY FROM GETCAPABILITY P METHOD");
    }
    string capabilityKeyPayload = PMachineToChildCapabilityKey[make_tuple(currentMachinePID, string((char*) val, SGX_RSA3072_KEY_SIZE))];
    PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_P_CAPABILITY_FOREIGN_TYPE));
	char* finalString;
    int finalStringSize;
    char* concatStrings[] = {(char*) val, ":", (char*)capabilityKeyPayload.c_str()};
    int concatLengths[] = {SGX_RSA3072_KEY_SIZE, 1, SIZE_OF_CAPABILITYKEY};
    finalString = concatMutipleStringsWithLength(concatStrings, concatLengths, 3);
    finalStringSize = returnTotalSizeofLengthArray(concatLengths, 3) + 1;

    memcpy(str, finalString, finalStringSize);
    safe_free(finalString);
    return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_capability);

    #endif
    
}

extern "C" void P_SaveCapability_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    #ifdef ENCLAVE_STD_ALT

    uint32_t currentMachinePID = context->id->valueUnion.mid->machineId;
    PRT_VALUE** P_VAR_payload = argRefs[0];
    PRT_UINT64 val = (*P_VAR_payload)->valueUnion.frgn->value;
    char* machine_handle = (char*) malloc(SGX_RSA3072_KEY_SIZE);
    memcpy(machine_handle, (char*)val, SGX_RSA3072_KEY_SIZE);
    char* capabilityToSave = (char*) malloc(SIZE_OF_CAPABILITYKEY);
    memcpy(capabilityToSave, ((char*)val) + SGX_RSA3072_KEY_SIZE + 1, SIZE_OF_CAPABILITYKEY);
    PMachineToChildCapabilityKey[make_tuple(currentMachinePID, string(machine_handle, SGX_RSA3072_KEY_SIZE))] = string(capabilityToSave, SIZE_OF_CAPABILITYKEY);
    safe_free(machine_handle);
    safe_free(capabilityToSave);
    #endif
    
}

extern "C" void P_MeasureTime_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{

    ocall_print_current_time();
    
}

extern "C" PRT_VALUE* P_GetHelloWorld_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    char user_input[100];
    // ocall_request_user_input(user_input, 100);
    memcpy(user_input, "helloworld", 11);
    PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED));
	sprintf_s(str, SIZE_OF_PRT_STRING_SERIALIZED, user_input);
    return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_StringType);
    
}



extern "C" PRT_VALUE* P_GetUserInput_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    char user_input[100];
    // ocall_request_user_input(user_input, 100);
    memcpy(user_input, "pword", 6);
    PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED));
	sprintf_s(str, SIZE_OF_PRT_STRING_SERIALIZED, user_input);
    return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_StringType);
    
}

extern "C" PRT_VALUE* P_GenerateRandomMasterSecret_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED));
	sprintf_s(str, SIZE_OF_PRT_STRING_SERIALIZED, "MasterSecret");
    return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_secure_StringType);
    
}

extern "C" void P_PrintRawStringType_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE** P_VAR_payload = argRefs[0];
    PRT_UINT64 val = (*P_VAR_payload)->valueUnion.frgn->value;

    printPayload((char*)val, SIZE_OF_PRT_STRING_SERIALIZED);
   
    
}

extern "C" void P_PrintRawSecureStringType_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE** P_VAR_payload = argRefs[0];
    PRT_UINT64 val = (*P_VAR_payload)->valueUnion.frgn->value;

    printPayload((char*)val, SIZE_OF_PRT_STRING_SERIALIZED);
   
    
}


extern "C" PRT_VALUE* P_DeclassifyInt_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE** P_VAR_payload = argRefs[0];
    return PrtMkIntValue((*P_VAR_payload)->valueUnion.nt);
}

extern "C" PRT_VALUE* P_DeclassifyBool_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE** P_VAR_payload = argRefs[0];
    return PrtMkBoolValue((*P_VAR_payload)->valueUnion.bl);
}



extern "C" void P_PrintMachineHandle_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE** P_VAR_payload = argRefs[0];
    ocall_print("print machine handle");
    ocall_print("print public id key");
    printPayload((char*)(*P_VAR_payload)->valueUnion.frgn->value, SGX_RSA3072_KEY_SIZE);
    ocall_print("print public signing key");
    printPayload((char*)(*P_VAR_payload)->valueUnion.frgn->value + SGX_RSA3072_KEY_SIZE + 1, sizeof(sgx_rsa3072_public_key_t));


}

extern "C" PRT_VALUE* P_GenerateCredential1_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED));
    memset(str, sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED), 0);
	sprintf_s(str, SIZE_OF_PRT_STRING_SERIALIZED, "ZeaipvqyqBTpbebZKyWub9uVXVmiWt1bk7RZtzVl5dCVN0mdYB87iw9ggZBHYZKmkeg9uOVA4OPU4HtjlJXb4b6ZmXmdUbqoaRsOUNW6H43mCpmvM5KenYnASIWKTv8sFwDdjpeGynIYHKfh2M5yE2VjiM0XoJSD55MB8sdca9GYsHuDCD8M9Ha2vrKe7eNbFfcsfqei3GQmY98hgIWIXxHrO3HOxrHgvmdoj9FvYeOsewL3BhuKSyqI6YjSxbMermFldGL2Q7zyZi0ss6e7UIPYzG2iAvb1OZJt9q2xGhRPPMGXUmlz4kN7nyaiKkWQjKFKRFfYHDqhpxPPPticYetylRz9weh3ors9PvH7gm5qvMGANcwwWlOpQrFW4m1");
    return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_StringType);
    
}

extern "C" PRT_VALUE* P_GenerateCredential2_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED));
    memset(str, sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED), 0);
	sprintf_s(str, SIZE_OF_PRT_STRING_SERIALIZED, "AZWmDUUegwGZsrJa9qMZ5YQVoJrRd7DySp5VNDzNr3dUise9Vh3lwbpiULug9AAf9Y4zlPXaLZouQXtrzEFh5C3iDzR9HJuQmTEhKIqBXrAPL0WOhxTJzrxCVbSrY3ftRCLuztlv4Kcsrq1Knp1MkYwzqf5sUBVAerHMHpd5z8SODEvbiF7KjSH6GzF2HrTeLUlnS64FCxIMnnpzo7zGEigHRJ5unOt3gwFm4MDEwu7UdiiN19tPGIgYJl1Ep23s4D37KOb2WoEj7AcIdL6w5nQdrmNGmWV8squ2kMApg57PT53risbj3Fw0Obvg7BqhIJ2DUfBiu5tC56PPe0r8VbIChaSGQ5QUTzbWxDtLxlKDiwmJDw08qp4HtABfsVg");
    return PrtMkForeignValue((PRT_UINT64)str, P_TYPEDEF_StringType);
    
}



extern "C" void P_Debug_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    
    #ifdef ENCLAVE_STD_ALT
    // ocall_print("P Debug!");
    // uint32_t currentMachinePID = context->id->valueUnion.mid->machineId;

    // string sendingToMachineCapabilityKeyPayload = PMachineToChildCapabilityKey[make_tuple(currentMachinePID, string(sendingToMachinePublicID, SGX_RSA3072_KEY_SIZE))];
    // printPublicCapabilityKey((char*)sendingToMachineCapabilityKeyPayload.c_str());
    // printPrivateCapabilityKey((char*)sendingToMachineCapabilityKeyPayload.c_str());

    // uint32_t currentMachinePID = context->id->valueUnion.mid->machineId;
    // PRT_VALUE** P_VAR_payload = argRefs[0];
    // PRT_UINT64 val = (*P_VAR_payload)->valueUnion.frgn->value;
    // char* machine_handle = (char*) malloc(SGX_RSA3072_KEY_SIZE);
    // memcpy(machine_handle, (char*)val, SGX_RSA3072_KEY_SIZE);
    // char* capabilityToSave = (char*) malloc(SIZE_OF_CAPABILITYKEY);
    // memcpy(capabilityToSave, ((char*)val) + SGX_RSA3072_KEY_SIZE + 1, SIZE_OF_CAPABILITYKEY);
    // PMachineToChildCapabilityKey[make_tuple(currentMachinePID, string(machine_handle, SGX_RSA3072_KEY_SIZE))] = string(capabilityToSave, SIZE_OF_CAPABILITYKEY);
    // safe_free(machine_handle);
    // safe_free(capabilityToSave);
    #endif
}

//StringType Class

extern "C" void P_FREE_StringType_IMPL(PRT_UINT64 frgnVal)
{
	PrtFree((PRT_STRING)frgnVal);
}

extern "C" PRT_BOOLEAN P_ISEQUAL_StringType_IMPL(PRT_UINT64 frgnVal1, PRT_UINT64 frgnVal2)
{
    ocall_print("Checking the following strings");
    ocall_print((char*) frgnVal1);
    ocall_print((char*) frgnVal2);
	return strcmp((PRT_STRING)frgnVal1, (PRT_STRING)frgnVal2) == 0 ? PRT_TRUE : PRT_FALSE;
}

extern "C" PRT_STRING P_TOSTRING_StringType_IMPL(PRT_UINT64 frgnVal)
{
	PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED));
	sprintf_s(str, SIZE_OF_PRT_STRING_SERIALIZED, "String : %s", frgnVal);
	return str;
}

extern "C" PRT_UINT32 P_GETHASHCODE_StringType_IMPL(PRT_UINT64 frgnVal)
{
    return 7;
	// return (PRT_UINT32)frgnVal;
}

extern "C" PRT_UINT64 P_MKDEF_StringType_IMPL(void)
{
	PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED));
	sprintf_s(str, SIZE_OF_PRT_STRING_SERIALIZED, "xyx$12");
	return (PRT_UINT64)str;
}

extern "C" PRT_UINT64 P_CLONE_StringType_IMPL(PRT_UINT64 frgnVal)
{
	PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED));
    // if (NETWORK_DEBUG) {
    //     sprintf_s(str, SIZE_OF_PRT_STRING_SERIALIZED, (PRT_STRING)frgnVal);
    // } else {
        memcpy(str, (void*)frgnVal, SIZE_OF_PRT_STRING_SERIALIZED);
    // }
	
	return (PRT_UINT64)str;
}

//secure_StringType Class

extern "C" void P_FREE_secure_StringType_IMPL(PRT_UINT64 frgnVal)
{
	PrtFree((PRT_STRING)frgnVal);
}

extern "C" PRT_BOOLEAN P_ISEQUAL_secure_StringType_IMPL(PRT_UINT64 frgnVal1, PRT_UINT64 frgnVal2)
{
    ocall_print("Checking the following strings");
    ocall_print((char*) frgnVal1);
    ocall_print((char*) frgnVal2);
	return strcmp((PRT_STRING)frgnVal1, (PRT_STRING)frgnVal2) == 0 ? PRT_TRUE : PRT_FALSE;
}

extern "C" PRT_STRING P_TOSTRING_secure_StringType_IMPL(PRT_UINT64 frgnVal)
{
	PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED));
	sprintf_s(str, SIZE_OF_PRT_STRING_SERIALIZED, "String : %s", frgnVal);
	return str;
}

extern "C" PRT_UINT32 P_GETHASHCODE_secure_StringType_IMPL(PRT_UINT64 frgnVal)
{
    return 7;

	// return (PRT_UINT32)frgnVal;
}

extern "C" PRT_UINT64 P_MKDEF_secure_StringType_IMPL(void)
{
	PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED));
	sprintf_s(str, SIZE_OF_PRT_STRING_SERIALIZED, "xyx$12");
	return (PRT_UINT64)str;
}

extern "C" PRT_UINT64 P_CLONE_secure_StringType_IMPL(PRT_UINT64 frgnVal)
{
	PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_PRT_STRING_SERIALIZED));
    // if (NETWORK_DEBUG) {
    //     sprintf_s(str, SIZE_OF_PRT_STRING_SERIALIZED, (PRT_STRING)frgnVal);
    // } else {
        memcpy(str, (void*)frgnVal, SIZE_OF_PRT_STRING_SERIALIZED);
    // }
	
	return (PRT_UINT64)str;
}

//machine_handle class

extern "C" void P_FREE_machine_handle_IMPL(PRT_UINT64 frgnVal)
{
	PrtFree((PRT_STRING)frgnVal);
}

extern "C" PRT_BOOLEAN P_ISEQUAL_machine_handle_IMPL(PRT_UINT64 frgnVal1, PRT_UINT64 frgnVal2)
{
	return memcmp((PRT_STRING)frgnVal1, (PRT_STRING)frgnVal2, SIZE_OF_MACHINE_HANDLE) == 0 ? PRT_TRUE : PRT_FALSE;
}

extern "C" PRT_STRING P_TOSTRING_machine_handle_IMPL(PRT_UINT64 frgnVal)
{
	PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_MACHINE_HANDLE));
	sprintf_s(str, SIZE_OF_MACHINE_HANDLE, "String : %s", frgnVal);
	return str;
}

extern "C" PRT_UINT32 P_GETHASHCODE_machine_handle_IMPL(PRT_UINT64 frgnVal)
{
	return (PRT_UINT32)frgnVal;
}

extern "C" PRT_UINT64 P_MKDEF_machine_handle_IMPL(void)
{
	PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_MACHINE_HANDLE));
	sprintf_s(str, SIZE_OF_MACHINE_HANDLE, "xyx$12");
	return (PRT_UINT64)str;
}

extern "C" PRT_UINT64 P_CLONE_machine_handle_IMPL(PRT_UINT64 frgnVal)
{
	PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_MACHINE_HANDLE));
    // if (NETWORK_DEBUG) {
    //     sprintf_s(str, SIZE_OF_PRT_STRING_SERIALIZED, (PRT_STRING)frgnVal);
    // } else {
        memcpy(str, (void*)frgnVal, SIZE_OF_MACHINE_HANDLE);
    // }
	
	return (PRT_UINT64)str;
}

//capability class

extern "C" void P_FREE_capability_IMPL(PRT_UINT64 frgnVal)
{
	PrtFree((PRT_STRING)frgnVal);
}

extern "C" PRT_BOOLEAN P_ISEQUAL_capability_IMPL(PRT_UINT64 frgnVal1, PRT_UINT64 frgnVal2)
{
	return memcmp((PRT_STRING)frgnVal1, (PRT_STRING)frgnVal2, SIZE_OF_P_CAPABILITY_FOREIGN_TYPE) == 0 ? PRT_TRUE : PRT_FALSE;
}

extern "C" PRT_STRING P_TOSTRING_capability_IMPL(PRT_UINT64 frgnVal)
{
	PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_P_CAPABILITY_FOREIGN_TYPE));
	sprintf_s(str, SIZE_OF_P_CAPABILITY_FOREIGN_TYPE, "String : %s", frgnVal);
	return str;
}

extern "C" PRT_UINT32 P_GETHASHCODE_capability_IMPL(PRT_UINT64 frgnVal)
{
	return (PRT_UINT32)frgnVal;
}

extern "C" PRT_UINT64 P_MKDEF_capability_IMPL(void)
{
	PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_P_CAPABILITY_FOREIGN_TYPE));
	sprintf_s(str, SIZE_OF_P_CAPABILITY_FOREIGN_TYPE, "xyx$12");
	return (PRT_UINT64)str;
}

extern "C" PRT_UINT64 P_CLONE_capability_IMPL(PRT_UINT64 frgnVal)
{
	PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_P_CAPABILITY_FOREIGN_TYPE));
    // if (NETWORK_DEBUG) {
    //     sprintf_s(str, SIZE_OF_PRT_STRING_SERIALIZED, (PRT_STRING)frgnVal);
    // } else {
        memcpy(str, (void*)frgnVal, SIZE_OF_P_CAPABILITY_FOREIGN_TYPE);
    // }
	
	return (PRT_UINT64)str;
}

//secure_machine_handle class

extern "C" void P_FREE_secure_machine_handle_IMPL(PRT_UINT64 frgnVal)
{
	PrtFree((PRT_STRING)frgnVal);
}

extern "C" PRT_BOOLEAN P_ISEQUAL_secure_machine_handle_IMPL(PRT_UINT64 frgnVal1, PRT_UINT64 frgnVal2)
{
	return memcmp((PRT_STRING)frgnVal1, (PRT_STRING)frgnVal2, SIZE_OF_SECURE_MACHINE_HANDLE) == 0 ? PRT_TRUE : PRT_FALSE;
}

extern "C" PRT_STRING P_TOSTRING_secure_machine_handle_IMPL(PRT_UINT64 frgnVal)
{
	PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_SECURE_MACHINE_HANDLE));
	sprintf_s(str, SIZE_OF_SECURE_MACHINE_HANDLE, "String : %s", frgnVal);
	return str;
}

extern "C" PRT_UINT32 P_GETHASHCODE_secure_machine_handle_IMPL(PRT_UINT64 frgnVal)
{
	return (PRT_UINT32)frgnVal;
}

extern "C" PRT_UINT64 P_MKDEF_secure_machine_handle_IMPL(void)
{
	PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_SECURE_MACHINE_HANDLE));
	sprintf_s(str, SIZE_OF_SECURE_MACHINE_HANDLE, "xyx$12");
	return (PRT_UINT64)str;
}

extern "C" PRT_UINT64 P_CLONE_secure_machine_handle_IMPL(PRT_UINT64 frgnVal)
{
	PRT_STRING str = (PRT_STRING) PrtMalloc(sizeof(PRT_CHAR) * (SIZE_OF_SECURE_MACHINE_HANDLE));
    // if (NETWORK_DEBUG) {
    //     sprintf_s(str, SIZE_OF_SECURE_MACHINE_HANDLE, (PRT_STRING)frgnVal);
    // } else {
        memcpy(str, (void*)frgnVal, SIZE_OF_SECURE_MACHINE_HANDLE);
    // }
	
	return (PRT_UINT64)str;
}