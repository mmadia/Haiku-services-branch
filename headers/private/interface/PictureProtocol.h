#ifndef _PICTUREPROTOCOL_H
#define _PICTUREPROTOCOL_H

enum {
	B_PIC_MOVE_PEN_BY		= 0x0010,

	B_PIC_STROKE_LINE		= 0x0100,
	B_PIC_STROKE_RECT		= 0x0101,
	B_PIC_FILL_RECT			= 0x0102,
	B_PIC_STROKE_ROUND_RECT		= 0x0103,
	B_PIC_FILL_ROUND_RECT		= 0x0104,
	B_PIC_STROKE_BEZIER		= 0x0105,
	B_PIC_FILL_BEZIER		= 0x0106,
	B_PIC_STROKE_POLYGON		= 0x010B,
	B_PIC_FILL_POLYGON		= 0x010C,
	B_PIC_STROKE_SHAPE		= 0x010D,
	B_PIC_FILL_SHAPE		= 0x010E,
	B_PIC_DRAW_STRING		= 0x010F,
	B_PIC_DRAW_PIXELS		= 0x0110,
	B_PIC_DRAW_PICTURE		= 0x0112,
	B_PIC_STROKE_ARC		= 0x0113,
	B_PIC_FILL_ARC			= 0x0114,
	B_PIC_STROKE_ELLIPSE		= 0x0115,
	B_PIC_FILL_ELLIPSE		= 0x0116,

	B_PIC_ENTER_STATE_CHANGE	= 0x0200,
	B_PIC_SET_CLIPPING_RECTS	= 0x0201,
	B_PIC_CLIP_TO_PICTURE		= 0x0202,
	B_PIC_PUSH_STATE		= 0x0203,
	B_PIC_POP_STATE			= 0x0204,
	B_PIC_CLEAR_CLIPPING_RECTS	= 0x0205,

	B_PIC_SET_ORIGIN		= 0x0300,
	B_PIC_SET_PEN_LOCATION		= 0x0301,
	B_PIC_SET_DRAWING_MODE		= 0x0302,
	B_PIC_SET_LINE_MODE		= 0x0303,
	B_PIC_SET_PEN_SIZE		= 0x0304,
	B_PIC_SET_SCALE			= 0x0305,
	B_PIC_SET_FORE_COLOR		= 0x0306,
	B_PIC_SET_BACK_COLOR		= 0x0307,
	B_PIC_SET_STIPLE_PATTERN	= 0x0308,
	B_PIC_ENTER_FONT_STATE		= 0x0309,
	B_PIC_SET_BLENDING_MODE		= 0x030A,
	B_PIC_SET_FONT_FAMILY		= 0x0380,
	B_PIC_SET_FONT_STYLE		= 0x0381,
	B_PIC_SET_FONT_SPACING		= 0x0382,
	B_PIC_SET_FONT_ENCODING		= 0x0383,
	B_PIC_SET_FONT_FLAGS		= 0x0384,
	B_PIC_SET_FONT_SIZE		= 0x0385,
	B_PIC_SET_FONT_ROTATE		= 0x0386,
	B_PIC_SET_FONT_SHEAR		= 0x0387,
	B_PIC_SET_FONT_BPP		= 0x0388,
	B_PIC_SET_FONT_FACE		= 0x0389,
};


const static uint32 kOpsTableSize = 48;


#endif

