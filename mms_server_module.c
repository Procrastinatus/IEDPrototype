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

#include "mms_server_module.h"

/* import IEC 61850 device model created from SCL-File */
extern IedModel iedModel;

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
}

int start_mms_server(char* interface) {
        
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
	    //anIn1 += 0.1;
		Thread_sleep(1000);
	}

	/* stop MMS server - close TCP server socket and all client sockets */
	IedServer_stop(iedServer);

	/* Cleanup - free all resources */
	IedServer_destroy(iedServer);
} /* main() */