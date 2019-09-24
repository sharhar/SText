#include "glad.h"
#include <GLFW/glfw3.h>
#include <stext/SText.h>

#include <stdio.h>

int main() {
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "SText-Test", NULL, NULL);
	
	SFont* font = stCreateFont("Helvetica", 300);
	
	glfwSwapInterval(1);
	glfwMakeContextCurrent(window);
	
	gladLoadGLLoader(glfwGetProcAddress);
	
	stInit(glfwGetProcAddress);
	
	stFontInitGL(font);
	
	glClearColor(1, 0, 1, 1);
	
	glBindTexture(GL_TEXTURE_2D, font->glyphs[' ']->GLTexID);
	
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		stRenderText(font, "test");
		
		glfwSwapBuffers(window);
	}
	
	glfwDestroyWindow(window);
	
	glfwTerminate();
	return 0;
}
