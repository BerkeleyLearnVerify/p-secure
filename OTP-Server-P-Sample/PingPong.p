event Success;
event Failure;

event OTPSecretMsg assert 1: (machine, int);
event OTPSecretReceived;
event OTPCodeMsg assert 1: int;
event OTPCodeValidated;
event OTPCodeFailed;

machine BANK_SERVER 
{
    var clientOtpGenerator: machine;

    // This is the entry point.
    start state Init {
        entry (payload:any) {
          clientOtpGenerator = payload as machine;
          raise (Success);   	   
        }
        on Success goto GenerateOTPSecret;
    }

    state GenerateOTPSecret {
        entry {
			// generate OTP secret 
			var secret : int;
			secret = 123456788;
			send clientOtpGenerator, OTPSecretMsg, (this, secret);
	    }
        on OTPSecretReceived goto WaitOTPCode;
     }

     state WaitOTPCode {
        on OTPCodeMsg goto ValidateOTPCode;
     }

	 state ValidateOTPCode {
        entry (payload: int) {
		  // validate OTP code
		  if (payload == 123456789) {
			send clientOtpGenerator, OTPCodeValidated;
          	raise (Success);  
		  } else  {
			send clientOtpGenerator, OTPCodeFailed;
			raise (Failure);
		  }  
        }
		on Success goto Done;
		on Failure goto WaitOTPCode;
     }

     state Done {}
}

machine CLIENT_OTP_GENERATOR
{
	var bankServer : machine;
	var OTPSecret: int;

    start state Init {
        on OTPSecretMsg goto HandleOTPSecret;
    }

    state HandleOTPSecret {
	    entry (payload: (machine, int)) {
	        bankServer = payload.0;
			OTPSecret = payload.1;
			send bankServer, OTPSecretReceived;
			raise (Success);	 	  
	    }
        on Success goto GenerateOTPCode;
    }

	state GenerateOTPCode {
	    entry {
			send bankServer, OTPCodeMsg, OTPSecret + 1;
	    }
        on OTPCodeValidated goto End;
		on OTPCodeFailed goto GenerateOTPCode;
    }
	
	state End {
		entry {
			raise(halt);
		}
	}
}

spec M observes Success {
    start state initialState {

    }
}

fun _CREATEMACHINE(cner: machine, typeOfMachine: int, param : any, newMachine: machine) : machine
{
	if(typeOfMachine == 1)
	{
		newMachine = new BANK_SERVER(param);
	}
	else if(typeOfMachine == 2)
	{
		newMachine = new CLIENT_OTP_GENERATOR();
	}
	else
	{
		assert(false);
	}
	return newMachine;
}

machine IntializerMachine
{
	var container : machine;
    var clientMachine: machine;

    start state Init {
	    entry {
			container = _CREATECONTAINER();
			clientMachine = _CREATEMACHINE(container, 2, null, null as machine);
			container = _CREATECONTAINER();
			_CREATEMACHINE(container, 1, clientMachine, null as machine); //Create bank server
	    }
	}
}
