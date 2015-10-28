/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#include "foundation/hash.h"
#include "foundation/murmur_hash.h"
#include "math/matrix4.h"

#include "transform_manager.h"

using namespace foundation;
using namespace altertum;
using namespace altertum::components::transform;

/**
 * allocated TransformData of @a sz with @a allocator
 * @param allocator foundation allocator
 * @param sz        number of elements
 */
void TransformManager::allocate(Allocator &allocator, unsigned sz)
{
    ASSERT(sz > _data.size);

    TransformData new_buffer;

    const unsigned bytes = sz * (
        1 * sizeof(Entity) + 
        2 * sizeof(Matrix4) +
        4 * sizeof(TransformInstance)
    );
    /* Header info */
    new_buffer.buffer       = allocator.allocate(bytes);
    new_buffer.size         = _data.size;
    new_buffer.capacity     = sz;
    /* data pointers */
    new_buffer.entity       = (Entity *)(new_buffer.buffer);
    new_buffer.local        = (Matrix4 *)(new_buffer.entity + sz);
    new_buffer.world        = new_buffer.local + sz;
    /* instance relation pointers */
    new_buffer.parent       = (TransformInstance *)(new_buffer.world + sz);
    new_buffer.first_child  = new_buffer.parent + sz;
    new_buffer.next_sibling = new_buffer.first_child + sz;
    new_buffer.prev_sibling = new_buffer.next_sibling + sz;

    /* copy matrices */
    memcpy(new_buffer.entity, _data.entity, _data.size * sizeof(Entity));
    memcpy(new_buffer.local, _data.local, _data.size * sizeof(Matrix4));
    memcpy(new_buffer.world, _data.world, _data.size * sizeof(Matrix4));
    /* copy transform relations */
    memcpy(new_buffer.parent, _data.parent, _data.size * sizeof(TransformInstance));
    memcpy(new_buffer.first_child, _data.first_child, _data.size * sizeof(TransformInstance));
    memcpy(new_buffer.next_sibling, _data.next_sibling, _data.size * sizeof(TransformInstance));
    memcpy(new_buffer.prev_sibling, _data.prev_sibling, _data.size * sizeof(TransformInstance));

    allocator.deallocate(_data.buffer);
    _data = new_buffer;
}

/** run garbage collection for TransformManager */
void TransformManager::gc(const EntityManager &em)
{
    unsigned cache_misses = 0;
    while ( _data.size > 0 && cache_misses < 4 )
    {
        unsigned i = rand() % _data.size;
        if ( em.alive(_data.entity[i]) )
        {
            ++cache_misses;
            continue;
        }
        cache_misses = 0;
        destroy(i);
    }
}

/**
 * create new TransformInstance for Entity
 * @param  allocator foundation allocator if realloc is needed
 * @param  e         entity instance is being created for
 * @return           created TransformInstance
 */
TransformInstance TransformManager::create(Allocator &allocator, Entity e)
{
    if ( _data.size == _data.capacity )
    {
        allocate( allocator, _data.size * 3 / 2 );
    }

    TransformInstance instance = { _data.size++ }; 
    _data.entity[instance.i] = e;
    hash::set(_map, murmur_hash_64(&e, sizeof(Entity), 0), instance.i);

    return instance;
}

/**
 * destroy an instance, maintains packed array
 * @param i TransformInstance
 */
void TransformManager::destroy(unsigned i)
{
    unsigned last   = _data.size - 1;
    Entity e        = _data.entity[i];
    Entity last_e   = _data.entity[last];

    _data.entity[i] = _data.entity[last];
    _data.local[i]  = _data.local[last];
    _data.world[i]  = _data.world[last];

    _data.parent[i]         = _data.parent[last];
    _data.first_child[i]    = _data.first_child[last];
    _data.next_sibling[i]   = _data.next_sibling[last];
    _data.prev_sibling[i]   = _data.prev_sibling[last];

    // _map[last_e] = i;
    // _map.erase(e);

    hash::set(_map, murmur_hash_64(&last_e, sizeof(Entity), 0), i);
    hash::remove(_map, murmur_hash_64(&e, sizeof(Entity), 0));

    --_data.size;
}

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
