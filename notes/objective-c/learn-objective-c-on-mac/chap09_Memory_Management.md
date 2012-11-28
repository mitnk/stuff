Chapter 09 Memory Management
============================

Each object maintains a retain count. Objects start their lives with a retain
count of 1. When the object is retained, the retain count increases by 1, and
when the object is released, the retain count is decreased by 1. When the 
retain count reaches 0, the object is destroyed. The object''s dealloc message
is called first, and then its memory is recycled, ready for use by other 
objects.

When an object receives the autorelease message, its retain count doesn''t 
change immediately; instead, the object is placed into an NSAutoreleasePool. 
When this pool is destroyed, all the objects in the pool are sent a release 
message. Any objects that have been autoreleased will then have their retain 
count decremented by 1. If the count goes to 0, the object is destroyed. When 
you use the AppKit, an autorelease pool will be created and destroyed for you 
at well-defined times, such as when the current user event has been handled.
Otherwise, you are responsible for creating your own autorelease pool. The 
template for Foundation tools includes code for this.

Cocoa has three rules about objects and their retain counts:

- If you get the object from a `new`, `alloc`, or `copy` operation, the object
has a retain counts of 1.

- If you get the object any other way, assume it has a retain counts of 1 and 
that it has been autoreleased.

- If you retain an object, you must balance every retain with a release.

