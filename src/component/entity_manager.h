/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#include "macros.h"

#include "foundation/collection_types.h"
#include "entity.h"

namespace altertum
{

class EntityManager
{
private:
    foundation::Array<unsigned char> _generation;
    foundation::Queue<unsigned> _free_indices;

    static const unsigned MINIMUM_FREE_INDICES = 1024; 

public:
    EntityManager();
    ~EntityManager();

    Entity create();
    void destroy(Entity e);
    inline Entity make_entity(unsigned id, unsigned generation) const;

    bool alive(Entity e) const;
};

} // namespace altertum
