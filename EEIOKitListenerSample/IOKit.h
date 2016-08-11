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

#ifndef IOKit_h
#define IOKit_h

#import <Foundation/Foundation.h>
#import <mach/mach.h>

typedef mach_port_t	io_object_t;
typedef io_object_t	io_registry_entry_t;
typedef char		io_name_t[128];
typedef UInt32		IOOptionBits;
typedef io_object_t io_service_t;
typedef io_object_t	io_iterator_t;
typedef void *      IONotificationPortRef;

CFTypeRef IOPSCopyPowerSourcesInfo();
CFArrayRef IOPSCopyPowerSourcesList (CFTypeRef blob);
CFDictionaryRef IOPSGetPowerSourceDescription (CFTypeRef blob, CFTypeRef ps);

kern_return_t IORegistryEntryGetParentEntry ( io_registry_entry_t entry, const io_name_t plane, io_registry_entry_t *parent );

void IONotificationPortDestroy ( IONotificationPortRef notify );

typedef void (* IOServiceMatchingCallback)( void *refcon, io_iterator_t iterator );
typedef void (* IOServiceInterestCallback)( void *refcon, io_service_t service, uint32_t messageType, void *messageArgument );

kern_return_t IOMasterPort ( mach_port_t	bootstrapPort, mach_port_t *	masterPort );

io_registry_entry_t IORegistryGetRootEntry (mach_port_t	masterPort );

kern_return_t IORegistryEntryGetChildIterator ( io_registry_entry_t entry, const io_name_t plane, io_iterator_t *iterator );

kern_return_t IORegistryEntryGetName ( io_registry_entry_t entry, io_name_t name );
kern_return_t IORegistryEntryCreateCFProperties ( io_registry_entry_t entry, CFMutableDictionaryRef *properties, CFAllocatorRef allocator, IOOptionBits options );

CFMutableDictionaryRef IOServiceMatching ( const char *name );
CFMutableDictionaryRef IOServiceNameMatching ( const char *name );

IONotificationPortRef IONotificationPortCreate ( mach_port_t masterPort );

CFRunLoopSourceRef IONotificationPortGetRunLoopSource ( void * notify );

kern_return_t IOServiceAddMatchingNotification (void * notifyPort, const io_name_t notificationType, CFDictionaryRef matching, IOServiceMatchingCallback callback, void *refCon, io_iterator_t *notification );

kern_return_t IOServiceAddInterestNotification ( void *notifyPort, io_service_t service, const io_name_t interestType, IOServiceInterestCallback callback, void *refCon, io_object_t *notification );

io_registry_entry_t IOServiceGetMatchingService ( mach_port_t masterPort, CFDictionaryRef matching );

io_object_t IOIteratorNext ( io_iterator_t iterator );

CFMutableDictionaryRef IOBSDNameMatching (
                  mach_port_t	masterPort,
                  uint32_t	options,
                  const char *	bsdName );

kern_return_t IOServiceOpen (
              io_service_t    service,
              task_port_t	owningTask,
              uint32_t	type,
              io_object_t  *	connect );

kern_return_t IOObjectRelease ( io_object_t object );

#define kIOGeneralInterest		"IOGeneralInterest"

#endif /* IOKit_h */
