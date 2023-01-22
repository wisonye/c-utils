#include "log.h"

#include <inttypes.h>

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

void print_void_ptr(char *v_name, void *v) {
    printf("\n>>> %s (ptr): %p", v_name, v);
}

void print_bool_ptr(char *v_name, bool *v) {
    printf("\n>>> %s (ptr): %p, value: %s", v_name, v,
           (*v == true) ? "true" : "false");
}

void print_u8_ptr(char *v_name, u8 *v) {
    printf("\n>>> %s (ptr): %p, value: %" PRIu8, v_name, v, *v);
}

void print_u16_ptr(char *v_name, u16 *v) {
    printf("\n>>> %s (ptr): %p, value: %" PRIu16, v_name, v, *v);
}

void print_u32_ptr(char *v_name, u32 *v) {
    printf("\n>>> %s (ptr): %p, value: %" PRIu32, v_name, v, *v);
}

void print_usize_ptr(char *v_name, usize *v) {
#if __APPLE__
    printf("\n>>> %s (ptr): %p, value: %" PRIuPTR, v_name, v, *v);
#elif __FreeBSD__
    printf("\n>>> %s (ptr): %p, value: %" PRIu64, v_name, v, *v);
#else
    printf("\n>>> %s (ptr): %p, value: %" PRIu64, v_name, v, *v);
#endif
}

void print_u64_ptr(char *v_name, u64 *v) {
    printf("\n>>> %s (ptr): %p, value: %" PRIu64, v_name, v, *v);
}

void print_i8_ptr(char *v_name, i8 *v) {
    printf("\n>>> %s (ptr): %p, value: %" PRIi8, v_name, v, *v);
}

void print_i16_ptr(char *v_name, i16 *v) {
    printf("\n>>> %s (ptr): %p, value: %" PRIi16, v_name, v, *v);
}

void print_i32_ptr(char *v_name, i32 *v) {
    printf("\n>>> %s (ptr): %p, value: %" PRIi32, v_name, v, *v);
}

void print_i64_ptr(char *v_name, i64 *v) {
    printf("\n>>> %s (ptr): %p, value: %" PRIi64, v_name, v, *v);
}

void print_float_ptr(char *v_name, float *v) {
    printf("\n>>> %s (ptr): %p, value: %f", v_name, v, *v);
}

void print_double_ptr(char *v_name, double *v) {
    printf("\n>>> %s (ptr): %p, value: %f", v_name, v, *v);
}

void print_long_double_ptr(char *v_name, long double *v) {
    printf("\n>>> %s (ptr): %p, value: %Lf", v_name, v, *v);
}
