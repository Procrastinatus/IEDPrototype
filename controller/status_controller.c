/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "status_controller.h"

extern IedServer iedServer;

void status_controller_main(char* gocbRef, MmsValue* values) {
    IedServer_lockDataModel(iedServer);
    if (strcmp("LIED10CTRL/LLN0$GO$Status", gocbRef) == 0) {
        update_status(values);
        //printf("%s received, updated status values!\n ", block);
    }
    IedServer_unlockDataModel(iedServer);
    Thread_sleep(100);
}

void update_status(MmsValue* values) {
    /* UNUSED FOR NOW */
}