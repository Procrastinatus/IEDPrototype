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

// These are for GOOSE
#include "goose_in.h"

// These two are for MMS server module
#include "model/static_model.h"
#include "model/dynamic_model.h"
#include "mms_server_module.h"

#include "model/custom_structs.h"

// has to be executed as root!

void main_sigint_handler(int dummy) {
    printf("ctrl+c/SIGINT caught, exiting...");
}

int
main(int argc, char** argv) {
    printf("Usage: -p <port> -i <interface> -n <IED number> \n");
    printf("The -n flag is simply for distinguishing IEDs, i.e. the physical device name will change. \n");
    printf("port may be opened on ALL interfaces (TODO: check) \n");

    signal(SIGINT, &main_sigint_handler);    
    //Initialise struct instance with default values
    Arg_pack args = {
        .interface = NULL,
        .start_port = 0,
        .n = 0
    };

    //Parse cmd-line arguments
    while ((args.opt = getopt(argc, argv, "p:i:n:")) != -1) {
        switch (args.opt) {
            case 'p':{
                args.start_port = atoi(optarg);
                break;
            }
            case 'n':{
                args.n = atoi(optarg);
                break;
            }
            case 'i':{
                args.interface = optarg;
                break;
            }
            case ':':  {
                printf("option needs a value\n");  
                break;  
            }
            case '?':  {
                printf("unknown option: %c\n", optopt); 
                break;  
            }
            default:{
                printf("No arguments! \n");
                break;
            }
        }
    }

    printf("Starting port is %d, IED ID (n) is %d, interface is %s \n", args.start_port, args.n, args.interface);
    printf("It has a few modules: a GOOSE receiver, and a (MMS server + GOOSE Publisher) bundled module. \n");

    pthread_t goose_receiver_thread, mms_server_thread;
    int goose_recv_thread_id, mms_server_thread_id;

    goose_recv_thread_id = pthread_create(&goose_receiver_thread, NULL, start_goose_receiver, (void*)&args); 
    //Note that there is a start_static_mms_server() if you wish to use a static model.
    mms_server_thread_id = pthread_create(&mms_server_thread, NULL, start_dynamic_mms_server, (void*)&args); 
    pthread_join(mms_server_thread, NULL); 
    
    printf("Reached main exit\n");
    return (0);
}
