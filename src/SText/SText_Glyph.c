#include <stext/SText.h>
#include <stext/SText_internal.h>

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
			if(rawData->data[y*rawData->width + x].a > 128) {
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
