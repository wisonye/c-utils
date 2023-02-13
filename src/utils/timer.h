#ifndef __UTILS_TIMER__
#define __UTILS_TIMER__

#include <stdint.h>

/*
 * Time unit
 */
typedef enum TimeUnit {
    TU_NANOSECONDS = 0x01,
    TU_MICROSECONDS = 0x02,
    TU_MILLISECONDS = 0x03,
    TU_SECONDS = 0x04,
} TimeUnit;

/*
 * Get back current time in the given time unit
 */
// uint64_t Timer_get_current_time(TimeUnit time_unit);
long double Timer_get_current_time(TimeUnit time_unit);

#endif
#include <stdint.h>
