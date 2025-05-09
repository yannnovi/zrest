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
    
    // Add some controls to the panel - with improved alignment and sizing
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
    
    NSTextField *descField = [[NSTextField alloc] initWithFrame:NSMakeRect(120, 220, 250, 20)];
    
    // Create a dictionary to store the form fields for access in the OK button handler
    NSMutableDictionary *formFields = [NSMutableDictionary dictionary];
    [formFields setObject:nameField forKey:@"nameField"];
    [formFields setObject:descField forKey:@"descField"];
    
    NSButton *okButton = [[NSButton alloc] initWithFrame:NSMakeRect(270, 20, 100, 30)];
    [okButton setTitle:@"OK"];
    [okButton setBezelStyle:NSBezelStyleRounded];
    
    // Set up a custom selector for the OK button that will process the form data
    [okButton setAction:@selector(handleOKButton:)];
    
    // Store the form fields dictionary in the button's represented object
    [okButton setRepresentedObject:formFields];
    
    // Set the target to self (AppDelegate)
    [okButton setTarget:self];
    
    // Add a cancel button
    NSButton *cancelButton = [[NSButton alloc] initWithFrame:NSMakeRect(160, 20, 100, 30)];
    [cancelButton setTitle:@"Cancel"];
    [cancelButton setBezelStyle:NSBezelStyleRounded];
    [cancelButton setAction:@selector(handleCancelButton:)];
    [cancelButton setTarget:self];
    
    // Add controls to panel
    [[panel contentView] addSubview:nameLabel];
    [[panel contentView] addSubview:nameField];
    [[panel contentView] addSubview:descLabel];
    [[panel contentView] addSubview:descField];
    [[panel contentView] addSubview:okButton];
    [[panel contentView] addSubview:cancelButton];
    
    // Store the panel in the button's represented object for access in the handler
    [formFields setObject:panel forKey:@"panel"];
    
    // Set the panel to close when the escape key is pressed
    [panel setDefaultButtonCell:[okButton cell]];
    
    // Also handle window close button
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(windowWillClose:)
                                                 name:NSWindowWillCloseNotification
                                               object:panel];
    
    // Show the panel
    [NSApp runModalForWindow:panel];
    
    // Release the panel - it will be closed by the button handlers
    [panel release];
}

// Handler for the OK button in the Ajouter panel
- (void)handleOKButton:(id)sender {
    // Get the form fields from the button's represented object
    NSDictionary *formFields = [sender representedObject];
    NSTextField *nameField = [formFields objectForKey:@"nameField"];
    NSTextField *descField = [formFields objectForKey:@"descField"];
    NSPanel *panel = [formFields objectForKey:@"panel"];
    
    // Get the values from the form fields
    NSString *name = [nameField stringValue];
    NSString *description = [descField stringValue];
    
    // Validate the form data
    if ([name length] == 0) {
        NSAlert *alert = [[NSAlert alloc] init];
        [alert setMessageText:@"Error"];
        [alert setInformativeText:@"Name is required"];
        [alert addButtonWithTitle:@"OK"];
        [alert runModal];
        [alert release];
        return;
    }
    
    // Log the form data
    NSLog(@"Project Name: %@", name);
    NSLog(@"Project Description: %@", description);
    
    // TODO: Add code to save the project to the database
    // Based on the codebase context, you would use zrestdb::Project to create a new project
    
    // Stop the modal session and close the panel
    [NSApp stopModal];
    
    // Remove the observer to prevent memory leaks
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:NSWindowWillCloseNotification
                                                  object:panel];
    
    [panel orderOut:nil];
}

// Handler for the Cancel button
- (void)handleCancelButton:(id)sender {
    // Find the panel (it's the window that contains the button)
    NSWindow *panel = [sender window];
    
    // Stop the modal session and close the panel
    [NSApp stopModal];
    
    // Remove the observer to prevent memory leaks
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:NSWindowWillCloseNotification
                                                  object:panel];
    
    [panel orderOut:nil];
}

// Handler for window close notification
- (void)windowWillClose:(NSNotification *)notification {
    // Stop the modal session when the window is closed
    [NSApp stopModal];
    
    // Remove the observer to prevent memory leaks
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:NSWindowWillCloseNotification
                                                  object:[notification object]];
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
    // Make sure we remove any observers
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [mainWindow release];
    [super dealloc];
}

@end