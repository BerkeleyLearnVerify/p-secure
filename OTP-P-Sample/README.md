# OTP Server in P

Commands Needed to Run:

`dotnet ~/Research/P/Bld/Drops/Release/Binaries/Pc.dll *.p && cmake CMakeLists.txt && make && ./otp_server`


Output:

CreateLog> Machine IntializerMachine(1) is created

StateLog> Machine IntializerMachine(1) entered state IntializerMachine.Init

CreateLog> Machine CLIENT_OTP_GENERATOR(2) is created

StateLog> Machine CLIENT_OTP_GENERATOR(2) entered state CLIENT_OTP_GENERATOR.Init

CreateLog> Machine BANK_SERVER(3) is created

StateLog> Machine BANK_SERVER(3) entered state BANK_SERVER.Init

RaiseLog> Machine BANK_SERVER(3) raised event Success with payload null

ExitLog> Machine BANK_SERVER(3) exiting state BANK_SERVER.Init

StateLog> Machine BANK_SERVER(3) entered state BANK_SERVER.GenerateOTPSecret

EnqueueLog> Enqueued event OTPSecretMsg with payload ( (1, 0, 0, 0), 3>, 123456788) on Machine CLIENT_OTP_GENERATOR(2)

DequeueLog> Dequeued event OTPSecretMsg with payload ( (1, 0, 0, 0), 3>, 123456788) by Machine CLIENT_OTP_GENERATOR(2)

ExitLog> Machine CLIENT_OTP_GENERATOR(2) exiting state CLIENT_OTP_GENERATOR.Init

StateLog> Machine CLIENT_OTP_GENERATOR(2) entered state CLIENT_OTP_GENERATOR.HandleOTPSecret

EnqueueLog> Enqueued event OTPSecretReceived with payload null on Machine BANK_SERVER(3)

RaiseLog> Machine CLIENT_OTP_GENERATOR(2) raised event Success with payload null

ExitLog> Machine CLIENT_OTP_GENERATOR(2) exiting state CLIENT_OTP_GENERATOR.HandleOTPSecret

StateLog> Machine CLIENT_OTP_GENERATOR(2) entered state CLIENT_OTP_GENERATOR.GenerateOTPCode

EnqueueLog> Enqueued event OTPCodeMsg with payload 123456789 on Machine BANK_SERVER(3)

DequeueLog> Dequeued event OTPSecretReceived with payload null by Machine BANK_SERVER(3)

ExitLog> Machine BANK_SERVER(3) exiting state BANK_SERVER.GenerateOTPSecret

StateLog> Machine BANK_SERVER(3) entered state BANK_SERVER.WaitOTPCode

DequeueLog> Dequeued event OTPCodeMsg with payload 123456789 by Machine BANK_SERVER(3)

ExitLog> Machine BANK_SERVER(3) exiting state BANK_SERVER.WaitOTPCode

StateLog> Machine BANK_SERVER(3) entered state BANK_SERVER.ValidateOTPCode

EnqueueLog> Enqueued event OTPCodeValidated with payload null on Machine CLIENT_OTP_GENERATOR(2)

DequeueLog> Dequeued event OTPCodeValidated with payload null by Machine CLIENT_OTP_GENERATOR(2)

ExitLog> Machine CLIENT_OTP_GENERATOR(2) exiting state CLIENT_OTP_GENERATOR.GenerateOTPCode

StateLog> Machine CLIENT_OTP_GENERATOR(2) entered state CLIENT_OTP_GENERATOR.End

RaiseLog> Machine CLIENT_OTP_GENERATOR(2) raised event halt with payload null

ExitLog> Machine CLIENT_OTP_GENERATOR(2) exiting state CLIENT_OTP_GENERATOR.End

HaltLog> Machine CLIENT_OTP_GENERATOR(2) halted in state CLIENT_OTP_GENERATOR.End

RaiseLog> Machine BANK_SERVER(3) raised event Success with payload null

ExitLog> Machine BANK_SERVER(3) exiting state BANK_SERVER.ValidateOTPCode

StateLog> Machine BANK_SERVER(3) entered state BANK_SERVER.Done