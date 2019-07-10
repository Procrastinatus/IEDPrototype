/*
 * sv_subscriber_example.c
 *
 * Example program for Sampled Values (SV) subscriber
 *
 */

#include "hal_thread.h"
#include <signal.h>
#include <stdio.h>
#include "sv_subscriber.h"
#include "sv_in.h"

static bool running = true;

void sv_in_sigint_handler(int signalId) {
    running = 0;
}

/* Callback handler for received SV messages */
static void
svUpdateListener(SVSubscriber subscriber, void* parameter, SVSubscriber_ASDU asdu) {
    //printf("svUpdateListener called\n");
    const char* svID = SVSubscriber_ASDU_getSvId(asdu);
    if (svID != NULL)
        //printf("  svID=(%s)\n", svID);
        //printf("  smpCnt: %i\n", SVSubscriber_ASDU_getSmpCnt(asdu));
        //printf("  confRev: %u\n", SVSubscriber_ASDU_getConfRev(asdu));

        /*
         * Access to the data requires a priori knowledge of the data set.
         * For this example we assume a data set consisting of FLOAT32 values.
         * A FLOAT32 value is encoded as 4 bytes. You can find the first FLOAT32
         * value at byte position 0, the second value at byte position 4, the third
         * value at byte position 8, and so on.
         *
         * To prevent damages due configuration, please check the length of the
         * data block of the SV message before accessing the data.
         */
        if (SVSubscriber_ASDU_getDataSize(asdu) >= 24) {
            //printf("   DATA[0]: %f\n", SVSubscriber_ASDU_getFLOAT32(asdu, 0));
            //printf("   DATA[1]: %f\n", SVSubscriber_ASDU_getFLOAT32(asdu, 4));
            //printf("   DATA[2]: %f\n", SVSubscriber_ASDU_getFLOAT32(asdu, 8));
            //printf("   DATA[3]: %f\n", SVSubscriber_ASDU_getFLOAT32(asdu, 12));
            float received_sv_vals[6];
            for (int i = 0; i < 6; i++) {
                received_sv_vals[i] = SVSubscriber_ASDU_getFLOAT32(asdu, 4 * i);
            }
            sv_update_mx_values(received_sv_vals);
            sv_raise_alarm(received_sv_vals);
        }

}

int
start_sv_receiver(void* arguments) {
    Arg_pack* args = arguments;
    char* ethernetIfcID = NULL;
    ethernetIfcID = args->interface;

    SVReceiver receiver = SVReceiver_create();
    SVReceiver_setInterfaceId(receiver, ethernetIfcID);

    /* Create a subscriber listening to SV messages with APPID 4000h */
    //SVSubscriber subscriber = SVSubscriber_create(NULL, 0x4000);
    SVSubscriber subscriber = SVSubscriber_create(NULL, args->sv_appid);

    /* Install a callback handler for the subscriber */
    SVSubscriber_setListener(subscriber, svUpdateListener, NULL);

    /* Connect the subscriber to the receiver */
    SVReceiver_addSubscriber(receiver, subscriber);

    /* Start listening to SV messages - starts a new receiver background thread */
    SVReceiver_start(receiver);

    signal(SIGINT, sv_in_sigint_handler);

    while (running)
        Thread_sleep(1);

    SVReceiver_stop(receiver);
    SVReceiver_destroy(receiver);
}