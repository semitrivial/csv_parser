# csv_parser

A simple C library for parsing CSV.

## License: MIT

## Overview

csv.c:  Parse a single line of CSV (a string with no unescaped linebreaks)

split.c:  Split a string of CSV (with unescaped linebreaks) into single lines
of CSV

fread_csv_line.c:  Extract a single line of CSV from a file

## Documentation (csv.c)

    char **parse_csv( const char *line );

Returns a `NULL`-terminated array of strings encoded in the indicated line of
CSV.

Returns `NULL` if there was insufficient RAM or if the line is not property
encoded CSV.

The return value of `parse_csv` is `malloc`'d.  Each string in the array is
also `malloc`'d.

    void free_csv_line( char **parsed );

Convenience function to free the `parse_csv` output.  Frees each string in the
array and then frees the array.

## Documentation (split.c)

    char **split_on_unescaped_newlines(const char *txt);

Given a string, which might contain unescaped linebreaks, get a
`NULL`-terminated array of strings, each of which does not contain unescaped
linebreaks.

Both the array and the strings in the array are `malloc`'d.

## Documentation (fread_csv_line.c)

    char *fread_csv_line(FILE *fp, int max_line_size, int *done, int *err)

Extract a line of CSV from a file.

`max_line_size`: Lines longer than this will cause `fread_csv_line` to return
`NULL`.

`done`: Pointer to an int.  The int is set to `1` when the end of `fp` is
reached.

`err`: Pointer to an int.  On error, an error code will be written to this int.
Error codes are defined in `csv.h`: `CSV_ERR_LONGLINE` and `CSV_ERR_NO_MEMORY`.

## Caveats

`fread_csv_line` is optimized for repeating until the file is exhausted.  It
mutates/depends on file position (in the `fseek` sense), in an unpredictable
way.

`fread_csv_line` shouldn't be called on different files in parallel. (Hopefully
sometime in the future we'll add a proper `init` system to deal with this).

Calling `fread_csv_line` on `fp` after a previous call exhausted the file
(indicated by `*done`) is undefined behavior.

## TODO

In `split.c` and `fread_csv_line.c`:  Deal with carriage returns when
"linebreak" doesn't mean "\n"