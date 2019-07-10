/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sv_in.h
 * Author: root
 *
 * Created on July 5, 2019, 12:51 PM
 */

#ifndef SV_IN_H
#define SV_IN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "model/custom_structs.h"
#include "sv_subscriber.h"
#include "controller/measurement_controller.h"
#include "controller/protection_controller.h"
    
void sv_in_sigint_handler(int signalId);
static void svUpdateListener (SVSubscriber subscriber, void* parameter, SVSubscriber_ASDU asdu);
int start_sv_receiver(void* arguments);

#ifdef __cplusplus
}
#endif

#endif /* SV_IN_H */

