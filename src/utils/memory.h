#ifndef __UTILS_MEMORY_H__
#define __UTILS_MEMORY_H__

#include "data_types.h"
#include "log.h"

#define PRINT_MEMORY_BLOCK(TYPE_NAME, VAR_NAME)                             \
    print_memory_block((char *)#TYPE_NAME " " #VAR_NAME, sizeof(TYPE_NAME), \
                       &VAR_NAME);

/*
 * Print memory block data in HEX format
 */
void print_memory_block(char *type_name, usize type_size, void *value);

#endif
