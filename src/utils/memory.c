#include "memory.h"

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

    DEBUG_LOG(Memory, print_memory_block, "[ %s, size: %lu ]", type_name,
              type_size);
    DEBUG_LOG(Memory, print_memory_block, "%s", hr);

    u8 memory_byte = 0x00;
    char memory_bytes[type_size * 2 + 1];
    for (usize index = 0; index < type_size; index++) {
        // 1. Convert (void *) to `(unsigned char *)`, so each `+1` means moving
        //    just 1 byte!!!
        // 2. Get back the pointer offset by `(type_name *) + index`
        // 3. Dereference that pointer offset value (in HEX format)
        memory_byte = *(((u8 *)value) + index);

        char hex_buffer[2];
        sprintf(memory_bytes + (index * 2), "%02X", memory_byte);
    }
    memory_bytes[hex_len_in_char] = '\0';
    DEBUG_LOG(Memory, print_memory_block, "%s", memory_bytes);
    DEBUG_LOG(Memory, print_memory_block, "%s\n", hr);
}
