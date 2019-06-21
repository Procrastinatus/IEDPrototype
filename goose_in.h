/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   goose_out.h
 * Author: root
 *
 * Created on June 17, 2019, 11:48 AM
 */

#ifndef GOOSE_OUT_H
#define GOOSE_OUT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "goose_receiver.h"
#include "goose_subscriber.h"
#include "hal_thread.h"

void sigint_handler(int signalId);
void gooseListener(GooseSubscriber subscriber, void* parameter);
int start_goose_receiver(int argc, char** argv);


#ifdef __cplusplus
}
#endif

#endif /* GOOSE_OUT_H */

