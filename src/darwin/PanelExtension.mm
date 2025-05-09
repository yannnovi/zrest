#import "PanelExtension.h"

@implementation NSPanel (PanelExtension)
- (void)closePanel:(id)sender {
    [NSApp stopModal];
    [self close];
}
@end