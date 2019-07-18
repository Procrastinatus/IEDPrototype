#include "hal_thread.h" /* for Thread_sleep() */
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

/* Include model header in header file*/
#include "ied_server.h"

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

/* IED Server = (MMS Server + GOOSE Publisher) Bundle */
int start_static_ied_server(void* arguments) {        
        Arg_pack* args = arguments;        
        int tcp_port = args->start_port;    
	iedServer = IedServer_create(&iedModel);
	
        /* Set up interface */
        char* ethernetIfcID = NULL;
	ethernetIfcID = args->interface;
	IedServer_setGooseInterfaceId(iedServer, ethernetIfcID);
	IedServer_enableGoosePublishing(iedServer);
        
        //printf("MMS Server + GOOSE Publisher Using interface: %s\n", ethernetIfcID);
	IedServer_setGooseInterfaceId(iedServer, ethernetIfcID);
        
        /* Register write handlers (for MMS) located in controller(s) */
        //register_meas_write_handlers();
        //register_prot_write_handlers();
        
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
    DataAttribute* temperatureValue = get_temperature_value();
    DataAttribute* temperatureTimestamp = get_temperature_timestamp();
            
    /*********************
     * run server
     ********************/
	IedServer iedServer = IedServer_create(model);
        IedServer_setWriteAccessPolicy(iedServer, IEC61850_FC_DC, ACCESS_POLICY_ALLOW);
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