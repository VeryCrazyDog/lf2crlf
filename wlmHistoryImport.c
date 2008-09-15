/*

    Windows Live Messenger History Import Plugin
    Imports messages from Windows Live Messenger
    Copyright (C) 2008  Very Crazy Dog (VCD)

    Based on
    Import plugin for Miranda IM
	Copyright (C) 2001,2002,2003,2004 Martin Öberg, Richard Hughes, Roland Rabien & Tristan Van de Vreede

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */

/*
 *
 * FileName: wlmHistoryImport.c
 * Description: This file contains functions for loading the plugin from DLL 
 * and also contains entry functions for the operation of the plugin. Functions
 * here are modified based on Import plugin for Miranda IM.
 *
 */

#include "WLMHistoryImport.h"
#include "resource.h"

// Variables for DLL loading
HINSTANCE hInst;
PLUGINLINK *pluginLink;

// Variables for plugin
struct MM_INTERFACE mmi;
static HWND hwndWizard = NULL;

// Functions declaration for plugin
BOOL CALLBACK wizardDlgProc(HWND hdlg,UINT message,WPARAM wParam,LPARAM lParam);

PLUGININFOEX pluginInfo = {
	sizeof(PLUGININFOEX),
	"Import WLM messages",
	PLUGIN_MAKE_VERSION(0,1,0,2),
	"Imports messages from Windows Live Messenger.",
	"Very Crazy Dog (VCD)",
	"Very_Crazy_Dog@yahoo.com.hk",
	"Copyright (C) 2008  Very Crazy Dog",
	"http://www.miranda-im.org/",
	UNICODE_AWARE,
	0,
	// UUID = {3bf4f550-1b3c-4739-a3db-c99eb912c422}
	{0x3bf4f550, 0x1b3c, 0x4739, { 0xa3, 0xdb, 0xc9, 0x9e, 0xb9, 0x12, 0xc4, 0x22 }}
};

/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////Functions for Plugin//////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

static int importCommand(WPARAM wParam,LPARAM lParam)
{
	if (IsWindow(hwndWizard)) {
		SetForegroundWindow(hwndWizard);
		SetFocus(hwndWizard);
	}
	else {
		hwndWizard = CreateDialog(hInst, MAKEINTRESOURCE(IDD_WIZARD), NULL, wizardDlgProc);
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////Functions for DLL Loading/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// DLL main function
BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	hInst = hinstDLL;
	return TRUE;
}

// MirandaPluginInfoEx - returns an information about a plugin
__declspec(dllexport) PLUGININFOEX* MirandaPluginInfoEx(DWORD mirandaVersion)
{
	if (mirandaVersion < PLUGIN_MAKE_VERSION(0, 7, 0, 0))
		return NULL;

	return &pluginInfo;
}

// MirandaPluginInterfaces - returns the protocol interface to the core
static const MUUID interfaces[] = {MIID_IMPORT, MIID_LAST};

__declspec(dllexport) const MUUID* MirandaPluginInterfaces(void)
{
	return interfaces;
}

// Performs a primary set of actions upon plugin loading
int __declspec(dllexport) Load(PLUGINLINK *link)
{
	pluginLink = link;
	mir_getMMI( &mmi );

	CreateServiceFunction(WLM_IMPORT_SERVICE, importCommand);
	{
		CLISTMENUITEM mi;
		ZeroMemory(&mi, sizeof(mi));
		mi.cbSize = sizeof(mi);
		mi.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_IMPORT));
		mi.pszName = Translate("&WLM Import...");
		mi.position = 500050000;
		mi.pszService = WLM_IMPORT_SERVICE;
		CallService(MS_CLIST_ADDMAINMENUITEM, 0, (LPARAM)&mi);
	}

	return 0;
}

// Unload the plugin
int __declspec(dllexport) Unload(void)
{
	return 0;
}
