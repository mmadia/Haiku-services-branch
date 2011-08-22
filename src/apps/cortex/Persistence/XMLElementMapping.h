/*
 * Copyright (c) 1999-2000, Eric Moon.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions, and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


// XMLElementMapping.h
// * PURPOSE
//   A simple class (template implementing a non-template
//   base interface) to encapsulate the operation:
//   "make an object for this XML element."
//
// * HISTORY
//   e.moon		04oct99		Begun.

#ifndef __XMLElementMapping_H__
#define __XMLElementMapping_H__

#include <functional>
#include <String.h>

#include "cortex_defs.h"
__BEGIN_CORTEX_NAMESPACE

class IPersistent;

// The base class:

class XMLElementMapping {
public:													// *** data
	const BString									element;
	
public:													// *** interface
	virtual ~XMLElementMapping() {}
	XMLElementMapping(
		const char*									_element) :
		element(_element) {}
	
	virtual IPersistent* create() const =0;	
};

// The template:

template <class T>
class Mapping :
	public	XMLElementMapping {
public:
	virtual ~Mapping() {}
	Mapping(
		const char*									element) :
		XMLElementMapping(element) {}

	IPersistent* create() const {
		return new T();
	}
};

// compare pointers to Mappings by element name
struct _mapping_ptr_less : public std::binary_function<XMLElementMapping*,XMLElementMapping*,bool> {
public:
	bool operator()(const XMLElementMapping* a, const XMLElementMapping* b) const {
		return a->element < b->element;
	}
};


__END_CORTEX_NAMESPACE
#endif /*__XMLElementMapping_H__*/
