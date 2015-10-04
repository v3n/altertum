/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#include <cassert>

#include "platform.h"

/* allows changing later without major refactor */
#define ASSERT(a) assert(a)

/* alignment macros */
#if ALTERTUM_COMPILER_GCC || ALTERTUM_COMPILER_CLANG
#   define __ALIGNED__(x)      __attribute__ ((aligned(x)))
#   define __FORCE_INLINE__    inline  __attribute__ ((always_inline))
#elif ALTERTUM_COMPILER_MSVC
#   define __ALIGNED__(x)      __declspec(align(x))
#   define __FORCE_INLINE__    __forceinline
#else
#   error "Unknown compiler ALTERTUM_COMPILER_?"
#endif
