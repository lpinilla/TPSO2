#ifndef _MUTEX_H
#define _MUTEX_H

#include <process.h>
#include <scheduler.h>

void lock_mutex();
void unlock_mutex();

#endif