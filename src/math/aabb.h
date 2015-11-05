/* 
 * Copyright (c) 2015 Jonathan Howard, Nathanael Thompson
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#include "math_types.h"

namespace altertum
{
namespace aabb
{

/**
 * @file aabb.h
 * Extended implementation of AABB API
 * @note Does not use C++ constructors to maintain aggregate struct status
 */

/** returns true if the 2 boxes intersect, false otherwise*/
inline bool intersect(const AABB & bb1, const AABB & bb2)
{
    return(bb1.max.x > bb2.min.x &&
           bb1.min.x < bb2.max.x &&
           bb1.max.y > bb2.min.y &&
           bb1.min.y < bb2.max.y &&
           bb1.max.z > bb2.min.z &&
           bb1.min.z < bb2.max.z);
}

/** Initializes an AABB type with a minimum and maximum point.*/
AABB aabb(const Vector3 & min, const Vector3 & max)
{
	AABB box;
	box.min = min;
	box.max = max;
	return box;
}

/** Initializes an AABB type from another AABB.*/
AABB aabb(const AABB & box)
{
	AABB newBox;
	newBox.min = box.min;
	newBox.max = box.max;
	return newBox;
}

/** Returns the center point of a given box.*/
Vector3 center(const AABB & box)
{
	Vector3 centerPoint;
	centerPoint.x = (box.max.x + box.min.x) / 2.0f;
	centerPoint.y = (box.max.y + box.min.y) / 2.0f;
	centerPoint.z = (box.max.z + box.min.z) / 2.0f;
	return centerPoint;
}

/** Returns the size of the X value of a given box.*/
float xsize(const AABB & box)
{
	return (box.max.x - box.min.x);
}

/** Returns the size of the Y value of a given box.*/
float ysize(const AABB & box)
{
	return (box.max.y - box.min.y);
}

/** Returns the size of the Z value of a given box.*/
float zsize(const AABB & box)
{
	return (box.max.z - box.min.z);
}

/** Returns the volume of a given box.*/
float volume(const AABB & box)
{
	return (xsize(box) * xsize(box) * zsize(box));
}

/** Returns true if a point is contained within a box*/
bool contains(const AABB & box, const Vector3 & point)
{
	return ((point.x <= box.max.x) && (point.x >= box.min.x)
		&& (point.y <= box.max.y) && (point.y >= box.min.y)
		&& (point.z <= box.max.z) && (point.z >= box.min.z));
}
}; // namespace aabb
}; // namespace altertum