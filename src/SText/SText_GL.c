//
//  SText_Renderer.c
//  SText
//
//  Created by Shahar Sandhaus on 9/22/19.
//

#include <stext/SText.h>
#include <stext/SText_GL.h>
#include <stext/SText_internal.h>

#include <stdio.h>

#define GL_FALSE 0
#define GL_TRUE 1
#define GL_TRIANGLES 0x0004
#define GL_UNPACK_ALIGNMENT 0x0CF5
#define GL_TEXTURE_2D 0x0DE1
#define GL_UNSIGNED_BYTE 0x1401
#define GL_FLOAT 0x1406
#define GL_RED 0x1903
#define GL_RGBA 0x1908
#define GL_LINEAR 0x2601
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_TEXTURE0 0x84C0
#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_COMPILE_STATUS 0x8B81
#define GL_INFO_LOG_LENGTH 0x8B84

typedef void (*pfnGlGenTextures)(int n, unsigned int *textures);
typedef void (*pfnGlBindTexture)(unsigned int target, unsigned int texture);
typedef void (*pfnGlTexParameteri)(unsigned int target, unsigned int pname, const int *params);
typedef void (*pfnGlPixelStorei)(unsigned int pname, int param);
typedef void (*pfnGlTexImage2D)(unsigned int target, int level, int internalformat, int width, int height, int border, unsigned int format, unsigned int type, const void *pixels);
typedef void (*pfnGlActiveTexture)(unsigned int texture);

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

typedef void (*pfnGlUniform4f)(int location, float v0, float v1, float v2, float v3);

typedef void (*pfnGlEnableVertexAttribArray)(unsigned int index);
typedef void (*pfnGlDrawArrays)(unsigned int mode, int first, int count);

pfnGlGenTextures __glGenTextures = 0;
pfnGlBindTexture __glBindTexture = 0;
pfnGlTexParameteri __glTexParameteri = 0;
pfnGlPixelStorei __glPixelStorei = 0;
pfnGlTexImage2D __glTexImage2D = 0;
pfnGlActiveTexture __glActiveTexture = 0;

pfnGlGenVertexArrays __glGenVertexArrays = 0;
pfnGlBindVertexArray __glBindVertexArray = 0;
pfnGlGenBuffers __glGenBuffers = 0;
pfnGlBindBuffer __glBindBuffer = 0;
pfnGlBufferData __glBufferData = 0;
pfnGlVertexAttribPointer __glVertexAttribPointer = 0;

pfnGlCreateShader __glCreateShader = 0;
pfnGlCreateProgram __glCreateProgram = 0;
pfnGlShaderSource __glShaderSource = 0;
pfnGlCompileShader __glCompileShader = 0;
pfnGlGetShaderiv __glGetShaderiv = 0;
pfnGlGetShaderInfoLog __glGetShaderInfoLog = 0;
pfnGlAttachShader __glAttachShader = 0;
pfnGlBindAttribLocation __glBindAttribLocation = 0;
pfnGlLinkProgram __glLinkProgram = 0;
pfnGlValidateProgram __glValidateProgram = 0;
pfnGlUseProgram __glUseProgram = 0;
pfnGlGetUniformLocation __glGetUniformLocation = 0;
pfnGlDeleteProgram __glDeleteProgram = 0;
pfnGlDeleteShader __glDeleteShader = 0;

pfnGlUniform4f __glUniform4f = 0;

pfnGlEnableVertexAttribArray __glEnableVertexAttribArray = 0;
pfnGlDrawArrays __glDrawArrays = 0;

unsigned int __rectVAO;
unsigned int __rectVBO1;
unsigned int __rectVBO2;

unsigned int __vertShader;
unsigned int __fragShader;
unsigned int __shaderProgram;

unsigned int __screenLoc;
unsigned int __transLoc;

void stInitGL(stPfnGetProdAdressGL gl_func) {
	__glGenTextures = gl_func("glGenTextures");
	__glBindTexture = gl_func("glBindTexture");
	__glTexParameteri = gl_func("glTexParameteri");
	__glPixelStorei = gl_func("glPixelStorei");
	__glTexImage2D = gl_func("glTexImage2D");
	__glActiveTexture = gl_func("glActiveTexture");
	
	__glGenVertexArrays = gl_func("glGenVertexArrays");
	__glBindVertexArray = gl_func("glBindVertexArray");
	__glGenBuffers = gl_func("glGenBuffers");
	__glBindBuffer = gl_func("glBindBuffer");
	__glBufferData = gl_func("glBufferData");
	__glVertexAttribPointer = gl_func("glVertexAttribPointer");
	
	__glCreateShader = gl_func("glCreateShader");
	__glCreateProgram = gl_func("glCreateProgram");
	__glShaderSource = gl_func("glShaderSource");
	__glCompileShader = gl_func("glCompileShader");
	__glGetShaderiv = gl_func("glGetShaderiv");
	__glGetShaderInfoLog = gl_func("glGetShaderInfoLog");
	__glAttachShader = gl_func("glAttachShader");
	__glBindAttribLocation = gl_func("glBindAttribLocation");
	__glLinkProgram = gl_func("glLinkProgram");
	__glValidateProgram = gl_func("glValidateProgram");
	__glUseProgram = gl_func("glUseProgram");
	__glGetUniformLocation = gl_func("glGetUniformLocation");
	__glDeleteProgram = gl_func("glDeleteProgram");
	__glDeleteShader = gl_func("glDeleteShader");
	
	__glUniform4f = gl_func("glUniform4f");
	
	__glEnableVertexAttribArray = gl_func("glEnableVertexAttribArray");
	__glDrawArrays = gl_func("glDrawArrays");
	
	float vects[] = {
		0, 0,
		1, 0,
		1, 1,
		
		0, 0,
		1, 1,
		0, 1
	};
	
	float texcoords[] = {
		0, 1,
		1, 1,
		1, 0,
		
		0, 1,
		1, 0,
		0, 0
	};
	
	__glGenVertexArrays(1, &__rectVAO);
	__glBindVertexArray(__rectVAO);
	
	__glGenBuffers(1, &__rectVBO1);
	__glBindBuffer(GL_ARRAY_BUFFER, __rectVBO1);
	__glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vects, GL_STATIC_DRAW);
	__glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	__glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	__glGenBuffers(1, &__rectVBO2);
	__glBindBuffer(GL_ARRAY_BUFFER, __rectVBO2);
	__glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, texcoords, GL_STATIC_DRAW);
	__glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	__glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	__glBindVertexArray(0);
	
	const char* vertSource = "\
	#version 330 core\n\
	in vec2 position;\n\
	in vec2 texcoord;\n\
	out vec2 texcoord_out;\n\
	uniform vec4 screen;\n\
	uniform vec4 trans;\n\
	void main(void) {\n\
	vec2 translated_coords = vec2(trans.x + position.x*trans.z, trans.y + position.y*trans.w);\
	gl_Position = vec4(2*translated_coords.x/screen.x - 1, 2*translated_coords.y/screen.y - 1, 0, 1);\n\
	texcoord_out = texcoord;\n\
	}\n";
	
	const char* fragSource = "\
	#version 330 core\n\
	out vec4 out_color;\n\
	uniform sampler2D tex;\n\
	in vec2 texcoord_out;\n\
	void main(void) {\n\
	float alpha = texture(tex, texcoord_out).r;\n\
	if(alpha < 0.01) {discard;}\n\
	out_color = vec4(1, 1, 1, alpha);\n\
	}\n";
	
	__vertShader = __glCreateShader(GL_VERTEX_SHADER);
	__fragShader = __glCreateShader(GL_FRAGMENT_SHADER);
	__shaderProgram = __glCreateProgram();
	
	__glShaderSource(__vertShader, 1, &vertSource, 0);
	__glShaderSource(__fragShader, 1, &fragSource, 0);
	
	__glCompileShader(__vertShader);
	
	int compiled = 0;
	__glGetShaderiv(__vertShader, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE) {
		int maxLength = 0;
		__glGetShaderiv(__vertShader, GL_INFO_LOG_LENGTH, &maxLength);
		
		char* message = (char*)malloc(sizeof(char)*maxLength);
		__glGetShaderInfoLog(__vertShader, maxLength, &maxLength, message);
		
		printf("Vertex Shader failed to compile:\n");
		printf("%s\n", message);
		
		free(message);
		return;
	}
	
	__glCompileShader(__fragShader);
	
	__glGetShaderiv(__fragShader, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE) {
		int maxLength = 0;
		__glGetShaderiv(__fragShader, GL_INFO_LOG_LENGTH, &maxLength);
		
		char* message = (char*)malloc(sizeof(char)*maxLength);
		__glGetShaderInfoLog(__fragShader, maxLength, &maxLength, message);
		
		printf("Fragment Shader failed to compile:\n");
		printf("%s\n", message);
		
		free(message);
		return;
	}
	
	__glAttachShader(__shaderProgram, __vertShader);
	__glAttachShader(__shaderProgram, __fragShader);
	
	__glBindAttribLocation(__shaderProgram, 0, "position");
	__glBindAttribLocation(__shaderProgram, 1, "texcoord");
	
	__glLinkProgram(__shaderProgram);
	__glValidateProgram(__shaderProgram);
	
	__glUseProgram(__shaderProgram);
	
	__screenLoc = __glGetUniformLocation(__shaderProgram, "screen");
	__transLoc = __glGetUniformLocation(__shaderProgram, "trans");
	
	__glUniform4f(__screenLoc, 800, 600, 0, 0);
	
	__glUseProgram(0);
}

void stRenderTextGL(SFontGL* fontGL, const char* text, float posx, float posy) {
	__glBindVertexArray(__rectVAO);
	
	__glEnableVertexAttribArray(0);
	__glEnableVertexAttribArray(1);
	
	__glUseProgram(__shaderProgram);
	
	float xOff = 0;
	float yOff = 0;
	
	SGlyph* glyph = 0;
	
	for (int i = 0; text[i] != 0; i ++) {
		if(text[i] == ' ') {
			xOff += fontGL->font->spaceWidth;
			continue;
		}
		
		if(text[i] == '\n') {
			yOff += fontGL->font->size;
			xOff = 0;
			continue;
		}
		
		glyph = fontGL->font->glyphs[(int)text[i]];
		
		__glActiveTexture(GL_TEXTURE0);
		__glBindTexture(GL_TEXTURE_2D, fontGL->GLTexIDs[(int)text[i]]);
		
		float x = xOff + posx + glyph->bearingX;
		float y = posy - glyph->bearingY - glyph->height - yOff;
		
		__glUniform4f(__transLoc, x, y, glyph->width, glyph->height);
		
		__glDrawArrays(GL_TRIANGLES, 0, 6);
		
		xOff += glyph->advance;
	}
	
	__glUseProgram(0);
	
	__glBindVertexArray(0);
}

SFontGL* stCreateFontGL(SFont* font) {
	SFontGL* result = (SFontGL*)malloc(sizeof(SFontGL));
	
	result->GLTexIDs = malloc(sizeof(unsigned int)*255);
	result->font = font;
	
	for(int i = 33; i < 127; i++) {
		__glGenTextures(1, &result->GLTexIDs[i]);
		__glBindTexture(GL_TEXTURE_2D, result->GLTexIDs[i]);
		
		__glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		__glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		__glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		__glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		__glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		
		__glTexImage2D(
					   GL_TEXTURE_2D,
					   0,
					   GL_RGBA,
					   font->glyphs[i]->width,
					   font->glyphs[i]->height,
					   0,
					   GL_RED,
					   GL_UNSIGNED_BYTE,
					   font->glyphs[i]->data
					   );
	}
	
	__glGenTextures(1, &result->GLTexIDs[' ']);
	__glBindTexture(GL_TEXTURE_2D, result->GLTexIDs[' ']);
	
	__glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	__glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	__glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	__glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	__glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	__glTexImage2D(
				   GL_TEXTURE_2D,
				   0,
				   GL_RGBA,
				   font->glyphs[' ']->width,
				   font->glyphs[' ']->height,
				   0,
				   GL_RGBA,
				   GL_UNSIGNED_BYTE,
				   font->glyphs[' ']->data
				   );
	
	__glBindTexture(GL_TEXTURE_2D, 0);
	
	return result;
}
