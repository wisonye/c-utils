#include "hex_buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_types.h"

#ifdef ENABLE_DEBUG_LOG
#include "log.h"
#endif

/*
 * Create `HexBuffer` from the given `char *`. Only accept `0~9` `a~f` `A~F`
 * characters, all another characters will be ignored.
 *
 * Return `NULL` if:
 *
 * - `hex_str` is NULL or empty string
 * - `hex_str` (after ignored all invalid characters) has an odd length
 */
HexBuffer *Hex_from_string(const char *hex_str) {
    if (hex_str == NULL) return NULL;

    usize hex_str_len = strlen(hex_str);
    //
    // Remove all non `0~9` `a~z` `A~Z` characters
    //
    char valid_hex_str[hex_str_len + 1];
    usize valid_str_index = 0;
    for (usize t = 0; t < hex_str_len; t++) {
        char temp_char = hex_str[t];

        if ((temp_char >= 48 && temp_char <= 57) ||
            (temp_char >= 65 && temp_char <= 70) ||
            (temp_char >= 97 && temp_char <= 102)) {
            valid_hex_str[valid_str_index] = temp_char;
            valid_str_index++;
        }
    }
    valid_hex_str[valid_str_index] = '\0';

    usize valid_hex_str_len = strlen(valid_hex_str);
#ifdef ENABLE_DEBUG_LOG
    DEBUG_LOG(HexBuffer, Hex_from_string, "valid_hex_str len: %lu, value: %s",
              valid_hex_str_len, valid_hex_str);
#endif

    if (valid_hex_str_len <= 0 || valid_hex_str_len % 2 != 0) {
#ifdef ENABLE_DEBUG_LOG
        DEBUG_LOG(HexBuffer, Hex_from_string,
                  "valid_hex_str length <= 0 or is odd length, return NULL.",
                  valid_hex_str_len, valid_hex_str);
#endif
        return NULL;
    }

    //
    // `_buffer` is a fixed array and it's the last member in the struct, so
    // `malloc` supports allocated the continuous memory block to container the
    // enitre `HexBuffer` and that fixed array space.
    //
    usize buffer_size = sizeof(char) * valid_hex_str_len / 2;
    HexBuffer *buffer = malloc(sizeof(HexBuffer) + buffer_size);
    buffer->_len = buffer_size;

    char *copy_str = (char *)valid_hex_str;
    for (usize index = 0; index < buffer_size; index++) {
        char temp_hex_str[3] = {0};
        strncpy(temp_hex_str, copy_str, 2);

#ifdef ENABLE_DEBUG_LOG
        DEBUG_LOG(HexBuffer, Hex_from_string, "temp_hex_str: %s, strlen: %lu",
                  temp_hex_str, strlen(temp_hex_str));
#endif

        // `strtol` converts the 16 base ASCII to long
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
