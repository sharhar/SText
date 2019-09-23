#include "glad.h"
#include <GLFW/glfw3.h>
#include <stext/SText.h>

#include <stdio.h>

#define GL_DEBUG_SOURCE_API 0x8246
#define GL_DEBUG_TYPE_ERROR 0x824C

typedef void (APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC)(GLDEBUGPROC callback, const void *userParam);

int min_c(int a, int b) {
	return a < b ? a : b;
}

const char*
getGLSourceStr(GLenum source)
{
	static const char* sources[] = {
		"API",   "Window System", "Shader Compiler", "Third Party", "Application",
		"Other", "Unknown"
	};
	
	int str_idx =
	min_c(source - GL_DEBUG_SOURCE_API,
		sizeof(sources) / sizeof(const char *));
	
	return sources[str_idx];
}

const char*
getGLTypeStr(GLenum type)
{
	static const char* types[] = {
		"Error",       "Deprecated Behavior", "Undefined Behavior", "Portability",
		"Performance", "Other",               "Unknown"
	};
	
	int str_idx =
	min_c(type - GL_DEBUG_TYPE_ERROR,
		sizeof(types) / sizeof(const char *));
	
	return types[str_idx];
}

void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id,
							  GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	
	printf("OpenGL Error:\n");
	printf("=============\n");
	printf(" Object ID: %d\n", id);
	printf(" Type: %s\n", getGLTypeStr(type));
	printf(" Source: %s\n", getGLSourceStr(source));
	printf(" Message: %s\n\n", message);
}

int main() {
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "SText-Test", NULL, NULL);
	
	PFNGLDEBUGMESSAGECALLBACKPROC pfnDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)
	glfwGetProcAddress("glDebugMessageCallback");
	
	if (pfnDebugMessageCallback) {
		pfnDebugMessageCallback(glDebugCallback, NULL);
	}
	
	printf("%p\n", window);
	
	SFont* font = stCreateFont("Helvetica", 300);
	
	glfwSwapInterval(1);
	glfwMakeContextCurrent(window);
	
	gladLoadGLLoader(glfwGetProcAddress);
	
	stInit(glfwGetProcAddress);
	
	printf("%d\n", glGetError());
	
	stFontInitGL(font);
	
	glClearColor(1, 0, 1, 1);
	
	glBindTexture(GL_TEXTURE_2D, font->glyphs[' ']->GLTexID);
	
	printf("%d\n", glGetError());
	
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		stRenderText(font, "test");
		
		printf("%d\n", glGetError());
		
		glfwSwapBuffers(window);
	}
	
	glfwDestroyWindow(window);
	
	glfwTerminate();
	return 0;
}
