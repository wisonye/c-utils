#ifndef __UTILS_SMART_PTR_H__
#define __UTILS_SMART_PTR_H__

/*
 * Simulates the `std::make_unique` in `C++`:
 *
 * Attaches the `__attribute__((cleanup(destructor)))` to the variable inside
 * the `var_define` statement. So the `destructor` will be called automatic when
 * the variable is out of scope.
 *
 * `destructor` - Destructor function that accepts a `** Type` parameter
 */
#define MAKE_UNIQUE_PTR(VAR_DEFINE, DESTRUCTOR)                                \
    __attribute__((cleanup(DESTRUCTOR))) VAR_DEFINE

#endif
