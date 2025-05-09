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
    
    // Create the main window with larger dimensions to accommodate the list box
    NSWindow *window = [[[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 800, 600)
        styleMask:NSWindowStyleMaskClosable|NSWindowStyleMaskResizable|NSWindowStyleMaskTitled 
        backing:NSBackingStoreBuffered defer:NO] autorelease];
    
    // Set window to not terminate the app when closed
    [window setReleasedWhenClosed:NO];
    
    // Store a reference to the main window in the app delegate
    appDelegate.mainWindow = window;

    //[window setContentViewController:vc];           
    [window cascadeTopLeftFromPoint:NSMakePoint(20,20)];
    [window setTitle:appName];
    
    // Create a scroll view to contain the table view (list box)
    NSScrollView *scrollView = [[NSScrollView alloc] initWithFrame:NSMakeRect(5, 5, 790, 550)];
    [scrollView setBorderType:NSBezelBorder];
    [scrollView setHasVerticalScroller:YES];
    [scrollView setHasHorizontalScroller:YES];
    [scrollView setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
    
    // Create a table view (macOS equivalent of a list box)
    NSTableView *tableView = [[NSTableView alloc] initWithFrame:NSMakeRect(0, 0, 790, 550)];
    
    // Add a column to the table view
    NSTableColumn *column = [[NSTableColumn alloc] initWithIdentifier:@"name"];
    [column setWidth:780];
    [column setEditable:NO];
    [column setHeaderCell:[[NSTableHeaderCell alloc] initTextCell:@"Projects"]];
    [tableView addTableColumn:column];
    [column release];
    
    // Configure the table view
    [tableView setHeaderView:[[NSTableHeaderView alloc] init]];
    [tableView setAllowsMultipleSelection:NO];
    [tableView setAllowsColumnReordering:NO];
    [tableView setAllowsColumnResizing:YES];
    [tableView setAllowsEmptySelection:YES];
    [tableView setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
    
    // Set the table view as the document view of the scroll view
    [scrollView setDocumentView:tableView];
    [tableView release];
    
    // Add the scroll view to the window
    [[window contentView] addSubview:scrollView];
    [scrollView release];
    
    // Add buttons at the bottom of the window
    NSButton *buttonQuit = [[NSButton alloc] initWithFrame:NSMakeRect(700, 560, 100, 30)];
    [buttonQuit setTitle:@"Quitter"];
    [buttonQuit setBezelStyle:NSBezelStyleRoundRect];
    [buttonQuit setAction:@selector(terminate:)];
    [[window contentView] addSubview: buttonQuit];
    [buttonQuit release];

    NSButton *buttonAjout = [[NSButton alloc] initWithFrame:NSMakeRect(590, 560, 100, 30)];
    [buttonAjout setTitle:@"Ajouter"];
    [buttonAjout setBezelStyle:NSBezelStyleRoundRect];
    [buttonAjout setAction:@selector(ajouter:)];
    [buttonAjout setTarget:appDelegate];  // Set the target to our app delegate
    [[window contentView] addSubview: buttonAjout];
    [buttonAjout release];
    
    [window makeKeyAndOrderFront:window];
    [NSApp activateIgnoringOtherApps:YES];
    [NSApp run];
    [appDelegate release];  // Release our app delegate
    [NSApp release];      // release the app 
    [pool release];

    return 0;
}