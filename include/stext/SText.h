#ifndef SText_h
#define SText_h

typedef struct SGlyph {
	unsigned int width, height;
	unsigned int bearingX, bearingY;
	unsigned int advance;
	char* data;
} SGlyph;

typedef struct SFont {
	SGlyph* glyphs;
} SFont;

char** stGetAllFonts();
SFont* stCreateFont(char* fontFamily, int fontSize);



#endif /* SText_h */
