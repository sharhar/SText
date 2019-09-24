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

pfnGlEnableVertexAttribArray __glEnableVertexAttribArray = 0;
pfnGlDrawArrays __glDrawArrays = 0;

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
	
	__glEnableVertexAttribArray = gl_func("glEnableVertexAttribArray");
	__glDrawArrays = gl_func("glDrawArrays");
	
	__stInitRenderer();
}
