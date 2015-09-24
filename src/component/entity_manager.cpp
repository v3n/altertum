/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#include "entity_manager.h"

#include "foundation/array.h"
#include "foundation/queue.h"

namespace altertum
{

using namespace foundation;

Entity EntityManager::create()
{
    unsigned idx;
    if ( queue::size(_free_indices) > MINIMUM_FREE_INDICES ) 
    {
        idx = _free_indices[0];
        queue::pop_front(_free_indices);
    } 
    else
    {
        array::push_back(_generation, (unsigned char)0);
        idx = array::size(_generation) - 1;
        ASSERT(idx < (1 << ENTITY_INDEX_BITS));
    }
    return make_entity(idx, _generation[idx]);
}

void EntityManager::destroy(Entity e)
{
    const unsigned idx = e.index();
    ++_generation[idx];
    queue::push_back(_free_indices, idx);
}

inline Entity EntityManager::make_entity(unsigned id, unsigned generation) const
{
    Entity e = { ((id << ENTITY_INDEX_BITS) & ENTITY_INDEX_MASK) | (generation & ENTITY_GENERATION_MASK) };
    return e;
}

bool EntityManager::alive(Entity e) const
{
    return _generation[e.index()] == e.generation();
}

} // namespace altertum
