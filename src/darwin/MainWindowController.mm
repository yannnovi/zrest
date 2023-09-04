#import "MainWindowController.h"
id gWindow;
@interface MainWindowController ()
@end
@implementation MainWindowController 
//@synthesize viewController=vc;
- (void)windowDidLoad {
    [super windowDidLoad];
    // Implement this method to handle any initialization after your window controller’s window has been loaded from its nib file.
}
- (BOOL)windowShouldClose:(id)sender {
    [NSApp hide:nil];
    return NO;
}

- (BOOL)applicationShouldHandleReopen:(NSApplication *)theApplication hasVisibleWindows:(BOOL)flag
{
    if (flag) {
        return NO;
    }
    else
    {
       [gWindow makeKeyAndOrderFront:self];// Window that you want open while click on dock app icon
        return YES;
    }
}
/*
- (void)setViewController:(NSViewController *)newController
{
    if (vc)
    {
        NSResponder *controllerNextResponder = [vc nextResponder];
        [super setNextResponder:controllerNextResponder];
        [vc setNextResponder:nil];
    }

    vc = newController;
    
    if (newController)
    {
        NSResponder *ownNextResponder = [self nextResponder];
        [super setNextResponder: vc];
        [vc setNextResponder:ownNextResponder];
    }
}
*/
-(void)awakeFromNib {
 // [self setViewController:this]
}

@end 