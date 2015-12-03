/*
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#include "math_types.h"

namespace altertum
{

/**
 * @file matrix3.h
 * Extended implementation of Matrix3 API
 * @note Does not use C++ constructors to maintain aggregate struct status
 */

/* constructors */
namespace matrix3
{

inline Matrix3 matrix3(Vector3 vec[3])
{
    Matrix3 tmp;

    tmp.a = vec[0];
    tmp.b = vec[1];
    tmp.c = vec[2];

    return tmp;
}

}; // namespace matrix3

/* implementation */
namespace matrix3
{

inline Matrix3 rotation(const Quaternion& rot)
{
    Matrix3 tmp;

    tmp.a.x = 1.0f - (rot.y * rot.y + rot.z * rot.z);
    tmp.a.y = (rot.x * rot.y - rot.w * rot.z);
    tmp.a.z = (rot.x * rot.z + rot.w * rot.y);

    tmp.b.x = (rot.x * rot.y + rot.w * rot.z);
    tmp.b.y = 1.0f - (rot.x * rot.x + rot.z * rot.z);
    tmp.b.z = (rot.y * rot.z - rot.w * rot.x);

    tmp.c.x = (rot.x * rot.z - rot.w * rot.y);
    tmp.c.y = (rot.y * rot.z + rot.w * rot.x);
    tmp.c.z = 1.0f - (rot.x * rot.x + rot.y * rot.y);

    return tmp;
}

}; // namespace matrix3
}; // namespace altertum
