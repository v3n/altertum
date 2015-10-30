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
inline bool intersects(const AABB & bb1, const AABB & bb2)
{
    return(bb1.max.x > bb2.min.x &&
           bb1.min.x < bb2.max.x &&
           bb1.max.y > bb2.min.y &&
           bb1.min.y < bb2.max.y &&
           bb1.max.z > bb2.min.z &&
           bb1.min.z < bb2.max.z);
}

}; // namespace aabb
}; // namespace altertum
