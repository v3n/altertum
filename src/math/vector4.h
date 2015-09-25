/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#include "math_types.h"

namespace altertum 
{

/** Returns result of comparison of vectors @a v1 and @a v2. */
inline bool operator==(const Vector4& v1, const Vector4& v2)
{
    return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z) && (v1.w == v2.w);
}

} // namespace altertum
