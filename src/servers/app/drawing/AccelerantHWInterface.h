//------------------------------------------------------------------------------
//
// Copyright 2005, Haiku, Inc.
// Distributed under the terms of the MIT License.
//
//
//	File Name:		AccelerantHWInterface.h
//	Author:			Michael Lotz <mmlr@mlotz.ch>
//					Stephan Aßmus <superstippi@gmx.de>
//	Description:	Accelerant based HWInterface implementation
//  
//------------------------------------------------------------------------------

#ifndef ACCELERANT_HW_INTERFACE_H
#define ACCELERANT_HW_INTERFACE_H

#include "HWInterface.h"
#include <image.h>

class BitmapBuffer;
class AccelerantBuffer;
class UpdateQueue;

class AccelerantHWInterface : public HWInterface {
public:
								AccelerantHWInterface();
virtual							~AccelerantHWInterface();

virtual	status_t				Initialize();
virtual	status_t				Shutdown();

virtual	status_t				SetMode(const display_mode &mode);
virtual	void					GetMode(display_mode *mode);

virtual status_t				GetDeviceInfo(accelerant_device_info *info);
virtual status_t				GetModeList(display_mode **mode_list,
											uint32 *count);
virtual status_t				GetPixelClockLimits(display_mode *mode,
													uint32 *low,
													uint32 *high);
virtual status_t				GetTimingConstraints(display_timing_constraints *dtc);
virtual status_t				ProposeMode(display_mode *candidate,
											const display_mode *low,
											const display_mode *high);

virtual status_t				WaitForRetrace(bigtime_t timeout = B_INFINITE_TIMEOUT);

virtual status_t				SetDPMSMode(const uint32 &state);
virtual uint32					DPMSMode() const;
virtual uint32					DPMSCapabilities() const;

	// frame buffer access
virtual	RenderingBuffer			*FrontBuffer() const;
virtual	RenderingBuffer			*BackBuffer() const;

protected:
virtual	void					_DrawCursor(BRect area) const;

private:
		int						OpenGraphicsDevice(int deviceNumber);
		status_t				SetupDefaultHooks();
		status_t				UpdateModeList();
		status_t				UpdateFrameBufferConfig();

		int						fCardFD;
		image_id				fAccelerantImage;
		GetAccelerantHook		fAccelerantHook;
		engine_token			*fEngineToken;
		
		// required hooks - guaranteed to be valid
		acquire_engine			fAccAcquireEngine;
		release_engine			fAccReleaseEngine;
		accelerant_mode_count	fAccGetModeCount;
		get_mode_list			fAccGetModeList;
		get_frame_buffer_config	fAccGetFrameBufferConfig;
		set_display_mode		fAccSetDisplayMode;
		get_pixel_clock_limits	fAccGetPixelClockLimits;
	
		// optional accelerant hooks
		get_timing_constraints	fAccGetTimingConstraints;
		propose_display_mode	fAccProposeDisplayMode;
		fill_rectangle			fAccFillRect;
		invert_rectangle		fAccInvertRect;
		screen_to_screen_blit	fAccScreenBlit;
		set_cursor_shape		fAccSetCursorShape;
		move_cursor				fAccMoveCursor;
		show_cursor				fAccShowCursor;					
		
		// dpms hooks
		dpms_capabilities		fAccDPMSCapabilities;
		dpms_mode				fAccDPMSMode;
		set_dpms_mode			fAccSetDPMSMode;

		frame_buffer_config		fFrameBufferConfig;
		int						fModeCount;
		display_mode			*fModeList;


		BitmapBuffer			*fBackBuffer;
		AccelerantBuffer		*fFrontBuffer;


		display_mode			fDisplayMode;

		UpdateQueue				*fUpdateExecutor;
};

#endif // ACCELERANT_HW_INTERFACE_H
