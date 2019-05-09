#ifndef _MUTEX_H_
#define _MUTEX_H_

#include "./process.h"
#include "./scheduler.h"

void lock_mutex();
void unlock_mutex();

#endif