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
#define make_unique_ptr(var_define, destructor) \
    __attribute__((cleanup(destructor))) var_define

#endif
