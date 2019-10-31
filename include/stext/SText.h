#ifndef SText_h
#define SText_h

#include <stext/SText.h>

typedef struct SGlyph {
	float width, height;
	float bearingX, bearingY;
	float advance;
	char* data;
} SGlyph;

typedef struct SFont {
	SGlyph** glyphs;
	int size;
	float spaceWidth;
	int firstChar;
	int lastChar;
} SFont;

char** stGetAllFonts();
SFont* stCreateFont(char* fontFamily, int fontSize);

#endif /* SText_h */
