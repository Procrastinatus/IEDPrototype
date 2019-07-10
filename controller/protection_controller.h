/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   protection_controller.h
 * Author: root
 *
 * Created on July 9, 2019, 4:04 PM
 */

#ifndef PROTECTION_CONTROLLER_H
#define PROTECTION_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../mms_server_module.h"
#include "mms_value.h"
void protection_controller_main(char* gocbRef, MmsValue* values);


#ifdef __cplusplus
}
#endif

#endif /* PROTECTION_CONTROLLER_H */

