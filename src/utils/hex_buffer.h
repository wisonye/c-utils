#ifndef __UTILS_HEX_BUFFER_H__
#define __UTILS_HEX_BUFFER_H__

#include "data_types.h"

/*
 * Opaque pointer to `struct _HexBuffer`
 */
typedef struct _HexBuffer *HexBuffer;

/*
 * Create `HexBuffer` from the given `char *`. Only accept `0~9` `a~f` `A~F`
 * characters, all another characters will be ignored.
 *
 * Return `NULL` if:
 *
 * - `hex_str` is NULL or empty string
 * - `hex_str` (after ignored all invalid characters) has an odd length
 */
HexBuffer Hex_from_string(const char *hex_str);

/*
 * Return the hex buffer length
 */
usize Hex_length(HexBuffer self);

/*
 * Return `out_buffer` size (same with strlen()) if `HexBuffer` is an valid
 * `HexBuffer`.
 *
 * Return 0 when something wrong
 * Return -1 when `out_buffer_size` is not big enough to hold the hex string.
 */
int Hex_to_string(const HexBuffer self, char *out_buffer,
                  usize out_buffer_size);

/*
 * Free
 */
void Hex_free(HexBuffer self);

#endif
