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

void stInit() {
	int width = 300;
	int height = 300;
	char* title = "SText-Test";
	
	NSUInteger windowStyle = NSWindowStyleMaskTitled  | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable;
	
	NSRect screenRect = [[NSScreen mainScreen] frame];
	NSRect viewRect = NSMakeRect(0, 0, width, height);
	NSRect windowRect = NSMakeRect(NSMidX(screenRect) - NSMidX(viewRect),
								   NSMidY(screenRect) - NSMidY(viewRect),
								   viewRect.size.width,
								   viewRect.size.height);
	
	NSWindow* window = [[NSWindow alloc] initWithContentRect:windowRect
												   styleMask:windowStyle
													 backing:NSBackingStoreBuffered
													   defer:NO];
	
	[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
	
	[window setDelegate:(AppDelegate*)[NSApp delegate]];
	[window setAcceptsMouseMovedEvents:YES];
	
	[window setTitle:@(title)];
	
	[window setContentView:[[NSView alloc] initWithFrame:viewRect]];
	[[window contentView] setWantsLayer:YES];
	
	[window makeKeyAndOrderFront:nil];
	
	//[window setBackgroundColor:NSColor.whiteColor];
	
	//[[window contentView] lockFocus];
	
	//[[NSColor redColor] set];
	//[NSBezierPath fillRect:NSMakeRect(0,0,4,4)];
	
	//[[window contentView] unlockFocus];
	//[[window contentView] setNeedsDisplay:YES];
	
	//NSArray *fonts = [[NSFontManager sharedFontManager] availableFontFamilies];
	
	NSFont* font = [[NSFontManager sharedFontManager] fontWithFamily:@"Arial"
															  traits:0
															  weight:5
																size:12];
	
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
	
	[[NSColor redColor] set];
	[NSBezierPath fillRect:NSMakeRect(0,height-10,20,10)];
	
	NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys:[NSFont fontWithName:@"Helvetica" size:26], NSFontAttributeName,[NSColor blackColor], NSForegroundColorAttributeName, nil];
	
	NSAttributedString * currentText=[[NSAttributedString alloc] initWithString:@"C|" attributes: attributes];
	
	NSSize attrSize = [currentText size];
	[currentText drawAtPoint:NSMakePoint(40, 40)];
	
	[NSGraphicsContext restoreGraphicsState];
	
	NSImage* image = [[NSImage alloc] initWithSize:NSMakeSize(width, height)];
	[image addRepresentation:newRep];
	
	NSImageView* imageView = [[NSImageView alloc] init];
	[imageView setFrame:NSMakeRect(0, 0, width, height)];
	[imageView setImage:image];
	
	[[window contentView] addSubview:imageView];
	
	NSData* imageData = [image TIFFRepresentation];
	char* rawData = [imageData bytes];
	unsigned int rawLength = [imageData length];
	
	TIFFImageHeaderRaw* imageHeaderRaw = (TIFFImageHeaderRaw*)rawData;
	
	TIFFImageHeaderRaw* imageHeaderFixed = malloc(sizeof(TIFFImageHeaderRaw));
	
	imageHeaderFixed->ID[0] = imageHeaderRaw->ID[0];
	imageHeaderFixed->ID[1] = imageHeaderRaw->ID[1];
	
	imageHeaderFixed->version[0] = imageHeaderRaw->version[1];
	imageHeaderFixed->version[1] = imageHeaderRaw->version[0];
	
	imageHeaderFixed->offsetOfImage[0] = imageHeaderRaw->offsetOfImage[3];
	imageHeaderFixed->offsetOfImage[1] = imageHeaderRaw->offsetOfImage[2];
	imageHeaderFixed->offsetOfImage[2] = imageHeaderRaw->offsetOfImage[1];
	imageHeaderFixed->offsetOfImage[3] = imageHeaderRaw->offsetOfImage[0];
	
	TIFFImageHeader* imageHeader = (TIFFImageHeader*)imageHeaderFixed;
	
	printf("%s %d %d\n", imageHeader->ID, imageHeader->version, imageHeader->offsetOfImage);
	
	printf("%d x %d = %d\n", width, height, width * height);
	printf("%d\n", rawLength);
	
	TIFFImageData* data = (TIFFImageData*)rawData+8;
	
	printf("%d %d %d %d\n", data[21].r, data[21].g, data[21].b, data[21].a);
	
	while (![[window delegate] getRunning]) {
		@autoreleasepool {
			NSEvent* ev;
			do {
				ev = [NSApp nextEventMatchingMask: NSEventMaskAny
										untilDate: nil
										   inMode: NSDefaultRunLoopMode
										  dequeue: YES];
				
				if (ev) {
					
					[NSApp sendEvent: ev];
				}
			} while (ev);
		}
	}
	
	[window close];
	[window dealloc];
}
