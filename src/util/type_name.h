/*
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

/*
 * ATTRIB: Getting the type of a template argument as string – without RTTI
 * http://blog.molecular-matters.com/2015/12/11/getting-the-type-of-a-template-argument-as-string-without-rtti/
 */

#pragma once

#include "platform.h"

#if ALTERTUM_COMPILER_GCC
#   define __FUNCTION__ __PRETTY_FUNCTION__
#endif

namespace altertum
{

namespace internal
{
    /* @TODO test GetTypeName() under GCC */

    static const unsigned int FRONT_SIZE = sizeof("internal::GetTypeNameHelper<") - 1u;
    static const unsigned int BACK_SIZE = sizeof(">::GetTypeName") - 1u;

    template <typename T>
    struct GetTypeNameHelper
    {
        static const char* GetTypeName(void)
        {
            static const size_t size = sizeof(__FUNCTION__) - FRONT_SIZE - BACK_SIZE;
            static char typeName[size] = {};
            memcpy(typeName, __FUNCTION__ + FRONT_SIZE, size - 1u);

            return typeName;
        }
    };
} // namespace internal


template <typename T>
const char* GetTypeName(void)
{
    return internal::GetTypeNameHelper<T>::GetTypeName();
}

} // namespace altertum

#if ALTERTUM_COMPILER_GCC
#   undef __FUNCTION__
#endif
