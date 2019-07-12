/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* This is the controller that interacts with the "CTRL" Logical Device */

#include "ctrl_controller.h"

extern IedServer iedServer;

void update_cb_status(int status){
    /* ../XCBR.Pos.stVal , 0=open, 1=closed */
    IedServer_lockDataModel(iedServer);
    IedServer_updateInt32AttributeValue(iedServer, IEDMODEL_CTRL_XCBR_Pos_stVal, status);
    IedServer_unlockDataModel(iedServer);
    //Thread_sleep(100);
}
