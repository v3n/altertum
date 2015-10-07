/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#include "math_types.h"

namespace altertum
{

/* constructors */
namespace vector2
{
    inline Vector2 vector2(float x, float y)
    {
        Vector2 tmp;

        tmp.x = x;
        tmp.y = y;

        return tmp;
    }
}; // namespace vector2

inline bool operator==(const Vector2& v1, const Vector2& v2)
{
    return (v1.x == v2.x) && (v1.y == v2.y);
}

}; // namespace altertum
