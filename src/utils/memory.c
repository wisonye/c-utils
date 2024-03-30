#include "memory.h"

#include <string.h>

#include "log.h"

/*
 * Print memory block data in HEX format
 */
void print_memory_block(char *type_name, usize type_size, void *value) {
    usize hex_len_in_char = type_size * 2;

    char hr[hex_len_in_char + 1];
    for (size_t i = 0; i < hex_len_in_char; i++) {
        hr[i] = '-';
    }
    hr[hex_len_in_char] = '\0';

    DEBUG_LOG(Memory,
              print_memory_block,
              "[ %s, size: %lu ]",
              type_name,
              type_size);
    DEBUG_LOG(Memory, print_memory_block, "%s", hr);

    if (value == NULL) {
        DEBUG_LOG(Memory, print_memory_block, "value is NULL", "");
        DEBUG_LOG(Memory, print_memory_block, "%s\n", hr);
    } else {
        u8 memory_byte         = 0x00;
        usize memory_bytes_len = hex_len_in_char + 1;
        char memory_bytes[memory_bytes_len];
        memset(memory_bytes, 0, memory_bytes_len);

        for (usize index = 0; index < type_size; index++) {
            // 1. Convert (void *) to `(unsigned char *)`, so each `+1` means
            //    moving just 1 byte!!!
            // 2. Get back the pointer offset by `(u8 *) + index`
            // 3. Dereference that pointer offset value (in HEX format)
            memory_byte = *(((u8 *)value) + index);

            //
            // If you run `valgrind --leak-check=full --show-reachable=yes -s
            // --track-origins=yes`, it will print out the following error on
            // the `sprintf` line:
            //
            // ==80526== Use of uninitialised value of size 8
            // ==80526==    at 0x497EE65: ??? (in /lib/libc.so.7)
            // ==80526==    by 0x498846D: vsprintf (in /lib/libc.so.7)
            // ==80526==    by 0x497BACC: sprintf (in /lib/libc.so.7)
            // ==80526==    by 0x2081A8: print_memory_block
            // (src/utils/memory.c:44)
            // ==80526==    by 0x20744F: HS_push_str (src/utils/string.c:290)
            // ==80526==    by 0x20C913: main (src/main.c:758)
            // ==80526==  Uninitialised value was created by a heap allocation
            // ==80526==    at 0x484C984: malloc (in
            // /usr/local/libexec/valgrind/vgpreload_memcheck-amd64-freebsd.so)
            // ==80526==    by 0x2073EE: HS_push_str (src/utils/string.c:278)
            // ==80526==    by 0x20C913: main (src/main.c:758)
            //
            //
            // It's a little bit confuses, as it complains about the `value`
            // is uninitialised, as that's the `self->_buffer` and it hasn't
            // been initialised after:
            //
            // `realloc(self->_buffer, new_len_with_null_terminated_char);`
            //
            // That's what it complains about, you can totally just ignore it:)
            //
            // sprintf(memory_bytes + (index * 2), "%02X", memory_byte);
            snprintf(memory_bytes + (index * 2), 3, "%02X", memory_byte);
        }
        memory_bytes[hex_len_in_char] = '\0';
        DEBUG_LOG(Memory, print_memory_block, "%s", memory_bytes);
        DEBUG_LOG(Memory, print_memory_block, "%s\n", hr);
    }
}
