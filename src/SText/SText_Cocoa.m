#include <stext/SText.h>
#include <stext/SText_internal.h>
#include <stext/SText_Cocoa.h>

@implementation AppDelegate

- (id) init {
	self = [super init];
	
	self->running = YES;
	
	return self;
}

- (BOOL) getRunning {
	return self->running;
}

#pragma mark - Window Delegate

- (void)windowWillClose:(NSNotification *)notification {
	self->running = NO;
}

- (void)mouseMoved:(NSEvent *)event {
	//printf("hello\n");
}

@end

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
	
	NSAttributedString * currentText=[[NSAttributedString alloc] initWithString:@(character) attributes: attributes];
	
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
	
	return __stCreateGlyph(rawGlyphData);
}

SFont* stCreateFont(char* fontFamily, int fontSize) {
	SFont* result = malloc(sizeof(SFont));
	
	NSFont* nsFont = [NSFont fontWithName:@(fontFamily) size:fontSize];
	
	result->glyphs = malloc(sizeof(SGlyph)*255);
	
	char* string = malloc(sizeof(char) * 2);
	string[1]=0;
	
	for(unsigned char c = 33; c < 127; c++) {
		string[0]=c;
		result->glyphs[c] = getGlyph(nsFont, fontSize, string);
	}
	
	result->glyphs[' '] = getGlyph(nsFont, fontSize, "H H");
	
	result->spaceWidth = result->glyphs[' ']->width - 2*result->glyphs['H']->width;
	
	result->size = fontSize;
	
	printf("space: %f\n", result->spaceWidth);
	
	return  result;
}
