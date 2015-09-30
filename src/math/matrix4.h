/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#include "math_types.h"
#include "vector4.h"
#include "matrix3.h"

namespace altertum
{

/**
 * @file matrix4.h
 * Extended implementation of Matrix4 API
 * @note Does not use C++ constructors to maintain aggregate struct status
 */

/* constructors */
namespace matrix4
{

inline Matrix4 matrix4(const Vector4 vec[4])
{
    Matrix4 tmp;

    tmp.a = vec[0];
    tmp.b = vec[1];
    tmp.c = vec[2];
    tmp.d = vec[3];

    return tmp;
}

/** Construct Matrix4 from float array. */
inline Matrix4 matrix4(const float f[16])
{
    Matrix4 m;

    m.a.x = f[0];
    m.a.y = f[1];
    m.a.z = f[2];
    m.a.w = f[3];

    m.b.x = f[4];
    m.b.y = f[5];
    m.b.z = f[6];
    m.b.w = f[7];

    m.c.x = f[8];
    m.c.y = f[9];
    m.c.z = f[10];
    m.c.w = f[11];

    m.d.x = f[12];
    m.d.y = f[13];
    m.d.z = f[14];
    m.d.w = f[15];

    return m;
}

/** Construct Matrix4 from Matrix3 @a mat3. */
inline Matrix4 matrix4(const Matrix3& mat3)
{
    Matrix4 tmp;

    tmp.a.x = mat3.a.x;
    tmp.a.y = mat3.a.y;
    tmp.a.z = mat3.a.z;
    tmp.a.w = 0.0;

    tmp.b.x = mat3.b.x;
    tmp.b.y = mat3.b.y;
    tmp.b.z = mat3.b.z;
    tmp.b.w = 0.0;

    tmp.c.x = mat3.c.x;
    tmp.c.y = mat3.c.y;
    tmp.c.z = mat3.c.z;
    tmp.c.w = 0.0;

    tmp.d.x = 0.0;
    tmp.d.y = 0.0;
    tmp.d.z = 0.0;
    tmp.d.w = 1.0;

    return tmp;
}

}; // namespace matrix4

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

/* implementation */
namespace matrix4
{

/** Construct rotation Matrix from Quarternion @a rot. */
inline Matrix4 rotation(const Quaternion& rot)
{
    return matrix4(matrix3::rotation(rot));
}

/** Construct transform matrix from @a scale, @a rotation, and @a translation. */
inline Matrix4 compose(const Vector3& scale, const Quaternion& rotation, const Vector3& translation)
{
    Matrix4 tmp;

    /* scale */
    tmp.a.x = scale.x;
    tmp.b.y = scale.y;
    tmp.c.z = scale.z;
    tmp.d.w = 1.0;

    /* rotation */
    tmp *= matrix4::rotation(rotation);

    /* translation */
    tmp.a.z += translation.x;
    tmp.b.z += translation.y;
    tmp.c.z += translation.z;

    return tmp;
}

}; // namespace matrix4
}; // namespace altertum
