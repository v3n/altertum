/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#include "mutex.h"
#include "macros.h"

namespace altertum
{

/**
 * Scope-based mutex locking and unlocking.
 */
struct ScopeLock
{
private:
    Mutex _mutex;

public:
    /** Locks @a m mutex. */
    ScopeLock(Mutex& m) : _mutex(m)
    {
        _mutex.lock();
    }

    /** Unlock internal mutex */
    ~ScopeLock()
    {
        _mutex.unlock();
    }

private: /* no copying */
    ScopeLock(const ScopeLock&);
    ScopeLock& operator=(const ScopeLock&);
}; // struct ScopeLock

}; // namespace altertum
