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

void __stInitRenderer();

typedef void (*pfnGlGenTextures)(int n, unsigned int *textures);
typedef void (*pfnGlBindTexture)(unsigned int target, unsigned int texture);
typedef void (*pfnGlTexParameteri)(unsigned int target, unsigned int pname, const int *params);
typedef void (*pfnGlPixelStorei)(unsigned int pname, int param);
typedef void (*pfnGlTexImage2D)(unsigned int target, int level, int internalformat, int width, int height, int border, unsigned int format, unsigned int type, const void *pixels);

typedef void (*pfnGlGenVertexArrays)(int n, unsigned int *arrays);
typedef void (*pfnGlBindVertexArray)(unsigned int array);

typedef void (*pfnGlGenBuffers)(int n, unsigned int *buffers);
typedef void (*pfnGlBindBuffer)(unsigned int target, unsigned int buffer);
typedef void (*pfnGlBufferData)(unsigned int target, signed long int size, const void *data, unsigned int usage);
typedef void (*pfnGlVertexAttribPointer)(unsigned int index, int size, unsigned int type, unsigned char normalized, int stride, const void *pointer);

typedef void (*pfnGlEnableVertexAttribArray)(unsigned int index);
typedef void (*pfnGlDrawArrays)(unsigned int mode, int first, int count);
typedef void (*pfnGlDrawElements)(unsigned int mode, int count, unsigned int type, const void *indices);

extern pfnGlGenTextures __glGenTextures;
extern pfnGlBindTexture __glBindTexture;
extern pfnGlTexParameteri __glTexParameteri;
extern pfnGlPixelStorei __glPixelStorei;
extern pfnGlTexImage2D __glTexImage2D;

extern pfnGlGenVertexArrays __glGenVertexArrays;
extern pfnGlBindVertexArray __glBindVertexArray;
extern pfnGlGenBuffers __glGenBuffers;
extern pfnGlBindBuffer __glBindBuffer;
extern pfnGlBufferData __glBufferData;
extern pfnGlVertexAttribPointer __glVertexAttribPointer;

extern pfnGlEnableVertexAttribArray __glEnableVertexAttribArray;
extern pfnGlDrawArrays __glDrawArrays;
extern pfnGlDrawElements __glDrawElements;

#define GL_TRIANGLES 0x0004
#define GL_UNPACK_ALIGNMENT 0x0CF5
#define GL_TEXTURE_2D 0x0DE1
#define GL_UNSIGNED_BYTE 0x1401
#define GL_FLOAT 0x1406
#define GL_RGBA 0x1908
#define GL_LINEAR 0x2601
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4

#endif /* SText_internal_h */
