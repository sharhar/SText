//
//  SText_Cocoa.m
//  SText
//
//  Created by Shahar Sandhaus on 9/13/19.
//

#include <stext/SText.h>
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
	
	//[[NSColor redColor] set];
	//[NSBezierPath fillRect:NSMakeRect(10,10,40,40)];
	
	NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys:[NSFont fontWithName:@"Helvetica" size:26], NSFontAttributeName,[NSColor blackColor], NSForegroundColorAttributeName, nil];
	
	NSAttributedString * currentText=[[NSAttributedString alloc] initWithString:@"Catç" attributes: attributes];
	
	NSSize attrSize = [currentText size];
	[currentText drawAtPoint:NSMakePoint(40, 40)];
	
	[NSGraphicsContext restoreGraphicsState];
	
	NSImage* image = [[NSImage alloc] initWithSize:NSMakeSize(width, height)];
	[image addRepresentation:newRep];
	
	NSImageView* imageView = [[NSImageView alloc] init];
	[imageView setFrame:NSMakeRect(0, 0, width, height)];
	[imageView setImage:image];
	
	[[window contentView] addSubview:imageView];
	
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
