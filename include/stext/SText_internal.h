//
//  SText_internal.h
//  SText
//
//  Created by Shahar Sandhaus on 9/15/19.
//

#ifndef SText_internal_h
#define SText_internal_h

#include "SText.h"

typedef struct _SRawGlyphData {
	int width, height;
	int originX, originY;
	int fontSize;
	
	char* data;
} _SRawGlyphData;

SGlyph* createGlyph(_SRawGlyphData* rawData);

#endif /* SText_internal_h */
