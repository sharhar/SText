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
unsigned int __rectVBO2;

unsigned int __vertShader;
unsigned int __fragShader;
unsigned int __shaderProgram;

void __stInitRenderer() {
	float vects[] = {
		-0.5f,-0.5f,
		 0.5f,-0.5f,
		 0.5f, 0.5f,
		
		-0.5f,-0.5f,
		 0.5f, 0.5f,
		-0.5f, 0.5f
	};
	
	float texcoords[] = {
		-1,-1,
		 1,-1,
		 1, 1,
		
		-1,-1,
		 1, 1,
		-1, 1
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
	
	char* vertSource = "\
	#version 330 core\n\
	in vec2 position;\n\
	in vec2 texcoord;\n\
	out vec2 texcoord_out;\n\
	void main(void) {\n\
	gl_Position = vec4(position.x, position.y, 0, 1);\n\
	texcoord_out = texcoord;\n\
	}\n";
	
	char* fragSource = "\
	#version 330 core\n\
	out vec4 out_color;\n\
	uniform sampler2D tex;\n\
	in vec2 texcoord_out;\n\
	void main(void) {\n\
	out_color = vec4(texcoord_out.x, texcoord_out.y, 0, 1.0);//texture(tex, texcoord_out);\n\
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
		return NULL;
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
		return NULL;
	}
	
	__glAttachShader(__shaderProgram, __vertShader);
	__glAttachShader(__shaderProgram, __fragShader);
	
	__glBindAttribLocation(__shaderProgram, 0, "position");
	__glBindAttribLocation(__shaderProgram, 1, "texcoord");
	
	__glLinkProgram(__shaderProgram);
	__glValidateProgram(__shaderProgram);
	
	__glUseProgram(__shaderProgram);
	
	//result->uniformLocs[i] = glGetUniformLocation(result->program, uniforms[i]);
	
	__glUseProgram(0);
}

void stRenderText(SFont* font, const char* text) {
	__glBindVertexArray(__rectVAO);
	
	__glEnableVertexAttribArray(0);
	__glEnableVertexAttribArray(1);
	
	__glUseProgram(__shaderProgram);
	
	__glDrawArrays(GL_TRIANGLES, 0, 6);
	
	__glUseProgram(0);
	
	__glBindVertexArray(0);
}
