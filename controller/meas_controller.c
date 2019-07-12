/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* This is a LD-specific controller */
/* This is the controller that interacts with the "MEAS" Logical Device */

#include "meas_controller.h";
extern IedServer iedServer;

float received_measurements[6];

DataAttribute* timestamp_ptrs[3] = {
    IEDMODEL_MEAS_MMXU_A_phsA_t,
    IEDMODEL_MEAS_MMXU_A_phsB_t,
    IEDMODEL_MEAS_MMXU_A_phsC_t
};

DataAttribute* instCVal_ptrs[6] = {
    IEDMODEL_MEAS_MMXU_A_phsA_instCVal_mag_f, 
    IEDMODEL_MEAS_MMXU_A_phsB_instCVal_mag_f, 
    IEDMODEL_MEAS_MMXU_A_phsC_instCVal_mag_f,
    IEDMODEL_MEAS_MMXU_PhV_phsA_instCVal_mag_f,
    IEDMODEL_MEAS_MMXU_PhV_phsB_instCVal_mag_f,
    IEDMODEL_MEAS_MMXU_PhV_phsC_instCVal_mag_f,
};


void goose_update_meas_values(MmsValue* values){
    IedServer_lockDataModel(iedServer);
    
    /* Update Timestamps*/
    for(int i=0;i<3;i++){
        IedServer_updateUTCTimeAttributeValue(iedServer, timestamp_ptrs[i], Hal_getTimeInMs());
    }
    
    /* Update MX values */
    for(int i=0;i<6;i++){
        received_measurements[i] = MmsValue_toFloat(MmsValue_getElement(values,i));
    }
    for(int i=0;i<6;i++){
        //if(!received_measurements[i]){
            IedServer_updateFloatAttributeValue(iedServer, instCVal_ptrs[i], received_measurements[i]);
        //}
    }
    
    IedServer_unlockDataModel(iedServer);
}

void sv_update_meas_values(float* values, int len){
    IedServer_lockDataModel(iedServer);
    /* Update Timestamps*/
    for(int i=0;i<3;i++){
        IedServer_updateUTCTimeAttributeValue(iedServer, timestamp_ptrs[i], Hal_getTimeInMs());
    }  
    
    /* Update Measurement Values from MU */
    for(int i=0;i<len;i++){
        IedServer_updateFloatAttributeValue(iedServer, instCVal_ptrs[i], values[i]);
    }
    IedServer_unlockDataModel(iedServer);
}

void meas_write_handlers(){
    printf("Write to IED MEAS LD detected \n");
}

void register_meas_write_handlers(){
    /* Register write handlers for "MEAS" logical device */
    
    /* Set write access policies*/
    //IedServer_setWriteAccessPolicy(iedServer, IEC61850_FC_MX , ACCESS_POLICY_ALLOW );
    
    /* Set DA write callbacks*/
    //IedServer_handleWriteAccess(iedServer,IEDMODEL_MEAS_MMXU_A_phsA_db, (WriteAccessHandler)meas_write_handlers, NULL); 
    //IedServer_handleWriteAccess(iedServer,IEDMODEL_MEAS_MMXU_A_phsA_instCVal_mag_f, (WriteAccessHandler)meas_write_handlers, NULL); 
    //printf("MEAS LD Write Handlers (for MMS) Registered! \n");
}