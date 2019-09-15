#ifndef SText_h
#define SText_h

typedef struct SGlyph {
	unsigned int width, height;
	unsigned int bearingX, bearingY;
	unsigned int advance;
	char* data;
} SGlyph;

void stInit();



#endif /* SText_h */
