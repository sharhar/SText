#include <GLFW/glfw3.h>
#include <stext/SText.h>

int main() {
	glfwInit();
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "SText-Test", NULL, NULL);
	
	glfwSwapInterval(1);
	glfwMakeContextCurrent(window);

	SFont* font = stCreateFont("Helvetica", 300);
	
	glEnable(GL_TEXTURE_2D);
	
	stFontInitGL(font);
	
	glClearColor(1, 0, 1, 1);
	
	glBindTexture(GL_TEXTURE_2D, font->glyphs[' ']->GLTexID);
	
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1); glVertex2f(-0.5f, -0.5f);
		glTexCoord2f(0, 0); glVertex2f(-0.5f,  0.5f);
		glTexCoord2f(1, 0); glVertex2f( 0.5f,  0.5f);
		glTexCoord2f(1, 1); glVertex2f( 0.5f, -0.5f);
		glEnd();
		
		glfwSwapBuffers(window);
	}
	
	glfwDestroyWindow(window);
	
	glfwTerminate();
	return 0;
}
