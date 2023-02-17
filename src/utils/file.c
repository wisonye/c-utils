#include "file.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string.h"

#ifdef ENABLE_DEBUG_LOG
#include "log.h"
#endif

/*
 *
 */
void file_mode_to_string(FileMode *mode, char *out) {
    if (*mode == FM_READ_ONLY) {
        out[0] = 'r';
        out[1] = '\0';
    } else if (*mode == FM_WRITE_ONLY) {
        out[0] = 'w';
        out[1] = '\0';
    } else if (*mode == FM_APPEND) {
        out[0] = 'a';
        out[1] = '\0';
    } else if (*mode == FM_READ_WRITE) {
        out[0] = 'r';
        out[1] = 'w';
        out[2] = '\0';
    } else {
        out[0] = 'r';
        out[1] = '\0';
    }
}

/*
 * Open a file with the given mode
 */
File File_open(const char *filename, FileMode mode) {
    File open_file = malloc(sizeof(struct _File));
    *open_file = (struct _File){
        .inner = NULL,
        .mode = mode,
        .error = NULL,
        .filename = Str_from_str(filename),
        .data = NULL,
        .open_successfully = false,
    };

    char temp_mode[3] = {0};
    file_mode_to_string(&mode, temp_mode);

#ifdef ENABLE_DEBUG_LOG
    DEBUG_LOG(File, open, "self ptr: %p, filename: %s, open mode: %s",
              open_file, filename, temp_mode);
#endif

    FILE *file_handle = fopen(filename, temp_mode);
    if (file_handle == NULL) {
        // char error_buffer[100] = {0};
        // strerror_r(errno, error_buffer, sizeof(error_buffer));
        // open_file->error = Str_from_str(error_buffer);
        open_file->error = Str_from_str(strerror(errno));

#ifdef ENABLE_DEBUG_LOG
        DEBUG_LOG(File, open, "Open file failed - '%s': %s", filename,
                  Str_as_str(open_file->error));
#endif

    } else {
        open_file->inner = file_handle;
        open_file->open_successfully = true;
    }

    return open_file;
}

/*
 * Load the entire file into `self->data` if the file has been opened already.
 * It returns total bytes loaded from file, otherwise, return -1 when error
 * happens.
 */
usize File_load_into_buffer(File self) {
    if (self == NULL || !self->open_successfully || self->inner == NULL)
        return -1;

    //
    // Get the file size and rewind back to the beginning postion
    //
    fseek(self->inner, 0L, SEEK_END);
    usize file_size = ftell(self->inner);
    rewind(self->inner);

#ifdef ENABLE_DEBUG_LOG
    DEBUG_LOG(File, load_into_buffer, "file_size: %lu", file_size);
#endif

    //
    // Free the orignal `self->data` if exists
    //
    if (self->data != NULL) {
#ifdef ENABLE_DEBUG_LOG
        DEBUG_LOG(File, load_into_buffer,
                  "free original self->data, len: %lu, value: %s",
                  Str_length(self->data), Str_as_str(self->data));
#endif
        Str_free(self->data);
        self->data = NULL;
    }

    //
    // Create `struct Str *` buffer with enough capacity to hold the entire
    // file content
    //
    usize file_str_size = file_size + 1;
    struct Str *str_buffer = malloc(sizeof(struct Str));
    Str_init_with_capacity(str_buffer, file_str_size);
    memset(str_buffer->_buffer, 0, file_str_size);

    //
    // Here, we write to `str_buffer->_buffer` in an unusual way for performance
    // purpose, that's why we need to set the correct `str_buffer->_len` value
    // manually!!!
    //
    // `read_bytes` means the number of object has been read which should
    // be `1`!!!
    //
    usize read_bytes = fread(str_buffer->_buffer, file_size, 1, self->inner);
    str_buffer->_buffer[file_size] = '\0';
    str_buffer->_len = file_size;

    //
    // Move `str_buffer` into `self->data`
    //
    self->data = Str_move_from(str_buffer);

#ifdef ENABLE_DEBUG_LOG
    DEBUG_LOG(File, load_into_buffer,
              "after read from file, self->data, len: %lu, value: %s",
              Str_length(self->data), Str_as_str(self->data));
#endif

    //
    // Free the `str_buffer`
    //
    Str_free(str_buffer);

    // `number of object has been read` * object size
    return read_bytes * file_size;
}

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
const char *File_get_filename(File self) {
    return (self != NULL && self->filename != NULL) ? Str_as_str(self->filename)
                                                    : NULL;
}

/*
 * Whether open successfully or not
 */
bool File_is_open_successfully(File self) {
    return (self != NULL) ? self->open_successfully : false;
}

/*
 * Get back error
 */
const char *File_get_error(File self) {
    return (self != NULL && self->error != NULL) ? Str_as_str(self->error)
                                                 : (char *)NULL;
}

/*
 * Get back internal buffer data
 */
const char *File_get_data(File self) {
    return (self != NULL && self->data != NULL) ? Str_as_str(self->data)
                                                : (char *)NULL;
}

/*
 * Print out file like `bat`
 */
void File_print_out_file_like_bat(File self) {
    if (self == NULL || self->inner == NULL) return;

    usize line_buffer_size = 255;
    char line_buffer[line_buffer_size];
    memset(line_buffer, 0, line_buffer_size);

    //
    // Read each line and add line number at the beginning
    //
    // Line number ` XXXXX | ` holds 9 spaces, add more if you need to print
    // lines more than `99999`!!!
    //
    // ` XXXXX │ LINE_CONTENT_HERE`
    //
    // So, that's why max buffer size to read should be `255 - 9`
    //
    u32 line_no_buffer_str_len = 9;
    u32 line_no_buffer_size = line_no_buffer_str_len + 1;

    u32 current_line_no = 1;
    usize max_line_buffer_to_write = line_buffer_size - line_no_buffer_str_len;

    while (fgets(line_buffer, max_line_buffer_to_write, self->inner) != NULL) {
        //
        // `line_buffer` always end with `\n\0`!!!
        //
        // line_buffer[line_str_len - 1] == '\n'
        // line_buffer[line_str_len] == '\0'
        //

        usize line_str_len = strlen(line_buffer);

        struct Str line_str_added_line_no;
        Str_init_with_capacity(&line_str_added_line_no,
                               line_no_buffer_str_len + line_str_len + 1);

        //
        // Formatted line number
        //
        char line_no_buffer[line_no_buffer_size];
        memset(line_no_buffer, 0, line_no_buffer_size);
        snprintf(line_no_buffer, line_no_buffer_size, " %5u | ",
                 current_line_no);
        /* printf("\n>>> %s, len: %lu", line_no_buffer, */
        /*        strlen(line_no_buffer)); */

        Str_push_str(&line_str_added_line_no, line_no_buffer);

        //
        // Orignal line content
        //
        Str_push_str(&line_str_added_line_no, line_buffer);

        current_line_no++;

        // Print out
        printf("%s", Str_as_str(&line_str_added_line_no));

        Str_free_buffer_only(&line_str_added_line_no);
    }
}

#ifdef ENABLE_DEBUG_LOG
/*
 * Print out self for debugging purpose
 */
void File_print_debug_info(File self) {
    SMART_STRING(debug_info) = Str_from_empty_with_capacity(100);

    char file_handler[20] = {0};
    snprintf(file_handler, sizeof(file_handler), "%p", self->inner);

    char file_mode[4] = {0};
    file_mode_to_string(&self->mode, file_mode);

    DEBUG_LOG(File, print_debug_info,
              "\n[ File, ptr: %p "
              "]\n----------------------------------------\ninner: %s\nmode: "
              "%s\nfilename: %s\nerror: "
              "%s\ndata: %s\n----------------------------------------",
              self, file_handler, file_mode, Str_as_str(self->filename),
              Str_as_str(self->error), Str_as_str(self->data));
}
#endif

/*
 * Free
 */
void File_free(File self) {
    if (self == NULL) return;

    if (self->error != NULL) {
        Str_free(self->error);
        self->error = NULL;
    }

    if (self->data != NULL) {
        Str_free(self->data);
        self->data = NULL;
    }

    if (self->inner != NULL) {
        // Flush before closing
        if (self->mode != FM_READ_ONLY) {
            fflush(self->inner);
        }

        int close_result = fclose(self->inner);

#ifdef ENABLE_DEBUG_LOG
        DEBUG_LOG(File, free, "Close file - '%s', result: %d",
                  Str_as_str(self->filename), close_result);
#endif
        if (close_result != 0) {
#ifdef ENABLE_DEBUG_LOG
            ERROR_LOG(File, free, "Failed to close file - '%s': %s",
                      Str_as_str(self->filename), strerror(errno));
#endif
        }
        self->inner = NULL;
    }

    if (self->filename != NULL) {
        Str_free(self->filename);
        self->filename = NULL;
    }

    free(self);
}

/*
 * Auto free file call
 */
void auto_free_file(File *ptr) {
#ifdef ENABLE_DEBUG_LOG
    DEBUG_LOG(File, auto_free_file,
              "out of scope with File ptr: %p, filename: %s", *ptr,
              File_get_filename(*ptr));

#endif
    File_free(*ptr);
}
