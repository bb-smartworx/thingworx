// **************************************************************************
//
// Functions for work with lock files
//
// **************************************************************************

#ifndef _LOCK_H_
#define _LOCK_H_

// create lock
extern int lock(const char *device, int tout);

// release lock
extern void unlock(const char *device);

#endif

