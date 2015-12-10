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
#include "scope_lock.h"

namespace altertum
{

struct Semaphore
{
private:
#if ALTERTUM_PLATFORM_POSIX
    Mutex _mutex;
    pthread_cond_t _cond;
    int32_t _count;
#elif ALTERTUM_PLATFORM_WINDOWS
    HANDLE _handle;
#endif // ALTERTUM_PLATFORM_*

public:
    Semaphore()
#	if ALTERTUM_PLATFORM_POSIX
        : _count(0)
#	endif
    {
#   if ALTERTUM_PLATFORM_POSIX
        int result = pthread_cond_init(&_cond, NULL);
        ASSERT(result == 0);
#   elif ALTERTUM_PLATFORM_WINDOWS
        _handle = CreateSemaphore(NULL, 0, LONG_MAX, NULL);
        ASSERT(_handle != NULL);
#   endif // ALTERTUM_PLATFORM_*
    }

    ~Semaphore()
    {
#   if ALTERTUM_PLATFORM_POSIX
        int result = pthread_cond_destroy(&_cond);
        ASSERT(0 == result);
#   elif ALTERTUM_PLATFORM_WINDOWS
        bool result = CloseHandle(_handle);
#   endif // ALTERTUM_PLATFORM_*
    }

    void signal(uint32_t count = 1)
    {
#   if ALTERTUM_PLATFORM_POSIX
        ScopeLock sl(_mutex);

        for ( size_t i = 0; i < count; i++ )
        {
            int result = pthread_cond_signal(&_cond);
            ASSERT(result == 0);
        }

        _count += count;
#   elif ALTERTUM_PLATFORM_WINDOWS
        BOOL err = ReleaseSemaphore(_handle, count, NULL);
        ASSERT(err != 0);
#   endif // ALTERTUM_PLATFORM_*
    }

    void wait()
    {
#   if ALTERTUM_PLATFORM_POSIX
        ScopeLock sl(_mutex);

        while ( _count <= 0 )
        {
            int result = pthread_cond_wait(&_cond, &_mutex._mutex);
            ASSERT(result == 0);
        }

        _count--;
#   elif ALTERTUM_PLATFORM_WINDOWS
        DWORD result = WaitForSingleObject(_handle, INFINITE);
        ASSERT(result == WAIT_OBJECT_0);
#   endif // ALTERTUM_PLATFORM_*
    }

private: /* no copying */
    Semaphore(const Semaphore&);
    Semaphore& operator=(const Semaphore&);
}; // struct Semaphore

}; // namespace altertum
