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

    float fVal1 = 1234.5678f;
    float fVal2 = 0.12345f;
    float fVal3 = 333.333f;
    float fVal4 = 4444.4444f;
    float fVal5 = 555.555f;
    float fVal6 = 6666.6666f;

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

        fVal1 += 1.1f;
        fVal2 += 0.1f;
        fVal3 += 1.1f;
        fVal4 += 0.1f;
        fVal5 += 1.1f;
        fVal6 += 0.1f;

        SVPublisher_publish(svPublisher);

        Thread_sleep(50);
    }

    SVPublisher_destroy(svPublisher);
}
