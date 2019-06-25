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
}

void
gooseExampleListener(GooseSubscriber subscriber, void* parameter)
{
    printf("GOOSE ANALOG event:\n");
    printf("  stNum: %u sqNum: %u\n", GooseSubscriber_getStNum(subscriber),
            GooseSubscriber_getSqNum(subscriber));
    printf("  timeToLive: %u\n", GooseSubscriber_getTimeAllowedToLive(subscriber));
    uint64_t timestamp = GooseSubscriber_getTimestamp(subscriber);
    printf("  timestamp: %u.%u\n", (uint32_t) (timestamp / 1000), (uint32_t) (timestamp % 1000));
    MmsValue* values = GooseSubscriber_getDataSetValues(subscriber);
    char buffer[1024];
    MmsValue_printToBuffer(values, buffer, 1024);
    printf("Analog values : %s\n", buffer);
    //if (GooseSubscriber_getSqNum(subscriber)==0 && GooseSubscriber_getStNum(subscriber)>1){
        printf("stNum increased, sqNum reset, Attempting to change some data attribute...\n");
        printf("Changing HARD-CODED DA (Data Attr.): GGIO_AnIn2_mag_f \n");
        int received_val = MmsValue_toInt32(MmsValue_getElement(values,0));
        float new_anin2_mag_f = (float)received_val;
        //IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_AnIn2_mag_f, new_anin2_mag_f);
    //};
    
}

int
start_goose_receiver(char* interface)
{
    iedServer = IedServer_create(&iedModel);
    char* ethernetIfcID = NULL;
    if(interface!=NULL)
        ethernetIfcID = interface;
    else
        ethernetIfcID = "lo";
    
    GooseReceiver receiver = GooseReceiver_create();

    printf("GOOSE RECEIVER Using interface %s\n", ethernetIfcID);
    GooseReceiver_setInterfaceId(receiver, ethernetIfcID);
    
    //Make sure APPID from publisher matches that of subscribers!
    
    //GooseSubscriber event_subscriber = GooseSubscriber_create("simpleIOGenericIO/LLN0$GO$gcbEvents", NULL);
    //GooseSubscriber_setAppId(event_subscriber, 4096);
    //GooseSubscriber_setListener(event_subscriber, gooseListener, NULL);   
    //GooseReceiver_addSubscriber(receiver, event_subscriber);
    
    GooseSubscriber subscriber = GooseSubscriber_create("simpleIOGenericIO/LLN0$GO$gcbAnalogValues", NULL);
    GooseSubscriber_setAppId(subscriber, 1000);
    GooseSubscriber_setListener(subscriber, gooseExampleListener, NULL);
    GooseReceiver_addSubscriber(receiver, subscriber);

    GooseReceiver_start(receiver);

    signal(SIGINT, goose_in_sigint_handler);

    while (running) {
        Thread_sleep(100);
    }

    GooseReceiver_stop(receiver);

    GooseReceiver_destroy(receiver);
}