/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#include <stdint.h>

namespace altertum {
class Random
{
    /** initialize generator with value of @a */
    Random(int32_t seed);

    /** return integer in the range [0, 32767] */
    int32_t integer();
    /** return integer in range [0, max) */
    int32_t integer( uint32_t max );
    /** return float in the range [0.0, 1.0] */
    float   real(); 

private:
    void    set_seed( uint32_t );
    uint32_t _rand();

    int32_t _seed;
}; // class Random

inline Random::Random(int32_t seed)
{
    this->set_seed(seed);
}

inline int32_t Random::integer()
{
    return _rand();
}

inline int32_t Random::integer( uint32_t max )
{
    return _rand() % max;
}

inline float Random::real()
{
    return integer() / (float)0x7fff; // preserve sign bit
}

inline void Random::set_seed( uint32_t seed )
{
    _seed = seed;
}

inline uint32_t Random::_rand()
{
    _seed = (214013 * _seed + 2531011);
    return (_seed >> 16) & 0x7FFF;
}

} // namespace altertum

