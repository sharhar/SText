#include <GLFW/glfw3.h>
#include <stext/SText.h>

int main() {
	glfwInit();
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "SText-Test", NULL, NULL);
	
	glfwSwapInterval(1);
	glfwMakeContextCurrent(window);

	SGlyph* glyph = stCreateFont("Helvetica", 206);
	
	glEnable(GL_TEXTURE_2D);
	
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	printf("%d\n", glGetError());
	
	glTexImage2D(
				 GL_TEXTURE_2D,
				 0,
				 GL_RGBA,
				 glyph->width,
				 glyph->height,
				 0,
				 GL_RGBA,
				 GL_UNSIGNED_BYTE,
				 glyph->data
				 );
	
	printf("%d\n", glGetError());
	
	glClearColor(1, 0, 1, 1);
	
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
