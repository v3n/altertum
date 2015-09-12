# Contributing

## Coding Conventions

### C++

- Soft tabs, four spaces.
- Braces on next line 
- Spaces inside parenthesis
```
if ( true )
{
    ...
}
```
- Spaces in between pointer declarations `int * foo`
- No space in address and derefencing operators `*foo` or `&foo`
- Use `#pragma once` instead of C-style include guards
- Class, struct, and namespace block ends should be commented such as:
```
namespace engine
{
...
} // namespace engine
```
- Exceptions are [forbidden](http://www.lighterra.com/papers/exceptionsharmful/), use assert() instead.

### Lua
