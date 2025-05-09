#import <Cocoa/Cocoa.h>
#include "main_darwin.h"
#include "languages.hpp"
#import "MainWindowController.h"
#import "AppDelegate.h"
#import "PanelExtension.h"

int zrestgui::main_app(int argc, char *argv[])
{
    NSImage *mImage = [[NSImage alloc] initWithContentsOfFile:@"img/zrestgui.png"];

    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    
    // Create and set the app delegate
    AppDelegate *appDelegate = [[AppDelegate alloc] init];
    [NSApp setDelegate:appDelegate];
    
    id menubar = [[NSMenu new] autorelease];
    id appMenuItem = [[NSMenuItem new] autorelease];
    [menubar addItem:appMenuItem];
    
    [NSApp setMainMenu:menubar];

    [NSApp setApplicationIconImage:mImage];
    id appMenu = [[NSMenu new] autorelease];
    id appName = [[NSProcessInfo processInfo] processName];
    id vc =  [[MainWindowController new] autorelease];
    
    NSString *quitTitle = [NSString stringWithFormat:@"%s %@", _("Quit"),appName];
    id quitMenuItem = [[[NSMenuItem alloc] initWithTitle:quitTitle
        action:@selector(terminate:) keyEquivalent:@"q"] autorelease];
    [appMenu addItem:quitMenuItem];
    [appMenuItem setSubmenu:appMenu];
    
    // Create the main window
    NSWindow *window = [[[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 800, 200)
        styleMask:NSWindowStyleMaskClosable|NSWindowStyleMaskResizable|NSWindowStyleMaskTitled 
        backing:NSBackingStoreBuffered defer:NO] autorelease];
    
    // Set window to not terminate the app when closed
    [window setReleasedWhenClosed:NO];
    
    // Store a reference to the main window in the app delegate
    appDelegate.mainWindow = window;

    //[window setContentViewController:vc];           
    [window cascadeTopLeftFromPoint:NSMakePoint(20,20)];
    [window setTitle:appName];
    [window makeKeyAndOrderFront:window];

    NSButton *buttonQuit = [[NSButton alloc] initWithFrame:NSMakeRect(700,150, 100, 20)];
    [buttonQuit setTitle:@"Quitter"];
    [buttonQuit setBezelStyle:NSBezelStyleRoundRect];
    [buttonQuit setAction:@selector(terminate:)];
    [[window contentView] addSubview: buttonQuit];

    NSButton *buttonAjout = [[NSButton alloc] initWithFrame:NSMakeRect(700, 170, 100, 20)];
    [buttonAjout setTitle:@"Ajouter"];
    [buttonAjout setBezelStyle:NSBezelStyleRoundRect];
    [buttonAjout setAction:@selector(ajouter:)];
    [buttonAjout setTarget:appDelegate];  // Set the target to our app delegate
    [[window contentView] addSubview: buttonAjout];
    
    [NSApp activateIgnoringOtherApps:YES];
    [NSApp run];
    [appDelegate release];  // Release our app delegate
    [NSApp release];      // release the app 
    [pool release];

    return 0;
}