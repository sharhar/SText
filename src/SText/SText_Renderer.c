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

unsigned int __screenLoc;
unsigned int __transLoc;

void __stInitRenderer() {
	float vects[] = {
		0, 0,
		1, 0,
		1, 1,
		
		0, 0,
		1, 1,
		0, 1
	};
	
	float texcoords[] = {
		0, 1,
		1, 1,
		1, 0,
		
		0, 1,
		1, 0,
		0, 0
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
	
	const char* vertSource = "\
	#version 330 core\n\
	in vec2 position;\n\
	in vec2 texcoord;\n\
	out vec2 texcoord_out;\n\
	uniform vec4 screen;\n\
	uniform vec4 trans;\n\
	void main(void) {\n\
	vec2 translated_coords = vec2(trans.x + position.x*trans.z, trans.y + position.y*trans.w);\
	gl_Position = vec4(2*translated_coords.x/screen.x - 1, 2*translated_coords.y/screen.y - 1, 0, 1);\n\
	texcoord_out = texcoord;\n\
	}\n";
	
	const char* fragSource = "\
	#version 330 core\n\
	out vec4 out_color;\n\
	uniform sampler2D tex;\n\
	in vec2 texcoord_out;\n\
	void main(void) {\n\
	float alpha = texture(tex, texcoord_out).r;\n\
	//if(alpha < 0.5) {discard;}\n\
	out_color = vec4(1, 1, 1, alpha);\n\
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
		return;
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
		return;
	}
	
	__glAttachShader(__shaderProgram, __vertShader);
	__glAttachShader(__shaderProgram, __fragShader);
	
	__glBindAttribLocation(__shaderProgram, 0, "position");
	__glBindAttribLocation(__shaderProgram, 1, "texcoord");
	
	__glLinkProgram(__shaderProgram);
	__glValidateProgram(__shaderProgram);
	
	__glUseProgram(__shaderProgram);
	
	__screenLoc = __glGetUniformLocation(__shaderProgram, "screen");
	__transLoc = __glGetUniformLocation(__shaderProgram, "trans");
	
	__glUniform4f(__screenLoc, 800, 600, 0, 0);
	
	__glUseProgram(0);
}

void stRenderText(SFont* font, const char* text, float posx, float posy) {
	__glBindVertexArray(__rectVAO);
	
	__glEnableVertexAttribArray(0);
	__glEnableVertexAttribArray(1);
	
	__glUseProgram(__shaderProgram);
	
	float xOff = 0;
	float yOff = 0;
	
	SGlyph* glyph = 0;
	
	for (int i = 0; text[i] != 0; i ++) {
		if(text[i] == ' ') {
			xOff += font->spaceWidth;
			continue;
		}
		
		if(text[i] == '\n') {
			yOff += font->size;
			xOff = 0;
			continue;
		}
		
		glyph = font->glyphs[(int)text[i]];
		
		__glActiveTexture(GL_TEXTURE0);
		__glBindTexture(GL_TEXTURE_2D, glyph->GLTexID);
		
		float x = xOff + posx + glyph->bearingX;
		float y = posy + (font->size - glyph->bearingY - glyph->height) - yOff;
		
		//printf("%f %f %f\n", x, y, glyph->bearingX);
		
		__glUniform4f(__transLoc, x, y, glyph->width, glyph->height);
		
		__glDrawArrays(GL_TRIANGLES, 0, 6);
		
		xOff += glyph->advance;
	}
	
	__glUseProgram(0);
	
	__glBindVertexArray(0);
}
