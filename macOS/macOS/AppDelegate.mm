//
//  AppDelegate.m
//  macOS
//
//  Created by Christoph Purrer on 3/10/21.
//

#import "AppDelegate.h"
#import "MainWindowController.h"

@implementation AppDelegate {
  MainWindowController *_windowController;
}

- (void)applicationWillFinishLaunching:(NSNotification *)__unused
    aNotification {
  _windowController = [MainWindowController new];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
  [_windowController showWindow:self];
  // Insert code here to initialize your application
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
  // Insert code here to tear down your application
}

@end
