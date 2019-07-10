/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "measurement_controller.h";
extern IedServer iedServer;
//void* ptrs = 

DataAttribute* instCVal_ptrs[6] = {
    IEDMODEL_MEAS_MMXU_A_phsA_instCVal_mag_f, 
    IEDMODEL_MEAS_MMXU_A_phsB_instCVal_mag_f, 
    IEDMODEL_MEAS_MMXU_A_phsC_instCVal_mag_f,
    IEDMODEL_MEAS_MMXU_PhV_phsA_instCVal_mag_f,
    IEDMODEL_MEAS_MMXU_PhV_phsB_instCVal_mag_f,
    IEDMODEL_MEAS_MMXU_PhV_phsC_instCVal_mag_f,
};

void mx_controller_main(char* gocbRef, MmsValue* values){
/* Even if pass in gocb as arg, how to determine next action dynamically? */
    IedServer_lockDataModel(iedServer);
    if(strcmp("LIED10MEAS/LLN0$GO$Meas",(char*)gocbRef) == 0){
        goose_update_mx_values(values);
        printf("%s received, updated MX values!\n ", gocbRef);
    }
    IedServer_unlockDataModel(iedServer);
    Thread_sleep(100);
}

void goose_update_mx_values(MmsValue* values){
    IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_A_phsA_t, Hal_getTimeInMs());
    IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_A_phsB_t, Hal_getTimeInMs());
    IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_A_phsC_t, Hal_getTimeInMs());
    /* Does this imply we need to know the full struct of the gocb and what each val represents? 
       How do we create such controllers dynamically instead of hardcoding for diff IEDs? 
       How to know each element and its type without looking at SCL file or IEDScout? */
    //float val_1 = MmsValue_toFloat(MmsValue_getElement(values,0));
    //float val_2 = MmsValue_toFloat(MmsValue_getElement(values,1));
    //float val_3 = MmsValue_toFloat(MmsValue_getElement(values,2));
    //float val_4 = MmsValue_toFloat(MmsValue_getElement(values,3));
    //float val_5 = MmsValue_toFloat(MmsValue_getElement(values,4));
    //float val_6 = MmsValue_toFloat(MmsValue_getElement(values,5));
    //DAs can be anywhere in the IED Data Model, how to know which DA to update?
    //IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_A_phsA_instCVal_mag_f, val_1+1);
    //IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_A_phsB_instCVal_mag_f, val_2+2);
    //IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_A_phsC_instCVal_mag_f, val_3+3);
    //IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_PhV_phsA_instCVal_mag_f, val_4);
    //IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_PhV_phsB_instCVal_mag_f, val_5);
    //IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_PhV_phsC_instCVal_mag_f, val_6);
    
    float vals[6];
    for(int i=0;i<6;i++){
        vals[i] = MmsValue_toFloat(MmsValue_getElement(values,i));
    }
    for(int i=0;i<6;i++){
        if(!vals[i]){
            IedServer_updateFloatAttributeValue(iedServer, instCVal_ptrs[i], vals[i]);
        }
    }
}

void sv_update_mx_values(float values[6]){
    /* This method should be called by the the SV callback directly */
    /* Should we have fixed size arr or use libiec61850's LinkedList? */
    
    printf("SV passed into mx_ctrl: %f, %f, %f , %f , %f , %f \n", values[0], values[1], values[2], values[3], values[4], values[5]);
    
    IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_A_phsA_t, Hal_getTimeInMs());
    IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_A_phsB_t, Hal_getTimeInMs());
    IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_A_phsC_t, Hal_getTimeInMs());
    
    //DAs can be anywhere in the IED Data Model, how to know which DA to update?
   
    //IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_A_phsA_instCVal_mag_f, values[0]);
    //IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_A_phsB_instCVal_mag_f, values[1]);
    //IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_A_phsC_instCVal_mag_f, values[2]);
    //IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_PhV_phsA_instCVal_mag_f, values[3]);
    //IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_PhV_phsB_instCVal_mag_f, values[4]);
    //IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_PhV_phsC_instCVal_mag_f, values[5]);
    
    //printf("memaddr OUTSIDE LOOP is %p\n", IEDMODEL_MEAS_MMXU_A_phsA_instCVal_mag_f);
    for(int i=0;i<6;i++){
        //if(values[i]!=values[i]){
        /* How to do NULL-checking or strong typing? */
            //printf("loop i val is %i \n",i);
            //printf("memaddr INSIDE LOOP is %p\n", instCVal_ptrs[0]);
            IedServer_updateFloatAttributeValue(iedServer, instCVal_ptrs[i], values[i]);
        //}
    }
}