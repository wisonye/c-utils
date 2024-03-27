#ifndef __UTILS_MEMORY_H__
#define __UTILS_MEMORY_H__

#include "data_types.h"
#include "log.h"

#ifdef ENABLE_DEBUG_LOG

    #define PRINT_MEMORY_BLOCK(TYPE_NAME, VAR_NAME)                            \
        print_memory_block((char *)#TYPE_NAME " " #VAR_NAME,                   \
                           sizeof(TYPE_NAME),                                  \
                           &VAR_NAME);

    #define PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(TYPE_NAME, VAR_NAME, TYPE_SIZE)  \
        print_memory_block((char *)#TYPE_NAME " " #VAR_NAME,                   \
                           TYPE_SIZE,                                          \
                           VAR_NAME);
#else

    /** Define as nothing when `ENABLE_DEBUG_LOG` is undefined!!! **/
    #define PRINT_MEMORY_BLOCK(TYPE_NAME, VAR_NAME)
    #define PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(TYPE_NAME, VAR_NAME, TYPE_SIZE)

#endif

/*
 * Print memory block data in HEX format
 */
void print_memory_block(char *type_name, usize type_size, void *value);

#endif
