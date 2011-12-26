/*
 * Copyright 2011 Haiku Inc.
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef B_CONTACT_DEFS_H
#define B_CONTACT_DEFS_H

#include <Errors.h>

enum DefaultDefs {
	B_CONTACT_ANY = 'BCAN'
};

enum ContactGroupDefs {
	B_CONTACT_GROUP_DEFAULT = 'BCGD'
};

enum ContactFieldType {
	B_CONTACT_NAME 			= 'CFNN',
	B_CONTACT_NICKNAME 		= 'CFNK',
	B_CONTACT_PHOTO 		= 'CFNH',
	B_CONTACT_ADDRESS 		= 'CFNA',
	B_CONTACT_PHONE			= 'CFNP',
	B_CONTACT_EMAIL			= 'CFNE',
	B_CONTACT_URL			= 'CFNU',
	B_CONTACT_GEO			= 'CFNG',
	B_CONTACT_NOTE			= 'CFNO',
	B_CONTACT_ORGANIZATION  = 'CFNJ',
	B_CONTACT_IM			= 'CFNI',
	B_CONTACT_UID			= 'CFND',
	B_CONTACT_GROUP			= 'CFNR',
	B_CONTACT_PROTOCOLS 	= 'CFNL'
};

enum CommonFieldUsageTypes {
	CONTACT_DATA_CUSTOM = 'CDTC',
	CONTACT_DATA_OTHER	= 'CDOT',	
	CONTACT_DATA_HOME	= 'CDHM',
	CONTACT_DATA_WORK	= 'CDWK'
};

enum SpecificFieldUsageTypes {
	CONTACT_NAME_FAMILY = 'CNFM',
	CONTACT_NAME_GIVEN	= 'CNGV',
	CONTACT_NAME_MIDDLE	= 'CNMD',
	CONTACT_NAME_SUFFIX	= 'CNSF',

	CONTACT_NICKNAME_DEFAULT = 'CNDF',
	CONTACT_NICKNAME_MAIDEN	 = 'CNMN',
	CONTACT_NICKNAME_SHORT_NAME	 = 'CNSN',
	CONTACT_NICKNAME_INITIALS	 = 'CNIN',

	CONTACT_EMAIL_MOBILE = 'CEMB',

	CONTACT_PHONE_MOBILE = 'CPMB',
	CONTACT_PHONE_FAX_WORK = 'CPFW',
	CONTACT_PHONE_FAX_HOME = 'CPFH',
	CONTACT_PHONE_PAGER = 'CPPG',
	CONTACT_PHONE_CALLBACK = 'CPXK',
	CONTACT_PHONE_CAR = 'CPCR',
	CONTACT_PHONE_ORG_MAIN = 'CPOM',
	CONTACT_PHONE_ISDN = 'CPIN',
	CONTACT_PHONE_MAIN  = 'CPMN',
	CONTACT_PHONE_RADIO = 'CPRA',
	CONTACT_PHONE_TELEX = 'CPTE',
	CONTACT_PHONE_TTY_TDD = 'CPTY',
	CONTACT_PHONE_WORK_MOBILE = 'CPWM',
	CONTACT_PHONE_WORK_PAGER = 'CPWP',
	CONTACT_PHONE_ASSISTANT = 'CPAS',
	CONTACT_PHONE_MMS = 'CPMS',

	CONTACT_PHOTO_URL = 'CPUL',
	CONTACT_PHOTO_REF = 'CPRF',
	CONTACT_PHOTO_BITMAP = 'CPBT'
};

#endif // B_CONTACT_DEFS_H
