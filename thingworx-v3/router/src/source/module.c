/*
 *  Copyright (C) 2014 ThingWorx Inc.
 *
 *  Test application
 */

 /* LICENSE AND DISCLAIMER
 * ----------------------
 * This material contains sample programming source code ("Sample Code").
 * B+B Smartworx grants you a nonexclusive license to compile, link, run,
 * display, reproduce, distribute and prepare derivative works of 
 * this Sample Code.  The Sample Code has not been thoroughly
 * tested under all conditions.  B+B Smartworx, therefore, does not guarantee
 * or imply its reliability, serviceability, or function. B+B Smartworx
 * provides no program services for the Sample Code.
 *
 * All Sample Code contained herein is provided to you "AS IS" without
 * any warranties of any kind. THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGMENT ARE EXPRESSLY
 * DISCLAIMED.  SOME JURISDICTIONS DO NOT ALLOW THE EXCLUSION OF IMPLIED
 * WARRANTIES, SO THE ABOVE EXCLUSIONS MAY NOT APPLY TO YOU.  IN NO 
 * EVENT WILL IBM BE LIABLE TO ANY PARTY FOR ANY DIRECT, INDIRECT, 
 * SPECIAL OR OTHER CONSEQUENTIAL DAMAGES FOR ANY USE OF THE SAMPLE CODE
 * INCLUDING, WITHOUT LIMITATION, ANY LOST PROFITS, BUSINESS 
 * INTERRUPTION, LOSS OF PROGRAMS OR OTHER DATA ON YOUR INFORMATION
 * HANDLING SYSTEM OR OTHERWISE, EVEN IF WE ARE EXPRESSLY ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGES.
 *
 * COPYRIGHT
 * ---------
 * (C) Copyright B+B Smartworx. 2015
 * All rights reserved.
 * Licensed Material - Property of B+B Smartworx
*/

#include "twOSPort.h"
#include "twLogger.h"
#include "twApi.h"

#include "gpio.h"
#include "module.h"
#include "module_cfg.h"

#include <stdio.h>
#include <string.h>

/* Name of our thing */
char * thingName;

/*****************
A simple structure to handle
properties. Not related to
the API in anyway, just for
the demo application.
******************/
struct  {
	double LanTx;
	double LanRx;
	double Temperature;
	double Voltage;
	
} properties;

/*****************
Helper Functions
*****************/
void sendPropertyUpdate() {

	/* Create the property list */
	propertyList * proplist = twApi_CreatePropertyList("LanTx",twPrimitive_CreateFromNumber(properties.LanTx), 0);
	if (!proplist) {
		TW_LOG(TW_ERROR,"sendPropertyUpdate: Error allocating property list");
		return;
	}
	twApi_AddPropertyToList(proplist,"LanRx",twPrimitive_CreateFromNumber(properties.LanRx), 0);
	twApi_AddPropertyToList(proplist,"Temperature",twPrimitive_CreateFromNumber(properties.Temperature), 0);
	twApi_AddPropertyToList(proplist,"Voltage",twPrimitive_CreateFromNumber(properties.Voltage), 0);
	twApi_PushProperties(TW_THING, thingName, proplist, -1, FALSE);
	twApi_DeletePropertyList(proplist);
}

void shutdownTask(DATETIME now, void * params) {
	TW_LOG(TW_FORCE,"shutdownTask - Shutdown service called.  SYSTEM IS SHUTTING DOWN");
	twApi_UnbindThing(thingName);
	twSleepMsec(100);
	twApi_Delete();
	twLogger_Delete();
	exit(0);	
}

/***************
Data Collection Task
****************/
/*
This function gets called at the rate defined in the task creation.  The SDK has 
a simple cooperative multitasker, so the function cannot infinitely loop.
Use of a task like this is optional and not required in a multithreaded
environment where this functonality could be provided in a separate thread.
*/
#define DATA_COLLECTION_RATE_MSEC 2000
void dataCollectionTask(DATETIME now, void * params) {
    /* TW_LOG(TW_TRACE,"dataCollectionTask: Executing"); */

	/* Get LAN Transmit Data value */
	const int bufsize = 100;
	FILE *f = popen("status -h lan", "r");

	int i = 0;
	char buftx[bufsize];
	while(fgets(buftx, bufsize, f))
	{
		if(i == 3)
		{
			char *strip = strchr(buftx, ':');
			strip = strip + 2;
			int len = strlen(strip);
			char resultstr[12];
			strncpy(resultstr, strip, len - 3);
			sscanf(resultstr, "%lf", &properties.LanTx);
		}

		i++;
	}
	pclose(f);

	/* Get LAN Received Data value */
	f = popen("status -h lan", "r");

	i = 0;
	char bufrx[bufsize];
	while(fgets(bufrx, bufsize, f))
	{
		if(i == 2)
		{
			char *strip = strchr(bufrx, ':');
			strip = strip + 2;
			int len = strlen(strip);
			char resultstr[12];
			strncpy(resultstr, strip, len - 3);
			sscanf(resultstr, "%lf", &properties.LanRx);
		}

		i++;
	}
	pclose(f);

	/* Get CPU Temperature Data value */
	int temperature = gpio_get_temperature();
  	temperature -= 273;

  	properties.Temperature = (double) temperature;

	/* Get Supply Voltage Data value */
	f = popen("status -h sys", "r");

	i = 0;
	char bufvolt[bufsize];
	while(fgets(bufvolt, bufsize, f))
	{
		if(i == 3)
		{
			char *strip = strchr(bufvolt, ':');
			strip = strip + 2;
			int len = strlen(strip);
			char resultstr[12];
			strncpy(resultstr, strip, len - 2);
			sscanf(resultstr, "%lf", &properties.Voltage);
		}

		i++;
	}
	pclose(f);

	/* Update the properties on the server */
	sendPropertyUpdate();
}

/*****************
Property Handler Callbacks 
******************/
enum msgCodeEnum propertyHandler(const char * entityName, const char * propertyName,  twInfoTable ** value, char isWrite, void * userdata) {
	char * asterisk = "*";
	if (!propertyName) propertyName = asterisk;
	TW_LOG(TW_TRACE,"propertyHandler - Function called for Entity %s, Property %s", entityName, propertyName);
	if (value) {
		if (isWrite && *value) {
			/* Property Writes */
			// if (strcmp(propertyName, "InletValve") == 0) twInfoTable_GetBoolean(*value, propertyName, 0, &properties.InletValve); 
			// else if (strcmp(propertyName, "FaultStatus") == 0) twInfoTable_GetBoolean(*value, propertyName, 0, &properties.FaultStatus);
			// else if (strcmp(propertyName, "TemperatureLimit") == 0) twInfoTable_GetNumber(*value, propertyName, 0, &properties.TemperatureLimit);
			// else return TWX_NOT_FOUND;
			return TWX_SUCCESS;
		} else {
			/* Property Reads */
			if (strcmp(propertyName, "LanTx") == 0) *value = twInfoTable_CreateFromNumber(propertyName, properties.LanTx); 
			else if (strcmp(propertyName, "LanRx") == 0) *value = twInfoTable_CreateFromNumber(propertyName, properties.LanRx); 
			else if (strcmp(propertyName, "Temperature") == 0) *value = twInfoTable_CreateFromNumber(propertyName, properties.Temperature); 
			else if (strcmp(propertyName, "Voltage") == 0) *value = twInfoTable_CreateFromNumber(propertyName, properties.Voltage);  
			// else if (strcmp(propertyName, "Location") == 0) *value = twInfoTable_CreateFromLocation(propertyName, &properties.Location); 
			// else if (strcmp(propertyName, "BigGiantString") == 0) *value = twInfoTable_CreateFromString(propertyName, properties.BigGiantString, TRUE);
			else return TWX_NOT_FOUND;
		}
		return TWX_SUCCESS;
	} else {
		TW_LOG(TW_ERROR,"propertyHandler - NULL pointer for value");
		return TWX_BAD_REQUEST;
	}
}

/*****************
Service Callbacks 
******************/
/* Example of handling a single service in a callback */
// enum msgCodeEnum addNumbersService(const char * entityName, const char * serviceName, twInfoTable * params, twInfoTable ** content, void * userdata) {
// 	double a, b, res;
// 	TW_LOG(TW_TRACE,"addNumbersService - Function called");
// 	if (!params || !content) {
// 		TW_LOG(TW_ERROR,"addNumbersService - NULL params or content pointer");
// 		return TWX_BAD_REQUEST;
// 	}

// 	twInfoTable_GetNumber(params, "a", 0, &a);
// 	twInfoTable_GetNumber(params, "b", 0, &b);
// 	res = a + b;
// 	*content = twInfoTable_CreateFromNumber("result", res);
// 	if (*content) return TWX_SUCCESS;
// 	else return TWX_INTERNAL_SERVER_ERROR;
// }

// /* Example of handling multiple services in a callback */
// enum msgCodeEnum multiServiceHandler(const char * entityName, const char * serviceName, twInfoTable * params, twInfoTable ** content, void * userdata) {
// 	TW_LOG(TW_TRACE,"multiServiceHandler - Function called");
// 	if (!content) {
// 		TW_LOG(TW_ERROR,"multiServiceHandler - NULL content pointer");
// 		return TWX_BAD_REQUEST;
// 	}
// 	if (strcmp(entityName, thingName) == 0) {
// 		if (strcmp(serviceName, "GetBigString") == 0) {
// 			int len = 10000;
// 			char text[] = "inna gadda davida ";
// 			char * bigString = (char *)TW_CALLOC(len,1);
// 			int textlen = strlen(text);
// 			while (bigString && len > textlen) {
// 				strncat(bigString, text, len - textlen - 1);
// 				len = len - textlen;
// 			}
// 			*content = twInfoTable_CreateFromString("result", bigString, FALSE);
// 			if (*content) return TWX_SUCCESS;
// 			return TWX_ENTITY_TOO_LARGE;
// 		} else if (strcmp(serviceName, "Shutdown") == 0) {
// 			/* Create a task to handle the shutdown so we can respond gracefully */
// 			twApi_CreateTask(1, shutdownTask);
// 		}
// 		return TWX_NOT_FOUND;	
// 	}
// 	return TWX_NOT_FOUND;	
// }

/***************
Main Loop
****************/
/*
Solely used to instantiate and configure the API.
*/
int main( int argc, char** argv ) {

	// Load configuration
	module_cfg_t cfg;
	module_cfg_load( &cfg );

	thingName = cfg.name;
	char * hostip = cfg.addr;
	char * appKey = cfg.key;

#if defined NO_TLS
	int16_t port = 80;
#else
	int16_t port = 443;
#endif

	twDataShape * ds = 0;
	DATETIME nextDataCollectionTime = 0;
	int err = 0;

	twLogger_SetLevel(TW_TRACE);
	twLogger_SetIsVerbose(1);
	TW_LOG(TW_FORCE, "Starting up");

	/* Initialize the API */
	err = twApi_Initialize(hostip, port, TW_URI, appKey, 
		NULL, MESSAGE_CHUNK_SIZE, MESSAGE_CHUNK_SIZE, TRUE);
	if (err) {
		TW_LOG(TW_ERROR, "Error initializing the API");
		exit(err);
	}

	/* Allow self signed certs */
	twApi_SetSelfSignedOk();

	/* Register our services */
	// ds = twDataShape_Create(twDataShapeEntry_Create("a",NULL,TW_NUMBER));
	// twDataShape_AddEntry(ds, twDataShapeEntry_Create("b",NULL,TW_NUMBER));
	// twApi_RegisterService(TW_THING, thingName, "AddNumbers", NULL, ds, TW_NUMBER, NULL, addNumbersService, NULL);
	// twApi_RegisterService(TW_THING, thingName, "GetBigString", NULL, NULL, TW_STRING, NULL, multiServiceHandler, NULL);
	// twApi_RegisterService(TW_THING, thingName, "Shutdown", NULL, NULL, TW_NOTHING, NULL, multiServiceHandler, NULL);

	/* Regsiter our properties */
	twApi_RegisterProperty(TW_THING, thingName, "LanTx", TW_NUMBER, NULL, "ALWAYS", 0, propertyHandler, NULL);
	twApi_RegisterProperty(TW_THING, thingName, "LanRx", TW_NUMBER, NULL, "ALWAYS", 0, propertyHandler, NULL);
	twApi_RegisterProperty(TW_THING, thingName, "Temperature", TW_NUMBER, NULL, "ALWAYS", 0, propertyHandler, NULL);
	twApi_RegisterProperty(TW_THING, thingName, "Voltage", TW_NUMBER, NULL, "ALWAYS", 0, propertyHandler, NULL);
	// twApi_RegisterProperty(TW_THING, thingName, "BigGiantString", TW_STRING, NULL, "ALWAYS", 0, propertyHandler, NULL);

	/* Bind our thing */
	twApi_BindThing(thingName);

	/* Connect to server */
	if (!twApi_Connect(CONNECT_TIMEOUT, CONNECT_RETRIES)) {
		/* Register our "Data collection Task" with the tasker */
		twApi_CreateTask(DATA_COLLECTION_RATE_MSEC, dataCollectionTask);
	}

	while(1) {
	/*while (twApi_isConnected()) {*/
		char in = 0;
#ifndef ENABLE_TASKER
		DATETIME now = twGetSystemTime(TRUE);
		twApi_TaskerFunction(now, NULL);
		twMessageHandler_msgHandlerTask(now, NULL);
		if (twTimeGreaterThan(now, nextDataCollectionTime)) {
			dataCollectionTask(now, NULL);
			nextDataCollectionTime = twAddMilliseconds(now, DATA_COLLECTION_RATE_MSEC);
		}
#else
		in = getch();
		if (in == 'q') break;
		else printf("\n");
#endif
		twSleepMsec(5);
	}
	twApi_UnbindThing(thingName);
	twSleepMsec(1000l);
	twApi_Delete();
	twLogger_Delete();
	exit(0);
}
