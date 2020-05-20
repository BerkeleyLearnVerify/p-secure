# Code Architecture Overview


### Distributed Host Machine

The distributed host machine runs the `main` method in app.cpp first. This spawns a thread to listen for network requests from other distributed host machines. This also spawns the appropiate P Process to host USMs in this host and parses the command line instructions in order to create the first USM in the system or wait to receive a network message from the start distributed host. App.cpp contains all of the USM hosting code and various foreign functions to handle USM operations (such as USM creation, USM message sending). 

###### Network Request Processing in Distributed Host Machines
Network_simulator.cpp contains all of the functions for handling network socket requests and sending out network socket requests to other distributed host machines. Incoming requests are forwarded to the `send_network_request_API` in network_ra.cpp.

Network_ra.cpp contains the first layer of network processing logic. The `send_network_request_API` method creates a thread that calls the `network_request_logic`, which forwards the request to the `receiveNetworkRequest` method in app.cpp. 

`receiveNetworkRequest` in app.cpp forwards the request to `receiveNetworkRequestHelper` in helper.cpp. 


### KPS

The KPS distributed host machine runs the `main` method in app.cpp first. This spawns a thread that listens for network messages sent to the KPS for attestation requests and other functionality. The main KPS functionality is implemented in TODO