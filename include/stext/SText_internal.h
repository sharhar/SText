//
//  SText_internal.h
//  SText
//
//  Created by Shahar Sandhaus on 9/15/19.
//

#ifndef SText_internal_h
#define SText_internal_h

#include "SText.h"

typedef struct SPixel {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} SPixel;

typedef struct _SRawGlyphData {
	int width, height;
	int originX, originY;
	int fontSize;
	
	SPixel* data;
} _SRawGlyphData;

SGlyph* __stCreateGlyph(_SRawGlyphData* rawData);

#endif /* SText_internal_h */
