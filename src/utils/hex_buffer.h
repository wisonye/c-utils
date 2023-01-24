#ifndef __UTILS_HEX_BUFFER_H__
#define __UTILS_HEX_BUFFER_H__

#include "data_types.h"

//
//
//
typedef struct {
    usize _len;

    //
    // `Flexible Array Member(FAM)` is a feature introduced in `C99` standard
    // of the C programming language. The `FAM` has the following feature and
    // limitation:
    //
    // - Declare with out dimension size
    // - Must be the last member of the struct
    //
    u8 _buffer[];
} HexBuffer;

/*
 * Create `HexBuffer` from the given `char *`
 *
 * Return `NULL` if:
 *
 * - `hex_str` is NULL or empty string
 * - `hex_str` has an odd length
 */
HexBuffer *Hex_from_string(const char *hex_str);

/*
 * Return the hex buffer length
 */
usize Hex_length(HexBuffer *self);

/*
 * Return `out_buffer` size (same with strlen()) if `HexBuffer` is an valid
 * `HexBuffer`.
 *
 * Return 0 when something wrong
 * Return -1 when `out_buffer_size` is not big enough to hold the hex string.
 */
int Hex_to_string(const HexBuffer *self, char *out_buffer,
                  usize out_buffer_size);

/*
 * Free
 */
void Hex_free(HexBuffer *self);

#endif
