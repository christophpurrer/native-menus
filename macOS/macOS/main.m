//
//  main.m
//  macOS
//
//  Created by Christoph Purrer on 3/10/21.
//

#import <Cocoa/Cocoa.h>
#import "AppDelegate.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        //https://stackoverflow.com/questions/34664206/how-can-i-create-a-cocoa-application-without-storyboards-or-interface-builders-i
        [NSApplication sharedApplication];
        [NSApp setDelegate:[AppDelegate new]];
        [NSApp run];
        // Setup code that might create autoreleased objects goes here.
    }
    // return NSApplicationMain(argc, argv);
}
