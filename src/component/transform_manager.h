/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#include <climits>

#include "foundation/collection_types.h"
#include "foundation/memory_types.h"
#include "math/math_types.h"

#include "entity.h"
#include "entity_manager.h"

namespace altertum
{
namespace components
{
namespace transform
{

using namespace foundation;

/*
 * http://bitsquid.blogspot.com/2014/10/building-data-oriented-entity-system.html
 */

struct TransformInstance { unsigned i; };

/**
 * Transform component manager for a world
 * - Runtime can have multiple worlds
 * - Each world has its own manager
 */
class TransformManager
{
private:
    Hash<unsigned> _map;

    /** Transform data. */
    struct TransformData {
        unsigned size;                      /** Number of used entries in arrays */
        unsigned capacity;                  /** Number of allocated entries in arrays */
        void * buffer;                      /** Raw buffer for data. */

        Entity  * entity;                   /** The entity owning this instance. */
        Matrix4 * local;                    /** Local transform with respect to parent. */
        Matrix4 * world;                    /** World transform. */
        TransformInstance * parent;         /** The parent instance of this instance. */
        TransformInstance * first_child;    /** The first child of this instance. */
        TransformInstance * next_sibling;   /** The next sibling of this instance. */
        TransformInstance * prev_sibling;   /** The previous sibling of this instance. */
    };
    TransformData _data;

    inline TransformInstance make_instance(int i) const { TransformInstance inst = { i }; return inst; }

public:
    // TransformManager(Allocator * allocator) : _allocator(allocator) { }

    /** Create instance from Entity lookup */
    inline TransformInstance lookup(Entity e) const 
        { return make_instance(hash::get(_map, e.id, (unsigned)0)); }

    /** allocate a buffer large enough to hold @a sz elements */
    void allocate(Allocator &allocator, unsigned sz);
    /** run garbage collection for TransformManager */
    void gc(const EntityManager &em);

    /** create new TransformInstance */
    TransformInstance create(Allocator &allocator, Entity e);
    /** destroys a single instance @a i */
    void destroy(unsigned i);

    /** returns whether or not the instance is valid */
    inline bool is_valid(TransformInstance i) { return i.i < UINT_MAX && i.i < _data.size; }

    /** get local matrix for TransformInstance @a i */
    inline Matrix4 local(TransformInstance i) { return _data.local[i.i]; }
    /** get world matrix for TransformInstance @a i */
    inline Matrix4 world(TransformInstance i) { return _data.world[i.i]; }

    /** set matrix of instance @i from @a local */
    void set_local(TransformInstance i, Matrix4 local);
    /** regenerate @a TransformInstance's world matrix from @parent */
    void transform(const Matrix4 &parent, TransformInstance i);

}; // class TransformManager

} // namespace transform
} // namespace components
} // namespace altertum
