//------------------------------------------------------------------------------
//	Copyright (c) 2001-2002, Haiku, Inc.
//
//	Permission is hereby granted, free of charge, to any person obtaining a
//	copy of this software and associated documentation files (the "Software"),
//	to deal in the Software without restriction, including without limitation
//	the rights to use, copy, modify, merge, publish, distribute, sublicense,
//	and/or sell copies of the Software, and to permit persons to whom the
//	Software is furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//	DEALINGS IN THE SOFTWARE.
//
//	File Name:		FontFamily.h
//	Author:			DarkWyrm <bpmagic@columbus.rr.com>
//	Description:	classes to represent font styles and families
//  
//------------------------------------------------------------------------------
#ifndef FONT_FAMILY_H_
#define FONT_FAMILY_H_

#include <String.h>
#include <Rect.h>
#include <Font.h>
#include <List.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "SharedObject.h"

class FontFamily;
class ServerFont;

enum font_format
{
	FONT_TRUETYPE=0,
	FONT_TYPE_1,
	FONT_OPENTYPE,
	FONT_BDF,
	FONT_CFF,
	FONT_CID,
	FONT_PCF,
	FONT_PFR,
	FONT_SFNT,
	FONT_TYPE_42,
	FONT_WINFONT,
};

/*
//! data structure used by the FreeType cache manager
typedef struct CachedFaceRec_
{
	BString file_path; 
	int face_index; 
} CachedFaceRec, *CachedFace;
*/
/*!
	\brief Private structure to store font height values
	
	Units provided by FT2 are in font units, so they are stored in the style as
	such. Each value must be multiplied by the point size to determine size in pixels
	
*/
typedef struct
{
	FT_Short ascent;
	FT_Short descent;
	FT_Short leading;
	FT_UShort units_per_em;
} FontStyleHeight;

/*!
	\class FontStyle FontFamily.h
	\brief Object used to represent a font style
	
	FontStyle objects help abstract a lot of the font engine details while
	still offering plenty of information the style in question.
*/
class FontStyle : public SharedObject {
 public:
								FontStyle(const char* filepath,
										  FT_Face face);
	virtual						~FontStyle();

/*!
	\fn bool FontStyle::IsFixedWidth(void)
	\brief Determines whether the font's character width is fixed
	\return true if fixed, false if not
*/
	inline	bool				IsFixedWidth() const
									{ return fFTFace->face_flags & FT_FACE_FLAG_FIXED_WIDTH; }
/*!
	\fn bool FontStyle::IsScalable(void)
	\brief Determines whether the font can be scaled to any size
	\return true if scalable, false if not
*/
	inline	bool				IsScalable() const
									{ return fFTFace->face_flags & FT_FACE_FLAG_SCALABLE; }
/*!
	\fn bool FontStyle::HasKerning(void)
	\brief Determines whether the font has kerning information
	\return true if kerning info is available, false if not
*/
	inline	bool				HasKerning() const
									{ return fFTFace->face_flags & FT_FACE_FLAG_KERNING; }
/*!
	\fn bool FontStyle::HasTuned(void)
	\brief Determines whether the font contains strikes
	\return true if it has strikes included, false if not
*/
	inline	bool				HasTuned() const
									{ return fFTFace->num_fixed_sizes > 0; }
/*!
	\fn bool FontStyle::TunedCount(void)
	\brief Returns the number of strikes the style contains
	\return The number of strikes the style contains
*/
	inline	int32				TunedCount() const
									{ return fFTFace->num_fixed_sizes; }
/*!
	\fn bool FontStyle::GlyphCount(void)
	\brief Returns the number of glyphs in the style
	\return The number of glyphs the style contains
*/
	inline	uint16				GlyphCount() const
									{ return fFTFace->num_glyphs; }
/*!
	\fn bool FontStyle::CharMapCount(void)
	\brief Returns the number of character maps the style contains
	\return The number of character maps the style contains
*/
	inline	uint16				CharMapCount() const
									{ return fFTFace->num_charmaps; }

			const char*			Name() const;
	inline	FontFamily*			Family() const
									{ return fFontFamily; }
	inline	uint16				GetID() const
									{ return fID; }
			int32				GetFlags() const;

	inline	uint16				GetFace() const
									{ return fFace; }

			const char*			GetPath() const;
			font_height			GetHeight(const float& size) const;
	
	inline	FT_Face				GetFTFace() const
									{ return fFTFace; }
	
	// TODO: Re-enable when I understand how the FT2 Cache system changed from
	// 2.1.4 to 2.1.8
//			int16				ConvertToUnicode(uint16 c);
								
			void				AttachedToFamily(FontFamily* family);
			void				DetachedFromFamily();

protected:
			uint16				TranslateStyleToFace(const char *name) const;
	
	friend class FontFamily;

			FT_Face				fFTFace;
	//		CachedFace			cachedface;

			FontFamily*			fFontFamily;

			BString				fName;
			BString				fPath;

			BRect				fBounds;

			uint16				fID;
			uint16				fFace;

			FontStyleHeight		fHeight;
};

/*!
	\class FontFamily FontFamily.h
	\brief Class representing a collection of similar styles
	
	FontFamily objects bring together many styles of the same face, such as
	Arial Roman, Arial Italic, Arial Bold, etc.
*/
class FontFamily : public SharedObject {
 public:
								FontFamily(const char* namestr,
										   const uint16& index);
	virtual						~FontFamily();

			const char*			Name() const;
	
			bool				AddStyle(FontStyle* style);
			void				RemoveStyle(const char* style);
			void				RemoveStyle(FontStyle* style);
			
			FontStyle*			GetStyle(int32 index) const;
			FontStyle*			GetStyle(const char* style) const;
			
			uint16				GetID() const
									{ return fID; }
			
			bool				HasStyle(const char* style) const;
			int32				CountStyles() const;
			int32				GetFlags();
	
protected:
			BString				fName;
			BList				fStyles;
			uint16				fID;
			int32				fFlags;
};

#endif
