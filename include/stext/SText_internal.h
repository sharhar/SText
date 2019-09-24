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

typedef unsigned int (*pfnGlCreateShader)(unsigned int type);
typedef unsigned int (*pfnGlCreateProgram)(void);
typedef void (*pfnGlShaderSource)(unsigned int shader, int count, const char *const*string, const int *length);
typedef void (*pfnGlCompileShader)(unsigned int shader);
typedef void (*pfnGlGetShaderiv)(unsigned int shader, unsigned int pname, int *params);
typedef void (*pfnGlGetShaderInfoLog)(unsigned int shader, int bufSize, int *length, char *infoLog);
typedef void (*pfnGlAttachShader)(unsigned int program, unsigned int shader);
typedef void (*pfnGlBindAttribLocation)(unsigned int program, unsigned int index, const char *name);
typedef void (*pfnGlLinkProgram)(unsigned int program);
typedef void (*pfnGlValidateProgram)(unsigned int program);
typedef void (*pfnGlUseProgram)(unsigned int program);
typedef int (*pfnGlGetUniformLocation)(unsigned int program, const char *name);
typedef void (*pfnGlDeleteProgram)(unsigned int program);
typedef void (*pfnGlDeleteShader)(unsigned int shader);

typedef void (*pfnGlEnableVertexAttribArray)(unsigned int index);
typedef void (*pfnGlDrawArrays)(unsigned int mode, int first, int count);

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

extern pfnGlCreateShader __glCreateShader;
extern pfnGlCreateProgram __glCreateProgram;
extern pfnGlShaderSource __glShaderSource;
extern pfnGlCompileShader __glCompileShader;
extern pfnGlGetShaderiv __glGetShaderiv;
extern pfnGlGetShaderInfoLog __glGetShaderInfoLog;
extern pfnGlAttachShader __glAttachShader;
extern pfnGlBindAttribLocation __glBindAttribLocation;
extern pfnGlLinkProgram __glLinkProgram;
extern pfnGlValidateProgram __glValidateProgram;
extern pfnGlUseProgram __glUseProgram;
extern pfnGlGetUniformLocation __glGetUniformLocation;
extern pfnGlDeleteProgram __glDeleteProgram;
extern pfnGlDeleteShader __glDeleteShader;

extern pfnGlEnableVertexAttribArray __glEnableVertexAttribArray;
extern pfnGlDrawArrays __glDrawArrays;

#define GL_FALSE 0
#define GL_TRUE 1
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
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_COMPILE_STATUS 0x8B81
#define GL_INFO_LOG_LENGTH 0x8B84

#endif /* SText_internal_h */
