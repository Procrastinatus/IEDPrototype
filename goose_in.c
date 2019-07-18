#include "goose_receiver.h"
#include "goose_subscriber.h"
#include "hal_thread.h"

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include "goose_in.h"
//#include "model/static_model.h"
#include "model/LIED10_model.h"
#include "ied_server.h"
#include "mms_value.h"

#include "controller/ctrl_controller.h"
#include "controller/prot_controller.h"
#include "controller/meas_controller.h"
#include "controller/overcurrent_controller.h"
#include "controller/cb_failure_controller.h"

/* import IEC 61850 device mod */
extern IedModel iedModel;

//For static model LIED10_model
Received_goose_data new_vals;

static int running = 0;

void goose_in_sigint_handler(int signalId)
{
    running = 0;
}

void
gooseListener(GooseSubscriber subscriber, void* parameter)
{
    /* Note that parameter is currently just a char* of the gocbRef */
    printf("=====\nGocbRef Found: %s \n",(char*)parameter);
    printf("GOOSE vendor event:\n");
    printf("  stNum: %u sqNum: %u\n", GooseSubscriber_getStNum(subscriber),
            GooseSubscriber_getSqNum(subscriber));
    printf("  timeToLive: %u\n", GooseSubscriber_getTimeAllowedToLive(subscriber));
    uint64_t timestamp = GooseSubscriber_getTimestamp(subscriber);
    printf("  timestamp: %u.%u\n", (uint32_t) (timestamp / 1000), (uint32_t) (timestamp % 1000));
    MmsValue* values = GooseSubscriber_getDataSetValues(subscriber);
    char buffer[1024];
    MmsValue_printToBuffer(values, buffer, 1024);
    printf("GOOSE values : %s\n", buffer);
    //printf("This dataset is of MMSTYPE: %i \n", MmsValue_getType(values));
    
    /* Callback controllers for received GOOSE data */
    /* parameter=gocbRef, values=values in GOOSE block */
    breaker_failure_controller_main(subscriber, parameter, values);
}

int
start_goose_receiver(void* arguments)
{
    Arg_pack* args = arguments; 
    char* ethernetIfcID = NULL;
    ethernetIfcID = args->interface;    
    GooseReceiver receiver = GooseReceiver_create();
    //printf("GOOSE RECEIVER Using interface %s\n", ethernetIfcID);
    GooseReceiver_setInterfaceId(receiver, ethernetIfcID);
    
    /* Get gocbrefs from args*/
    GooseSubscribers goose_subscribers;
    goose_subscribers.subscribers = LinkedList_create();
    GooseSubscriber tmp_subscriber;
    
    int no_of_gocbref = LinkedList_size(args->go_cb_refs);
    
    for(int i=0; i < no_of_gocbref; i++){        
        char* current_gocbref = LinkedList_getData(LinkedList_get(args->go_cb_refs, i)); 
        tmp_subscriber = GooseSubscriber_create(current_gocbref, NULL);
        //Check APPID from publisher matches subscribers!  
        
        /* This is for multiple GOOSE blocks with SAME AppIDs */
        //GooseSubscriber_setAppId(tmp_subscriber, args->goose_in_appid);
        
        /* This is for multiple GOOSE blocks with UNIQUE AppIDs */
        uint16_t current_appid = LinkedList_getData(LinkedList_get(args->goose_in_appid, i));
        GooseSubscriber_setAppId(tmp_subscriber, current_appid);
        
        GooseSubscriber_setListener(tmp_subscriber, gooseListener, current_gocbref);
        
        GooseReceiver_addSubscriber(receiver, tmp_subscriber);
        LinkedList_add(goose_subscribers.subscribers,tmp_subscriber);
    }
    
    GooseReceiver_start(receiver);
    running = 1;
    signal(SIGINT, goose_in_sigint_handler);
    while (running) {
        Thread_sleep(100);
    }
    GooseReceiver_stop(receiver);
    GooseReceiver_destroy(receiver);
}