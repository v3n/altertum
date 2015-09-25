/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#include "math_types.h"
#include "vector4.h"

namespace altertum
{

/** Return result of comparison of matrices @a m1 and @a m2. */
inline bool operator==(const Matrix4& m1, const Matrix4& m2)
{
    return (m1.a == m2.a) && (m1.b == m2.b) && (m1.c == m2.c) && (m1.d == m2.d);
}

/** Assign to @a m1 the result of matrix multiplication @a m1 * @a m2. */
inline Matrix4 operator*=(Matrix4& m1, const Matrix4& m2)
{
    Matrix4 tmp;

    tmp.a.x = (m1.a.x * m2.a.x) + (m1.b.x * m2.a.y) + (m1.c.x * m2.a.z) + (m1.d.x * m2.a.w);
    tmp.a.y = (m1.a.y * m2.a.x) + (m1.b.y * m2.a.y) + (m1.c.y * m2.a.z) + (m1.d.y * m2.a.w);
    tmp.a.z = (m1.a.z * m2.a.x) + (m1.b.z * m2.a.y) + (m1.c.z * m2.a.z) + (m1.d.z * m2.a.w);
    tmp.a.w = (m1.a.w * m2.a.x) + (m1.b.w * m2.a.y) + (m1.c.w * m2.a.z) + (m1.d.w * m2.a.w);

    tmp.b.x = (m1.a.x * m2.b.x) + (m1.b.x * m2.b.y) + (m1.c.x * m2.b.z) + (m1.d.x * m2.b.w);
    tmp.b.y = (m1.a.y * m2.b.x) + (m1.b.y * m2.b.y) + (m1.c.y * m2.b.z) + (m1.d.y * m2.b.w);
    tmp.b.z = (m1.a.z * m2.b.x) + (m1.b.z * m2.b.y) + (m1.c.z * m2.b.z) + (m1.d.z * m2.b.w);
    tmp.b.w = (m1.a.w * m2.b.x) + (m1.b.w * m2.b.y) + (m1.c.w * m2.b.z) + (m1.d.w * m2.b.w);

    tmp.c.x = (m1.a.x * m2.c.x) + (m1.b.x * m2.c.y) + (m1.c.x * m2.c.z) + (m1.d.x * m2.c.w);
    tmp.c.y = (m1.a.y * m2.c.x) + (m1.b.y * m2.c.y) + (m1.c.y * m2.c.z) + (m1.d.y * m2.c.w);
    tmp.c.z = (m1.a.z * m2.c.x) + (m1.b.z * m2.c.y) + (m1.c.z * m2.c.z) + (m1.d.z * m2.c.w);
    tmp.c.w = (m1.a.w * m2.c.x) + (m1.b.w * m2.c.y) + (m1.c.w * m2.c.z) + (m1.d.w * m2.c.w);

    tmp.d.x = (m1.a.x * m2.d.x) + (m1.b.x * m2.d.y) + (m1.c.x * m2.d.z) + (m1.d.x * m2.d.w);
    tmp.d.y = (m1.a.y * m2.d.x) + (m1.b.y * m2.d.y) + (m1.c.y * m2.d.z) + (m1.d.y * m2.d.w);
    tmp.d.z = (m1.a.z * m2.d.x) + (m1.b.z * m2.d.y) + (m1.c.z * m2.d.z) + (m1.d.z * m2.d.w);
    tmp.d.w = (m1.a.w * m2.d.x) + (m1.b.w * m2.d.y) + (m1.c.w * m2.d.z) + (m1.d.w * m2.d.w);

    return m1 = tmp;
}

/** Multiply matrix @a m1 by @a m2 and returns result. */
inline Matrix4 operator*(Matrix4 m1, const Matrix4& m2)
{
    m1 *= m2;
    return m1;
}

}; // namespace altertum
