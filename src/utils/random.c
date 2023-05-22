#include "random.h"

#include <stdlib.h>
#include <math.h>

float get_random_float_between_0_and_1(void) {
    const u32 max_u32_value = pow(2, 32) -1;
    return (float)arc4random() / (float)max_u32_value;
}

///
///
///
float get_random_float(float max_float) {
    const u32 max_u32_value = pow(2, 32) -1;
    // u32 temp_uint = arc4random_uniform(max_uint);
    return (float)arc4random_uniform((u32)max_float);
}

///
///
///
u32 get_random_uint(u32 max_uint) {
    return arc4random_uniform(max_uint);
}
