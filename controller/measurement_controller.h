/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   measurement_controller.h
 * Author: root
 *
 * Created on July 9, 2019, 4:04 PM
 */

#ifndef MEASUREMENT_CONTROLLER_H
#define MEASUREMENT_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../mms_server_module.h"
#include "mms_value.h"
void mx_controller_main(char* gocbRef, MmsValue* values);
void goose_update_mx_values(MmsValue* values);
void sv_update_mx_values(float values[]);

#ifdef __cplusplus
}
#endif

#endif /* MEASUREMENT_CONTROLLER_H */

