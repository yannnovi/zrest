#import "MainWindowController.h"

static NSWindow *gWindow = nil;

@interface MainWindowController ()
@end

@implementation MainWindowController 

- (void)windowDidLoad {
    [super windowDidLoad];
    gWindow = self.window;
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
}

- (BOOL)windowShouldClose:(id)sender {
    [NSApp hide:nil];
    return NO;
}

- (BOOL)applicationShouldHandleReopen:(NSApplication *)theApplication hasVisibleWindows:(BOOL)flag {
    if (flag) {
        return NO;
    } else {
        if (gWindow) {
            [gWindow makeKeyAndOrderFront:self];
        }
        return YES;
    }
}

- (void)awakeFromNib {
    // Placeholder for nib-based initialization
}

@end
