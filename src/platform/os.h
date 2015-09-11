/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#include "bx/os.h"

namespace altertum
{
    namespace os
    {
        inline void sleep(uint32_t) = bx::sleep;
        inline void yield() = bx::yield;
        inline uint32_t getTid() = bx::getTid;
        inline void * dlopen(const char *) = bx::dlopen;
        inline void dlclose(void *) = bx::dlclose;
        inline void * dlsym(void *, const char *) = bx::dlsym;
        inline void setenv(const char *, const char *) = bx::setenv;
        inline void unsetenv(const char *) = bx::unsetenv;
        inline int chdir(const char *) = bx::chdir;
        inline char * pwd(char *, uint32_t) = bx::pwd;
    } // namespace os
} // namespace altertum
