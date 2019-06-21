/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * goose_subscriber_example.c
 *
 * This is an example for a standalone GOOSE subscriber
 *
 * Has to be started as root in Linux.
 */

#include "goose_receiver.h"
#include "goose_subscriber.h"
#include "hal_thread.h"

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include "goose_in.h"
#include "model/static_model.h"
#include "mms_server_module.h"
#include "mms_value.h"

/* import IEC 61850 device mod */
extern IedModel iedModel;
extern IedServer iedServer;

static int running = 1;

void goose_in_sigint_handler(int signalId)
{
    running = 0;
}

void
gooseListener(GooseSubscriber subscriber, void* parameter)
{
    printf("GOOSE event:\n");
    printf("  stNum: %u sqNum: %u\n", GooseSubscriber_getStNum(subscriber),
            GooseSubscriber_getSqNum(subscriber));
    printf("  timeToLive: %u\n", GooseSubscriber_getTimeAllowedToLive(subscriber));

    uint64_t timestamp = GooseSubscriber_getTimestamp(subscriber);

    printf("  timestamp: %u.%u\n", (uint32_t) (timestamp / 1000), (uint32_t) (timestamp % 1000));

    MmsValue* values = GooseSubscriber_getDataSetValues(subscriber);

    char buffer[1024];

    MmsValue_printToBuffer(values, buffer, 1024);

    printf("%s\n", buffer);
    
    //controlHandlerForBinaryOutput(IEDMODEL_GenericIO_GGIO1_SPCSO1, MmsValue_newIntegerFromInt32(5));
    //Try modifying model directly?
    //DA Changes = Immediately send out GOOSE?
    printf("Attempting to change some data attribute...\n");
    IedServer_updateAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_AnIn2_mag_f, MmsValue_newFloat(5));
}

int
start_goose_receiver(int argc, char** argv)
{
    GooseReceiver receiver = GooseReceiver_create();

    printf("GOOSE RECEIVER Using interface (lo)\n");
    GooseReceiver_setInterfaceId(receiver, "lo");

    //printf("Addr of EXTERN iedServer is %p\n",&iedServer);
    
    GooseSubscriber subscriber = GooseSubscriber_create("simpleIOGenericIO/LLN0$GO$gcbAnalogValues", NULL);

    //GooseSubscriber_setAppId(subscriber, 1000);
    GooseSubscriber_setAppId(subscriber, 4096);

    GooseSubscriber_setListener(subscriber, gooseListener, NULL);

    GooseReceiver_addSubscriber(receiver, subscriber);

    GooseReceiver_start(receiver);

    signal(SIGINT, goose_in_sigint_handler);

    while (running) {
        Thread_sleep(100);
    }

    GooseReceiver_stop(receiver);

    GooseReceiver_destroy(receiver);
}