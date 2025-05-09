#import "AppDelegate.h"
#include "languages.hpp"

@implementation AppDelegate
@synthesize mainWindow;

- (void)ajouter:(id)sender {
    NSLog(@"Ajouter");
    
    // Create the panel
    NSPanel *panel = [[NSPanel alloc] initWithContentRect:NSMakeRect(0, 0, 400, 300)
                                                styleMask:NSWindowStyleMaskTitled|NSWindowStyleMaskClosable
                                                  backing:NSBackingStoreBuffered
                                                    defer:NO];
    [panel setTitle:@"Ajouter un projet"];
    [panel center];
    
    // Add some controls to the panel
    NSTextField *nameLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(20, 250, 100, 20)];
    [nameLabel setStringValue:@"Nom:"];
    [nameLabel setBezeled:NO];
    [nameLabel setDrawsBackground:NO];
    [nameLabel setEditable:NO];
    [nameLabel setSelectable:NO];
    
    NSTextField *nameField = [[NSTextField alloc] initWithFrame:NSMakeRect(120, 250, 250, 20)];
    
    NSTextField *descLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(20, 220, 100, 20)];
    [descLabel setStringValue:@"Description:"];
    [descLabel setBezeled:NO];
    [descLabel setDrawsBackground:NO];
    [descLabel setEditable:NO];
    [descLabel setSelectable:NO];
    
    NSTextField *descField = [[NSTextField alloc] initWithFrame:NSMakeRect(120, 220, 250, 60)];
    
    NSButton *okButton = [[NSButton alloc] initWithFrame:NSMakeRect(270, 20, 100, 30)];
    [okButton setTitle:@"OK"];
    [okButton setBezelStyle:NSBezelStyleRounded];
    [okButton setAction:@selector(closePanel:)];
    [okButton setTarget:panel];
    
    // Add controls to panel
    [[panel contentView] addSubview:nameLabel];
    [[panel contentView] addSubview:nameField];
    [[panel contentView] addSubview:descLabel];
    [[panel contentView] addSubview:descField];
    [[panel contentView] addSubview:okButton];
    
    // Show the panel
    [NSApp runModalForWindow:panel];
}

// Called when the application is activated (including dock icon click)
- (void)applicationDidBecomeActive:(NSNotification *)notification {
    // If there are no visible windows, show the main window
    BOOL hasVisibleWindows = NO;
    for (NSWindow *window in [NSApp windows]) {
        if ([window isVisible]) {
            hasVisibleWindows = YES;
            break;
        }
    }
    
    if (!hasVisibleWindows && self.mainWindow != nil) {
        [self.mainWindow makeKeyAndOrderFront:self];
    }
}

// This method is called when the user clicks on the dock icon
- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag {
    if (!flag && self.mainWindow != nil) {
        [self.mainWindow makeKeyAndOrderFront:self];
    }
    return YES;
}

- (void)dealloc {
    [mainWindow release];
    [super dealloc];
}

@end