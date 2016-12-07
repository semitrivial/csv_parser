#include <stdlib.h>
#include <string.h>
#include "csv.h"

char read_buf[READ_BLOCK_SIZE], *read_ptr, *read_end;
int fread_len;

/*
 * Given a file pointer, read a CSV line from that file.
 * Advances file read location accordingly.
 * File may include newlines escaped with "double quotes".
 *
 * Other arguments:
 * size_t max_line_size: Maximum line size, in bytes.
 * int *err: (Optional) Pointer to an int where error code can be written.
 *
 * See csv.h for definitions of error codes.
 */
char *fread_csv_line(FILE *fp, int max_line_size, int *err) {

}