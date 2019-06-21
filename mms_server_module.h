/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mms_server_module.h
 * Author: root
 *
 * Created on June 17, 2019, 5:20 PM
 */

#ifndef MMS_SERVER_MODULE_H
#define MMS_SERVER_MODULE_H


#include "model/static_model.h"
#include "iec61850_server.h"

extern IedServer iedServer;

void mms_server_module_handler(int signalId);
void controlHandlerForBinaryOutput(void* parameter, MmsValue* value);
int start_mms_server();



#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif

#endif /* MMS_SERVER_MODULE_H */

