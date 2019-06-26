Instructions:

Each instance only runs ONE IED. You have to use a bash script of some sort to run multiple IEDs.
There are usable bash scripts in dist/Debug/GNU-Linux that allow you to start & stop multiple IEDs.

The current prototype IED has a bundled (MMS Server + GOOSE Publisher) module, and a GOOSE Receiver module.

Usage:
sudo ./iedprototype -p \<port\> -i \<interface\> -n \<IED number\> 

-p flag determines the port that the MMS server runs on.
MMS servers typically run on TCP port 102.

-i is the interface to run the (MMS server + GOOSE Publisher) + GOOSE Receiver on. 
(TODO: Check if correct interface is used.)

-n determines the IED ID. It's simply for distinguishing IEDs.
e.g. If you pass 1 as the argument to -n, the GOOSE message should show gocbRef "PHY1LDEV".
Note the "1" in "PHY1LDEV".

Compiled with Netbeans + GCC on Ubuntu 18.04, not tested with Windows.
