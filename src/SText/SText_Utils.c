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
	
	result->width = boundsX2 - boundsX;
	result->height = boundsY2 - boundsY;
	
	if(result->width <= 0 || result->height <= 0) {
		return 0;
	}
	
	result->bearingX = boundsX - rawData->originX;
	result->bearingY = boundsY - rawData->originY;
	result->advance = result->width + result->bearingX;
	result->data = malloc(sizeof(char) * result->width * result->height);
	
	for(int y = 0; y < result->height; y++) {
		for(int x = 0; x < result->width; x++) {
			result->data[(int)(y*result->width + x)] = rawData->data[(y + boundsY)*rawData->width + (x + boundsX)].a;
		}
	}
	
	return result;
}
