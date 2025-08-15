#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate, NSTableViewDataSource, NSTableViewDelegate>
@property (retain) NSWindow *mainWindow;
@property (retain) NSPanel *currentPanel;
@property (retain) NSTextField *currentNameField;
@property (retain) NSTextField *currentDescField;
@property (retain) NSTableView *projectsTableView;
@property (retain) NSMutableArray *projectsArray;
- (void)ajouter:(id)sender;
- (void)loadProjects;
- (void)refreshProjectsList;
@end