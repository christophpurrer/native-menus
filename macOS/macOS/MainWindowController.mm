//
//  MainWindowController.m
//  macOS
//
//  Created by Christoph Purrer on 3/10/21.
//

#import "MainWindowController.h"
#import "Menu.h"
#include <typeinfo>

@implementation MainWindowController {
}

- (instancetype)init {
    // Nib name must be non-nil: http://www.openradar.me/19289232
    if (self = [super initWithWindowNibName:@""]) {
        self.windowFrameAutosaveName = @"MainWindow";
    }
    return self;
}

- (IBAction)menuItemClicked:(id)sender {
    if ([sender conformsToProtocol:@protocol(NSUserInterfaceItemIdentification)] &&
        [sender identifier]) {
        NSLog(@"menuItem: %@", ((NSMenuItem *) sender).title);
    }
}

void createAppMenu() {
    // https://medium.com/@theboi/macos-apps-without-storyboard-or-xib-menu-bar-in-swift-5-menubar-and-toolbar-6f6f2fa39ccb
    auto applicationMenus = createApplicationMenu();
    NSMenu* menubar = [NSMenu new];
    for (auto const& applicationMenu : applicationMenus) {
        NSMenuItem* menuItem = [NSMenuItem new];
        [menubar addItem:menuItem];
        NSMenu* menu = [NSMenu new];
        menu.title = [NSString stringWithUTF8String: applicationMenu.title.c_str()];
        
        for (auto& menuEntry : applicationMenu.entries) {
            auto menuEntryItem = dynamic_cast<MenuEntry*>(menuEntry.get());
            if (menuEntryItem) { //
                NSString* title =[NSString stringWithUTF8String: menuEntryItem->title.c_str()];
                NSMenuItem* subMenuItem = [[NSMenuItem alloc] initWithTitle:title
                                                                     action:@selector(menuItemClicked:)
                                                              keyEquivalent:@""];
                [subMenuItem setEnabled:menuEntryItem->enabled ? YES : NO];
                [menu addItem:subMenuItem];
            }
            auto menuEntrySeparator = dynamic_cast<Separator*>(menuEntry.get());
            if (menuEntrySeparator) {
                [menu addItem: [NSMenuItem separatorItem]];              
            }
        }
        [menuItem setSubmenu:menu];
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
    [NSMenu setMenuBarVisible:YES];
    [self.window center];
    createAppMenu();
}


#pragma mark - NSWindowDelegate

- (BOOL)windowShouldClose:(NSWindow*)window {
    [window orderOut:self];
    return NO;
}

@end
