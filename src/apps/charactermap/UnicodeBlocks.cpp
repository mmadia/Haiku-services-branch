/*
 * Copyright 2009, Axel Dörfler, axeld@pinc-software.de.
 * Distributed under the terms of the MIT License.
 */


#include "UnicodeBlocks.h"

#include <Catalog.h>

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "UnicodeBlocks"

const unicode_block kNoBlock;

const struct unicode_block_entry kUnicodeBlocks[] = {
	{B_TRANSLATE("Basic Latin"), 0x0000, 0x007f, false, B_BASIC_LATIN_BLOCK},
	{B_TRANSLATE("Latin-1 supplement"), 0x0080, 0x00ff, false,
		 B_LATIN1_SUPPLEMENT_BLOCK},
	{B_TRANSLATE("Latin extended A"), 0x0100, 0x017f, false,
		B_LATIN_EXTENDED_A_BLOCK},
	{B_TRANSLATE("Latin extended B"), 0x0180, 0x024f, false,
		B_LATIN_EXTENDED_B_BLOCK},
	{B_TRANSLATE("IPA extensions"), 0x0250, 0x02af, false,
		B_IPA_EXTENSIONS_BLOCK},
	{B_TRANSLATE("Spacing modifier letters"), 0x02b0, 0x02ff, false,
		B_SPACING_MODIFIER_LETTERS_BLOCK},
	{B_TRANSLATE("Combining diacritical marks"), 0x0300, 0x036f, false,
		B_COMBINING_DIACRITICAL_MARKS_BLOCK},
	{B_TRANSLATE("Greek and Coptic"), 0x0370, 0x03ff, false,
		B_BASIC_GREEK_BLOCK | B_GREEK_SYMBOLS_AND_COPTIC_BLOCK},
	{B_TRANSLATE("Cyrillic"), 0x0400, 0x04ff, false, B_CYRILLIC_BLOCK},
	{B_TRANSLATE("Cyrillic supplement"), 0x0500, 0x052f, false,
		 B_CYRILLIC_BLOCK},
	{B_TRANSLATE("Armenian"), 0x0530, 0x058f, false, B_ARMENIAN_BLOCK},
	{B_TRANSLATE("Hebrew"), 0x0590, 0x05ff, false,
		B_BASIC_HEBREW_BLOCK | B_HEBREW_EXTENDED_BLOCK},
	{B_TRANSLATE("Arabic"), 0x0600, 0x06ff, false,
		B_BASIC_ARABIC_BLOCK | B_ARABIC_EXTENDED_BLOCK},
	{B_TRANSLATE("Syriac"), 0x0700, 0x074f, false, kNoBlock},
	{B_TRANSLATE("Arabic supplement"), 0x0750, 0x077f, false, kNoBlock},
	{B_TRANSLATE("Thaana"), 0x0780, 0x07bf, false, kNoBlock},
	{B_TRANSLATE("N'Ko"), 0x07c0, 0x07ff, false, kNoBlock},
	{B_TRANSLATE("Devanagari"), 0x0900, 0x097f, false, B_DEVANAGARI_BLOCK},
	{B_TRANSLATE("Bengali"), 0x0980, 0x09ff, false, B_BENGALI_BLOCK},
	{B_TRANSLATE("Gurmukhi"), 0x0a00, 0x0a7f, false, B_GURMUKHI_BLOCK},
	{B_TRANSLATE("Gujarati"), 0x0a80, 0x0aff, false, B_GUJARATI_BLOCK},
	{B_TRANSLATE("Oriya"), 0x0b00, 0x0b7f, false, B_ORIYA_BLOCK},
	{B_TRANSLATE("Tamil"), 0x0b80, 0x0bff, false, B_TAMIL_BLOCK},
	{B_TRANSLATE("Telugu"), 0x0c00, 0x0c7f, false, B_TELUGU_BLOCK},
	{B_TRANSLATE("Kannada"), 0x0c80, 0x0cff, false, B_KANNADA_BLOCK},
	{B_TRANSLATE("Malayalam"), 0x0d00, 0x0d7f, false, B_MALAYALAM_BLOCK},
	{B_TRANSLATE("Sinhala"), 0x0d80, 0x0dff, false, kNoBlock},
	{B_TRANSLATE("Thai"), 0x0e00, 0x0e7f, false, B_THAI_BLOCK},
	{B_TRANSLATE("Lao"), 0x0e80, 0x0eff, false, B_LAO_BLOCK},
	{B_TRANSLATE("Tibetan"), 0x0f00, 0x0fff, false, kNoBlock},
	{B_TRANSLATE("Myanmar"), 0x1000, 0x109f, false, kNoBlock},
	{B_TRANSLATE("Georgian"), 0x10a0, 0x10ff, false, B_BASIC_GEORGIAN_BLOCK},
	{B_TRANSLATE("Hangul Jamo"), 0x1100, 0x11ff, false, kNoBlock},
// TODO!
	{B_TRANSLATE("Ethiopic"), 0x1200, 0x137f, false, kNoBlock},
	{B_TRANSLATE("Ethiopic supplement"), 0x1380, 0x139f, false, kNoBlock},
	{B_TRANSLATE("Cherokee"), 0x13a0, 0x13ff, false, kNoBlock},
	{B_TRANSLATE("Unified Canadian Aboriginal syllabics"),
		0x1400, 0x167f, false, kNoBlock},
	{B_TRANSLATE("Ogham"), 0x1680, 0x169f, false, kNoBlock},
	{B_TRANSLATE("Runic"), 0x16a0, 0x16ff, false, kNoBlock},
	{B_TRANSLATE("Tagalog"), 0x1700, 0x171f, false, kNoBlock},
	{B_TRANSLATE("Hanunoo"), 0x1720, 0x173f, false, kNoBlock},
	{B_TRANSLATE("Buhid"), 0x1740, 0x175f, false, kNoBlock},
	{B_TRANSLATE("Tagbanwa"), 0x1760, 0x177f, false, kNoBlock},
	{B_TRANSLATE("Khmer"), 0x1780, 0x17ff, false, kNoBlock},
	{B_TRANSLATE("Mongolian"), 0x1800, 0x18af, false, kNoBlock},
	{B_TRANSLATE("Limbu"), 0x1900, 0x194f, false, kNoBlock},
	{B_TRANSLATE("Tai Le"), 0x1950, 0x197f, false, kNoBlock},
	{B_TRANSLATE("New Tai Lue"), 0x1980, 0x19df, false, kNoBlock},
	{B_TRANSLATE("Khmer symbols"), 0x19e0, 0x19ff, false, kNoBlock},
	{B_TRANSLATE("Buginese"), 0x1a00, 0x1a1f, false, kNoBlock},
	{B_TRANSLATE("Balinese"), 0x1b00, 0x1b7f, false, kNoBlock},
	{B_TRANSLATE("Sundanese"), 0x1b80, 0x1bbf, false, kNoBlock},
	{B_TRANSLATE("Lepcha"), 0x1c00, 0x1c4f, false, kNoBlock},
	{B_TRANSLATE("Ol Chiki"), 0x1c50, 0x1c7f, false, kNoBlock},
	{B_TRANSLATE("Phonetic extensions"), 0x1d00, 0x1d7f, false, kNoBlock},
	{B_TRANSLATE("Phonetic extensions supplement"),
		 0x1d80, 0x1dbf, false, kNoBlock},
	{B_TRANSLATE("Combining diacritical marks supplement"),
		0x1dc0, 0x1dff, false, kNoBlock},
	{B_TRANSLATE("Latin extended additional"),
		 0x1e00, 0x1eff, false, kNoBlock},
	{B_TRANSLATE("Greek extended"), 0x1f00, 0x1fff, false, kNoBlock},
	{B_TRANSLATE("General punctuation"), 0x2000, 0x206f, false, kNoBlock},
	{B_TRANSLATE("Superscripts and subscripts"),
		 0x2070, 0x209f, false, kNoBlock},
	{B_TRANSLATE("Currency symbols"), 0x20a0, 0x20cf, false, kNoBlock},
	{B_TRANSLATE("Combining diacritical marks for symbols"),
		 0x20d0, 0x20ff, false, kNoBlock},
	{B_TRANSLATE("Letterlike symbols"), 0x2100, 0x214f, false, kNoBlock},
	{B_TRANSLATE("Number forms"), 0x2150, 0x218f, false, kNoBlock},
	{B_TRANSLATE("Arrows"), 0x2190, 0x21ff, false, kNoBlock},
	{B_TRANSLATE("Mathematical operators"), 0x2200, 0x22ff, false, kNoBlock},
	{B_TRANSLATE("Miscellaneous technical"), 0x2300, 0x23ff, false, kNoBlock},
	{B_TRANSLATE("Control pictures"), 0x2400, 0x243f, false, kNoBlock},
	{B_TRANSLATE("Optical character recognition"),
		 0x2440, 0x245f, false, kNoBlock},
	{B_TRANSLATE("Enclosed alphanumerics"), 0x2460, 0x24ff, false, kNoBlock},
	{B_TRANSLATE("Box drawing"), 0x2500, 0x257f, false, kNoBlock},
	{B_TRANSLATE("Block elements"), 0x2580, 0x259f, false, kNoBlock},
	{B_TRANSLATE("Geometric shapes"), 0x25a0, 0x25ff, false, kNoBlock},
	{B_TRANSLATE("Miscellaneous symbols"), 0x2600, 0x26ff, false, kNoBlock},
	{B_TRANSLATE("Dingbats"), 0x2700, 0x27bf, false, kNoBlock},
	{B_TRANSLATE("Miscellaneous mathematical symbols A"),
		 0x27c0, 0x27ef, false, kNoBlock},
	{B_TRANSLATE("Supplemental arrows A"), 0x27f0, 0x27ff, false, kNoBlock},
	{B_TRANSLATE("Braille patterns"), 0x2800, 0x28ff, false, kNoBlock},
	{B_TRANSLATE("Supplemental arrows B"), 0x2900, 0x297f, false, kNoBlock},
	{B_TRANSLATE("Miscellaneous mathematical symbols B"),
		 0x2980, 0x29ff, false, kNoBlock},
	{B_TRANSLATE("Supplemental mathematical operators"),
		 0x2a00, 0x2aff, false, kNoBlock},
	{B_TRANSLATE("Miscellaneous symbols and arrows"),
		 0x2b00, 0x2bff, false, kNoBlock},
	{B_TRANSLATE("Glagotic"), 0x2c00, 0x2c5f, false, kNoBlock},
	{B_TRANSLATE("Latin extended C"), 0x2c60, 0x2c7f, false, kNoBlock},
	{B_TRANSLATE("Coptic"), 0x2c80, 0x2cff, false, kNoBlock},
	{B_TRANSLATE("Georgian supplement"), 0x2d00, 0x2d2f, false, kNoBlock},
	{B_TRANSLATE("Tifinagh"), 0x2d30, 0x2d7f, false, kNoBlock},
	{B_TRANSLATE("Ethiopic extended"), 0x2d80, 0x2ddf, false, kNoBlock},
	{B_TRANSLATE("Cyrillic extended A"), 0x2de0, 0x2dff, false, kNoBlock},
	{B_TRANSLATE("Supplement punctuation"), 0x2e00, 0x2e7f, false, kNoBlock},
	{B_TRANSLATE("CJK radicals supplement"), 0x2e80, 0x2eff, false, kNoBlock},
	{B_TRANSLATE("Kangxi radicals"), 0x2f00, 0x2fdf, false, kNoBlock},
	{B_TRANSLATE("Ideographic description characters"),
		 0x2ff0, 0x2fff, false, kNoBlock},
	{B_TRANSLATE("CJK symbols and punctuation"),
		 0x3000, 0x303f, false, kNoBlock},
	{B_TRANSLATE("Hiragana"), 0x3040, 0x309f, false, kNoBlock},
	{B_TRANSLATE("Katakana"), 0x30a0, 0x30ff, false, kNoBlock},
	{B_TRANSLATE("Bopomofo"), 0x3100, 0x312f, false, kNoBlock},
	{B_TRANSLATE("Hangul compatibility Jamo"), 0x3130, 0x318f, false, kNoBlock},
	{B_TRANSLATE("Kanbun"), 0x3190, 0x319f, false, kNoBlock},
	{B_TRANSLATE("Bopomofo extended"), 0x31a0, 0x31bf, false, kNoBlock},
	{B_TRANSLATE("CJK strokes"), 0x31c0, 0x31ef, false, kNoBlock},
	{B_TRANSLATE("Katakana phonetic extensions"),
		 0x31f0, 0x31ff, false, kNoBlock},
	{B_TRANSLATE("Enclosed CJK letters and months"), 
		 0x2ff0, 0x2fff, false, kNoBlock},
	{B_TRANSLATE("CJK compatibility"), 0x3300, 0x33ff, false, kNoBlock},
	{B_TRANSLATE("CJK unified ideographs extension A"),
		 0x3400, 0x4dbf, false, kNoBlock},
	{B_TRANSLATE("Yijing hexagram symbols"), 0x4dc0, 0x4dff, false, kNoBlock},
	{B_TRANSLATE("CJK unified ideographs"), 0x4e00, 0x9fff, false, kNoBlock},
	{B_TRANSLATE("Yi syllables"), 0xa000, 0xa48f, false, kNoBlock},
	{B_TRANSLATE("Yi Radicals"), 0xa490, 0xa4cf, false, kNoBlock},
	{B_TRANSLATE("Vai"), 0xa500, 0xa63f, false, kNoBlock},
	{B_TRANSLATE("Cyrillic extended B"), 0xa640, 0xa69f, false, kNoBlock},
	{B_TRANSLATE("Modifier tone letters"), 0xa700, 0xa71f, false, kNoBlock},
	{B_TRANSLATE("Latin extended D"), 0xa720, 0xa7ff, false, kNoBlock},
	{B_TRANSLATE("Syloti Nagri"), 0xa800, 0xa82f, false, kNoBlock},
	{B_TRANSLATE("Phags-pa"), 0xa840, 0xa87f, false, kNoBlock},
	{B_TRANSLATE("Saurashtra"), 0xa880, 0xa8df, false, kNoBlock},
	{B_TRANSLATE("Kayah Li"), 0xa900, 0xa92f, false, kNoBlock},
	{B_TRANSLATE("Rejang"), 0xa930, 0xa95f, false, kNoBlock},
	{B_TRANSLATE("Cham"), 0xaa00, 0xaa5f, false, kNoBlock},
	{B_TRANSLATE("Hangul syllables"), 0xac00, 0xd7af, false, kNoBlock},
//	{B_TRANSLATE("High surrogates"), 0xd800, 0xdb7f, false, kNoBlock},
//	{B_TRANSLATE("High private use surrogates"), 0xdb80, 0xdbff, false, kNoBlock},
//	{B_TRANSLATE("Low surrogates"), 0xdc00, 0xdfff, false, kNoBlock},
	{B_TRANSLATE("Private use area"), 0xe000, 0xf8ff, true, kNoBlock},
	{B_TRANSLATE("CJK compatibility ideographs"),
		 0xf900, 0xfaff, false, kNoBlock},
	{B_TRANSLATE("Alphabetic presentation forms"),
		0xfb00, 0xfb4f, false, kNoBlock},
	{B_TRANSLATE("Arabic presentation forms A"),
		 0xfb50, 0xfdff, false, kNoBlock},
	{B_TRANSLATE("Variation selectors"), 0xfe00, 0xfe0f, false, kNoBlock},
	{B_TRANSLATE("Vertical forms"), 0xfe10, 0xfe1f, false, kNoBlock},
	{B_TRANSLATE("Combining half marks"), 0xfe20, 0xfe2f, false, kNoBlock},
	{B_TRANSLATE("CJK compatibility forms"), 0xfe30, 0xfe4f, false, kNoBlock},
	{B_TRANSLATE("Small form variants"), 0xfe50, 0xfe6f, false, kNoBlock},
	{B_TRANSLATE("Arabic presentation forms B"),
		 0xfe70, 0xfeff, false, kNoBlock},
	{B_TRANSLATE("Halfwidth and fullwidth forms"),
		 0xff00, 0xffef, false, kNoBlock},
	{B_TRANSLATE("Specials"), 0xfff0, 0xffff, false, kNoBlock},
	{B_TRANSLATE("Linear B syllabary"), 0x010000, 0x01007f, false, kNoBlock},
	{B_TRANSLATE("Linear B ideograms"), 0x010080, 0x0100ff, false, kNoBlock},
	{B_TRANSLATE("Aegean numbers"), 0x010100, 0x01013f, false, kNoBlock},
	{B_TRANSLATE("Ancient Greek numbers"),
		 0x010140, 0x01018f, false, kNoBlock},
	{B_TRANSLATE("Ancient smbols"), 0x010190, 0x0101cf, false, kNoBlock},
	{B_TRANSLATE("Phaistos disc"), 0x0101d0, 0x0101ff, false, kNoBlock},
	{B_TRANSLATE("Lycian"), 0x010280, 0x01029f, false, kNoBlock},
	{B_TRANSLATE("Carian"), 0x0102a0, 0x0102df, false, kNoBlock},
	{B_TRANSLATE("Old italic"), 0x010300, 0x01032f, false, kNoBlock},
	{B_TRANSLATE("Gothic"), 0x010330, 0x01034f, false, kNoBlock},
	{B_TRANSLATE("Ugaritic"), 0x010380, 0x01039f, false, kNoBlock},
	{B_TRANSLATE("Old Persian"), 0x0103a0, 0x0103df, false, kNoBlock},
	{B_TRANSLATE("Deseret"), 0x010400, 0x01044f, false, kNoBlock},
	{B_TRANSLATE("Shavian"), 0x010450, 0x01047f, false, kNoBlock},
	{B_TRANSLATE("Osmanya"), 0x010480, 0x0104af, false, kNoBlock},
	{B_TRANSLATE("Cypriot syllabary"), 0x010800, 0x01083f, false, kNoBlock},
	{B_TRANSLATE("Phoenician"), 0x010900, 0x01091f, false, kNoBlock},
	{B_TRANSLATE("Lydian"), 0x010920, 0x01093f, false, kNoBlock},
	{B_TRANSLATE("Kharoshthi"), 0x010a00, 0x010a5f, false, kNoBlock},
	{B_TRANSLATE("Cuneiform"), 0x012000, 0x0123ff, false, kNoBlock},
	{B_TRANSLATE("Cuneiform numbers and punctuation"),
		 0x012400, 0x01247f, false, kNoBlock},
	{B_TRANSLATE("Byzantine musical symbols"),
		 0x01d000, 0x01d0ff, false, kNoBlock},
	{B_TRANSLATE("Musical symbols"), 0x01d100, 0x01d1ff, false, kNoBlock},
	{B_TRANSLATE("Ancient Greek musical notation"),
		 0x01d200, 0x01d24f, false, kNoBlock},
	{B_TRANSLATE("Tai Xuan Jing symbols"),
		 0x01d300, 0x01d35f, false, kNoBlock},
	{B_TRANSLATE("Counting rod numerals"),
		 0x01d360, 0x01d37f, false, kNoBlock},
	{B_TRANSLATE("Mathematical alphanumeric symbols"),
		 0x01d400, 0x01d7ff, false, kNoBlock},
	{B_TRANSLATE("Mahjong tiles"), 0x01f000, 0x01f02f, false, kNoBlock},
	{B_TRANSLATE("Domino tiles"), 0x01f030, 0x01f09f, false, kNoBlock},
	{B_TRANSLATE("CJK unified ideographs extension B"),
		 0x020000, 0x02a6df, false, kNoBlock},
	{B_TRANSLATE("CJK compatibility ideographs Supplement"),
		 0x02f800, 0x02fa1f, false, kNoBlock},
	{B_TRANSLATE("Tags"), 0x0e0000, 0x0e007f, false, kNoBlock},
	{B_TRANSLATE("Variation selectors supplement"),
		 0x0e0100, 0x0e01ef, false, kNoBlock},
	{B_TRANSLATE("Supplementary private use area A"),
		 0x0f0000, 0x0fffff, true, kNoBlock},
	{B_TRANSLATE("Supplementary private use area B"),
		 0x100000, 0x10ffff, true, kNoBlock},
};

const uint32 kNumUnicodeBlocks
	= sizeof(kUnicodeBlocks) / sizeof(kUnicodeBlocks[0]);
