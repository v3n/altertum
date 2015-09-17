/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#include "macros.h"

#ifdef __WITH_SSE
#include "emmintrin.h"
#endif

/* sse implementation courtesy Intel: 
https://software.intel.com/en-us/articles/fast-random-number-generator-on-the-intel-pentiumr-4-processor/
 */

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

#   ifdef __WITH_SSE
    __m128i cur_seed __ALIGNED__(16);
#   else
    unsigned int _seed;
#   endif
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

/**
 * SSE implementation specific 
 */

#ifdef __WITH_SSE

inline void Random::set_seed( uint32_t seed )
{
    cur_seed = _mm_set_epi32( seed, seed+1, seed, seed+1 );
}

inline uint32_t Random::_rand()
{
    __m128i cur_seed_split __ALIGNED__(16);
    __m128i multiplier __ALIGNED__(16);
    __m128i adder __ALIGNED__(16);
    __m128i mod_mask __ALIGNED__(16);
    __m128i sra_mask __ALIGNED__(16);
    __m128i sseresult __ALIGNED__(16);
    static const unsigned int mult[4] __ALIGNED__(16) =
        { 214013, 17405, 214013, 69069 };
    static const unsigned int gadd[4] __ALIGNED__(16) =
        { 2531011, 10395331, 13737667, 1 };
    static const unsigned int mask[4] __ALIGNED__(16) =
        { 0xFFFFFFFF, 0, 0xFFFFFFFF, 0 };
    static const unsigned int masklo[4] __ALIGNED__(16) =
        { 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF };

    adder = _mm_load_si128( (__m128i*) gadd);
    multiplier = _mm_load_si128( (__m128i*) mult);
    mod_mask = _mm_load_si128( (__m128i*) mask);
    sra_mask = _mm_load_si128( (__m128i*) masklo);
    cur_seed_split = _mm_shuffle_epi32( cur_seed, _MM_SHUFFLE( 2, 3, 0, 1 ) );

    cur_seed = _mm_mul_epu32( cur_seed, multiplier );
    multiplier = _mm_shuffle_epi32( multiplier, _MM_SHUFFLE( 2, 3, 0, 1 ) );
    cur_seed_split = _mm_mul_epu32( cur_seed_split, multiplier );

    cur_seed = _mm_and_si128( cur_seed, mod_mask);
    cur_seed_split = _mm_and_si128( cur_seed_split, mod_mask );
    cur_seed_split = _mm_shuffle_epi32( cur_seed_split, _MM_SHUFFLE( 2, 3, 0, 1 ) );
    cur_seed = _mm_or_si128( cur_seed, cur_seed_split );
    cur_seed = _mm_add_epi32( cur_seed, adder);

    /* reduce to RAND_MAX */
    sseresult = _mm_srai_epi32( cur_seed, 16);
    sseresult = _mm_and_si128( sseresult, sra_mask );

    return *(uint32_t *)&cur_seed;
}

#else // !__WITH_SSE

/**
 * non-SSE implementation specific 
 */
inline void Random::set_seed( uint32_t seed )
{
    _seed = seed;
}

inline uint32_t Random::_rand()
{
    _seed = (214013 * _seed + 2531011);
    return (_seed >> 16) & 0x7FFF;
}

#endif // __WITH_SSE

} // namespace altertum
