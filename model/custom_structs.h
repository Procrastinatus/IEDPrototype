/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   custom_structs.h
 * Author: root
 *
 * Created on June 26, 2019, 10:39 AM
 */

#ifndef CUSTOM_STRUCTS_H
#define CUSTOM_STRUCTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "linked_list.h"

//This struct is for passing arguments from main() to child threads
typedef struct arg_pack{
    char* interface;
    char mode;
    int opt, start_port, n;
    LinkedList go_cb_refs;
    //int goose_in_appid;
    LinkedList goose_in_appid;
    LinkedList goose_out_appid;
    uint16_t sv_in_appid;
    bool cb_fail;
} Arg_pack;

typedef struct received_goose_data{
    char* go_cb_ref;
    float new_val;
} Received_goose_data;

typedef struct gooseSubscribers{
    LinkedList subscribers;
} GooseSubscribers;

#ifdef __cplusplus
}
#endif

#endif /* CUSTOM_STRUCTS_H */

