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

}; // namespace vector3

/** Returns result of comparison of vectors @a v1 and @a v2. */
inline bool operator==(const Vector3& v1, const Vector3& v2)
{
    return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
}

/** dot product */
inline float operator*(const Vector3& v1, const Vector3& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
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

}; // namespace vector3
}; // namespace altertum
