#include <stext/SText.h>
#include <stext/SText_internal.h>

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#define FIRST_CHAR 33
#define LAST_CHAR 127

typedef struct TIFFImageHeaderRaw {
	char ID[2];
	char version[2];
	char offsetOfImage[4];
} TIFFImageHeaderRaw;

typedef struct TIFFImageHeader {
	char ID[2];
	short version;
	int offsetOfImage;
} TIFFImageHeader;

typedef struct TIFFImageData {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
}TIFFImageData;

char** stGetAllFonts() {
	//NSArray *fonts = [[NSFontManager sharedFontManager] availableFontFamilies];
	
	return 0;
}

SGlyph* getGlyph(NSFont* font, int fontSize, char* character) {
	int width = fontSize*3;
	int height = fontSize*3;

	NSBitmapImageRep *newRep = [[NSBitmapImageRep alloc] initWithBitmapDataPlanes:NULL
																	   pixelsWide:width
																	   pixelsHigh:height
																	bitsPerSample:8
																  samplesPerPixel:4
																		 hasAlpha:YES
																		 isPlanar:NO
																   colorSpaceName:NSDeviceRGBColorSpace
																	  bytesPerRow:4 * width
																	 bitsPerPixel:32];
	
	NSGraphicsContext* context = [NSGraphicsContext graphicsContextWithBitmapImageRep:newRep];
	
	[NSGraphicsContext saveGraphicsState];
	[NSGraphicsContext setCurrentContext:context];
	
	NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys:font, NSFontAttributeName,[NSColor blackColor], NSForegroundColorAttributeName, nil];
	
	NSAttributedString * currentText = [[NSAttributedString alloc] initWithString:@(character) attributes: attributes];
	
	[currentText drawAtPoint:NSMakePoint(fontSize, height-2*fontSize)];
	
	[NSGraphicsContext restoreGraphicsState];
	
	NSImage* image = [[NSImage alloc] initWithSize:NSMakeSize(width, height)];
	[image addRepresentation:newRep];
	
	NSData* imageData = [image TIFFRepresentation];
	char* rawData = [imageData bytes];

	_SRawGlyphData* rawGlyphData = malloc(sizeof(_SRawGlyphData));
	
	rawGlyphData->fontSize = fontSize;
	rawGlyphData->width = width;
	rawGlyphData->height = height;
	rawGlyphData->originX = fontSize;
	rawGlyphData->originY = fontSize;
	rawGlyphData->data = rawData+8;
	rawGlyphData->c = character[0];
	
	SGlyph* result = __stCreateGlyph(rawGlyphData);
	
	free(rawGlyphData);
	
	[imageData release];
	[image release];
	[currentText release];
	[attributes release];
	[context release];
	[newRep release];
	
	return result;
}

SFont* stCreateFont(char* fontFamily, int fontSize) {
	SFont* result = malloc(sizeof(SFont));
	
	NSFont* nsFont = [NSFont fontWithName:@(fontFamily) size:fontSize];
	
	result->glyphs = malloc(sizeof(SGlyph)*(LAST_CHAR -  FIRST_CHAR));
	
	char* string = malloc(sizeof(char) * 2);
	string[1]=0;
	
	for(unsigned char c = 0; c < LAST_CHAR -  FIRST_CHAR; c++) {
		string[0]=c + FIRST_CHAR;
		result->glyphs[c] = getGlyph(nsFont, fontSize, string);
	}
	
	free(string);
	
	SGlyph* spaceGlyph = getGlyph(nsFont, fontSize, "H H");
	
	result->spaceWidth = spaceGlyph->width - 2*result->glyphs['H' - FIRST_CHAR]->width;
	
	__stDestroyGlyph(spaceGlyph);
	
	result->size = fontSize;
	result->firstChar = FIRST_CHAR;
	result->lastChar = LAST_CHAR;
	
	[nsFont release];
	
	return  result;
}
