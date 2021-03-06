/*
 * Copyright 2011 Dario Casalinuovo
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include <ContactField.h>

#include <shared/AutoDeleter.h>
#include <ContactDefs.h>
#include <DataIO.h>
#include <String.h>

#include <assert.h>
#include <stdio.h>

// TODO add decent debug to whole kit

struct EqualityVisitorBase : public BContactFieldVisitor {
	EqualityVisitorBase() : result(false) {}
	bool result;

	virtual void Visit(BStringContactField* field) {}
	virtual void Visit(BAddressContactField* field) {}
	virtual void Visit(BPhotoContactField* field) {}
};

struct CopyVisitorBase : public BContactFieldVisitor {
	CopyVisitorBase() : error(B_ERROR) {}
	status_t error;

	virtual void Visit(BStringContactField* field) {}
	virtual void Visit(BAddressContactField* field) {}
	virtual void Visit(BPhotoContactField* field) {}
};


BContactField::BContactField(field_type type, bool autoLabel)
	:
	fType(type),
	fUsage(-1)
{
	if (autoLabel)
		fLabel = SimpleLabel(type);
}


BContactField::~BContactField()
{
}


field_type
BContactField::FieldType() const
{
	return fType;
}


field_usage
BContactField::Usage() const
{
	return fUsage;
}


void
BContactField::SetUsage(field_usage usage)
{
	fUsage = usage;
}


// This is basically a common way to get a generic label
const char*
BContactField::SimpleLabel(field_type type)
{
	BString label;
	switch (type) {
		case B_CONTACT_ADDRESS:
			label.SetTo("Address");
		break;

		case B_CONTACT_BIRTHDAY:
			label.SetTo("Birthday");
		break;

		case B_CONTACT_EMAIL:
			label.SetTo("Email");
		break;

		case B_CONTACT_FORMATTED_NAME:
			label.SetTo("Formatted Name");
		break;

		// TODO add a function that opens a webpositive tab
		// with google maps and the coordinates set
		case B_CONTACT_GEO:
			label.SetTo("Geographic location");
		break;

		case B_CONTACT_GROUP:
			label.SetTo("Group");
		break;

		case B_CONTACT_IM:
			label.SetTo("IM");
		break;

		case B_CONTACT_LABEL:
			label.SetTo("Label");
		break;

		case B_CONTACT_NAME:
			label.SetTo("Name");
		break;

		case B_CONTACT_NICKNAME:
			label.SetTo("Nickname");
		break;

		case B_CONTACT_NOTE:
			label.SetTo("Note");
		break;

		case B_CONTACT_ORGANIZATION:
			label.SetTo("Organization");
		break;

		break;
		case B_CONTACT_PHONE:
			label.SetTo("Phone/Fax");
		break;

		case B_CONTACT_PHOTO:
			label.SetTo("Photo");
		break;

		case B_CONTACT_PROTOCOLS:
			label.SetTo("Protocols");
		break;

		case B_CONTACT_SIMPLE_GROUP:
			label.SetTo("Simple Group");
		break;

		case B_CONTACT_SOUND:
			label.SetTo("Sound");
		break;

		case B_CONTACT_TIME_ZONE:
			label.SetTo("Time zone");
		break;

		case B_CONTACT_TITLE:
			label.SetTo("Title");
		break;

		case B_CONTACT_URL:
			label.SetTo("URL");
		break;

		case B_CONTACT_UID:
			label.SetTo("Contact ID");
		break;

		case B_CONTACT_REV:
			label.SetTo("Revision");
		break;

		case B_CONTACT_CUSTOM:
			label.SetTo("Custom");
		break;
	}
	return label.String();
}


// this is used to load a label that explains field usage
const char*
BContactField::ExtendedLabel(field_type type, field_usage usage)
{
	BString label = SimpleLabel(type);

	switch (usage) {
		case CONTACT_DATA_HOME:
			label.Prepend("Home ");
		break;

		case CONTACT_DATA_WORK:
			label.Prepend("Work ");
		break;

		case CONTACT_DATA_CUSTOM:
			label.Prepend("Custom ");
		break;
		case CONTACT_DATA_OTHER:
			label.Prepend("Other ");
		break;

		case CONTACT_NAME_FAMILY:
			label.Prepend("Family ");
		break;

		case CONTACT_NAME_GIVEN:
			label.Prepend("Given ");		
		break;

		case CONTACT_NAME_MIDDLE:
			label.Prepend("Middle ");
		break;

		case CONTACT_NAME_SUFFIX:
			label.SetTo("Name Suffix");
		break;

		case CONTACT_NICKNAME_DEFAULT:
			label.SetTo("Preferred Nickname");
		break;

		case CONTACT_NICKNAME_MAIDEN:
			label.SetTo("Maiden Nickname");
		break;

		case CONTACT_NICKNAME_SHORT_NAME:
			label.SetTo("Short Name Nickname");
		break;

		case CONTACT_NICKNAME_INITIALS:
			label.SetTo("Nickname Initials");
		break;

		case CONTACT_EMAIL_MOBILE:
			label.SetTo("Mobile email");
		break;

		case CONTACT_PHONE_MOBILE:
			label.SetTo("Mobile Phone");
		break;

		case CONTACT_PHONE_FAX_WORK:
			label.SetTo("Work Fax");
		break;

		case CONTACT_PHONE_FAX_HOME:
			label.SetTo("Home Fax");
		break;

		case CONTACT_PHONE_PAGER:
			label.SetTo("Phone (pager)");
		break;

		case CONTACT_PHONE_CALLBACK:
			label.SetTo("Phone (callback)");		
		break;

		case CONTACT_PHONE_CAR:
			label.SetTo("Phone (car)");
		break;

		case CONTACT_PHONE_ORG_MAIN:
			label.SetTo("Main Phone (org)");
		break;

		case CONTACT_PHONE_ISDN:
			label.SetTo("Phone ISDN");
		break;

		case CONTACT_PHONE_MAIN:
			label.SetTo("Main Phone");
		break;

		case CONTACT_PHONE_RADIO:
			label.SetTo("Phone (radio)");
		break;

		case CONTACT_PHONE_TELEX:
			label.SetTo("Phone (telex)");
		break;

		case CONTACT_PHONE_TTY_TDD:
			label.SetTo("Phone (tty/tdd)");
		break;

		case CONTACT_PHONE_WORK_MOBILE:
			label.SetTo("Work Mobile Phone");
		break;

		case CONTACT_PHONE_WORK_PAGER:
			label.SetTo("Work Phone (pager)");
		break;

		case CONTACT_PHONE_ASSISTANT:
			label.SetTo("Phone Assistant");
		break;

		case CONTACT_PHONE_MMS:
			label.SetTo("MMS Phone");
		break;
	}
	return label.String();
}


const BString&
BContactField::Label() const
{
	return fLabel;
}


void
BContactField::SetLabel(const BString& label)
{
	fLabel.SetTo(label);
}


bool
BContactField::IsFixedSize() const
{ 
	return false;
}


type_code
BContactField::TypeCode() const
{
	return B_CONTACT_FIELD_TYPE;
}


bool
BContactField::AllowsTypeCode(type_code code) const
{
	if (code != B_CONTACT_FIELD_TYPE)
		return false;
	
	return true;
}


ssize_t
BContactField::FlattenedSize() const
{
	ssize_t size = sizeof(type_code);

	return size + sizeof(fUsage);
}


status_t
BContactField::Flatten(BPositionIO* flatData) const
{
	if (flatData == NULL)
		return B_BAD_VALUE;

	// TODO ADD ENDIANESS CODE

	// NOTE this is needed because we need to know
	// whitch derived class we need to instantiate
	// in BContactField::UnflattenChildClass()
	flatData->Write(&fType, sizeof(type_code));

	flatData->Write(&fUsage, sizeof(fUsage));

	return B_OK;
}


status_t
BContactField::Flatten(void* buffer, ssize_t size) const
{
	if (buffer == NULL)
		return B_BAD_VALUE;

	BMemoryIO flatData(buffer, size);
	return Flatten(&flatData, size);
}


status_t
BContactField::Unflatten(type_code code,
	const void* buffer,	ssize_t size)
{
	if (buffer == NULL)
		return B_BAD_VALUE;

	BMemoryIO flatData(buffer, size);
	return Unflatten(code, &flatData);
}


status_t
BContactField::Unflatten(type_code code, BPositionIO* flatData)
{
	if (code != B_CONTACT_FIELD_TYPE)
		return B_BAD_VALUE;

	// read the type of the field	
	flatData->Read(&fType, sizeof(type_code));

	flatData->Read(&fUsage, sizeof(fUsage));

	return B_OK;
}


status_t
BContactField::CopyDataFrom(BContactField* field)
{
	return B_ERROR;
}


// You cannot instantiate a pure BContactField
// so this method help to unflatten the correct 
// derived class
BContactField*
BContactField::UnflattenChildClass(const void* from, ssize_t size)
{
	BMemoryIO data(from, size);

	type_code childType;
	data.Read(&childType, sizeof(childType));
	ObjectDeleter<BContactField> deleter;
	BContactField* child = NULL;
	switch (childType) {
		case B_CONTACT_BIRTHDAY:
		case B_CONTACT_EMAIL:
		case B_CONTACT_FORMATTED_NAME:
		case B_CONTACT_GEO:
		case B_CONTACT_GROUP:
		case B_CONTACT_IM:
		case B_CONTACT_LABEL:
		case B_CONTACT_NAME:
		case B_CONTACT_NICKNAME:
		case B_CONTACT_NOTE:
		case B_CONTACT_ORGANIZATION:
		case B_CONTACT_PHONE:
		case B_CONTACT_PROTOCOLS:
		case B_CONTACT_SIMPLE_GROUP:
		case B_CONTACT_SOUND:
		case B_CONTACT_TIME_ZONE:
		case B_CONTACT_TITLE:
		case B_CONTACT_URL:
		case B_CONTACT_UID:
		case B_CONTACT_REV:
			child = new BStringContactField(childType);
			break;

		case B_CONTACT_ADDRESS:
			child = new BAddressContactField();
			break;
		case B_CONTACT_PHOTO:
			child = new BPhotoContactField();
			break;
		case B_CONTACT_CUSTOM:
			//child = new BCustomContactField();
			break;

		default:
			return NULL;
	}

	if (child == NULL)
		return NULL;

	status_t ret = child->Unflatten(B_CONTACT_FIELD_TYPE, from, size);
	if (ret == B_OK)
		return child;

	deleter.SetTo(child);
	return NULL;
}


BContactField*
BContactField::Duplicate(BContactField* from)
{
	BContactField* child = NULL;
	type_code childType = from->FieldType();
	ObjectDeleter<BContactField> deleter;

	switch (childType) {
		case B_CONTACT_BIRTHDAY:
		case B_CONTACT_EMAIL:
		case B_CONTACT_FORMATTED_NAME:
		case B_CONTACT_GEO:
		case B_CONTACT_GROUP:
		case B_CONTACT_IM:
		case B_CONTACT_LABEL:
		case B_CONTACT_NAME:
		case B_CONTACT_NICKNAME:
		case B_CONTACT_NOTE:
		case B_CONTACT_ORGANIZATION:
		case B_CONTACT_PHONE:
		case B_CONTACT_PROTOCOLS:
		case B_CONTACT_SIMPLE_GROUP:
		case B_CONTACT_SOUND:
		case B_CONTACT_TIME_ZONE:
		case B_CONTACT_TITLE:
		case B_CONTACT_URL:
		case B_CONTACT_UID:
		case B_CONTACT_REV:
			child = new BStringContactField(childType);
			break;

		case B_CONTACT_ADDRESS:
			child = new BAddressContactField();
			break;
		case B_CONTACT_PHOTO:
			child = new BPhotoContactField();
			break;
		case B_CONTACT_CUSTOM:
			//child = new BCustomContactField();
			break;
	}

	if (child != NULL && child->CopyDataFrom(from) == B_OK)
		return child;

	deleter.SetTo(child);
	return NULL;
}


BContactField*
BContactField::InstantiateChildClass(type_code type)
{
	BContactField* child = NULL;
	switch (type) {
		case B_CONTACT_BIRTHDAY:
		case B_CONTACT_EMAIL:
		case B_CONTACT_FORMATTED_NAME:
		case B_CONTACT_GEO:
		case B_CONTACT_GROUP:
		case B_CONTACT_IM:
		case B_CONTACT_LABEL:
		case B_CONTACT_NAME:
		case B_CONTACT_NICKNAME:
		case B_CONTACT_NOTE:
		case B_CONTACT_ORGANIZATION:
		case B_CONTACT_PHONE:
		case B_CONTACT_PROTOCOLS:
		case B_CONTACT_SIMPLE_GROUP:
		case B_CONTACT_SOUND:
		case B_CONTACT_TIME_ZONE:
		case B_CONTACT_TITLE:
		case B_CONTACT_URL:
		case B_CONTACT_UID:
		case B_CONTACT_REV:
			child = new BStringContactField(type);
			break;

		case B_CONTACT_ADDRESS:
			child = new BAddressContactField();
			break;
		case B_CONTACT_PHOTO:
			child = new BPhotoContactField();
			break;
		case B_CONTACT_CUSTOM:
			//child = new BCustomContactField();
			break;

		default:
			return NULL;
	}

	if (child == NULL)
		return NULL;

	return child;
}


bool
BContactField::IsHidden() const
{
	switch (fType) {
		case B_CONTACT_BIRTHDAY:
		case B_CONTACT_EMAIL:
		case B_CONTACT_FORMATTED_NAME:
		case B_CONTACT_GEO:
		case B_CONTACT_IM:
		case B_CONTACT_LABEL:
		case B_CONTACT_NAME:
		case B_CONTACT_NICKNAME:
		case B_CONTACT_NOTE:
		case B_CONTACT_ORGANIZATION:
		case B_CONTACT_PHONE:
		case B_CONTACT_PROTOCOLS:
		case B_CONTACT_SIMPLE_GROUP:
		case B_CONTACT_SOUND:
		case B_CONTACT_TIME_ZONE:
		case B_CONTACT_TITLE:
		case B_CONTACT_URL:
		case B_CONTACT_PHOTO:
		case B_CONTACT_CUSTOM:
			return false;
			break;

		case B_CONTACT_ADDRESS:
		case B_CONTACT_GROUP:
		case B_CONTACT_UID:
		case B_CONTACT_REV:
			return true;
			break;
	}
	return false;
}


ssize_t
BContactField::_AddStringToBuffer(BPositionIO* buffer, const BString& str) const
{
	ssize_t valueLength = str.Length();
	if (valueLength > 0) {
		ssize_t ret = buffer->Write(&valueLength, sizeof(valueLength));
		return ret + buffer->Write(str, valueLength);
	} else
		return buffer->Write(0, sizeof(ssize_t));

	return -1;
}


BString
BContactField::_ReadStringFromBuffer(BPositionIO* buffer, ssize_t len)
{
	BString ret;
	if (len == -1)
		buffer->Read(&len, sizeof(len));

	char* valueBuffer;
	if (len != 0) {
		ArrayDeleter<char> deleter(valueBuffer = new char[len]);
		buffer->Read(valueBuffer, len);
		ret = BString(valueBuffer, len);
	} else {
		ret = BString();
	}
	return ret; 
}

// BStringContactField

BStringContactField::BStringContactField(type_code type, const BString& str)   
	:
	BContactField(type),
	fValue(str)
{
}


BStringContactField::BStringContactField(type_code type, const char* str) 
	:
	BContactField(type),
	fValue(str)
{
}


BStringContactField::~BStringContactField()
{	
}


struct BStringContactField::CopyVisitor : public CopyVisitorBase {

	BStringContactField* fOwner;

	CopyVisitor(BStringContactField* owner)
		:
		CopyVisitorBase(),
		fOwner(owner)
		{
		}

	virtual void Visit(BStringContactField* field)
	{
		fOwner->SetUsage(field->Usage());
		fOwner->SetValue(field->Value());
		error = B_OK;
	}

	virtual void Visit(BAddressContactField* field)
	{
	}

	virtual void Visit(BPhotoContactField* field)
	{
	}
};


struct BStringContactField::EqualityVisitor : public EqualityVisitorBase {

	BStringContactField* fOwner;

	EqualityVisitor(BStringContactField* owner)
		:
		EqualityVisitorBase(),
		fOwner(owner) 
		{
		}

	virtual void Visit(BStringContactField* field)
	{
		if (fOwner->Usage() == field->Usage())
			result = true;

		if (field->Value().Compare(fOwner->Value()) == 0)
			result = true;
	}

	virtual void Visit(BAddressContactField* field)
	{
	}

	virtual void Visit(BPhotoContactField* field)
	{
	}
};


void
BStringContactField::Accept(BContactFieldVisitor* v)
{ 
	v->Visit(this);
}


bool
BStringContactField::IsEqual(BContactField* field)
{
	BStringContactField::EqualityVisitor equalityChecker(this);
	field->Accept(&equalityChecker);
	return equalityChecker.result;
}


void
BStringContactField::SetValue(const BString& value)
{
	fValue.SetTo(value);	
}


void
BStringContactField::SetUsage(int32 usage)
{
	fUsage = usage;
}


const BString&
BStringContactField::Value() const
{
	return fValue;
}


// this method should take a BStringContactField
status_t
BStringContactField::CopyDataFrom(BContactField* field)
{
	BStringContactField::CopyVisitor copier(this);
	field->Accept(&copier);
	return copier.error;
}


ssize_t
BStringContactField::FlattenedSize() const
{
	ssize_t size = BContactField::FlattenedSize();
	size += sizeof(ssize_t);
	size += fValue.Length();

	return size;
}


status_t
BStringContactField::Flatten(void* buffer, ssize_t size) const
{
	if (size < FlattenedSize())
		return B_ERROR;

	BMemoryIO flatData(buffer, size);
	status_t ret = BContactField::Flatten(&flatData);
	if (ret != B_OK)
		return ret;

	_AddStringToBuffer(&flatData, fValue);

	return B_OK;
}


status_t
BStringContactField::Unflatten(type_code code,
	const void* buffer,	ssize_t size)
{
	BMemoryIO data(buffer, size);
	status_t ret = BContactField::Unflatten(code, &data);
	if (ret != B_OK)
		return ret;

	fValue = _ReadStringFromBuffer(&data);
	SetUsage(fUsage);
	return B_OK;
}

/** BAddressContactField **/

struct BAddressContactField::CopyVisitor : public CopyVisitorBase {

	BAddressContactField* fOwner;

	CopyVisitor(BAddressContactField* owner)
		:
		CopyVisitorBase(),
		fOwner(owner)
		{
		}

	virtual void Visit(BStringContactField* field)
	{
	}

	virtual void Visit(BAddressContactField* field)
	{
		fOwner->SetValue(field->Value());
		fOwner->SetUsage(field->Usage());
		error = B_OK;
	}

	virtual void Visit(BPhotoContactField* field)
	{
	}
};


struct BAddressContactField::EqualityVisitor : public EqualityVisitorBase {

	BAddressContactField* fOwner;

	EqualityVisitor(BAddressContactField* owner)
		:
		EqualityVisitorBase(),
		fOwner(owner) 
		{
		}

	virtual void Visit(BStringContactField* field)
	{
	}

	virtual void Visit(BAddressContactField* field)
	{
		if (fOwner->Value().Compare(fOwner->Value()) == 0)
			if (fOwner->Usage() == field->Usage())
				result = true;
	}

	virtual void Visit(BPhotoContactField* field)
	{
	}
};


/*
BAddressContactField::BAddressContactField(const BAddress& address)
	:
	BContactField(B_CONTACT_ADDRESS)
{
}*/


BAddressContactField::BAddressContactField(BString address, bool isLabel)
  	:
	BContactField(B_CONTACT_ADDRESS),
	fIsLabel(isLabel)
{
	_SplitValue(address);
}


BAddressContactField::~BAddressContactField()
{
}


void
BAddressContactField::Accept(BContactFieldVisitor* v)
{
	v->Visit(this);
}


bool
BAddressContactField::IsEqual(BContactField* field)
{
	BAddressContactField::EqualityVisitor equalityChecker(this);
	field->Accept(&equalityChecker);
	return equalityChecker.result;
}


void
BAddressContactField::SetValue(const BString& value)
{
	_SplitValue(value);
}


const BString&
BAddressContactField::Value() const
{
	// this is returning the address
	// as described in the vcard-21 spec

	if (!fValue.IsEmpty())
		return fValue;

	fValue << fPostalBox << ";" << fNeighbor << ";";
	fValue << fStreet << ";" << fCity << ";" << fRegion;
	fValue << ";" << fPostalCode << ";" << fCountry << ";"; 

	return fValue;
}


status_t
BAddressContactField::CopyDataFrom(BContactField* field)
{
	BAddressContactField::CopyVisitor copier(this);
	field->Accept(&copier);
	return copier.error;
}


bool
BAddressContactField::IsLabel() const
{
	return fIsLabel;	
}


const BString&
BAddressContactField::Street() const
{
	return fStreet;
}


const BString&
BAddressContactField::PostalBox() const
{
	return fPostalBox;
}


const BString&
BAddressContactField::Neighborhood() const
{
	return fNeighbor;
}


const BString&
BAddressContactField::City() const
{
	return fCity;
}


const BString&
BAddressContactField::Region() const
{
	return fRegion;
}


const BString&
BAddressContactField::PostalCode() const
{
	return fPostalCode;
}


const BString&
BAddressContactField::Country() const
{
	return fCountry;
}


void
BAddressContactField::SetStreet(const BString& street)
{
	fValue = "";
	fStreet.SetTo(street);
}


void
BAddressContactField::SetPostalBox(const BString& postBox)
{
	fValue = "";
	fPostalBox.SetTo(postBox);
}


void
BAddressContactField::SetNeighborhood(const BString& neighbor)
{
	fValue = "";
	fNeighbor.SetTo(neighbor);
}


void
BAddressContactField::SetCity(const BString& city)
{
	fValue = "";
	fCity.SetTo(city);
}


void
BAddressContactField::SetRegion(const BString& region)
{
	fValue = "";
	fRegion.SetTo(region);
}


void
BAddressContactField::SetPostalCode(const BString& postalCode)
{
	fValue = "";
	fPostalCode.SetTo(postalCode);
}


void
BAddressContactField::SetCountry(const BString& country)
{
	fValue = "";
	fCountry.SetTo(country);
}


ssize_t
BAddressContactField::FlattenedSize() const
{
	ssize_t size = BContactField::FlattenedSize();
	size += sizeof(ssize_t);
	size += Value().Length();

	return size + sizeof(fIsLabel);
}


status_t
BAddressContactField::Flatten(void* buffer, ssize_t size) const
{
	if (size < FlattenedSize())
		return B_ERROR;

	BMemoryIO flatData(buffer, size);
	status_t ret = BContactField::Flatten(&flatData);
	if (ret != B_OK)
		return ret;

	_AddStringToBuffer(&flatData, Value());

	flatData.Write(&fIsLabel, sizeof(fIsLabel));

	return B_OK;
}


status_t
BAddressContactField::Unflatten(type_code code,
	const void* buffer,	ssize_t size)
{
	BMemoryIO data(buffer, size);
	status_t ret = BContactField::Unflatten(code, &data);
	if (ret != B_OK)
		return ret;

	SetValue(_ReadStringFromBuffer(&data));
	data.Read(&fIsLabel, sizeof(fIsLabel));

	return B_OK;

}


bool
BAddressContactField::_SplitValue(const BString& str)
{
	BString value(str);
	_PopValue(value, fPostalBox);
	_PopValue(value, fNeighbor);
	_PopValue(value, fStreet);
	_PopValue(value, fCity);
	_PopValue(value, fRegion);
	_PopValue(value, fPostalCode);
	_PopValue(value, fCountry);
	return true;
}


void
BAddressContactField::_PopValue(BString& str, BString& value)
{
	int32 index = str.FindFirst(";", 0);
	if (index == B_ERROR) {
		value.SetTo("");
		return;
	}
	str.MoveInto(value, 0, index);
	str.Remove(0,1);
}

/** BPhotoContactField */

// TODO add support for refs and urls photos, then
// fix the visitors, to allow fields compare

struct BPhotoContactField::CopyVisitor : public CopyVisitorBase {

	BPhotoContactField* fOwner;

	CopyVisitor(BPhotoContactField* owner)
		:
		CopyVisitorBase(),
		fOwner(owner)
		{
		}

	virtual void Visit(BStringContactField* field)
	{
	}

	virtual void Visit(BAddressContactField* field)
	{
	}

	virtual void Visit(BPhotoContactField* field)
	{
		error = B_OK;
	}
};


struct BPhotoContactField::EqualityVisitor : public EqualityVisitorBase {

	BPhotoContactField* fOwner;

	EqualityVisitor(BPhotoContactField* owner)
		:
		EqualityVisitorBase(),
		fOwner(owner) 
		{
		}

	virtual void Visit(BStringContactField* field)
	{
	}

	virtual void Visit(BAddressContactField* field)
	{
	}


	virtual void Visit(BPhotoContactField* field)
	{
		/*if (fOwner->RefToPhoto() == field->RefToPhoto())
			result = true;*/

		/*if (field->Value().Compare(fOwner->Value()) == 0)
			result = true;*/
	}
};


BPhotoContactField::BPhotoContactField(BBitmap* bitmap)   
	:
	BContactField(B_CONTACT_PHOTO),
	fBitmap(bitmap),
	fUrl(),
	fPhotoType(CONTACT_PHOTO_BITMAP),
	fPictureType(0)
{
}

/*
BPhotoContactField::BPhotoContactField(const char* url)   
	:
	BContactField(B_CONTACT_PHOTO),
	fPhotoType(CONTACT_PHOTO_URL)
{

}
*/

BPhotoContactField::~BPhotoContactField()
{
	_CleanUp();	
}


void
BPhotoContactField::Accept(BContactFieldVisitor* v)
{ 
	v->Visit(this);
}


bool
BPhotoContactField::IsEqual(BContactField* field)
{
	BPhotoContactField::EqualityVisitor equalityChecker(this);
	field->Accept(&equalityChecker);
	return equalityChecker.result;
}


BBitmap*
BPhotoContactField::Photo() const
{
	if (fBitmap)
		return fBitmap;

	return NULL;
}


void
BPhotoContactField::SetPhoto(BBitmap* photo)
{
	_CleanUp();
	fBitmap = photo;
}


void
BPhotoContactField::SetValue(const BString& value)
{
	fUrl.SetTo(value);	
}


const BString&
BPhotoContactField::Value() const
{
	return fUrl;
}


uint32
BPhotoContactField::PictureType() const
{
	return fPictureType;
}


void
BPhotoContactField::SetPictureType(uint32 type)
{
	fPictureType = type;
}


const BString&
BPhotoContactField::PictureMIME() const
{
	return fPictureMIME;
}


void
BPhotoContactField::SetPictureMIME(const BString& mime)
{
	fPictureMIME.SetTo(mime);
}


status_t
BPhotoContactField::CopyDataFrom(BContactField* field)
{
	BPhotoContactField::CopyVisitor copier(this);
	field->Accept(&copier);
	return copier.error;
}


ssize_t
BPhotoContactField::FlattenedSize() const
{
	ssize_t size = BContactField::FlattenedSize();

	if (fBitmap) {
		BMessage msg;
		fBitmap->Archive(&msg);
		size += msg.FlattenedSize();
		size += sizeof(ssize_t);
	}
	return size;
}


status_t
BPhotoContactField::Flatten(void* buffer, ssize_t size) const
{
	if (size < FlattenedSize())
		return B_ERROR;

	BMemoryIO flatData(buffer, size);
	status_t ret = BContactField::Flatten(&flatData);
	if (ret != B_OK)
		return ret;

	ssize_t destSize;

	if (fBitmap != NULL) {
		BMessage msg;
		BMallocIO dest;

		fBitmap->Archive(&msg);
		destSize = msg.FlattenedSize();
		msg.Flatten(&dest);

		flatData.Write(&destSize, sizeof(destSize));
		flatData.Write(dest.Buffer(), destSize);
	} else {
		size = 0;
		flatData.Write(&size, sizeof(destSize));
	}

	return B_OK;
}


status_t
BPhotoContactField::Unflatten(type_code code,
	const void* buffer,	ssize_t size)
{
	BMemoryIO data(buffer, size);
	status_t ret = BContactField::Unflatten(code, &data);
	if (ret != B_OK)
		return ret;

	BMessage msg;
	ssize_t destSize;
	data.Read(&destSize, sizeof(destSize));

	if (destSize < 1) {
		fBitmap = NULL;
		return B_OK;
	}

	void* buf = malloc(destSize);
	MemoryDeleter deleter(buf);
	data.Read(buf, destSize);

	BMemoryIO dest(buf, destSize);
	msg.Unflatten(&dest);

	fBitmap = new BBitmap(&msg);

	return fBitmap->InitCheck();
}


void
BPhotoContactField::_CleanUp()
{
	delete fBitmap;
}
