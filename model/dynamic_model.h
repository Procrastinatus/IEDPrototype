/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#ifndef DYNAMIC_MODEL_H
#define DYNAMIC_MODEL_H

#include "iec61850_server.h"
#include "hal_thread.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "custom_structs.h"

IedModel* create_dynamic_model(Arg_pack* args);
DataAttribute* get_temperature_value();
DataAttribute* get_temperature_timestamp();

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#endif /* DYNAMIC_MODEL_H */

