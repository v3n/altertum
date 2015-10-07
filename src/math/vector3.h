/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#include <cmath>

#include "math_types.h"

namespace altertum 
{

/**
 * @file vector3.h
 * Extended implementation of Vector3 API
 * @note Does not use C++ constructors to maintain aggregate struct status
 */

/* constructors */
namespace vector3
{
    /** Construct Vector3 from Vector2 */
    inline Vector3 vector3(Vector2 v)
    {
        Vector3 tmp;

        tmp.x = v.x;
        tmp.y = v.y;
        tmp.z = 0.0f;

        return tmp;
    }

    /** Construct Vector3 from components */
    inline Vector3 vector3(float x, float y, float z)
    {
        Vector3 tmp;

        tmp.x = x;
        tmp.y = y;
        tmp.z = z;

        return tmp;
    }
}; // namespace vector3

/** Returns result of comparison of vectors @a v1 and @a v2. */
inline bool operator==(const Vector3& v1, const Vector3& v2)
{
    return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
}

inline Vector3 operator+=(Vector3& v1, const Vector3& v2)
{
    v1.x += v2.x;
    v1.y += v1.y;
    v1.z += v2.z;

    return v1;
}

inline Vector3 operator+(Vector3 v1, const Vector3& v2)
{
    v1 += v2;
    return v1;
}

inline Vector3 operator-=(Vector3& v1, const Vector3& v2)
{
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;

    return v1;
}

inline Vector3 operator-(Vector3 v1, const Vector3& v2)
{
    v1 -= v2;
    return v1;
}

/** dot product @todo: remove this operator */
inline float operator*(const Vector3& v1, const Vector3& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/** Returns result of scalar multiplication of Vector3 @a v and float @a f */
inline Vector3 operator*=(Vector3& v, const float f)
{
    v.x *= f;
    v.y *= f;
    v.z *= f;

    return v;
}

/** Returns result of scalar multiplication of Vector3 @a v and float @a f */
inline Vector3 operator*(Vector3 v, const float f)
{
    v *= f;
    return v;
}

/** scalar division */
inline Vector3 operator/=(Vector3& v1, const float f)
{
    v1.x /= f;
    v1.y /= f;
    v1.z /= f;

    return v1;
}

/** scalar division */
inline Vector3 operator/(Vector3 v1, const float f)
{
    v1 /= f;
    return v1;
}

/* implementation */
namespace vector3
{

/** cross product */
inline Vector3 cross(const Vector3& v1, const Vector3& v2)
{
    Vector3 v = { 
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
    return v;
}

/** Dot product */
inline float dot(const Vector3& v1, const Vector3& v2)
{
    return v1 * v2;
}

/* returns distance for @a v */
inline float distance(const Vector3& v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

/* Returns unit vector for @a v */
inline Vector3 normalize(const Vector3& v)
{
    return v / distance(v);
}


inline Vector2 xy(const Vector3& v)
{
    Vector2 tmp;

    tmp.x = v.x;
    tmp.y = v.y;

    return tmp;
}

}; // namespace vector3
}; // namespace altertum
