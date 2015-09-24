/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */


namespace altertum
{

const unsigned ENTITY_INDEX_BITS        = 22;
const unsigned ENTITY_INDEX_MASK        = (1 << ENTITY_INDEX_BITS) - 1;

const unsigned ENTITY_GENERATION_BITS   = 8;
const unsigned ENTITY_GENERATION_MASK   = (1 << ENTITY_GENERATION_BITS) - 1; 

struct Entity
{
    /**
     * Packed data:
     *     2: Lua litedata ID
     *     @ENTITY_INDEX_BITS: entity id
     *     @ENTITY_GENERATION_BITS: instance number
     */
    unsigned id;

    inline unsigned index() const { return id & ENTITY_INDEX_MASK; }
    inline unsigned generation() const { return (id >> ENTITY_INDEX_BITS) & ENTITY_GENERATION_MASK; }
};

} // namespace altertum
