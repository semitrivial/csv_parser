#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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
    static FILE *bookmark;
    char *buf, *bptr, *limit;
    char ch;
    int fQuote;

    buf = malloc( max_line_size + 1 );
    if ( !buf ) {
        if ( err ) {
            *err = CSV_ERR_NO_MEMORY;
        }
        return NULL;
    }
    bptr = buf;
    limit = buf + max_line_size;

    if ( bookmark != fp ) {
        read_ptr = read_end = read_buf + READ_BLOCK_SIZE;
        bookmark = fp;
    }

    for ( fQuote = 0; ; ) {
        QUICK_GETC(ch, fp);
fread_csv_line_loop:

        if ( !ch || (ch == '\n' && !fQuote)) {
            *bptr = '\0';
            return buf;
        }

        if ( bptr >= limit ) {
            free( buf );
            if ( err ) {
                *err = CSV_ERR_LONGLINE;
            }
            return NULL;
        }
        *bptr++ = ch;

        if ( fQuote ) {
            if ( ch == '\"' ) {
                QUICK_GETC(ch, fp);
                if ( ch != '\"' ) {
                    fQuote = 0;
                }
                goto fread_csv_line_loop;
            }
        } else if ( ch == '\"' ) {
            fQuote = 1;
        }
    }
}