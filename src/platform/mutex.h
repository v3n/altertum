/*
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#if ALTERTUM_PLATFORM_POSIX
#   include <pthread.h>
#elif ALTERTUM_PLATFORM_WINDOWS
#   ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
#   endif
#   include <windows.h>
#   include <process.h>
#endif

#include "macros.h"

namespace altertum
{

struct Mutex
{
public:
#if ALTERTUM_PLATFORM_POSIX
    pthread_mutex_t _mutex;
private:
    pthread_mutexattr_t _attr;
#elif ALTERTUM_PLATFORM_WINDOWS
    CRITICAL_SECTION _mutex;
#endif

public:
    Mutex()
    {
#   if ALTERTUM_PLATFORM_POSIX
        int result = pthread_mutexattr_init(&_attr);
        result = pthread_mutexattr_settype(&_attr, PTHREAD_MUTEX_ERRORCHECK);
        result = pthread_mutex_init(&_mutex, &_attr);
#   elif ALTERTUM_PLATFORM_WINDOWS
        InitializeCriticalSection(&_mutex);
#   endif // ALTERTUM_PLATFORM_*
    }

    ~Mutex()
    {
#   if ALTERTUM_PLATFORM_POSIX
        int result = pthread_mutex_destroy(&_mutex);
        result = pthread_mutexattr_destroy(&_attr);
#   elif ALTERTUM_PLATFORM_WINDOWS
        DeleteCriticalSection(&_mutex);
#   endif // ALTERTUM_PLATFORM_*
    }

    void lock()
    {
#   if ALTERTUM_PLATFORM_POSIX
        int result = pthread_mutex_lock(&_mutex);
        ASSERT(result == 0);
#   elif ALTERTUM_PLATFORM_WINDOWS
        EnterCriticalSection(&_mutex);
#   endif // ALTERTUM_PLATFORM_*
    }

    void unlock()
    {
#   if ALTERTUM_PLATFORM_POSIX
        int result = pthread_mutex_unlock(&_mutex);
#   elif ALTERTUM_PLATFORM_WINDOWS
        LeaveCriticalSection(&_mutex);
#   endif // ALTERTUM_PLATFORM_*
    }

private: /* no copying */
    Mutex(const Mutex&);
    Mutex& operator=(const Mutex&);
}; // struct mutex

}; // namespace altertum
