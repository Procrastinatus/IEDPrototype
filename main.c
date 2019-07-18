/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: root
 *
 * Created on June 14, 2019, 11:22 AM
 */

/*
 * goose_publisher_example.c
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h> 
#include <unistd.h>
#include <getopt.h>

#include "mms_value.h"
#include "goose_publisher.h"
#include "hal_thread.h"

#include "goose_in.h"
#include "sv_in.h"

// These two are for MMS server module
#include "model/dynamic_model.h"
#include "ied_server.h"

#include "model/custom_structs.h"

// has to be executed as root!

/* Global variable for goCb AppIDs in static model */

void main_sigint_handler(int dummy) {
    printf("ctrl+c/SIGINT caught, exiting...");
}

int
main(int argc, char** argv) {
    printf("Usage: -p <port> -i <interface> [-z <goose_in_appid>] [-x <gocbRef>] -c <sv_in_appid> \n");
    printf("Optional Args: -f (simulate breaker failure) \n ");
    printf("e.g. ./iedprototype -p 102 -i lo -z 0x1000 -z 0x1001 -z 0x1002 -x LIED10CTRL/LLN0\$GO\$Status -x LIED10PROT/LLN0\$GO\$Alarm -x LIED10MEAS/LLN0\$GO\$Meas -c 0x4000 \n");
    printf("\nIMPT: Notice 0x1000 corresponds to LIED10CTRL...$Status, 0x1001 to LIED10PROT...$Alarm, and 0x1002 to LIED10MEAS...$Meas\n");
    printf("The order of -z flags must correspond to the -x flags, use Wireshark to make sure you're listening to correct AppID(s) and gocbRef(s). \n");
    //printf("The -n flag is simply for distinguishing IEDs, i.e. the physical device name will change. \n");
    printf("\nTry escaping the $ signs with a backslash if you can't subscribe to the GOOSE packet(s). \n");
    printf("-z, -x, -c, are identifiers for LISTENING (e.g. listen for GOOSE/SV pkts with AppID=0x1000)\n\n");
    //printf("-o flag is optional and is used to specify OUTGOING Goose AppID(s). \n ");

    signal(SIGINT, &main_sigint_handler);

    //Initialise struct instance
    Arg_pack args = {
        .interface = NULL,
        .start_port = 0,
        .n = 0,
        //.goose_in_appid = 0,
        .goose_in_appid = LinkedList_create(),
        .goose_out_appid = LinkedList_create(),
        .go_cb_refs = LinkedList_create(),
        .sv_in_appid = 0,
        .cb_fail = false
    };

    //Parse cmd-line arguments
    while ((args.opt = getopt(argc, argv, "p:i:n:z:x:c:f")) != -1) {
        switch (args.opt) {
            case 'c':
            {
                /* This is for SV APPID */
                args.sv_in_appid = strtol(optarg, NULL, 16);
                break;
            }
            case 'f':
            {
                /* Simulate CB failure (alarm enabled but CB doesn't open) */
                printf("\n SIMULATING BREAKER FAILURE (alarm on but CB doesn't open) \n");
                args.cb_fail = true;
                break;
            }
            case 'i':
            {
                args.interface = optarg;
                break;
            }
            case 'm':
            {
                //printf("model = (s)tatic or (d)ynamic");
                //args.mode = optarg;
                break;
            }
            case 'n':
            {
                //n may still be used for differentiating IED names (dynamic model)
                //args.n = atoi(optarg);
                break;
            }
            case 'o':
            {
                /* This is for OUTGOING Goose AppIDs */
                //args.goose_out_appid = strtol(optarg, NULL, 16);
                //LinkedList_add(args.goose_out_appid, strtol(optarg, NULL, 16));
                break;
            }
            case 'p':
            {
                args.start_port = atoi(optarg);
                break;
            }
            case 'x':
            {
                /* This is for GOOSE Control Block References */
                LinkedList_add(args.go_cb_refs, optarg);
                break;
            }
            case 'z':
            {
                /* This is for GOOSE APPID */
                //args.goose_in_appid = strtol(optarg, NULL, 16);
                LinkedList_add(args.goose_in_appid, strtol(optarg, NULL, 16));
                break;
            }
            case ':':
            {
                printf("option needs a value\n");
                break;
            }
            case '?':
            {
                printf("unknown option: %c\n", optopt);
                break;
            }
            default:
            {
                printf("No arguments! \n");
                break;
            }
        }
    }

    for (; optind < argc; optind++) {
        //Do something if using extra options
    }

    printf("Starting port is %d, interface is %s \n", args.start_port, args.interface);
    //printf("GOOSE AppID is 0x%x\n", args.goose_in_appid);
    printf("Listening to SV, AppID: 0x%x\n", args.sv_in_appid);

    for (int i = 0; i < LinkedList_size(args.goose_in_appid); i++) {
        printf("Listening to GOOSE, gocbRef: %s, AppID: 0x%x\n",
                (char*) LinkedList_getData(LinkedList_get(args.go_cb_refs, i)),
                (uint16_t*) LinkedList_getData(LinkedList_get(args.goose_in_appid, i)));
    }

    pthread_t goose_receiver_thread, mms_server_thread, sv_receiver_thread;
    int goose_recv_thread_id, ied_server_thread_id, sv_recv_thread_id;

    /* Start GOOSE Receiver */
    goose_recv_thread_id = pthread_create(&goose_receiver_thread, NULL, start_goose_receiver, (void*) &args);

    /* IED Server = (MMS Server + GOOSE Publisher) Bundle */
    ied_server_thread_id = pthread_create(&mms_server_thread, NULL, start_static_ied_server, (void*) &args);

    /* Start SV Receiver */
    sv_recv_thread_id = pthread_create(&sv_receiver_thread, NULL, start_sv_receiver, (void*) &args);

    pthread_join(mms_server_thread, NULL);
    printf("Reached main exit\n");
    return (0);
}
