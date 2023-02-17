#ifndef __UTILS_FILE_H__
#define __UTILS_FILE_H__

#include <stdio.h>

#include "string.h"

//
//
//
typedef enum FileMode {
    FM_READ_ONLY = 0x01,
    FM_WRITE_ONLY,
    FM_READ_WRITE,
    FM_APPEND,
} FileMode;

//
//
//
struct _File {
    FILE *inner;

    FileMode mode;

    bool open_successfully;

    String filename;

    // Hold the last operation error if happens
    String error;

    // File data as cache
    String data;

    // File size
    usize size;
};

typedef struct _File *File;

//
//
//
void auto_free_file(File *ptr);

/*
 * Define smart `File` var that calls `File_free` automatically when the
 * variable is out of the scope
 *
 * ```c
 * SMART_FILE(my_profile) = Str_open("my_profile")
 * ```
 */
#define SMART_FILE(x) __attribute__((cleanup(auto_free_file))) File x

/*
 * Open a file with the given mode
 */
File File_open(const char *filename, FileMode mode);

/*
 * Load the entire file into `self->data` if the file has been opened already.
 * It returns total bytes loaded from file, otherwise, return -1 when error
 * happens.
 */
usize File_load_into_buffer(File self);

/*
 * Write the modified `self->data` back to `self->filename`
 */
void File_save(File self);

/*
 * Append to file, update the `self->data` as well
 */
void File_append(File self, char *content);

/*
 * Get back filename
 */
const char *File_get_filename(File self);

/*
 * Whether open successfully or not
 */
bool File_is_open_successfully(File self);

/*
 * Get back error
 */
const char *File_get_error(File self);

/*
 * Get back internal buffer data
 */
const char *File_get_data(File self);

/*
 * Get back file size
 */
usize File_get_size(File self);

/*
 * Print out file like `bat`
 */
void File_print_out_file_like_bat(File self);

#ifdef ENABLE_DEBUG_LOG
/*
 * Print out self for debugging purpose
 */
void File_print_debug_info(File self);
#endif

/*
 * Free
 */
void File_free(File self);

#endif
