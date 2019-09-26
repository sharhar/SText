#include <GLFW/glfw3.h>
#include <stext/SText.h>
#include <stext/SText_GL.h>

#include <stdio.h>
#include <math.h>

int main() {
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "SText-Test", NULL, NULL);
	
	SFont* font = stCreateFont("Times New Roman", 72);
	
	glfwSwapInterval(1);
	glfwMakeContextCurrent(window);
	
	stInitGL(glfwGetProcAddress);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	SFontGL* fontGL = stCreateFontGL(font);
	
	glClearColor(0, 0, 0, 1);
	
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		stRenderTextGL(fontGL, "The quick brown\nfox jumped over\nthe lazy dog", 0, 600);
		
		glfwSwapBuffers(window);
	}
	
	glfwDestroyWindow(window);
	
	glfwTerminate();
	return 0;
}
