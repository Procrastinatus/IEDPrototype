/*
 * sv_subscriber_example.c
 *
 * Example program for Sampled Values (SV) subscriber
 *
 */

#include <signal.h>
#include <stdio.h>
#include "hal_thread.h"
#include "sv_publisher.h"

static bool running = true;

void sigint_handler(int signalId)
{
    running = 0;
}

int
main(int argc, char** argv)
{
    char* interface;
  
    if (argc > 1)
        interface = argv[1];
    else
        interface = "eth0";
  
    printf("Using interface %s\n", interface);

    SVPublisher svPublisher = SVPublisher_create(NULL, interface);

    SVPublisher_ASDU asdu1 = SVPublisher_addASDU(svPublisher, "svpub1", NULL, 1);

    int float1 = SVPublisher_ASDU_addFLOAT(asdu1);
    int float2 = SVPublisher_ASDU_addFLOAT(asdu1);
    int float3 = SVPublisher_ASDU_addFLOAT(asdu1);
    int float4 = SVPublisher_ASDU_addFLOAT(asdu1);
    int float5 = SVPublisher_ASDU_addFLOAT(asdu1);
    int float6 = SVPublisher_ASDU_addFLOAT(asdu1);
    int ts1 = SVPublisher_ASDU_addTimestamp(asdu1);

    SVPublisher_setupComplete(svPublisher);

    float fVal1 = 500.0f;
    float fVal2 = 450.0f;
    float fVal3 = 550.0f;
    float fVal4 = 10.0f;
    float fVal5 = 9.5f;
    float fVal6 = 10.5f;
    bool fVal1_inc = true;
    bool fVal2_inc = true;
    bool fVal3_inc = true;
    bool fVal4_inc = true;
    bool fVal5_inc = true;
    bool fVal6_inc = true;

    while (running) {
        Timestamp ts;
        Timestamp_clearFlags(&ts);
        Timestamp_setTimeInMilliseconds(&ts, Hal_getTimeInMs());

        SVPublisher_ASDU_setFLOAT(asdu1, float1, fVal1);
        SVPublisher_ASDU_setFLOAT(asdu1, float2, fVal2);
        SVPublisher_ASDU_setFLOAT(asdu1, float3, fVal3);
        SVPublisher_ASDU_setFLOAT(asdu1, float4, fVal4);
        SVPublisher_ASDU_setFLOAT(asdu1, float5, fVal5);
        SVPublisher_ASDU_setFLOAT(asdu1, float6, fVal6);

        SVPublisher_ASDU_setTimestamp(asdu1, ts1, ts);

        SVPublisher_ASDU_increaseSmpCnt(asdu1);

	if(fVal1>=600.0f){fVal1_inc = false;}
	if(fVal1<=400.0f){fVal1_inc = true;}
	if(!fVal1_inc){fVal1 -= 1.1f;} else {fVal1 += 1.1f;}

	if(fVal2>=600.0f){fVal2_inc = false;}
	if(fVal2<=400.0f){fVal2_inc = true;}
	if(!fVal2_inc){fVal1 -= 2.1f;} else {fVal2 += 2.1f;}

	if(fVal3>=600.0f){fVal3_inc = false;}
	if(fVal3<=400.0f){fVal3_inc = true;}
	if(!fVal3_inc){fVal3 -= 3.1f;} else {fVal3 += 3.1f;}

	/* NOTE For voltages we remove 3 zeros (KILOvolt) because of float limits */
	if(fVal4>=11.0f){fVal4_inc = false;}
	if(fVal4<=9.0f){fVal4_inc = true;}
	if(!fVal4_inc){fVal4 -= 0.11f;} else {fVal4 += 0.11f;}

	if(fVal5>=11.0f){fVal5_inc = false;}
	if(fVal5<=9.0f){fVal5_inc = true;}
	if(!fVal5_inc){fVal5 -= 0.21f;} else {fVal5 += 0.21f;}

	if(fVal6>=11.0f){fVal6_inc = false;}
	if(fVal6<=9.0f){fVal6_inc = true;}
	if(!fVal6_inc){fVal6 -= 0.31f;} else {fVal6 += 0.31f;}

        SVPublisher_publish(svPublisher);

        Thread_sleep(100);
    }

    SVPublisher_destroy(svPublisher);
}
