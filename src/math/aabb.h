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

 /** Initializes an AABB type with a minimum and maximum point.*/
	AABB AABBinit(const Vector3 & min, const Vector3 & max);

	/** Initializes an AABB type from another AABB.*/
	AABB AABBinit(const AABB & box);

	/** Returns the center point of a given box.*/
	Vector3 GetCenter(const AABB & box);

	/** Returns the size of the X value of a given box.*/
	inline float GetXSize(const AABB & box);

	/** Returns the size of the Y value of a given box.*/
	inline float GetYSize(const AABB & box);

	/** Returns the size of the Z value of a given box.*/
	inline float GetZSize(const AABB & box);

	/** Returns the volume of a given box.*/
	inline float GetVolume(const AABB & box);

	/** returns true if the 2 boxes intersect, false otherwise*/
	bool Intersect(const AABB & box1, const AABB & box2);

	/** Returns true if a point is contained within a box*/
	bool ContainsPoint(const AABB & box, const Vector3 & point);

/** returns true if the 2 boxes intersect, false otherwise*/
inline bool Intersect(const AABB & bb1, const AABB & bb2)
{
    return(bb1.max.x > bb2.min.x &&
           bb1.min.x < bb2.max.x &&
           bb1.max.y > bb2.min.y &&
           bb1.min.y < bb2.max.y &&
           bb1.max.z > bb2.min.z &&
           bb1.min.z < bb2.max.z);
}
AABB AABBinit(const Vector3 & min, const Vector3 & max)
{
	AABB box = AABB(min, max);
	return box;
}
AABB AABBinit(const AABB & box)
{
	AABB newBox = AABB(box.min, box.max);
	return newBox;
}
Vector3 GetCenter(const AABB & box)
{
	Vector3 centerPoint;
	centerPoint.x = (box.max.x + box.min.x) / 2.0f;
	centerPoint.y = (box.max.y + box.min.y) / 2.0f;
	centerPoint.z = (box.max.z + box.min.z) / 2.0f;
	return centerPoint;
}
float GetXSize(const AABB & box)
{
	return (box.max.x - box.min.x);
}
float GetYSize(const AABB & box)
{
	return (box.max.y - box.min.y);
}
float GetZSize(const AABB & box)
{
	return (box.max.z - box.min.z);
}
float GetVolume(const AABB & box)
{
	return (GetXSize(box) * GetYSize(box) * GetZSize(box));
}
bool ContainsPoint(const AABB & box, const Vector3 & point)
{
	return ((point.x <= box.max.x) && (point.x >= box.min.x)
		&& (point.y <= box.max.y) && (point.y >= box.min.y)
		&& (point.z <= box.max.z) && (point.z >= box.min.z));
}
}; // namespace aabb
}; // namespace altertum
