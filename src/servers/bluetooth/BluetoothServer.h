/*
 * Copyright 2007 Oliver Ruiz Dorantes, oliver.ruiz.dorantes_at_gmail.com
 *
 * All rights reserved. Distributed under the terms of the MIT License.
 *
 */

#ifndef _BLUETOOTH_SERVER_APP_H
#define _BLUETOOTH_SERVER_APP_H

#include <stdlib.h>
#include <Application.h>
#include <OS.h>
#include <ObjectList.h>

#include "BPortNot.h"
#include "HCIDelegate.h"
#include "DeviceManager.h"
#include "LocalDeviceImpl.h"

#include <bluetooth/bluetooth.h>
#include <bluetooth/HCI/btHCI.h>
#include <bluetooth/HCI/btHCI_transport.h>
#include <bluetooth/HCI/btHCI_command.h>


#define BT "bluetooth_server: "

#define BLACKBOARD_GENERAL 		 0
#define BLACKBOARD_DEVICEMANAGER 1
#define BLACKBOARD_EVENTS        2
#define BLACKBOARD_KIT           3
#define BLACKBOARD_LD_OFFSET     4

typedef BObjectList<LocalDeviceImpl> LocalDevicesList;


class BluetoothServer : public BApplication
{
public:

	BluetoothServer();

	virtual bool QuitRequested(void);
	virtual void ArgvReceived(int32 argc, char **argv);
	virtual void ReadyToRun(void);


	virtual void AppActivated(bool act);
	virtual void MessageReceived(BMessage *message);
	
	
	static int32 notification_Thread(void* data);
	static int32 sdp_server_Thread(void* data);
	
	/* Messages reply */
	status_t	HandleLocalDevicesCount(BMessage* message, BMessage* reply);
	status_t    HandleAcquireLocalDevice(BMessage* message, BMessage* reply);
	status_t    HandleGetFriendlyName(BMessage* message, BMessage* reply);
	status_t    HandleGetAddress(BMessage* message, BMessage* reply);

	status_t    HandleSimpleRequest(BMessage* message, BMessage* reply);


    LocalDeviceImpl*    LocateLocalDeviceImpl(hci_id hid);

private:

	LocalDeviceImpl*	LocateDelegateFromMessage(BMessage* message);

	void 				ShowWindow(BWindow* pWindow);

	LocalDevicesList   	fLocalDevicesList;
	// UI

	// Notification system
	thread_id				fEventListener;
	DeviceManager*			fDeviceManager;

	BPoint 					fCenter;
};

#endif
