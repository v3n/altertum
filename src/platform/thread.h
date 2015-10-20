/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#if ALTERTUM_PLATFORM_POSIX
#   include <pthread.h>
#elif ALTERTUM_PLATFORM_WINDOWS 
#   include "win_headers.h"
#   include <process.h>
#endif

#include "macros.h"
#include "semaphore.h"

namespace altertum
{

typedef int32_t (* ThreadMethod)(void *);

struct Thread
{
private:
#if ALTERTUM_PLATFORM_POSIX
    pthread_t _handle;
#elif ALTERTUM_PLATFORM_WINDOWS
    HANDLE _handle;
#endif
    bool _is_active;
    ThreadMethod  _method;
    void * _data;
    size_t _stack_size;
    Semaphore _sem;

public:
    Thread()
#   if ALTERTUM_PLATFORM_POSIX
        : _handle(0)
#   elif ALTERTUM_PLATFORM_WINDOWS
        : _handle(INVALID_HANDLE_VALUE)
#   endif
        , _method(NULL)
        , _data(NULL)
        , _stack_size(0)
        , _is_active(false)
    {
    }

    ~Thread()
    {
        if ( _is_active )
        {
            join();
        }
    }

    void create(ThreadMethod method, void * data = nullptr, size_t stack_size = 0)
    {
        _method     = method;
        _data       = data;
        _stack_size = stack_size;

#   if ALTERTUM_PLATFORM_POSIX
        pthread_attr_t attr;
        int result = pthread_attr_init(&attr);

        if ( _stack_size > 0)
        {
            result = pthread_attr_setstacksize(&attr, _stack_size);
        }

        /* create thread */
        result = pthread_create(&_handle, &attr, thread_process, this);

        /* clean up attr */
        result = pthread_attr_destroy(&attr);

#   elif ALTERTUM_PLATFORM_WINDOWS
        _handle = CreateThread(NULL, m_stackSize, threadFunc, this, 0, NULL);
#   endif // ALTERTUM_PLATFORM_*

        _is_active = true;
        /* @todo: block creator until createe has been initialized */
    }

    void join()
    {
        ASSERT(_is_active);

        /* join thread */
#   if ALTERTUM_PLATFORM_POSIX
        int result = pthread_join(_handle, nullptr);
        ASSERT(result == 0);
        _handle = 0;
#   elif ALTERTUM_PLATFORM_WINDOWS
        WaitForSingleObject(_handle, INFINITE);
        GetExitCodeThread(_handle, (DWORD*)&m_exitCode);
        CloseHandle(_handle);
        _handle = INVALID_HANDLE_VALUE;
#   endif // ALTERTUM_PLATFORM_*

        _is_active = false;
    }

    inline bool is_active()
    {
        return _is_active;
    }

private:

    int32_t run()
    {
        _sem.signal();
        return _method(_data);
    }

#   if ALTERTUM_PLATFORM_POSIX
    static void * thread_process(void * arg)
    {
        static int32_t result = -1;
        result = ((Thread *)arg)->run();
        return (void *)&result;
    }
#   elif ALTERTUM_PLATFORM_WINDOWS
    static DWORD WINAPI thread_process(void * arg)
    {
        Thread * thread = (Thread *)arg;
        int32_t result = thread->run();
        return result;
    }
#   endif

private: /* no copying */
    Thread(const Thread&);
    Thread& operator=(const Thread&);

}; // struct Thread

}; // namespace altertum
