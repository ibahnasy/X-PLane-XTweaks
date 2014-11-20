/*
 * Author: Islam Bahnasy
 * Email: islam@cybertechlab.com
 */
 

#include <stdio.h>
#include <string.h>
#include "XPLMMenus.h"
#include "XPLMDataAccess.h"


XPLMDataRef clouds = NULL;
XPLMMenuID  pluginMenu = NULL;

void MyPlugin_Menu_Handler(void *	inMenuRef, void *	inItemRef);
void checkClouds();


PLUGIN_API int XPluginStart(char *	outName, char *	outSig, char *	outDesc)
{
	strcpy(outName, "XTweaks v1.0");
	strcpy(outSig, "xplane.xtweaks.clouds");
	strcpy(outDesc, "Disable/Enable clouds only to prevent FPS loss, \
		the rest of the weather is not affected");

	/* Creates plugin menu */
	pluginMenu = XPLMCreateMenu("XTweaks", pluginMenu, 1, \
		MyPlugin_Menu_Handler, NULL);
	XPLMAppendMenuItem(pluginMenu, "Enable Clouds", (void *) 0, 1);
	
	/* Disabling clouds by default on startup */
	clouds = XPLMFindDataRef("sim/operation/override/override_clouds");
	XPLMSetDatai(clouds, 1);

	/* Check if enabled/disabled to update menu item caption */
	checkClouds();

	return 1;
}


PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFromWho, long inMessage, \
							void * inParam)
{
}

void MyPlugin_Menu_Handler(void * inMenuRef, void * inItemRef)
{
	
	/* XPLMSpeakString("SpeakString"); for debugging */

	int val;
	clouds = XPLMFindDataRef("sim/operation/override/override_clouds");
	val = XPLMGetDatai(clouds);

	if ( val == 0 )
		XPLMSetDatai(clouds, 1);

	if ( val == 1 )
		XPLMSetDatai(clouds, 0);

	checkClouds();
}


void checkClouds()
{
	int val;
	clouds = XPLMFindDataRef("sim/operation/override/override_clouds");
	val = XPLMGetDatai(clouds);
	if ( val == 1 )
		XPLMSetMenuItemName(pluginMenu, 0, "Enable Clouds", 0);
	else
		XPLMSetMenuItemName(pluginMenu, 0, "Disable Clouds", 0);	
}


PLUGIN_API void XPluginStop(void)
{
	XPLMDestroyMenu(pluginMenu);
}


PLUGIN_API void XPluginDisable(void)
{
}


PLUGIN_API int XPluginEnable(void)
{
	return 1;
}