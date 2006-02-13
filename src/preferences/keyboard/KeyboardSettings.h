/*
** Copyright 2004, the Haiku project. All rights reserved.
** Distributed under the terms of the Haiku License.
**
** Author : mccall@digitalparadise.co.uk, Jérôme Duval
*/

#ifndef KEYBOARD_SETTINGS_H_
#define KEYBOARD_SETTINGS_H_

#include <SupportDefs.h>
#include "kb_mouse_settings.h"

class KeyboardSettings{
public :
	KeyboardSettings();
	~KeyboardSettings();
	
	void Dump();
	void Revert();
	void Defaults();
	
	BPoint WindowCorner() const { return fCorner; }
	void SetWindowCorner(BPoint corner);
	
	int32 KeyboardRepeatRate() const 
		{ return fSettings.key_repeat_rate; }
	void SetKeyboardRepeatRate(int32 rate);
	
	bigtime_t KeyboardRepeatDelay() const 
		{ return fSettings.key_repeat_delay; }
	void SetKeyboardRepeatDelay(bigtime_t delay);
	
private:
	BPoint				fCorner;
	kb_settings			fSettings;
	kb_settings			fOriginalSettings;
};

#endif
