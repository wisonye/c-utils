#include "timer.h"

#include <stdint.h>
#include <stdio.h>

//
// Linux
//
#if defined(__linux)
#define HAVE_POSIX_TIMER
#include <time.h>

#ifdef CLOCK_MONOTONIC
#define CLOCKID CLOCK_MONOTONIC
#else
#define CLOCKID CLOCK_REALTIME
#endif

//
// Apple/Darwin
//
#elif defined(__APPLE__)

#define HAVE_MACH_TIMER
#include <mach/mach_time.h>

//
// FreeBSD
//
#elif defined(__FreeBSD__)
#include <sys/_timespec.h>
#include <time.h>

#ifdef CLOCK_MONOTONIC
#define CLOCKID CLOCK_MONOTONIC
#else
#define CLOCKID CLOCK_REALTIME
#endif

#endif

//
// Include logger for debugging purpose
//
#ifdef ENABLE_DEBUG_LOG

#include "log.h"

#endif

//
// Global staic init flag
//
static uint64_t is_init = 0;

/*
 * Get back current time in the given time unit
 */
// uint64_t Timer_get_current_time(TimeUnit time_unit) {
long double Timer_get_current_time(TimeUnit time_unit) {
    uint64_t now = 0;

#if defined(__APPLE__)
    static mach_timebase_info_data_t info;
    if (0 == is_init) {
#ifdef ENABLE_DEBUG_LOG
        DEBUG_LOG(Timer, Timer_get_current_time, "Apple/Darwin Initialization",
                  "");
#endif
        mach_timebase_info(&info);
        is_init = 1;
    }
    now = mach_absolute_time();
    now *= info.numer;
    now /= info.denom;

#elif defined(__linux)
    static struct timespec linux_rate;
    if (0 == is_init) {
#ifdef ENABLE_DEBUG_LOG
        DEBUG_LOG(Timer, Timer_get_current_time, "Linux Initialization", "");
#endif
        clock_getres(CLOCKID, &linux_rate);
        is_init = 1;
    }

    struct timespec spec;
    clock_gettime(CLOCKID, &spec);
    now = spec.tv_sec * 1.0e9 + spec.tv_nsec;

#elif defined(__FreeBSD__)
    static struct timespec bsd_rate;
    if (0 == is_init) {
#ifdef ENABLE_DEBUG_LOG
        DEBUG_LOG(Timer, Timer_get_current_time, "FreeBSD Initialization", "");
#endif
        clock_getres(CLOCKID, &bsd_rate);
        is_init = 1;
    }

    struct timespec spec;
    clock_gettime(CLOCKID, &spec);
    now = spec.tv_sec * 1.0e9 + spec.tv_nsec;
#endif

    /* // */
    /* // TIME     	    IN NANOSECONDS */
    /* // 1 second     	1.000.000.000 ns */
    /* // 1 milli second	1.000.000 ns */
    /* // 1 micro second	1.000 ns */
    /* // */
    long double result = now;

    if (time_unit == TU_MICROSECONDS) {
        result = result / 1000.f;
    } else if (time_unit == TU_MILLISECONDS) {
        result = result / 1000000.f;
    } else if (time_unit == TU_SECONDS) {
        result = result / 1000000000.f;
    }

    return result;
    // return now;
}
