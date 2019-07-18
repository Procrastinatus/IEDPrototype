Instructions:

Run the included modified sv_publisher with this IED prototype and observe the "Status" and "Measurement" GOOSE blocks.

Each instance only runs ONE IED. You have to use a bash script of some sort to run multiple IEDs.
There are usable bash scripts in dist/Debug/GNU-Linux that allow you to start & stop multiple IEDs.

Usage:
sudo ./iedprototype -p \<port\> -i \<interface\> -n \<IED number\> -z \<GOOSE_APPID\> \[-x \<gocbref\>\] -c \<SV_APPID\> 

-p flag determines the port that the MMS server runs on.
MMS servers typically run on TCP port 102.

-i is the interface to run the IED on. 

-f is an optional flag which simulates circuit breaker failure (msut be used with included modified sv_publisher).

e.g. ./iedprototype -p 102 -i lo -z 4096 -x LIED10CTRL/LLN0\$GO\$Status -x LIED10PROT/LLN0\$GO\$Alarm -x LIED10MEAS/LLN0\$GO\$Meas -c 4096 

You may have to escape the dollar signs for the gocbRef(s).

Compiled with Netbeans + GCC on Ubuntu 18.04, not tested with Windows.
