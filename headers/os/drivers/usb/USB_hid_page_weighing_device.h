/*
 * Copyright 2004-2010, Haiku Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _USB_HID_PAGE_WEIGHING_DEVICE_H
#define _USB_HID_PAGE_WEIGHING_DEVICE_H


/* Reference:
 *		HID Usage Page 0x8D: WEIGHING DEVICES
 *		HID Point of Sale Usage Tables Ver. 1.0
 *		http://www.usb.org/developers/devclass_docs/pos1_02.pdf
 */

// Usage IDs
enum {
	B_HID_UID_WD_WEIGHING_DEVICE = 0x01,
	
	B_HID_UID_WD_SCALE_DEVICE = 0x20,
	B_HID_UID_WD_SCALE_CLASS_I_METRIC,
	B_HID_UID_WD_SCALE_CLASS_II_METRIC,
	B_HID_UID_WD_SCALE_CLASS_III_METRIC,
	B_HID_UID_WD_SCALE_CLASS_IIIL_METRIC,
	B_HID_UID_WD_SCALE_CLASS_IV_METRIC,
	B_HID_UID_WD_SCALE_CLASS_III_ENGLISH,
	B_HID_UID_WD_SCALE_CLASS_IIIL_ENGLISH,
	B_HID_UID_WD_SCALE_CLASS_IV_ENGLISH,
	B_HID_UID_WD_SCALE_CLASS_GENERIC,
	
	B_HID_UID_WD_SCALE_ATTRIBUTE_REPORT = 0x30,
	B_HID_UID_WD_SCALE_CONTROL_REPORT,
	B_HID_UID_WD_SCALE_DATA_REPORT,
	B_HID_UID_WD_SCALE_STATUS_REPORT,
	B_HID_UID_WD_SCALE_WEIGHT_LIMIT_REPORT,
	B_HID_UID_WD_SCALE_STATISTICS_REPORT,
	
	B_HID_UID_WD_DATA_WEIGHT = 0x40,
	B_HID_UID_WD_DATA_SCALING,
	
	B_HID_UID_WD_WEIGHT_UNIT = 0x50,
	B_HID_UID_WD_WEIGHT_UNIT_MILLIGRAM,
	B_HID_UID_WD_WEIGHT_UNIT_GRAM,
	B_HID_UID_WD_WEIGHT_UNIT_KILOGRAM,
	B_HID_UID_WD_WEIGHT_UNIT_CARATS,
	B_HID_UID_WD_WEIGHT_UNIT_TAELS,
	B_HID_UID_WD_WEIGHT_UNIT_GRAINS,
	B_HID_UID_WD_WEIGHT_UNIT_PENNYWEIGHTS,
	B_HID_UID_WD_WEIGHT_UNIT_METRIC_TON,
	B_HID_UID_WD_WEIGHT_UNIT_AVOIR_TON,
	B_HID_UID_WD_WEIGHT_UNIT_TROY_OUNCE,
	B_HID_UID_WD_WEIGHT_UNIT_OUNCE,
	B_HID_UID_WD_WEIGHT_UNIT_POUND,
	
	B_HID_UID_WD_CALIBRATION_COUNT = 0x60,
	B_HID_UID_WD_REZERO_COUNT,
	
	B_HID_UID_WD_SCALE_STATUS = 0x70,
	B_HID_UID_WD_SCALE_STATUS_FAULT,
	B_HID_UID_WD_SCALE_STATUS_STABLE_AT_CENTER_OF_ZERO,
	B_HID_UID_WD_SCALE_STATUS_IN_MOTION,
	B_HID_UID_WD_SCALE_STATUS_WEIGHT_STABLE,
	B_HID_UID_WD_SCALE_STATUS_UNDER_ZERO,
	B_HID_UID_WD_SCALE_STATUS_OVER_WEIGHT_LIMIT,
	B_HID_UID_WD_SCALE_STATUS_REQUIRES_CALIBRATION,
	B_HID_UID_WD_SCALE_STATUS_REQUIRES_REZEROING,
	
	B_HID_UID_WD_ZERO_SCALE = 0x80,
	B_HID_UID_WD_ENFORCED_ZERO_RETURN
};


#endif // _USB_HID_PAGE_WEIGHING_DEVICE_H
