#include "log.h"

#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>

//
// Print integer
//
void print_u8(char *v_name, u8 v) { printf("\n>>> %s: %" PRIu8, v_name, v); }

void print_u16(char *v_name, u16 v) { printf("\n>>> %s: %" PRIu16, v_name, v); }

void print_u32(char *v_name, u32 v) { printf("\n>>> %s: %" PRIu32, v_name, v); }

void print_u64(char *v_name, u64 v) { printf("\n>>> %s: %" PRIu64, v_name, v); }

void print_usize(char *v_name, usize v) {
#if __APPLE__
    printf("\n>>> %s: %lu", v_name, v);
#elif __FreeBSD__
    printf("\n>>> %s: %" PRIu64, v_name, v);
#else
    printf("\n>>> %s: %" PRIu64, v_name, v);
#endif
}

void print_i8(char *v_name, i8 v) { printf("\n>>> %s: %" PRIi8, v_name, v); }

void print_i16(char *v_name, i16 v) { printf("\n>>> %s: %" PRIi16, v_name, v); }

void print_i32(char *v_name, i32 v) { printf("\n>>> %s: %" PRIi32, v_name, v); }

void print_i64(char *v_name, i64 v) { printf("\n>>> %s: %" PRIi64, v_name, v); }

void print_int(char *v_name, i32 v) { printf("\n>>> %s: %" PRIi32, v_name, v); }

void print_long(char *v_name, long v) {
#if __APPLE__
    printf("\n>>> %s: %li", v_name, v);
#elif __FreeBSD__
    printf("\n>>> %s: %" PRIi64, v_name, v);
#else
    printf("\n>>> %s: %" PRIi64, v_name, v);
#endif
}

void print_char(char *v_name, char v) { printf("\n>>> %s: %c", v_name, v); }

void print_bool(char *v_name, bool v) {
    printf("\n>>> %s: %s", v_name, (v == true) ? "true" : "false");
}

void print_float(char *v_name, float v) { printf("\n>>> %s: %f", v_name, v); }

// void print_double(char *v_name, double v) { printf("\n>>> %s: %f", v_name,
// v); }
void print_long_double(char *v_name, long double v) {
    printf("\n>>> %s: %Lf", v_name, v);
}

void print_string(char *v_name, char *v) { printf("\n>>> %s: %s", v_name, v); }

void print_const_string(char *v_name, const char *v) {
    printf("\n>>> %s: %s", v_name, v);
}

//
// Print pointer
//
void print_void_ptr(char *v_name, void *v) {
    printf("\n>>> %s (ptr): 0x%" PRIXPTR, v_name, (uintptr_t)v);
}

void print_bool_ptr(char *v_name, bool *v) {
    printf("\n>>> %s (ptr): 0x%" PRIXPTR ", value: %s", v_name, (uintptr_t)v,
           (*v == true) ? "true" : "false");
}

void print_u8_ptr(char *v_name, u8 *v) {
    printf("\n>>> %s (ptr): 0x%" PRIXPTR ", value: %" PRIu8, v_name,
           (uintptr_t)v, *v);
}

void print_u16_ptr(char *v_name, u16 *v) {
    printf("\n>>> %s (ptr): 0x%" PRIXPTR ", value: %" PRIu16, v_name,
           (uintptr_t)v, *v);
}

void print_u32_ptr(char *v_name, u32 *v) {
    printf("\n>>> %s (ptr): 0x%" PRIXPTR ", value: %" PRIu32, v_name,
           (uintptr_t)v, *v);
}

void print_usize_ptr(char *v_name, usize *v) {
#if __APPLE__
    printf("\n>>> %s (ptr): 0x%" PRIXPTR ", value: %" PRIuPTR, v_name,
           (uintptr_t)v, *v);
#elif __FreeBSD__
    printf("\n>>> %s (ptr): 0x%" PRIXPTR ", value: %" PRIu64, v_name,
           (uintptr_t)v, *v);
#else
    printf("\n>>> %s (ptr): 0x%" PRIXPTR ", value: %" PRIu64, v_name,
           (uintptr_t)v, *v);
#endif
}

void print_u64_ptr(char *v_name, u64 *v) {
    printf("\n>>> %s (ptr): 0x%" PRIXPTR ", value: %" PRIu64, v_name,
           (uintptr_t)v, *v);
}

void print_i8_ptr(char *v_name, i8 *v) {
    printf("\n>>> %s (ptr): 0x%" PRIXPTR ", value: %" PRIi8, v_name,
           (uintptr_t)v, *v);
}

void print_i16_ptr(char *v_name, i16 *v) {
    printf("\n>>> %s (ptr): 0x%" PRIXPTR ", value: %" PRIi16, v_name,
           (uintptr_t)v, *v);
}

void print_i32_ptr(char *v_name, i32 *v) {
    printf("\n>>> %s (ptr): 0x%" PRIXPTR ", value: %" PRIi32, v_name,
           (uintptr_t)v, *v);
}

void print_i64_ptr(char *v_name, i64 *v) {
    printf("\n>>> %s (ptr): 0x%" PRIXPTR ", value: %" PRIi64, v_name,
           (uintptr_t)v, *v);
}

void print_float_ptr(char *v_name, float *v) {
    printf("\n>>> %s (ptr): 0x%" PRIXPTR ", value: %f", v_name, (uintptr_t)v,
           *v);
}

void print_double_ptr(char *v_name, double *v) {
    printf("\n>>> %s (ptr): 0x%" PRIXPTR ", value: %f", v_name, (uintptr_t)v,
           *v);
}

void print_long_double_ptr(char *v_name, long double *v) {
    printf("\n>>> %s (ptr): 0x%" PRIXPTR ", value: %Lf", v_name, (uintptr_t)v,
           *v);
}

/**
 * Log
 */
void __log__(LogLevel log_level, const char *module_name,
             const char *function_name, const char *format_str, ...) {
    char *log_level_str = NULL;
    switch (log_level) {
        case LL_DEBUG:
            log_level_str = "(D)";
            break;
        case LL_INFO:
            log_level_str = "(I)";
            break;
        case LL_WARN:
            log_level_str = "(W)";
            break;
        case LL_ERROR:
            log_level_str = "(E)";
            break;
        default:
            log_level_str = "(I)";
    }

    char buffer[LOG_BUFFER_SIZE] = {0};
    va_list args;
    va_start(args, format_str);
    vsnprintf(buffer, LOG_BUFFER_SIZE, format_str, args);
    va_end(args);
    printf("\n%s [ %s ] > %s - %s", log_level_str, module_name, function_name,
           buffer);
}
