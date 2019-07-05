#include "hal_thread.h" /* for Thread_sleep() */
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

/* Include model header in header file*/
#include "mms_server_module.h"

/* import IEC 61850 device model created from SCL-File */
/* IMPORTANT: remember to exclude unused model files from build */
extern IedModel iedModel;

//Custom struct initialised by goose_in and defined in custom_structs.h
extern Received_goose_data new_vals;

static int running = 0;
IedServer iedServer = NULL;

void mms_server_module_sigint_handler(int signalId)
{
	running = 0;
}

void
controlHandlerForExample(void* parameter, MmsValue* value)
{
    /* This method should be for writes from MMS client to MMS server */
    printf("=================IN CONTROL(WRITE) HANDLER CALLBACK=====================\n");
    //if (parameter == IEDMODEL_MEAS_LLN0_NamPlt) {
        //IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_SPCSO4_t, timestamp);
        //IedServer_updateAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_SPCSO4_stVal, value);
    //    IedServer_updateVisibleStringAttributeValue(iedServer, IEDMODEL_MEAS_LLN0_NamPlt_vendor, "new_static_vendor");
    //}
}

static MmsDataAccessError
writeAccessHandler (DataAttribute* dataAttribute, MmsValue* value, ClientConnection connection, void* parameter)
{
    //Note that this method is for MMS client to WRITE/CONTROL values, not SUBSTITUTE values (read from process bus)
    if (dataAttribute == IEDMODEL_MEAS_LLN0_NamPlt) {

        float newValue = MmsValue_toFloat(value);

        printf("New value for IEDMODEL_MEAS_LLN0_NamPlt = %f\n", newValue);

        /* Check if value is inside of valid range */
        if ((newValue >= 0.f) && (newValue <= 1000.1f))
            return DATA_ACCESS_ERROR_SUCCESS;
        else
            return DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;
    }

    return DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
}

int start_static_ied_server(void* arguments) {        
        Arg_pack* args = arguments;        
        int tcp_port = args->start_port;    
	iedServer = IedServer_create(&iedModel);
	
        /* Set up interface */
        char* ethernetIfcID = NULL;
	ethernetIfcID = args->interface;
	IedServer_setGooseInterfaceId(iedServer, ethernetIfcID);
	IedServer_enableGoosePublishing(iedServer);
        
        printf("MMS Server + GOOSE Publisher Using interface: %s\n", ethernetIfcID);
	IedServer_setGooseInterfaceId(iedServer, ethernetIfcID);
	IedServer_start(iedServer, tcp_port);

	if (!IedServer_isRunning(iedServer)) {
		printf("Starting server failed! Exit.\n");
		IedServer_destroy(iedServer);
		exit(-1);
	}

	/* Start GOOSE publishing */
	IedServer_enableGoosePublishing(iedServer);
        
	running = 1;
	signal(SIGINT, mms_server_module_sigint_handler);
	while (running) {
	    IedServer_lockDataModel(iedServer);
            IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEAS_MMXU_A_phsA_t, Hal_getTimeInMs());
            //IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_CTRL_LLN0_Mod_stVal, new_vals.new_val);
	    IedServer_unlockDataModel(iedServer);
		Thread_sleep(100);
	}

	IedServer_stop(iedServer);
	IedServer_destroy(iedServer);
}

int start_dynamic_ied_server(void* arguments) {
    
    Arg_pack* args = arguments;
    int tcp_port = args->start_port;
    //int tcpPort = 102;
    
    /*********************
     * Setup data model
     ********************/
    IedModel* model = create_dynamic_model(args);
    //printf("MemAddr of IED Model: %p \n", model);
    DataAttribute* temperatureValue = get_temperature_value();
    DataAttribute* temperatureTimestamp = get_temperature_timestamp();
            
    /*********************
     * run server
     ********************/
	IedServer iedServer = IedServer_create(model);
        IedServer_setWriteAccessPolicy(iedServer, IEC61850_FC_DC, ACCESS_POLICY_ALLOW);
        //printf("MemAddr of IED Server: %p \n", iedServer);
		char* ethernetIfcID = NULL;
		ethernetIfcID = args->interface;
		IedServer_setGooseInterfaceId(iedServer, ethernetIfcID);
		IedServer_enableGoosePublishing(iedServer);

	/* MMS server will be instructed to start listening to client connections. */
	IedServer_start(iedServer, tcp_port);
	if (!IedServer_isRunning(iedServer)) {
		printf("Starting IED server failed! Exit.\n");
		IedServer_destroy(iedServer);
		exit(-1);
	}

	running = 1;
	signal(SIGINT, mms_server_module_sigint_handler);
	float val = 0.f;
        
        /* Initialize values here */
        /* DataAttribute objects should be exposed from dynamic_model.c and/or its header */
        extern DataAttribute* lln0_vendor_DA;
        IedServer_updateVisibleStringAttributeValue(iedServer, lln0_vendor_DA, "orig_vendor_val");
        
	while (running) {
	    IedServer_lockDataModel(iedServer);
	    IedServer_updateUTCTimeAttributeValue(iedServer, temperatureTimestamp, Hal_getTimeInMs());
	    IedServer_updateFloatAttributeValue(iedServer, temperatureValue, val);
	    IedServer_unlockDataModel(iedServer);
	    val += 0.1f;
		Thread_sleep(100);
	}

        printf("\nIED Server module has stopped running \n");
	/* stop MMS server - close TCP server socket and all client sockets */
	IedServer_stop(iedServer);
	/* Cleanup - free all resources */
	IedServer_destroy(iedServer);
	/* destroy dynamic data model */
	IedModel_destroy(model);
}