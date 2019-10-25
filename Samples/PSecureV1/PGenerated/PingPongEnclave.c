#include "PingPongEnclave.h"

// Type universe for program:
static PRT_TYPE P_GEND_TYPE_n = { PRT_KIND_NULL, { NULL } };

// Function implementation prototypes:
PRT_VALUE* P_SecureSendPongEventToPingMachine_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);

PRT_VALUE* P_CreateMachineSecureChild_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);

PRT_VALUE* P_Anon_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon;

PRT_VALUE* P_Anon_IMPL_1(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_1;

PRT_VALUE* P_Anon_IMPL_2(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_2;

PRT_VALUE* P_Anon_IMPL_3(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_3;


PRT_EVENTDECL P_EVENT_Ping = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "Ping",
    2U,
    &P_GEND_TYPE_n
};

PRT_EVENTDECL P_EVENT_Pong = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "Pong",
    2U,
    &P_GEND_TYPE_n
};

PRT_EVENTDECL P_EVENT_Success = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "Success",
    4294967295U,
    &P_GEND_TYPE_n
};

PRT_FUNDECL P_FUNCTION_SecureSendPongEventToPingMachine =
{
    "SecureSendPongEventToPingMachine",
    &P_SecureSendPongEventToPingMachine_IMPL,
    NULL
};


PRT_FUNDECL P_FUNCTION_CreateMachineSecureChild =
{
    "CreateMachineSecureChild",
    &P_CreateMachineSecureChild_IMPL,
    NULL
};


PRT_EVENTDECL* P_Pong_RECV_INNER[] = { &P_EVENT_Ping, &P_EVENT_Pong, &P_EVENT_Success, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_Pong_RECV =
{
    4U,
    P_Pong_RECV_INNER,
    NULL
};

PRT_INTERFACEDECL P_I_Pong =
{
    0U,
    "Pong",
    &P_GEND_TYPE_n,
    &P_EVENTSET_Pong_RECV
};

PRT_EVENTDECL* P_SecureChild_RECV_INNER[] = { &P_EVENT_Ping, &P_EVENT_Pong, &P_EVENT_Success, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_SecureChild_RECV =
{
    4U,
    P_SecureChild_RECV_INNER,
    NULL
};

PRT_INTERFACEDECL P_I_SecureChild =
{
    1U,
    "SecureChild",
    &P_GEND_TYPE_n,
    &P_EVENTSET_SecureChild_RECV
};

PRT_EVENTDECL* P_Pong_WaitPing_DEFERS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Pong_WaitPing_DEFERS =
{
    0U,
    P_Pong_WaitPing_DEFERS_INNER,
    NULL
};

PRT_EVENTDECL* P_Pong_WaitPing_TRANS_INNER[] = { &P_EVENT_Ping };
PRT_EVENTSETDECL P_EVENTSET_Pong_WaitPing_TRANS =
{
    1U,
    P_Pong_WaitPing_TRANS_INNER,
    NULL
};

PRT_EVENTDECL* P_Pong_WaitPing_DOS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Pong_WaitPing_DOS =
{
    0U,
    P_Pong_WaitPing_DOS_INNER,
    NULL
};

PRT_TRANSDECL P_TRANS[] =
{
    { 0, &P_EVENT_Ping, 1, &_P_NO_OP }
};

#define P_STATE_Pong_Pong_WaitPing \
{ \
    "Pong.Pong_WaitPing", \
    1U, \
    0U, \
    &P_EVENTSET_Pong_WaitPing_DEFERS, \
    &P_EVENTSET_Pong_WaitPing_TRANS, \
    &P_EVENTSET_Pong_WaitPing_DOS, \
    P_TRANS, \
    NULL, \
    &P_FUNCTION_Anon, \
    &_P_NO_OP, \
}

PRT_EVENTDECL* P_Pong_SendingPong_DEFERS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Pong_SendingPong_DEFERS =
{
    0U,
    P_Pong_SendingPong_DEFERS_INNER,
    NULL
};

PRT_EVENTDECL* P_Pong_SendingPong_TRANS_INNER[] = { &P_EVENT_Success };
PRT_EVENTSETDECL P_EVENTSET_Pong_SendingPong_TRANS =
{
    1U,
    P_Pong_SendingPong_TRANS_INNER,
    NULL
};

PRT_EVENTDECL* P_Pong_SendingPong_DOS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Pong_SendingPong_DOS =
{
    0U,
    P_Pong_SendingPong_DOS_INNER,
    NULL
};

PRT_TRANSDECL P_TRANS_1[] =
{
    { 1, &P_EVENT_Success, 2, &_P_NO_OP }
};

#define P_STATE_Pong_Pong_SendingPong \
{ \
    "Pong.Pong_SendingPong", \
    1U, \
    0U, \
    &P_EVENTSET_Pong_SendingPong_DEFERS, \
    &P_EVENTSET_Pong_SendingPong_TRANS, \
    &P_EVENTSET_Pong_SendingPong_DOS, \
    P_TRANS_1, \
    NULL, \
    &P_FUNCTION_Anon_1, \
    &_P_NO_OP, \
}

PRT_EVENTDECL* P_Done_DEFERS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Done_DEFERS =
{
    0U,
    P_Done_DEFERS_INNER,
    NULL
};

PRT_EVENTDECL* P_Done_TRANS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Done_TRANS =
{
    0U,
    P_Done_TRANS_INNER,
    NULL
};

PRT_EVENTDECL* P_Done_DOS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Done_DOS =
{
    0U,
    P_Done_DOS_INNER,
    NULL
};

#define P_STATE_Pong_Done \
{ \
    "Pong.Done", \
    0U, \
    0U, \
    &P_EVENTSET_Done_DEFERS, \
    &P_EVENTSET_Done_TRANS, \
    &P_EVENTSET_Done_DOS, \
    NULL, \
    NULL, \
    &_P_NO_OP, \
    &_P_NO_OP, \
}

PRT_STATEDECL P_Pong_STATES[] = { P_STATE_Pong_Pong_WaitPing, P_STATE_Pong_Pong_SendingPong, P_STATE_Pong_Done };

PRT_VALUE* P_Anon_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PrtFreeValue(P_CreateMachineSecureChild_IMPL(context, _P_GEN_funargs));
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return;
    }
    
p_return: ;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon =
{
    NULL,
    &P_Anon_IMPL,
    NULL
};


PRT_VALUE* P_Anon_IMPL_1(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE = &(PTMP_tmp0);
    PrtFreeValue(*P_LVALUE);
    *P_LVALUE = PrtCloneValue((&P_EVENT_Success.value));
    
    PrtRaise(p_this, PTMP_tmp0, 0);
    *(&(PTMP_tmp0)) = NULL;
    goto p_return_1;
    
p_return_1: ;
    PrtFreeValue(PTMP_tmp0); PTMP_tmp0 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_1 =
{
    NULL,
    &P_Anon_IMPL_1,
    NULL
};


PRT_FUNDECL* P_Pong_METHODS[] = { &P_FUNCTION_Anon, &P_FUNCTION_Anon_1 };

PRT_EVENTDECL* P_Pong_RECV_INNER_1[] = { &P_EVENT_Ping, &P_EVENT_Pong, &P_EVENT_Success, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_Pong_RECV_1 =
{
    4U,
    P_Pong_RECV_INNER_1,
    NULL
};

PRT_EVENTDECL* P_Pong_SEND_INNER[] = { &P_EVENT_Ping, &P_EVENT_Pong, &P_EVENT_Success, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_Pong_SEND =
{
    4U,
    P_Pong_SEND_INNER,
    NULL
};

PRT_MACHINEDECL P_MACHINE_Pong = 
{
    0U,
    "Pong",
    &P_EVENTSET_Pong_RECV_1,
    &P_EVENTSET_Pong_SEND,
    NULL,
    0U,
    3U,
    2U,
    4294967295U,
    0U,
    NULL,
    P_Pong_STATES,
    P_Pong_METHODS
};

PRT_EVENTDECL* P_Pong_WaitPing_DEFERS_INNER_1[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Pong_WaitPing_DEFERS_1 =
{
    0U,
    P_Pong_WaitPing_DEFERS_INNER_1,
    NULL
};

PRT_EVENTDECL* P_Pong_WaitPing_TRANS_INNER_1[] = { &P_EVENT_Ping };
PRT_EVENTSETDECL P_EVENTSET_Pong_WaitPing_TRANS_1 =
{
    1U,
    P_Pong_WaitPing_TRANS_INNER_1,
    NULL
};

PRT_EVENTDECL* P_Pong_WaitPing_DOS_INNER_1[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Pong_WaitPing_DOS_1 =
{
    0U,
    P_Pong_WaitPing_DOS_INNER_1,
    NULL
};

PRT_TRANSDECL P_TRANS_2[] =
{
    { 0, &P_EVENT_Ping, 1, &_P_NO_OP }
};

#define P_STATE_SecureChild_Pong_WaitPing \
{ \
    "SecureChild.Pong_WaitPing", \
    1U, \
    0U, \
    &P_EVENTSET_Pong_WaitPing_DEFERS_1, \
    &P_EVENTSET_Pong_WaitPing_TRANS_1, \
    &P_EVENTSET_Pong_WaitPing_DOS_1, \
    P_TRANS_2, \
    NULL, \
    &P_FUNCTION_Anon_2, \
    &_P_NO_OP, \
}

PRT_EVENTDECL* P_Pong_SendingPong_DEFERS_INNER_1[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Pong_SendingPong_DEFERS_1 =
{
    0U,
    P_Pong_SendingPong_DEFERS_INNER_1,
    NULL
};

PRT_EVENTDECL* P_Pong_SendingPong_TRANS_INNER_1[] = { &P_EVENT_Success };
PRT_EVENTSETDECL P_EVENTSET_Pong_SendingPong_TRANS_1 =
{
    1U,
    P_Pong_SendingPong_TRANS_INNER_1,
    NULL
};

PRT_EVENTDECL* P_Pong_SendingPong_DOS_INNER_1[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Pong_SendingPong_DOS_1 =
{
    0U,
    P_Pong_SendingPong_DOS_INNER_1,
    NULL
};

PRT_TRANSDECL P_TRANS_3[] =
{
    { 1, &P_EVENT_Success, 2, &_P_NO_OP }
};

#define P_STATE_SecureChild_Pong_SendingPong \
{ \
    "SecureChild.Pong_SendingPong", \
    1U, \
    0U, \
    &P_EVENTSET_Pong_SendingPong_DEFERS_1, \
    &P_EVENTSET_Pong_SendingPong_TRANS_1, \
    &P_EVENTSET_Pong_SendingPong_DOS_1, \
    P_TRANS_3, \
    NULL, \
    &P_FUNCTION_Anon_3, \
    &_P_NO_OP, \
}

PRT_EVENTDECL* P_Done_DEFERS_INNER_1[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Done_DEFERS_1 =
{
    0U,
    P_Done_DEFERS_INNER_1,
    NULL
};

PRT_EVENTDECL* P_Done_TRANS_INNER_1[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Done_TRANS_1 =
{
    0U,
    P_Done_TRANS_INNER_1,
    NULL
};

PRT_EVENTDECL* P_Done_DOS_INNER_1[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Done_DOS_1 =
{
    0U,
    P_Done_DOS_INNER_1,
    NULL
};

#define P_STATE_SecureChild_Done \
{ \
    "SecureChild.Done", \
    0U, \
    0U, \
    &P_EVENTSET_Done_DEFERS_1, \
    &P_EVENTSET_Done_TRANS_1, \
    &P_EVENTSET_Done_DOS_1, \
    NULL, \
    NULL, \
    &_P_NO_OP, \
    &_P_NO_OP, \
}

PRT_STATEDECL P_SecureChild_STATES[] = { P_STATE_SecureChild_Pong_WaitPing, P_STATE_SecureChild_Pong_SendingPong, P_STATE_SecureChild_Done };

PRT_VALUE* P_Anon_IMPL_2(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_1 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PrtPrintf("Kirat");
    
    PRT_VALUE** P_LVALUE_1 = &(PTMP_tmp0_1);
    PrtFreeValue(*P_LVALUE_1);
    *P_LVALUE_1 = PrtCloneValue((&P_EVENT_Ping.value));
    
    PrtRaise(p_this, PTMP_tmp0_1, 0);
    *(&(PTMP_tmp0_1)) = NULL;
    goto p_return_2;
    
p_return_2: ;
    PrtFreeValue(PTMP_tmp0_1); PTMP_tmp0_1 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_2 =
{
    NULL,
    &P_Anon_IMPL_2,
    NULL
};


PRT_VALUE* P_Anon_IMPL_3(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_2 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_2 = &(PTMP_tmp0_2);
    PrtFreeValue(*P_LVALUE_2);
    *P_LVALUE_2 = PrtCloneValue((&P_EVENT_Success.value));
    
    PrtRaise(p_this, PTMP_tmp0_2, 0);
    *(&(PTMP_tmp0_2)) = NULL;
    goto p_return_3;
    
p_return_3: ;
    PrtFreeValue(PTMP_tmp0_2); PTMP_tmp0_2 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_3 =
{
    NULL,
    &P_Anon_IMPL_3,
    NULL
};


PRT_FUNDECL* P_SecureChild_METHODS[] = { &P_FUNCTION_Anon_2, &P_FUNCTION_Anon_3 };

PRT_EVENTDECL* P_SecureChild_RECV_INNER_1[] = { &P_EVENT_Ping, &P_EVENT_Pong, &P_EVENT_Success, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_SecureChild_RECV_1 =
{
    4U,
    P_SecureChild_RECV_INNER_1,
    NULL
};

PRT_EVENTDECL* P_SecureChild_SEND_INNER[] = { &P_EVENT_Ping, &P_EVENT_Pong, &P_EVENT_Success, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_SecureChild_SEND =
{
    4U,
    P_SecureChild_SEND_INNER,
    NULL
};

PRT_MACHINEDECL P_MACHINE_SecureChild = 
{
    1U,
    "SecureChild",
    &P_EVENTSET_SecureChild_RECV_1,
    &P_EVENTSET_SecureChild_SEND,
    NULL,
    0U,
    3U,
    2U,
    4294967295U,
    0U,
    NULL,
    P_SecureChild_STATES,
    P_SecureChild_METHODS
};

PRT_EVENTDECL* P_ALL_EVENTS[] = { &_P_EVENT_NULL_STRUCT, &_P_EVENT_HALT_STRUCT, &P_EVENT_Ping, &P_EVENT_Pong, &P_EVENT_Success };
PRT_MACHINEDECL* P_ALL_MACHINES[] = { &P_MACHINE_Pong, &P_MACHINE_SecureChild };
PRT_INTERFACEDECL* P_ALL_INTERFACES[] = { &P_I_Pong, &P_I_SecureChild };
PRT_FUNDECL* P_ALL_FUNCTIONS[] = { NULL };
PRT_FOREIGNTYPEDECL* P_ALL_FOREIGN_TYPES[] = { NULL };
int P_DefaultImpl_LME_0[] = { -1,-1 };
int P_DefaultImpl_LME_1[] = { -1,-1 };
int* P_DefaultImpl_LINKMAP[] = { P_DefaultImpl_LME_0, P_DefaultImpl_LME_1 };
int P_DefaultImpl_DEFMAP[] = { 0,1 };
PRT_PROGRAMDECL P_GEND_IMPL_DefaultImpl = {
    5U,
    2U,
    2U,
    0U,
    0U,
    P_ALL_EVENTS,
    P_ALL_MACHINES,
    P_ALL_INTERFACES,
    P_ALL_FUNCTIONS,
    P_ALL_FOREIGN_TYPES,
    P_DefaultImpl_LINKMAP,
    P_DefaultImpl_DEFMAP
};