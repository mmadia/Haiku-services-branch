/*
 * Copyright 2006, Axel Dörfler, axeld@pinc-software.de. All rights reserved.
 * Distributed under the terms of the MIT License.
 */


#include "FileTypes.h"
#include "FileTypeWindow.h"
#include "PreferredAppMenu.h"

#include <Application.h>
#include <Bitmap.h>
#include <Box.h>
#include <Button.h>
#include <MenuField.h>
#include <MenuItem.h>
#include <Mime.h>
#include <NodeInfo.h>
#include <PopUpMenu.h>
#include <TextControl.h>

#include <stdio.h>


const uint32 kMsgTypeEntered = 'type';
const uint32 kMsgSelectType = 'sltp';
const uint32 kMsgSameTypeAs = 'stpa';

const uint32 kMsgPreferredAppChosen = 'papc';
const uint32 kMsgSelectPreferredApp = 'slpa';
const uint32 kMsgSamePreferredAppAs = 'spaa';


FileTypeWindow::FileTypeWindow(BPoint position, const BMessage& refs)
	: BWindow(BRect(0.0f, 0.0f, 200.0f, 200.0f).OffsetBySelf(position),
		"File Type", B_TITLED_WINDOW,
		B_NOT_V_RESIZABLE | B_NOT_ZOOMABLE | B_ASYNCHRONOUS_CONTROLS)
{
	// "Icon" group

#if 0
	BFont font(be_bold_font);
	float labelWidth = font.StringWidth("Icon");
	font_height fontHeight;
	font.GetHeight(&fontHeight);

	BRect innerRect;
	fIconView = new IconView(innerRect, "icon box", NULL);
	fIconView->ResizeToPreferred();

	rect.left = rect.right + 12.0f + B_V_SCROLL_BAR_WIDTH;
	rect.right = rect.left + max_c(fIconView->Bounds().Width(), labelWidth) + 16.0f;
	rect.bottom = rect.top + ceilf(fontHeight.ascent)
		+ max_c(fIconView->Bounds().Height(),
			button->Bounds().Height() * 2.0f + 4.0f) + 12.0f;
	rect.top -= 2.0f;
	BBox* box = new BBox(rect);
	box->SetLabel("Icon");
	topView->AddChild(box);

	innerRect.left = 8.0f;
	innerRect.top = fontHeight.ascent / 2.0f
		+ (rect.Height() - fontHeight.ascent / 2.0f - fIconView->Bounds().Height()) / 2.0f
		+ 3.0f + fontHeight.ascent;
	if (innerRect.top + fIconView->Bounds().Height() > box->Bounds().Height() - 6.0f)
		innerRect.top = box->Bounds().Height() - 6.0f - fIconView->Bounds().Height();
	fIconView->MoveTo(innerRect.LeftTop());
	box->AddChild(fIconView);
#endif
	BRect rect = Bounds();
	BView* topView = new BView(rect, NULL, B_FOLLOW_ALL, B_WILL_DRAW);
	topView->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	AddChild(topView);

	// "File Type" group

	BFont font(be_bold_font);
//	float labelWidth = font.StringWidth("Icon");
	font_height fontHeight;
	font.GetHeight(&fontHeight);

	rect.InsetBy(8.0f, 8.0f);
	BBox* box = new BBox(rect, NULL, B_FOLLOW_LEFT_RIGHT);
	box->SetLabel("File Type");
	topView->AddChild(box);

	rect = box->Bounds();
	rect.InsetBy(8.0f, 4.0f + fontHeight.ascent + fontHeight.descent);
	fTypeControl = new BTextControl(rect, "type", NULL, NULL,
		new BMessage(kMsgTypeEntered), B_FOLLOW_LEFT_RIGHT);
	fTypeControl->SetDivider(0.0f);
	float width, height;
	fTypeControl->GetPreferredSize(&width, &height);
	fTypeControl->ResizeTo(rect.Width(), height);
	box->AddChild(fTypeControl);

	// filter out invalid characters that can't be part of a MIME type name
	BTextView* textView = fTypeControl->TextView();
	const char* disallowedCharacters = "/<>@,;:\"()[]?=";
	for (int32 i = 0; disallowedCharacters[i]; i++) {
		textView->DisallowChar(disallowedCharacters[i]);
	}

	rect.OffsetBy(0.0f, fTypeControl->Bounds().Height() + 5.0f);
	fSelectTypeButton = new BButton(rect, "select type", "Select" B_UTF8_ELLIPSIS,
		new BMessage(kMsgSelectType), B_FOLLOW_LEFT | B_FOLLOW_TOP);
	fSelectTypeButton->ResizeToPreferred();
	box->AddChild(fSelectTypeButton);

	rect.OffsetBy(fSelectTypeButton->Bounds().Width() + 8.0f, 0.0f);
	fSameTypeAsButton = new BButton(rect, "same type as", "Same As" B_UTF8_ELLIPSIS,
		new BMessage(kMsgSamePreferredAppAs), B_FOLLOW_LEFT | B_FOLLOW_TOP);
	fSameTypeAsButton->ResizeToPreferred();
	box->AddChild(fSameTypeAsButton);

	box->ResizeTo(box->Bounds().Width(), fSelectTypeButton->Frame().bottom
		+ 8.0f);

	// "Preferred Application" group

	rect.top = box->Frame().bottom + 8.0f;
	rect.bottom = rect.top + box->Bounds().Height();
	rect.left = 8.0f;
	rect.right = Bounds().Width() - 8.0f;
	box = new BBox(rect, NULL, B_FOLLOW_LEFT_RIGHT);
	box->SetLabel("Preferred Application");
	topView->AddChild(box);

	BMenu* menu = new BPopUpMenu("preferred");
	BMenuItem* item;
	menu->AddItem(item = new BMenuItem("Default Application",
		new BMessage(kMsgPreferredAppChosen)));
	item->SetMarked(true);

	rect = fTypeControl->Frame();
	BView* constrainingView = new BView(rect, NULL, B_FOLLOW_LEFT_RIGHT, B_WILL_DRAW);
	constrainingView->SetViewColor(topView->ViewColor());

	fPreferredField = new BMenuField(rect.OffsetToCopy(B_ORIGIN), "preferred",
		NULL, menu);
	fPreferredField->GetPreferredSize(&width, &height);
	fPreferredField->ResizeTo(rect.Width(), height);
	constrainingView->AddChild(fPreferredField);
		// we embed the menu field in another view to make it behave like
		// we want so that it can't obscure other elements with larger
		// labels

	box->AddChild(constrainingView);

	rect.OffsetBy(0.0f, fTypeControl->Bounds().Height() + 5.0f);
	fSelectAppButton = new BButton(rect, "select app", "Select" B_UTF8_ELLIPSIS,
		new BMessage(kMsgSelectPreferredApp), B_FOLLOW_LEFT | B_FOLLOW_TOP);
	fSelectAppButton->ResizeToPreferred();
	box->AddChild(fSelectAppButton);

	rect.OffsetBy(fSelectAppButton->Bounds().Width() + 8.0f, 0.0f);
	fSameAppAsButton = new BButton(rect, "same app as", "Same As" B_UTF8_ELLIPSIS,
		new BMessage(kMsgSamePreferredAppAs), B_FOLLOW_LEFT | B_FOLLOW_TOP);
	fSameAppAsButton->ResizeToPreferred();
	box->AddChild(fSameAppAsButton);

	ResizeTo(fSameAppAsButton->Frame().right + 100.0f, box->Frame().bottom + 8.0f);
	SetSizeLimits(fSameAppAsButton->Frame().right + 24.0f, 32767.0f, Bounds().Height(),
		Bounds().Height());

	fTypeControl->MakeFocus(true);

	BMimeType::StartWatching(this);
	_SetTo(refs);
}


FileTypeWindow::~FileTypeWindow()
{
	BMimeType::StopWatching(this);
}


BString
FileTypeWindow::_Title(const BMessage& refs)
{
	BString title;
	entry_ref ref;
	if (refs.FindRef("refs", 1, &ref) == B_OK) {
		bool same = false;
		BEntry entry, parent;
		if (entry.SetTo(&ref) == B_OK
			&& entry.GetParent(&parent) == B_OK) {
			same = true;

			// Check if all entries have the same parent directory
			for (int32 i = 0; refs.FindRef("refs", i, &ref) == B_OK; i++) {
				BEntry directory;
				if (entry.SetTo(&ref) == B_OK
					&& entry.GetParent(&directory) == B_OK) {
					if (directory != parent) {
						same = false;
						break;
					}
				}
			}
		}

		char name[B_FILE_NAME_LENGTH];
		if (same && parent.GetName(name) == B_OK) {
			title = "Multiple Files from \"";
			title.Append(name);
			title.Append("\"");
		} else
			title = "[Multiple Files]";
	} else if (refs.FindRef("refs", 0, &ref) == B_OK)
		title = ref.name;

	title.Append(" File Type");
	return title;
}


void
FileTypeWindow::_SetTo(const BMessage& refs)
{
	SetTitle(_Title(refs).String());

	// get common info and icons

	fCommonPreferredApp = "";
	fCommonType = "";
	entry_ref ref;
	for (int32 i = 0; refs.FindRef("refs", i, &ref) == B_OK; i++) {
		BNode node(&ref);
		if (node.InitCheck() != B_OK)
			continue;

		BNodeInfo info(&node);
		if (info.InitCheck() != B_OK)
			continue;

		// TODO: watch entries?

		entry_ref* copiedRef = new entry_ref(ref);
		fEntries.AddItem(copiedRef);

		char type[B_MIME_TYPE_LENGTH];
		if (info.GetType(type) != B_OK)
			type[0] = '\0';

		if (i > 0) {
			if (fCommonType != type)
				fCommonType = "";
		} else
			fCommonType = type;

		char preferredApp[B_MIME_TYPE_LENGTH];
		if (info.GetPreferredApp(preferredApp) != B_OK)
			preferredApp[0] = '\0';

		if (i > 0) {
			if (fCommonPreferredApp != preferredApp)
				fCommonPreferredApp = "";
		} else
			fCommonPreferredApp = preferredApp;
	}

	fTypeControl->SetText(fCommonType.String());
	_UpdatePreferredApps();
}


void
FileTypeWindow::_AdoptType()
{
	for (int32 i = 0; i < fEntries.CountItems(); i++) {
		BNode node(fEntries.ItemAt(i));
		BNodeInfo info(&node);
		if (node.InitCheck() != B_OK
			|| info.InitCheck() != B_OK)
			continue;

		info.SetType(fCommonType.String());
	}
}


void
FileTypeWindow::_AdoptPreferredApp()
{
	for (int32 i = 0; i < fEntries.CountItems(); i++) {
		BNode node(fEntries.ItemAt(i));
		if (fCommonPreferredApp.Length() == 0) {
			node.RemoveAttr("BEOS:PREF_APP");
			continue;
		}

		BNodeInfo info(&node);
		if (node.InitCheck() != B_OK
			|| info.InitCheck() != B_OK)
			continue;

		info.SetPreferredApp(fCommonPreferredApp.String());
	}
}


void
FileTypeWindow::_UpdatePreferredApps()
{
	BMimeType type(fCommonType.String());
	update_preferred_app_menu(fPreferredField->Menu(), &type,
		kMsgPreferredAppChosen, fCommonPreferredApp.String());
}


void
FileTypeWindow::MessageReceived(BMessage* message)
{
	switch (message->what) {
		// File Type group

		case kMsgTypeEntered:
			fCommonType = fTypeControl->Text();
			_AdoptType();
			break;

		// Preferred Application group

		case kMsgPreferredAppChosen:
		{
			const char* signature;
			if (message->FindString("signature", &signature) == B_OK)
				fCommonPreferredApp = signature;
			else
				fCommonPreferredApp = "";

			_AdoptPreferredApp();
			break;
		}

#if 0
		case kMsgSelectPreferredApp:
			be_app->PostMessage(kMsgOpenSelectPanel);
			break;
		case kMsgPreferredAppOpened:
			_AdoptPreferredApplication(message, false);
			break;

		case kMsgSamePreferredAppAs:
			be_app->PostMessage(kMsgOpenSameAsPanel);
			break;
		case kMsgSamePreferredAppAsOpened:
			_AdoptPreferredApplication(message, true);
			break;
#endif

		case B_META_MIME_CHANGED:
			const char* type;
			int32 which;
			if (message->FindString("be:type", &type) != B_OK
				|| message->FindInt32("be:which", &which) != B_OK)
				break;

			if (which == B_MIME_TYPE_DELETED
#ifdef __HAIKU__
				|| which == B_SUPPORTED_TYPES_CHANGED
#endif
				)
				_UpdatePreferredApps();
			break;

		default:
			BWindow::MessageReceived(message);
	}
}


bool
FileTypeWindow::QuitRequested()
{
	be_app->PostMessage(kMsgTypeWindowClosed);
	return true;
}

