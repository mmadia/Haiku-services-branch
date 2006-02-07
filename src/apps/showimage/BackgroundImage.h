/*
Open Tracker License

Terms and Conditions

Copyright (c) 1991-2000, Be Incorporated. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice applies to all licensees
and shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF TITLE, MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
BE INCORPORATED BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF, OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of Be Incorporated shall not be
used in advertising or otherwise to promote the sale, use or other dealings in
this Software without prior written authorization from Be Incorporated.

Tracker(TM), Be(R), BeOS(R), and BeIA(TM) are trademarks or registered trademarks
of Be Incorporated in the United States and other countries. Other brand product
names are registered trademarks or trademarks of their respective holders.
All rights reserved.
*/
#ifndef BACKGROUND_IMAGE_H
#define BACKGROUND_IMAGE_H


#include <SupportDefs.h>

class BDirectory;


class BackgroundImage {
	// This class knows everything about which bitmap to use for a given
	// view and how.
	// Unlike other windows, the Desktop window can have different backgrounds
	// for each workspace
	public:
		enum Mode {
			kAtOffset,
			kCentered,			// only works on Desktop
			kScaledToFit,		// only works on Desktop
			kTiled
		};

		static status_t SetImage(BDirectory& directory, const char* path, Mode mode,
							BPoint offset, bool eraseIconBackground = false);
		static status_t SetDesktopImage(BDirectory& directory, uint32 workspaces,
							const char* path, Mode mode, BPoint offset,
							bool eraseIconBackground = false);

	private:
		static status_t _SetImage(BDirectory& directory, bool desktop, uint32 workspaces,
							const char* path, Mode mode, BPoint offset,
							bool eraseIconBackground);
		static status_t _GetImages(BDirectory& directory, BMessage& images);
		static status_t _NotifyTracker(BDirectory& directory, bool desktop);
};

#endif	// BACKGROUND_IMAGE_H
