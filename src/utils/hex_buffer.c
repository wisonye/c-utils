#include "hex_buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_types.h"

#ifdef ENABLE_DEBUG_LOG
#include "log.h"
#endif

/*
unsigned char unsigned_char_v = 0x0A;
unsigned short unsigned_short_v = 0x0123;


// `04` means left-padding `0` until output len is 4
// Output: >>> unsigned_short_v: 0x0123
printf("\n>>> unsigned_short_v: 0x%04X", unsigned_short_v);
*/

/*
 * Create `HexBuffer` from the given `char *`
 *
 * Return `NULL` if:
 *
 * - `hex_str` is NULL or empty string
 * - `hex_str` has an odd length
 */
HexBuffer *Hex_from_string(const char *hex_str) {
    if (hex_str == NULL) return NULL;

    usize hex_str_len = strlen(hex_str);
    if (hex_str_len <= 0 || hex_str_len % 2 != 0) return NULL;

    //
    // `_buffer` is a fixed array and it's the last member in the struct, so
    // `malloc` supports allocated the continuous memory block to container the
    // enitre `HexBuffer` and that fixed array space.
    //
    usize buffer_size = sizeof(char) * hex_str_len / 2;
    HexBuffer *buffer = malloc(sizeof(HexBuffer) + buffer_size);
    buffer->_len = buffer_size;

    char *copy_str = (char *)hex_str;
    for (usize index = 0; index < buffer_size; index++) {
        char temp_hex_str[3] = {0};
        strncpy(temp_hex_str, copy_str, 2);

#ifdef ENABLE_DEBUG_LOG
        DEBUG_LOG(HexBuffer, Hex_from_string, "temp_hex_str: %s, strlen: %lu",
                  temp_hex_str, strlen(temp_hex_str));
#endif

        buffer->_buffer[index] = (u8)strtol(temp_hex_str, NULL, 16);

#ifdef ENABLE_DEBUG_LOG
        DEBUG_LOG(HexBuffer, Hex_from_string, "buffer->_buffer[%u]: %02X",
                  index, buffer->_buffer[index]);
#endif

        copy_str += 2;
    }

    return buffer;
}

/*
 * Return the hex buffer length
 */
usize Hex_length(HexBuffer *self) {
    if (self == NULL || self->_len < 0) return 0;

    return self->_len;
}

/*
 * Return `out20j_buffer` size (same with strlen()) if `HexBuffer` is an valid
 * `HexBuffer`.
 *
 * Return 0 when something wrong
 * Return -1 when `out_buffer_size` is not big enough to hold the hex string.
 */
int Hex_to_string(const HexBuffer *self, char *out_buffer,
                  usize out_buffer_size) {
    if (self == NULL || self->_len <= 0) return 0;

    usize copied_buffer_size = self->_len * 2;

    if (copied_buffer_size > out_buffer_size) return -1;

#ifdef ENABLE_DEBUG_LOG
    DEBUG_LOG(HexBuffer, Hex_to_string,
              "self->_len: %lu, copied_buffer_size: %lu, self->_buffer: 0x",
              self->_len, copied_buffer_size);

    for (usize index = 0; index < self->_len; index++) {
        printf("%02X", self->_buffer[index]);
        // printf("%u", self->_buffer[index]);
    }
#endif

    char *copy_ptr = out_buffer;
    for (usize index = 0; index < self->_len; index++) {
        char hex_value[3] = {0};

        // `02` means left-padding `0` until output len is 2
        usize copied_size =
            snprintf(hex_value, 3, "%02X", self->_buffer[index]);

#ifdef ENABLE_DEBUG_LOG
        DEBUG_LOG(HexBuffer, Hex_to_string, "copied_size: %lu, hex_value: %s",
                  copied_size, hex_value);
#endif
        memcpy(copy_ptr, hex_value, 2);
        copy_ptr += 2;
    }
    out_buffer[copied_buffer_size] = '\0';

    return self->_len * 2;
}

/*
 * Free
 */
void Hex_free(HexBuffer *self) {
    if (self != NULL) {
        free(self);
    }
}
