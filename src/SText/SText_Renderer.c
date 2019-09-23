//
//  SText_Renderer.c
//  SText
//
//  Created by Shahar Sandhaus on 9/22/19.
//

#include <stext/SText.h>
#include <stext/SText_internal.h>

#include <stdio.h>

unsigned int __rectVAO;
unsigned int __rectVBO1;

unsigned int __vertShader;
unsigned int __fragShader;
unsigned int __shaderProgram;

unsigned char indicies[3] = {
	0, 1, 2
};

void __stInitRenderer() {
	float rectBuffer[] = {
		-0.5f,-0.5f,
		 0.5f,-0.5f,
		 0.5f, 0.5f,
		
		-0.5f,-0.5f,
		 0.5f, 0.5f,
		-0.5f, 0.5f
	};
	
	__glGenVertexArrays(1, &__rectVAO);
	__glBindVertexArray(__rectVAO);
	
	__glGenBuffers(1, &__rectVBO1);
	__glBindBuffer(GL_ARRAY_BUFFER, __rectVBO1);
	__glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, rectBuffer, GL_STATIC_DRAW);
	__glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, 0);
	__glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	__glBindVertexArray(0);
}

void stRenderText(SFont* font, const char* text) {
	__glBindVertexArray(__rectVAO);
	
	__glEnableVertexAttribArray(0);
	
	//__glDrawArrays(GL_TRIANGLES, 0, 3);
	
	__glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indicies);
	
	__glBindVertexArray(0);
}
