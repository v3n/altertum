#include <cassert>

/* allows changing later without major refactor */
#define ASSERT(a) assert(a)

/* alignment macros */
#if defined(_MSC_VER)
#define __ALIGNED__(x) __declspec(align(x))
#else
#if defined(__GNUC__)
#define __ALIGNED__(x) __attribute__ ((aligned(x)))
#endif
#endif
