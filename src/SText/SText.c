#include <stext/SText.h>
#include <stext/SText_internal.h>

pfnGlGenTextures __glGenTextures = 0;
pfnGlBindTexture __glBindTexture = 0;
pfnGlTexParameteri __glTexParameteri = 0;
pfnGlPixelStorei __glPixelStorei = 0;
pfnGlTexImage2D __glTexImage2D = 0;

pfnGlGenVertexArrays __glGenVertexArrays = 0;
pfnGlBindVertexArray __glBindVertexArray = 0;
pfnGlGenBuffers __glGenBuffers = 0;
pfnGlBindBuffer __glBindBuffer = 0;
pfnGlBufferData __glBufferData = 0;
pfnGlVertexAttribPointer __glVertexAttribPointer = 0;

pfnGlEnableVertexAttribArray __glEnableVertexAttribArray = 0;
pfnGlDrawArrays __glDrawArrays = 0;
pfnGlDrawElements __glDrawElements = 0;

void stInit(stPfnGetProdAdress gl_func) {
	__glGenTextures = gl_func("glGenTextures");
	__glBindTexture = gl_func("glBindTexture");
	__glTexParameteri = gl_func("glTexParameteri");
	__glPixelStorei = gl_func("glPixelStorei");
	__glTexImage2D = gl_func("glTexImage2D");
	
	__glGenVertexArrays = gl_func("glGenVertexArrays");
	__glBindVertexArray = gl_func("glBindVertexArray");
	__glGenBuffers = gl_func("glGenBuffers");
	__glBindBuffer = gl_func("glBindBuffer");
	__glBufferData = gl_func("glBufferData");
	__glVertexAttribPointer = gl_func("glVertexAttribPointer");
	
	__glEnableVertexAttribArray = gl_func("glEnableVertexAttribArray");
	__glDrawArrays = gl_func("glDrawArrays");
	__glDrawElements = gl_func("glDrawElements");
	
	__stInitRenderer();
}
