/*
 *
 *    Copyright (C) 2016 Eldad Eilam
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This Program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#import "EEIOKitListener.h"

@implementation EEIOKitListener

+ (instancetype) sharedEEIOKitListener
{
    static EEIOKitListener *listener;
    static dispatch_once_t predicate;
    dispatch_once(&predicate, ^{
        listener = [[EEIOKitListener alloc] init];
    });
    
    return listener;
}

- (instancetype) init
{
    self = [super init];
    
    IOMasterPort(MACH_PORT_NULL, &masterPort);
    
    CFMutableDictionaryRef serviceDict = IOServiceMatching("AppleARMPMUCharger");
    charger_entry = IOServiceGetMatchingService(masterPort, serviceDict);
        
    return self;
}

- (void) chargerObjectRefreshed
{
    CFMutableDictionaryRef chargerProperties = nil, armPMUChargerProperties;
    
    IORegistryEntryCreateCFProperties( charger_entry, &armPMUChargerProperties,
                                            kCFAllocatorDefault,
                                            kNilOptions);
    
    _chargerDict = (__bridge NSDictionary *)(armPMUChargerProperties);

    [[NSNotificationCenter defaultCenter] postNotificationName:kEEIOKitListenerNewDataNotification object:self userInfo:_chargerDict];
}

void ARMPMUStateChanged( void *listenerInstance, io_service_t service, uint32_t messageType, void *messageArgument )
{
    [((__bridge EEIOKitListener *) listenerInstance) chargerObjectRefreshed];
}

- (void) requestDataRefresh
{
    [self chargerObjectRefreshed];
}

- (void) startListener
{
    if (listenerActive == NO)
    {
        // Set up auto notifications for our charger object:
        notificationPort = IONotificationPortCreate(masterPort);
        notificationRunLoopSource = IONotificationPortGetRunLoopSource(notificationPort);
        CFRunLoopAddSource([[NSRunLoop currentRunLoop] getCFRunLoop], notificationRunLoopSource, kCFRunLoopDefaultMode);
        
        io_object_t notificationObject;
        
        IOServiceAddInterestNotification(notificationPort,
                                               charger_entry,
                                               kIOGeneralInterest,
                                               ARMPMUStateChanged,
                                               (__bridge void *) self,
                                               &notificationObject);
        listenerActive = YES;        
    }
}

- (void) stopListener
{
    if (listenerActive == YES)
    {
        if (CFRunLoopSourceIsValid(notificationRunLoopSource) == YES)
        {
            CFRunLoopSourceInvalidate(notificationRunLoopSource);
        }
        
        if (CFRunLoopContainsSource([[NSRunLoop currentRunLoop] getCFRunLoop], notificationRunLoopSource, kCFRunLoopDefaultMode))
        {
            CFRunLoopRemoveSource([[NSRunLoop currentRunLoop] getCFRunLoop], notificationRunLoopSource, kCFRunLoopDefaultMode);
        }
        
        IONotificationPortDestroy(notificationPort);
        
        listenerActive = NO;
    }
}

@end
