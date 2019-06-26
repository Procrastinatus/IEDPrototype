/*
 *  server_example_dynamic.c
 *
 *  This example shows how to build a data model at runtime by API calls.
 *
 */

#include "iec61850_server.h"
#include "hal_thread.h"
#include "custom_structs.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

DataAttribute* temperatureValue;
DataAttribute* temperatureTimestamp;

IedModel* create_dynamic_model(Arg_pack* args) {
    /*********************
     * Setup data model
     ********************/
    //Get IED ID from args and convert to string
    char ied_id_string[sizeof (int) * 4 + 1];
    sprintf(ied_id_string, "%d", args->n);    
    char* physical_device_name = "PHY";
    //Allocate enough memory for the 2 strings to be concatenated
    char* final_physical_name = (char *) malloc(1 + strlen(physical_device_name) + strlen(ied_id_string));
    strcat(final_physical_name, physical_device_name);
    strcat(final_physical_name, ied_id_string);
    
    /* The GOOSE packets should show different physical device names if you have provided different -n flags when running*/
    IedModel* model = IedModel_create(final_physical_name);
    LogicalDevice* lDevice1 = LogicalDevice_create("LDEV", model);
    LogicalNode* lln0 = LogicalNode_create("LLN0", lDevice1);
    DataObject* lln0_mod = CDC_ENS_create("Mod", (ModelNode*) lln0, 0);
    DataObject* lln0_health = CDC_ENS_create("Health", (ModelNode*) lln0, 0);
    SettingGroupControlBlock_create(lln0, 1, 1);

    /* Add a temperature sensor LN */
    LogicalNode* ttmp1 = LogicalNode_create("TTMP1", lDevice1);
    DataObject* ttmp1_tmpsv = CDC_SAV_create("TmpSv", (ModelNode*) ttmp1, 0, false);
    temperatureValue = (DataAttribute*) ModelNode_getChild((ModelNode*) ttmp1_tmpsv, "instMag.f");
    temperatureTimestamp = (DataAttribute*) ModelNode_getChild((ModelNode*) ttmp1_tmpsv, "t");
    DataSet* dataSet = DataSet_create("events", lln0);
    DataSetEntry_create(dataSet, "TTMP1$MX$TmpSv$instMag$f", -1, NULL);
    //uint8_t rptOptions = RPT_OPT_SEQ_NUM | RPT_OPT_TIME_STAMP | RPT_OPT_REASON_FOR_INCLUSION;
    //ReportControlBlock_create("events01", lln0, "events01", false, NULL, 1, TRG_OPT_DATA_CHANGED, rptOptions, 50, 0);
    //ReportControlBlock_create("events02", lln0, "events02", false, NULL, 1, TRG_OPT_DATA_CHANGED, rptOptions, 50, 0);
    GSEControlBlock_create("gse01", lln0, "events01", "events", 1, false, 200, 3000);

    /* Add a lln0 nameplate (TODO: NOT WORKING YET) */
    DataObject* lln0_namplt = DataObject_create("NamPlt", (ModelNode*) lln0, 0);
    //DataAttribute* lln0_vendor_DA = DataAttribute_create("vendor", (ModelNode*)lln0, IEC61850_UNICODE_STRING_255, IEC61850_FC_DC, 0, 0, NULL);
    DataAttribute* lln0_vendor_DA = (DataAttribute*) ModelNode_getChild((ModelNode*) lln0_namplt, "vendor");
    DataSet* my_test_dataset = DataSet_create("mydataset", lln0);
    //DataSetEntry_create(my_test_dataset, "LLN0$DC$NamPlt$vendor", -1, NULL);
    GSEControlBlock_create("mygocb", lln0, "appid01", "mydataset", 1, false, 200, 3000);

    /* Add a writeable value for MMS clients (TODO: NOT WORKING YET)*/
    //LogicalNode* zinv1 = LogicalNode_create("ZINV1", lDevice1);
    //DataObject* zinv1_outvarset = DataObject_create("OutVarSet", (ModelNode*)zinv1, 0);
    //DataAttribute* lln0_vendor_DA = DataAttribute_create("vendor", (ModelNode*)lln0, IEC61850_UNICODE_STRING_255, IEC61850_FC_DC, 0, 0, NULL);
    //DataAttribute* setmag_val = (DataAttribute*) ModelNode_getChild((ModelNode*) zinv1_outvarset, "setMag.f");
    //DataAttribute* timestamp_val = (DataAttribute*) ModelNode_getChild((ModelNode*) zinv1_outvarset, "t");
    //DataSet* my_test_dataset2 = DataSet_create("mydataset2", zinv1);
    //DataSetEntry_create(my_test_dataset2, "ZINV1$OutVarSet$setMag$f", -1, NULL);
    //GSEControlBlock_create("mygocb2", zinv1, "appid01", "mydataset2", 1, false, 200, 3000);
    return model;
}

DataAttribute* get_temperature_value() {
    return temperatureValue;
}

DataAttribute* get_temperature_timestamp() {
    return temperatureTimestamp;
}