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
#include "model/custom_structs.h"

extern IedServer iedServer;
void mms_server_module_handler(int signalId);
void controlHandlerForBinaryOutput(void* parameter, MmsValue* value);
static MmsDataAccessError writeAccessHandler (DataAttribute* dataAttribute, MmsValue* value, ClientConnection connection, void* parameter);
int start_static_mms_server(char* interface);
int start_dynamic_mms_server(void* arguments);

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif

#endif /* MMS_SERVER_MODULE_H */

