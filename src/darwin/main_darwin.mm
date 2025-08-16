#import <Cocoa/Cocoa.h>
#include "main_darwin.h"
#include "languages.hpp"
#import "MainWindowController.h"
#import "AppDelegate.h"
#import "PanelExtension.h"

// Constants for UI layout
static const CGFloat kWindowWidth = 800.0;
static const CGFloat kWindowHeight = 600.0;
static const CGFloat kButtonHeight = 30.0;
static const CGFloat kButtonWidth = 100.0;
static const CGFloat kMargin = 5.0;
static const CGFloat kButtonBottomMargin = 10.0;

@interface ZRestApplication : NSObject
+ (ZRestApplication *)sharedInstance;
- (BOOL)setupApplication;
- (void)setupMenuBar;
- (NSWindow *)createMainWindow;
- (void)setupMainWindowContent:(NSWindow *)window;
- (NSScrollView *)createProjectsTableView;
- (void)addButtonsToWindow:(NSWindow *)window;
@end

@implementation ZRestApplication

+ (ZRestApplication *)sharedInstance {
    static ZRestApplication *instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[ZRestApplication alloc] init];
    });
    return instance;
}

- (BOOL)setupApplication {
    [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    
    // Set application icon
    NSString *imagePath = [[NSBundle mainBundle] pathForResource:@"zrestgui" ofType:@"png" inDirectory:@"img"];
    if (!imagePath) {
        imagePath = @"img/zrestgui.png"; // Fallback to relative path
    }
    NSImage *appIcon = [[NSImage alloc] initWithContentsOfFile:imagePath];
    if (appIcon) {
        [NSApp setApplicationIconImage:appIcon];
        [appIcon release];
    }
    
    // Create and set the app delegate
    AppDelegate *appDelegate = [[AppDelegate alloc] init];
    [NSApp setDelegate:appDelegate];
    
    return YES;
}

- (void)setupMenuBar {
    NSMenu *menubar = [[NSMenu new] autorelease];
    NSMenuItem *appMenuItem = [[NSMenuItem new] autorelease];
    [menubar addItem:appMenuItem];
    [NSApp setMainMenu:menubar];
    
    NSMenu *appMenu = [[NSMenu new] autorelease];
    NSString *appName = [[NSProcessInfo processInfo] processName];
    
    NSString *quitTitle = [NSString stringWithFormat:@"%s %@", _("Quit"), appName];
    NSMenuItem *quitMenuItem = [[[NSMenuItem alloc] 
        initWithTitle:quitTitle
        action:@selector(terminate:) 
        keyEquivalent:@"q"] autorelease];
    
    [appMenu addItem:quitMenuItem];
    [appMenuItem setSubmenu:appMenu];
}

- (NSWindow *)createMainWindow {
    NSRect windowFrame = NSMakeRect(0, 0, kWindowWidth, kWindowHeight);
    NSUInteger styleMask = NSWindowStyleMaskClosable | 
                          NSWindowStyleMaskResizable | 
                          NSWindowStyleMaskTitled;
    
    NSWindow *window = [[[NSWindow alloc] 
        initWithContentRect:windowFrame
        styleMask:styleMask
        backing:NSBackingStoreBuffered 
        defer:NO] autorelease];
    
    [window setReleasedWhenClosed:NO];
    [window cascadeTopLeftFromPoint:NSMakePoint(20, 20)];
    [window setTitle:[[NSProcessInfo processInfo] processName]];
    
    return window;
}

- (void)setupMainWindowContent:(NSWindow *)window {
    NSScrollView *scrollView = [self createProjectsTableView];
    [[window contentView] addSubview:scrollView];
    
    [self addButtonsToWindow:window];
}

- (NSScrollView *)createProjectsTableView {
    // Calculate table view frame (leave space for buttons at bottom)
    CGFloat tableHeight = kWindowHeight - kButtonHeight - (kButtonBottomMargin * 2) - kMargin;
    CGFloat tableWidth = kWindowWidth - (kMargin * 2);
    NSRect scrollFrame = NSMakeRect(kMargin, kButtonHeight + kButtonBottomMargin + kMargin, 
                                   tableWidth, tableHeight);
    
    NSScrollView *scrollView = [[NSScrollView alloc] initWithFrame:scrollFrame];
    [scrollView setBorderType:NSBezelBorder];
    [scrollView setHasVerticalScroller:YES];
    [scrollView setHasHorizontalScroller:YES];
    [scrollView setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
    
    // Create table view
    NSTableView *tableView = [[NSTableView alloc] initWithFrame:NSMakeRect(0, 0, tableWidth, tableHeight)];
    
    // Configure table columns
    NSTableColumn *nameColumn = [[NSTableColumn alloc] initWithIdentifier:@"name"];
    [nameColumn setWidth:(tableWidth - 20) * 0.4]; // 40% of width
    [nameColumn setEditable:NO];
    [nameColumn setHeaderCell:[[NSTableHeaderCell alloc] initTextCell:@"Project Name"]];
    [tableView addTableColumn:nameColumn];
    [nameColumn release];
    
    NSTableColumn *descColumn = [[NSTableColumn alloc] initWithIdentifier:@"description"];
    [descColumn setWidth:(tableWidth - 20) * 0.6]; // 60% of width
    [descColumn setEditable:NO];
    [descColumn setHeaderCell:[[NSTableHeaderCell alloc] initTextCell:@"Description"]];
    [tableView addTableColumn:descColumn];
    [descColumn release];
    
    // Configure table view
    [tableView setHeaderView:[[NSTableHeaderView alloc] init]];
    [tableView setAllowsMultipleSelection:NO];
    [tableView setAllowsColumnReordering:NO];
    [tableView setAllowsColumnResizing:YES];
    [tableView setAllowsEmptySelection:YES];
    [tableView setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
    
    // Set data source and delegate to AppDelegate
    AppDelegate *appDelegate = (AppDelegate *)[NSApp delegate];
    [tableView setDataSource:appDelegate];
    [tableView setDelegate:appDelegate];
    appDelegate.projectsTableView = tableView;
    
    [scrollView setDocumentView:tableView];
    [tableView release];
    
    return [scrollView autorelease];
}

- (void)addButtonsToWindow:(NSWindow *)window {
    AppDelegate *appDelegate = (AppDelegate *)[NSApp delegate];
    
    // Quit button (right-aligned)
    CGFloat quitButtonX = kWindowWidth - kButtonWidth - kMargin;
    NSRect quitFrame = NSMakeRect(quitButtonX, kButtonBottomMargin, kButtonWidth, kButtonHeight);
    NSButton *quitButton = [[NSButton alloc] initWithFrame:quitFrame];
    [quitButton setTitle:@"Quitter"];
    [quitButton setBezelStyle:NSBezelStyleRounded];
    [quitButton setAction:@selector(terminate:)];
    [quitButton setAutoresizingMask:NSViewMinXMargin | NSViewMaxYMargin];
    [[window contentView] addSubview:quitButton];
    [quitButton release];
    
    // Add button (left of quit button)
    CGFloat addButtonX = quitButtonX - kButtonWidth - kMargin;
    NSRect addFrame = NSMakeRect(addButtonX, kButtonBottomMargin, kButtonWidth, kButtonHeight);
    NSButton *addButton = [[NSButton alloc] initWithFrame:addFrame];
    [addButton setTitle:@"Ajouter"];
    [addButton setBezelStyle:NSBezelStyleRounded];
    [addButton setAction:@selector(ajouter:)];
    [addButton setTarget:appDelegate];
    [addButton setAutoresizingMask:NSViewMinXMargin | NSViewMaxYMargin];
    [[window contentView] addSubview:addButton];
    [addButton release];
    
    // Delete button (left of add button)
    CGFloat deleteButtonX = addButtonX - kButtonWidth - kMargin;
    NSRect deleteFrame = NSMakeRect(deleteButtonX, kButtonBottomMargin, kButtonWidth, kButtonHeight);
    NSButton *deleteButton = [[NSButton alloc] initWithFrame:deleteFrame];
    [deleteButton setTitle:@"Supprimer"];
    [deleteButton setBezelStyle:NSBezelStyleRounded];
    [deleteButton setAction:@selector(supprimer:)];
    [deleteButton setTarget:appDelegate];
    [deleteButton setAutoresizingMask:NSViewMinXMargin | NSViewMaxYMargin];
    [[window contentView] addSubview:deleteButton];
    [deleteButton release];
}

@end

int zrestgui::main_app(int argc, char *argv[])
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    @try {
        ZRestApplication *app = [ZRestApplication sharedInstance];
        
        if (![app setupApplication]) {
            NSLog(@"Failed to setup application");
            return -1;
        }
        
        [app setupMenuBar];
        
        NSWindow *mainWindow = [app createMainWindow];
        if (!mainWindow) {
            NSLog(@"Failed to create main window");
            return -1;
        }
        
        [app setupMainWindowContent:mainWindow];
        
        // Store window reference in app delegate
        AppDelegate *appDelegate = (AppDelegate *)[NSApp delegate];
        appDelegate.mainWindow = mainWindow;
        
        [mainWindow makeKeyAndOrderFront:nil];
        [NSApp activateIgnoringOtherApps:YES];
        
        // Load projects data
        [appDelegate loadProjects];
        
        [NSApp run];
    }
    @catch (NSException *exception) {
        NSLog(@"Exception occurred: %@", exception);
        return -1;
    }
    
    [pool release];
    return 0;
}