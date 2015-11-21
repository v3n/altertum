/*
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

/**
 * @file math_types.h
 * Light-weight type declaration for math POD structs
 * Include corresponding file for type API
 */

#pragma once

namespace altertum
{

/** 2D Vector */
struct Vector2
{
    float x, y;
};

/* 3D Vector */
struct Vector3
{
    float x, y, z;

    static inline Vector3 up()
    {
        Vector3 v = { 0.0f, 1.0f, 0.0f };
        return v;
    }
};

/* 4D Vector */
struct Vector4
{
    float x, y, z, w;
};

/* Rotation by quaternion */
struct Quaternion
{
    float x, y, z, w;
};

/** Row-column 3x3 Matrix */
struct Matrix3
{
    Vector3 a, b, c;

    static inline Matrix3 identity()
    {
        Matrix3 m = {
            {1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        return m;

    }
};

/** Row-column 4x4 Matrix */
struct Matrix4
{
    Vector4 a, b, c, d;

    static inline Matrix4 identity()
    {
        Matrix4 m = {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        return m;

    };
};

/** Axis-aligned bounding box */
/* http://www.yosoygames.com.ar/wp/2013/07/good-bye-axisalignedbox-hello-aabb/ */
struct AABB
{
    Vector3 origin;
    Vector3 radius;
};

/** Oriented bounding box */
struct OBB
{
    Matrix4 transform;
    AABB aabb;
};

}; // namespace altertum
