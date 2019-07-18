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
    Arg_pack* args = parameter;
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
            //printf("   DATA[0]: %f      ", SVSubscriber_ASDU_getFLOAT32(asdu, 0));
            //printf("   DATA[1]: %f      ", SVSubscriber_ASDU_getFLOAT32(asdu, 4));
            //printf("   DATA[2]: %f      ", SVSubscriber_ASDU_getFLOAT32(asdu, 8));
            //printf("   DATA[3]: %f      ", SVSubscriber_ASDU_getFLOAT32(asdu, 12));
            //printf("   DATA[4]: %f      ", SVSubscriber_ASDU_getFLOAT32(asdu, 16));
            //printf("   DATA[5]: %f\n", SVSubscriber_ASDU_getFLOAT32(asdu, 20));
            
            float received_sv_vals[6];
            for (int i = 0; i < 6; i++) {
                received_sv_vals[i] = SVSubscriber_ASDU_getFLOAT32(asdu, 4 * i);
            }
            
            /* Update Data Model */
            /* Second argument is the length (no. of ele) of the array */
            sv_update_meas_values(received_sv_vals, 6);
            
            /* Store latest N sampled values for determining if OC has occurred */
            /* First float is current, second float is voltage */
            /* Store phsA values */
            /* For now assume ballpark current of 500A and voltage of 10(KILO)V*/
            store_sampled_value(received_sv_vals[0], received_sv_vals[3]);
            
            /* Check if there is OC */
            overcurrent_controller_main(args->cb_fail);
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
    SVSubscriber subscriber = SVSubscriber_create(NULL, args->sv_in_appid);

    /* Install a callback handler for the subscriber */
    /* For arguments being passed, we currently use args.cb_fail only */
    SVSubscriber_setListener(subscriber, svUpdateListener, arguments);

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