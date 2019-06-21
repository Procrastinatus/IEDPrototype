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

#include "mms_value.h"
#include "goose_publisher.h"
#include "hal_thread.h"

// These are for GOOSE
#include "goose_in.h"
#include "goose_out.h"

// These two are for MMS server module
#include "model/static_model.h"
#include "mms_server_module.h"

// has to be executed as root!

#define lo_interface "lo"

int
main(int argc, char** argv)
{
    /* import IEC 61850 device model created from SCL-File */
    //extern IedModel iedModel;
    //IedServer iedServer = NULL;
    //iedServer = IedServer_create(&iedModel);
    
    //Start threads for different modules (GOOSE Receiver, GOOSE Publisher, MMS Server)
    pthread_t goose_publisher_thread, goose_receiver_thread, mms_server_thread;
    int goose_publ_thread_id, goose_recv_thread_id, mms_server_thread_id;

    //goose_publ_thread_id = pthread_create(&goose_publisher_thread, NULL, start_goose_publisher, &argv); 
    goose_recv_thread_id = pthread_create(&goose_receiver_thread, NULL, start_goose_receiver, NULL); 
    mms_server_thread_id = pthread_create(&mms_server_thread, NULL, start_mms_server, NULL); 
    //pthread_join(goose_publisher_thread, NULL); 
    pthread_join(goose_receiver_thread, NULL); 
    pthread_join(mms_server_thread, NULL); 
    printf("Reached main exit");
    //start_goose_publisher(0, argv);
    //start_goose_receiver(0, argv);
}