#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
@property (retain) NSWindow *mainWindow;
@property (retain) NSPanel *currentPanel;
@property (retain) NSTextField *currentNameField;
@property (retain) NSTextField *currentDescField;
- (void)ajouter:(id)sender;
@end