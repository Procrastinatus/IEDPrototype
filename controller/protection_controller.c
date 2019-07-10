/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "protection_controller.h"
extern IedServer iedServer;

void protection_controller_main(char* gocbRef, MmsValue* values){
    printf("gocbRef: %s \n", gocbRef);
    IedServer_lockDataModel(iedServer);
    if(strcmp("LIED10PROT/LLN0$GO$Alarm",gocbRef) == 0){
        raise_alarm(values);
        printf("%s received, over-current protection!\n ", gocbRef);
    }
    IedServer_unlockDataModel(iedServer);
    Thread_sleep(100);
}

void raise_alarm(MmsValue* values){
    IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_PROT_PIOC_Op_general, true);
}

void sv_raise_alarm(float values[6]){
    /* Logic to determine if OC has occurred */
    float sum = 0;
    for(int i=0;i<6;i++){
        sum+=values[i];
    }
    float avg_reading = sum/6;
    if(avg_reading > 2300){
        printf("Overcurrent detected with received SV with avg of %f (larger than hard-coded 2300 units)\n ", avg_reading);
        IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_PROT_PIOC_Op_general, true);
    } else {
        printf("No overcurrent, received SV avg value is %f \n ", avg_reading);
        IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_PROT_PIOC_Op_general, false);
    }    
}