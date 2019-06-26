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

//This struct is for passing arguments from main() to child threads
typedef struct arg_pack{
    char* interface;
    int opt,start_port,n;
} Arg_pack;


#ifdef __cplusplus
}
#endif

#endif /* CUSTOM_STRUCTS_H */

