/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* This is a scenario-specific controller which only takes in GOOSE msgs (for now) */

#include "cb_failure_controller.h"

/* Used to ascertain different incoming GOOSE messages belonging to same group (same stNum) */
typedef struct cb_failure_conditions {
    uint32_t current_stNum;
    int cb_pos_stval;
    bool pioc_op_general;
} CB_failure_conditions;


/* Start of methods pertaining to INCOMING GOOSE messages */

/* This method is for handling incoming GOOSE messages from LIED11/12/13 to LIED10 for breaker failure protection */
void breaker_failure_controller_main(GooseSubscriber subscriber, void* param, MmsValue* values) {
    static CB_failure_conditions conds;
    char* gocbRef = (char*) param;
    int incoming_stNum = GooseSubscriber_getStNum(subscriber);
    int curr_stNum = conds.current_stNum;
    /* If a CB were closed for example, we would see an increase in stNum, so we update the latest received stNum, */
    /* and set the conditions for CB failure to be NULL, so the final condition below will not pass */
    //printf("conds.current_stNum is %u \n ", conds.current_stNum);
    //printf("gocbRef is %s \n ", gocbRef);
    if (incoming_stNum > curr_stNum) {
        conds.current_stNum = GooseSubscriber_getStNum(subscriber);
        conds.cb_pos_stval = NULL;
        conds.pioc_op_general = NULL;
    }
    /* stNum may be different (e.g. cb.pos.stval stNum may be lower than alarm stNum */
    /* since alarm goes from false to true (increment stnum), but cb does not open (no increase in stnum) */
    //else if (GooseSubscriber_getStNum(subscriber) == conds.current_stNum) {
    if (strcmp(gocbRef, "LIED11PROT/LLN0$GO$Alarm") == 0) {
        bool PIOC_OP_GENERAL = MmsValue_getBoolean(MmsValue_getElement(values, 0));
        /* If OC is detected in GOOSE message from some other IED */
        if (PIOC_OP_GENERAL == true) {
            conds.pioc_op_general = PIOC_OP_GENERAL;
            //printf("OC Detected from other IED! (PIOC_OP_GENERAL = TRUE)\n");
        }
    }
    if (strcmp(gocbRef, "LIED11CTRL/LLN0$GO$Status") == 0) {
        uint32_t XCBR_POS_STVAL = MmsValue_toInt32(MmsValue_getElement(values, 0));
        /* If CB is CLOSED (1) in GOOSE message from some other IED */
        if (XCBR_POS_STVAL == 1) {
            conds.cb_pos_stval = 1;
            //printf("The breaker from other IED is still CLOSED! (XCBR_POS_STVAL = 1)\n");
        }
    }

    /* Check that both conditions have been fulfilled with same stNum */
    /* If other IED's CB is CLOSED and OC is detected (implying CB failure) */
    if (conds.cb_pos_stval == 1 && conds.pioc_op_general == true) {
        printf("Both conditions for breaker failure from other IED have been verified! \n ");
        //printf("Breaking own CB...\n");        
        /* Open own CB */
        update_cb_status(0);
    }
    //}
}