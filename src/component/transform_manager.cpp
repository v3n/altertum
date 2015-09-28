/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#include "foundation/hash.h"
#include "math/matrix4.h"

#include "transform_manager.h"

using namespace foundation;
using namespace altertum::components::transform;

/**
 * Set local matrix for TransformInstance (triggers transform)
 * @param  i     changing instance
 * @param  local new local matrix
 */
void TransformManager::set_local(TransformInstance i, Matrix4 local)
{
    _data.local[i.i] = local;

    TransformInstance parent = _data.parent[i.i];
    Matrix4 parent_tm = is_valid(parent) ? _data.world[ parent.i ] :
        Matrix4::identity();
    transform(parent_tm, i);
}

/**
 * Update matrices of TransformInstance and it's children
 * @param parent local matrix for parent instance
 * @param i      instance to update
 */
void TransformManager::transform(const Matrix4 &parent, TransformInstance i)
{
    _data.world[i.i] = _data.local[i.i] * parent;

     TransformInstance child = _data.first_child[i.i];
     while (is_valid(child)) {
        transform(_data.world[i.i], child);
        child = _data.next_sibling[child.i];
     }
}
