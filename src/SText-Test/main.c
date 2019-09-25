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
	
	SFont* font = stCreateFont("Helvetica", 100);
	
	glfwSwapInterval(1);
	glfwMakeContextCurrent(window);
	
	gladLoadGLLoader(glfwGetProcAddress);
	
	stInit(glfwGetProcAddress);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	stFontInitGL(font);
	
	glClearColor(0, 0, 0, 1);
	
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		//stRenderText(font, "testing", 100, 100);
		
		stRenderText(font, "The quick brown\nfox jumped over\nthe lazy dog", 50, 300);
		
		glfwSwapBuffers(window);
	}
	
	glfwDestroyWindow(window);
	
	glfwTerminate();
	return 0;
}
