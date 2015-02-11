#include <Foundation/Foundation.h>
#include <objc/runtime.h>
#include "MinGUI.h"




NSString *fakeBundleIdentifier = nil;

@implementation NSBundle(swizle)
- (NSString * )__bundleIdentifier
{
    if (self == [NSBundle mainBundle]) {
        return fakeBundleIdentifier ? fakeBundleIdentifier : @"com.apple.finder";
    } else {
        return [self __bundleIdentifier];
    }
}
@end

BOOL installNSBundleHook()
{
    Class classp = objc_getClass("NSBundle");
    if (classp) {
        method_exchangeImplementations(class_getInstanceMethod(classp, @selector(bundleIdentifier)),
                                       class_getInstanceMethod(classp, @selector(__bundleIdentifier)));
        return YES;
    }
	return NO;
}

BOOL keepRunning = YES;

@interface NotificationCenterDelegate : NSObject<NSUserNotificationCenterDelegate>
//@property (nonatomic, assign)
@end

@implementation NotificationCenterDelegate
- (void)userNotificationCenter:(NSUserNotificationCenter *)center didDeliverNotification:(NSUserNotification *)notification
{
    keepRunning = NO;
}

@end

void Notification(const char * title, const char * subtitle, const char * footer, int lifetime){
    if (installNSBundleHook()) {
        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
        
        fakeBundleIdentifier = [defaults stringForKey:@"identifier"];
        
        NSUserNotificationCenter *nc = [NSUserNotificationCenter defaultUserNotificationCenter];
        NotificationCenterDelegate *ncDelegate = [[NotificationCenterDelegate alloc]init];
//        NSUserNotificationCenterDelegate *ncDelegate = [[NSUserNotificationCenterDelegate alloc] init];
//        ncDelegate.keepRunning = YES;
        nc.delegate = ncDelegate;
        
        
        
//        [nc.delegate keepRunning: YES];
        
        NSUserNotification *note = [[NSUserNotification alloc] init];
        note.title = [defaults stringForKey:@"title"];
        note.subtitle = [defaults stringForKey:@"subtitle"];
        note.informativeText = [defaults stringForKey:@"informativeText"];
        
        if (!(note.title || note.subtitle || note.informativeText)) {
            note.title = [[NSString alloc] initWithUTF8String:title]; //@"Usage: usernotification";
            note.subtitle = [[NSString alloc] initWithUTF8String:subtitle];
            note.informativeText = [[NSString alloc] initWithUTF8String:footer]; //@"Options: [-identifier <IDENTIFIER>] [-title <TEXT>] [-subtitle TEXT] [-informativeText TEXT]";
        }
        
        [nc deliverNotification:note];
        
       while (keepRunning) {
            [[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:0.1]];
        }
    }
}
