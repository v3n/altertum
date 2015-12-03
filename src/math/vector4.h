/*
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#include "math_types.h"

namespace altertum
{

/**
 * @file vector4.h
 * Extended implementation of Vector4 API
 * @note Does not use C++ constructors to maintain aggregate struct status
 */

/* constructors */
namespace vector4
{
    /** Construct Vector4 from Vector3 @a v */
    inline Vector4 vector4(Vector3& v)
    {
        return { v.x, v.y, v.z, 0.0f };
    }

    /** Construct Vector4 from components */
    inline Vector4 vector4(float x, float y, float z, float w)
    {
        return { x, y, z, w };
    }
}

/** Returns result of comparison of vectors @a v1 and @a v2. */
inline bool operator==(const Vector4& v1, const Vector4& v2)
{
    return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z) && (v1.w == v2.w);
}

} // namespace altertum
