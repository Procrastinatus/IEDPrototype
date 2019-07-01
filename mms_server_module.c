/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 *  server_example_goose.c
 *
 *  This example demonstrates how to use GOOSE publishing, Reporting and the
 *  control model.
 *
 */

#include "hal_thread.h" /* for Thread_sleep() */
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include "model/static_model.h"
#include "model/dynamic_model.h"

#include "mms_server_module.h"

/* import IEC 61850 device model created from SCL-File */
extern IedModel iedModel;

/* Use dynamic model */
extern IedModel dynamicIedModel;

static int running = 0;
IedServer iedServer = NULL;

void mms_server_module_sigint_handler(int signalId)
{
	running = 0;
}

void
controlHandlerForBinaryOutput(void* parameter, MmsValue* value)
{
    uint64_t timestamp = Hal_getTimeInMs();
    
    printf("In controlHandlerForBinaryOutput()\n");

    if (parameter == IEDMODEL_GenericIO_GGIO1_SPCSO1) {
        IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_SPCSO1_t, timestamp);
        IedServer_updateAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_SPCSO1_stVal, value);
    }

    if (parameter == IEDMODEL_GenericIO_GGIO1_SPCSO2) {
        IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_SPCSO2_t, timestamp);
        IedServer_updateAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_SPCSO2_stVal, value);
    }

    if (parameter == IEDMODEL_GenericIO_GGIO1_SPCSO3) {
        IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_SPCSO3_t, timestamp);
        IedServer_updateAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_SPCSO3_stVal, value);
    }

    if (parameter == IEDMODEL_GenericIO_GGIO1_SPCSO4) {
        IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_SPCSO4_t, timestamp);
        IedServer_updateAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_SPCSO4_stVal, value);
    }
    
    //if (parameter == IEDMODEL_GenericIO_GGIO1_AnIn2) {
        //IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_SPCSO4_t, timestamp);
        //IedServer_updateAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_SPCSO4_stVal, value);
        printf("stNum increased, sqNum reset, Attempting to change some data attribute...\n");
        printf("Changing HARD-CODED DA (Data Attr.): GGIO_AnIn2_mag_f \n");
        int received_val = MmsValue_toInt32(MmsValue_getElement(value,0));
        float new_anin2_mag_f = (float)received_val;
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_AnIn2_mag_f, new_anin2_mag_f);
    //}
}

static MmsDataAccessError
writeAccessHandler (DataAttribute* dataAttribute, MmsValue* value, ClientConnection connection, void* parameter)
{
    if (dataAttribute == IEDMODEL_GenericIO_GGIO1_AnIn2_mag_f) {

        float newValue = MmsValue_toFloat(value);

        printf("New value for IEDMODEL_GenericIO_GGIO1_AnIn2_mag_f = %f\n", newValue);

        /* Check if value is inside of valid range */
        if ((newValue >= 0.f) && (newValue <= 1000.1f))
            return DATA_ACCESS_ERROR_SUCCESS;
        else
            return DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;

    }

    return DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
}

int start_static_mms_server(char* interface) {        
	iedServer = IedServer_create(&iedModel);
	char* ethernetIfcID = NULL;
        if(interface!=NULL)
            ethernetIfcID = interface;
        else
            ethernetIfcID = "lo";
        
        printf("MMS Server + GOOSE Publisher Using interface: %s\n", ethernetIfcID);
	IedServer_setGooseInterfaceId(iedServer, ethernetIfcID);

	/* MMS server will be instructed to start listening to client connections. */
        // IP must be same as interface, if not it'll segfault
        //char ied_ip[] = "192.168.16.51";
        //printf("The IED MMS Server's IP address is %s \n", ied_ip);
        //IedServer_setLocalIpAddress(iedServer, ied_ip);
	IedServer_start(iedServer, 102);
                
	/* Don't allow access to SP variables by default */
	IedServer_setWriteAccessPolicy(iedServer, IEC61850_FC_DC, ACCESS_POLICY_ALLOW);
        IedServer_handleWriteAccess(iedServer, IEDMODEL_GenericIO_LLN0_NamPlt_vendor, (ControlHandler) controlHandlerForBinaryOutput, NULL);
        
	IedServer_setControlHandler(iedServer, IEDMODEL_GenericIO_GGIO1_SPCSO1, (ControlHandler) controlHandlerForBinaryOutput,
	        IEDMODEL_GenericIO_GGIO1_SPCSO1);

	IedServer_setControlHandler(iedServer, IEDMODEL_GenericIO_GGIO1_SPCSO2, (ControlHandler) controlHandlerForBinaryOutput,
	            IEDMODEL_GenericIO_GGIO1_SPCSO2);

	IedServer_setControlHandler(iedServer, IEDMODEL_GenericIO_GGIO1_SPCSO3, (ControlHandler) controlHandlerForBinaryOutput,
	            IEDMODEL_GenericIO_GGIO1_SPCSO3);

	IedServer_setControlHandler(iedServer, IEDMODEL_GenericIO_GGIO1_SPCSO4, (ControlHandler) controlHandlerForBinaryOutput,
	            IEDMODEL_GenericIO_GGIO1_SPCSO4);

	if (!IedServer_isRunning(iedServer)) {
		printf("Starting server failed! Exit.\n");
		IedServer_destroy(iedServer);
		exit(-1);
	}

	/* Start GOOSE publishing */
	IedServer_enableGoosePublishing(iedServer);
	running = 1;
	signal(SIGINT, mms_server_module_sigint_handler);
	float anIn1 = 0.f;
	while (running) {
	    IedServer_lockDataModel(iedServer);
            IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_AnIn1_t, Hal_getTimeInMs());
	    IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_AnIn1_mag_f, anIn1);
            //IedServer_updateAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_AnIn2_mag_f, MmsValue_newFloat(5));
	    IedServer_unlockDataModel(iedServer);
	    anIn1 += 0.1;
		Thread_sleep(1000);
	}

	/* stop MMS server - close TCP server socket and all client sockets */
	IedServer_stop(iedServer);

	/* Cleanup - free all resources */
	IedServer_destroy(iedServer);
}


int start_dynamic_mms_server(void* arguments) {
    
    Arg_pack* args = arguments;
    int tcpPort = args->start_port;
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
	IedServer_start(iedServer, tcpPort);
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