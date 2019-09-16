#include <stext/SText.h>
#include <stext/SText_internal.h>

#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SGlyph* __stCreateGlyph(_SRawGlyphData* rawData) {
	SGlyph* result = malloc(sizeof(SGlyph));
	
	int boundsX = rawData->width;
	int boundsY = rawData->height;
	int boundsX2 = 0;
	int boundsY2 = 0;
	
	for(int y = 0; y < rawData->height; y++) {
		for(int x = 0; x < rawData->width; x++) {
			if(rawData->data[y*rawData->width + x].a > 0) {
				if(boundsX > x) {
					boundsX = x;
				}
				
				if(boundsY > y) {
					boundsY = y;
				}
				
				if(boundsX2 < x) {
					boundsX2 = x;
				}
				
				if(boundsY2 < y) {
					boundsY2 = y;
				}
			}
		}
	}
	
	//printf("%d %d %d %d\n", boundsX, boundsY, boundsX2, boundsY2);
	
	result->width = boundsX2 - boundsX;
	result->height = boundsY2 - boundsY;
	
	if(result->width <= 0 || result->height <= 0) {
		return 0;
	}
	
	result->bearingX = boundsX - rawData->originX;
	result->bearingY = boundsY - rawData->originY;
	result->advance = result->width + 2;
	result->data = malloc(sizeof(char) * result->width * result->height * 4);
	
	//memset(result->data, 0, sizeof(char) * result->width * result->height * 4);
	
	for(int y = 0; y < result->height; y++) {
		for(int x = 0; x < result->width; x++) {
			result->data[(y*result->width + x)*4 + 0] = rawData->data[(y + boundsY)*rawData->width + (x + boundsX)].a;
			result->data[(y*result->width + x)*4 + 1] = rawData->data[(y + boundsY)*rawData->width + (x + boundsX)].a;
			result->data[(y*result->width + x)*4 + 2] = rawData->data[(y + boundsY)*rawData->width + (x + boundsX)].a;
			result->data[(y*result->width + x)*4 + 3] = rawData->data[(y + boundsY)*rawData->width + (x + boundsX)].a;
		}
	}
	
	return result;
}

void stFontInitGL(SFont* font) {
	for(int i = 33; i < 127; i++) {
		glGenTextures(1, &font->glyphs[i]->GLTexID);
		glBindTexture(GL_TEXTURE_2D, font->glyphs[i]->GLTexID);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		
		glTexImage2D(
					 GL_TEXTURE_2D,
					 0,
					 GL_RGBA,
					 font->glyphs[i]->width,
					 font->glyphs[i]->height,
					 0,
					 GL_RGBA,
					 GL_UNSIGNED_BYTE,
					 font->glyphs[i]->data
					 );
	}
	
	glGenTextures(1, &font->glyphs[' ']->GLTexID);
	glBindTexture(GL_TEXTURE_2D, font->glyphs[' ']->GLTexID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	glTexImage2D(
				 GL_TEXTURE_2D,
				 0,
				 GL_RGBA,
				 font->glyphs[' ']->width,
				 font->glyphs[' ']->height,
				 0,
				 GL_RGBA,
				 GL_UNSIGNED_BYTE,
				 font->glyphs[' ']->data
				 );
	
	glBindTexture(GL_TEXTURE_2D, 0);
}
