#import "AppDelegate.h"
#include "languages.hpp"

// Constants for panel layout
static const CGFloat kPanelWidth = 400.0;
static const CGFloat kPanelHeight = 300.0;
static const CGFloat kFieldHeight = 20.0;
static const CGFloat kButtonHeight = 30.0;
static const CGFloat kButtonWidth = 100.0;
static const CGFloat kLabelWidth = 100.0;
static const CGFloat kFieldWidth = 250.0;
static const CGFloat kMargin = 20.0;

@interface AppDelegate ()
- (NSPanel *)createAddProjectPanel;
- (void)setupPanelControls:(NSPanel *)panel;
- (void)showPanel:(NSPanel *)panel;
- (void)cleanupPanel:(NSPanel *)panel;
- (BOOL)validateFormFields;
- (void)showValidationAlert:(NSString *)message;
@end

@implementation AppDelegate
@synthesize mainWindow;
@synthesize currentPanel = _currentPanel;
@synthesize currentNameField = _currentNameField;
@synthesize currentDescField = _currentDescField;

- (void)ajouter:(id)sender {
    NSLog(@"Ajouter method called");
    
    @try {
        self.currentPanel = [self createAddProjectPanel];
        NSLog(@"Panel created: %@", self.currentPanel);
        
        [self setupPanelControls:self.currentPanel];
        NSLog(@"Panel controls setup complete");
        
        [self showPanel:self.currentPanel];
        NSLog(@"Show panel called");
    }
    @catch (NSException *exception) {
        NSLog(@"Exception in ajouter: %@", exception);
    }
}

- (NSPanel *)createAddProjectPanel {
    NSRect panelFrame = NSMakeRect(0, 0, kPanelWidth, kPanelHeight);
    NSUInteger styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable;
    
    NSPanel *panel = [[NSPanel alloc] initWithContentRect:panelFrame
                                                styleMask:styleMask
                                                  backing:NSBackingStoreBuffered
                                                    defer:NO];
    [panel setTitle:@"Ajouter un projet"];
    [panel center];
    
    return panel; // Don't autorelease here since we want to retain it
}

- (void)setupPanelControls:(NSPanel *)panel {
    CGFloat currentY = kPanelHeight - kMargin - kFieldHeight;
    
    // Name label and field
    NSTextField *nameLabel = [[NSTextField alloc] initWithFrame:
        NSMakeRect(kMargin, currentY, kLabelWidth, kFieldHeight)];
    [nameLabel setStringValue:@"Nom:"];
    [nameLabel setBezeled:NO];
    [nameLabel setDrawsBackground:NO];
    [nameLabel setEditable:NO];
    [nameLabel setSelectable:NO];
    
    NSTextField *nameField = [[NSTextField alloc] initWithFrame:
        NSMakeRect(kMargin + kLabelWidth, currentY, kFieldWidth, kFieldHeight)];
    
    currentY -= (kFieldHeight + 10);
    
    // Description label and field
    NSTextField *descLabel = [[NSTextField alloc] initWithFrame:
        NSMakeRect(kMargin, currentY, kLabelWidth, kFieldHeight)];
    [descLabel setStringValue:@"Description:"];
    [descLabel setBezeled:NO];
    [descLabel setDrawsBackground:NO];
    [descLabel setEditable:NO];
    [descLabel setSelectable:NO];
    
    NSTextField *descField = [[NSTextField alloc] initWithFrame:
        NSMakeRect(kMargin + kLabelWidth, currentY, kFieldWidth, kFieldHeight)];
    
    // Create form fields dictionary
    NSMutableDictionary *formFields = [NSMutableDictionary dictionary];
    [formFields setObject:nameField forKey:@"nameField"];
    [formFields setObject:descField forKey:@"descField"];
    
    // OK button
    CGFloat okButtonX = kPanelWidth - kMargin - kButtonWidth;
    NSButton *okButton = [[NSButton alloc] initWithFrame:
        NSMakeRect(okButtonX, kMargin, kButtonWidth, kButtonHeight)];
    [okButton setTitle:@"OK"];
    [okButton setBezelStyle:NSBezelStyleRounded];
    [okButton setAction:@selector(handleOKButton:)];
    [okButton setTarget:self];
    [okButton setTag:1]; // Use tag to identify this as OK button
    
    // Cancel button
    CGFloat cancelButtonX = okButtonX - kButtonWidth - 10;
    NSButton *cancelButton = [[NSButton alloc] initWithFrame:
        NSMakeRect(cancelButtonX, kMargin, kButtonWidth, kButtonHeight)];
    [cancelButton setTitle:@"Cancel"];
    [cancelButton setBezelStyle:NSBezelStyleRounded];
    [cancelButton setAction:@selector(handleCancelButton:)];
    [cancelButton setTarget:self];
    [cancelButton setTag:2]; // Use tag to identify this as Cancel button
    
    // Store form fields in instance variables for later access
    self.currentNameField = nameField;
    self.currentDescField = descField;
    
    // Add controls to panel
    [[panel contentView] addSubview:nameLabel];
    [[panel contentView] addSubview:nameField];
    [[panel contentView] addSubview:descLabel];
    [[panel contentView] addSubview:descField];
    [[panel contentView] addSubview:okButton];
    [[panel contentView] addSubview:cancelButton];
    
    // Set default button and key view loop
    [panel setDefaultButtonCell:[okButton cell]];
    [nameField setNextKeyView:descField];
    [descField setNextKeyView:okButton];
    [okButton setNextKeyView:cancelButton];
    [cancelButton setNextKeyView:nameField];
    
    // Release controls (they're retained by their superview)
    [nameLabel release];
    [nameField release];
    [descLabel release];
    [descField release];
    [okButton release];
    [cancelButton release];
}

- (void)showPanel:(NSPanel *)panel {
    NSLog(@"showPanel called with panel: %@", panel);
    
    // Handle window close button
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(windowWillClose:)
                                                 name:NSWindowWillCloseNotification
                                               object:panel];
    
    NSLog(@"About to run modal for window");
    [NSApp runModalForWindow:panel];
    NSLog(@"Modal session ended");
}

- (void)cleanupPanel:(NSPanel *)panel {
    [NSApp stopModal];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:NSWindowWillCloseNotification
                                                  object:panel];
    
    [panel orderOut:nil];
    [panel release]; // Release the panel we created
    
    // Clear instance variables
    self.currentPanel = nil;
    self.currentNameField = nil;
    self.currentDescField = nil;
}
// Handler for the OK button in the Ajouter panel
- (void)handleOKButton:(id)sender {
    NSPanel *panel = (NSPanel *)[sender window];
    
    if (![self validateFormFields]) {
        return;
    }
    
    NSString *name = [self.currentNameField stringValue];
    NSString *description = [self.currentDescField stringValue];
    
    // Log the form data
    NSLog(@"Project Name: %@", name);
    NSLog(@"Project Description: %@", description);
    
    // TODO: Add code to save the project to the database
    // Based on the codebase context, you would use zrestdb::Project to create a new project
    
    [self cleanupPanel:panel];
}

// Handler for the Cancel button
- (void)handleCancelButton:(id)sender {
    NSPanel *panel = (NSPanel *)[sender window];
    [self cleanupPanel:panel];
}

// Handler for window close notification
- (void)windowWillClose:(NSNotification *)notification {
    NSPanel *panel = (NSPanel *)[notification object];
    [self cleanupPanel:panel];
}

- (BOOL)validateFormFields {
    NSString *name = [self.currentNameField stringValue];
    
    if ([name length] == 0) {
        [self showValidationAlert:@"Name is required"];
        return NO;
    }
    
    return YES;
}

- (void)showValidationAlert:(NSString *)message {
    NSAlert *alert = [[NSAlert alloc] init];
    [alert setMessageText:@"Error"];
    [alert setInformativeText:message];
    [alert addButtonWithTitle:@"OK"];
    [alert runModal];
    [alert release];
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
    [_currentPanel release];
    [_currentNameField release];
    [_currentDescField release];
    [super dealloc];
}

@end