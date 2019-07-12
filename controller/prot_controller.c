/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* This is a LD-specific controller */
/* This is the controller that interacts with the "PROT" Logical Device */

#include "prot_controller.h"
extern IedServer iedServer;

void set_alarm(bool alarm){
    IedServer_lockDataModel(iedServer);
    IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_PROT_PIOC_Op_general, alarm);
    IedServer_unlockDataModel(iedServer);
}

void prot_write_handlers(){
    printf("Write to IED PROT LD detected \n");
}

void register_prot_write_handlers(){
    /* Register write handlers for "PROT" logical device */
    
    /* Set write access policies*/
    //IedServer_setWriteAccessPolicy(iedServer, IEC61850_FC_DC , ACCESS_POLICY_ALLOW );
    
    /* Set DA write callbacks*/
    //IedServer_handleWriteAccess(iedServer, IEDMODEL_PROT_LLN0_NamPlt_vendor, (WriteAccessHandler)prot_write_handlers, NULL); 
    
    //printf("PROT LD Write Handlers (for MMS) Registered! \n");
}