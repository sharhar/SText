#ifndef SText_h
#define SText_h

typedef struct SGlyph {
	float width, height;
	float bearingX, bearingY;
	float advance;
	char* data;
	
	unsigned int GLTexID;
} SGlyph;

typedef struct SFont {
	SGlyph** glyphs;
	int size;
	float spaceWidth;
} SFont;

typedef void* (*stPfnGetProdAdress)(char* name);

void stInit(stPfnGetProdAdress gl_func);

char** stGetAllFonts();
SFont* stCreateFont(char* fontFamily, int fontSize);
void stFontInitGL(SFont* font);

void stRenderText(SFont* font, const char* text, float posx, float posy);

#endif /* SText_h */
