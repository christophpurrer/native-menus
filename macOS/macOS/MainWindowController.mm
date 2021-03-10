//
//  MainWindowController.m
//  macOS
//
//  Created by Christoph Purrer on 3/10/21.
//

#import "MainWindowController.h"
#import "Menu.h"

@implementation MainWindowController {
}

- (instancetype)init {
    // Nib name must be non-nil: http://www.openradar.me/19289232
    if (self = [super initWithWindowNibName:@""]) {
        self.windowFrameAutosaveName = @"MainWindow";
    }
    return self;
}

- (void)sayHelloToPerson {
    createMenu2();
}

void  createMenu2() {
    NSMenu* menubar = [NSMenu new];
    for(int i=0;i<3;i++) {
    {
        NSMenuItem* appMenuItem = [NSMenuItem new];
        [menubar addItem:appMenuItem];
        
        NSMenu* appMenu = [NSMenu new];
        appMenu.title = @"No we are talking";
        
        NSString* toggleFullScreenTitle = @"Toggle Full Screen";
        NSMenuItem* toggleFullScreenMenuItem = [[NSMenuItem alloc] initWithTitle:toggleFullScreenTitle
                                                                          action:@selector(sayHelloToPerson)
                                                                   keyEquivalent:@"f"];
        [appMenu addItem:toggleFullScreenMenuItem];
        
        NSString* quitTitle = [@"FFFFFF " stringByAppendingString:@"App"];
        NSMenuItem* quitMenuItem = [[NSMenuItem alloc] initWithTitle:quitTitle
                                                              action:@selector(terminate:)
                                                       keyEquivalent:@"q"];
        [appMenu addItem:quitMenuItem];
        [appMenuItem setSubmenu:appMenu];
    }
    }
    NSApplication.sharedApplication.menu = menubar;
}


void  createMenu() {
    NSMenu* menubar = [NSMenu new];
    {
        NSMenuItem* appMenuItem = [NSMenuItem new];
        [menubar addItem:appMenuItem];
        
        NSMenu* appMenu = [NSMenu new];
        appMenu.title = @"No we are talking";
        
        NSString* toggleFullScreenTitle = @"Toggle Full Screen";
        NSMenuItem* toggleFullScreenMenuItem = [[NSMenuItem alloc] initWithTitle:toggleFullScreenTitle
                                                                          action:@selector(sayHelloToPerson)
                                                                   keyEquivalent:@"f"];
        [appMenu addItem:toggleFullScreenMenuItem];
        
        NSString* quitTitle = [@"FFFFFF " stringByAppendingString:@"App"];
        NSMenuItem* quitMenuItem = [[NSMenuItem alloc] initWithTitle:quitTitle
                                                              action:@selector(terminate:)
                                                       keyEquivalent:@"q"];
        [appMenu addItem:quitMenuItem];
        [appMenuItem setSubmenu:appMenu];
    }
    NSApplication.sharedApplication.menu = menubar;
}

- (void)loadWindow {
    self.window = [[NSWindow alloc]
                   initWithContentRect:NSMakeRect(0, [[NSScreen mainScreen] frame].size.height - 640, 360, 640)
                   styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |
                   NSWindowStyleMaskResizable
                   backing:NSBackingStoreBuffered
                   defer:NO];
    self.window.title = @"App";
    self.window.delegate = self;
    [self.window makeKeyAndOrderFront:NULL];
    
    // Default the window to the center of the screen.
    createMenu();
    [NSMenu setMenuBarVisible:YES];
    [self.window center];
}


#pragma mark - NSWindowDelegate

- (BOOL)windowShouldClose:(NSWindow*)window {
    [window orderOut:self];
    return NO;
}

@end
