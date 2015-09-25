/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

namespace altertum
{

struct Vector2
{
    float x, y;
};

struct Vector3
{
    float x, y, z;
};

struct Vector4
{
    float x, y, z, w;
};

struct Quaternion
{
    float x, y, z, w;
};

struct Matrix3
{
    Vector3 a, b, c, d;

    static inline Matrix3 identity() 
    { 
        Matrix3 m = {
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {0.0, 0.0, 1.0}
        };
        return m;

    } 
};

struct Matrix4
{
    Vector4 a, b, c, d;

    static inline Matrix4 identity()
    {
        Matrix4 m = {
            {1.0, 0.0, 0.0, 0.0}, 
            {0.0, 1.0, 0.0, 0.0}, 
            {0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 1.0}
        };
        return m;

    };
};

}; // namespace altertum
