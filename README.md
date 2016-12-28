# csv_parser

csv_parser is a simple C library for parsing CSV.

The parse_cvs function takes a single row from a CSV file (as a string),
and outputs an array of strings corresponding to the values in
the columns in that row.

## License: MIT

## Overview of files

csv.c:  For parsing a single line of CSV (a string with no unescaped linebreaks)

split.c:  For splitting a string of CSV (with unescaped linebreaks) into single
lines of CSV

fread_csv_line.c:  For extracting a single line of CSV from a file

## Documentation (csv.c)

    char **parse_csv( const char *line );

Returns a `NULL`-terminated array of strings encoded in the indicated line of
CSV.

Returns `NULL` if there was insufficient RAM or if the line is not property
encoded CSV.

The return value of `parse_csv` is `malloc`'d, and each string in the array is
also `malloc`'d.

    void free_csv_line( char **parsed );

Convenience function to `free` the output of the `parse_csv` command.  All this
function does is `free` each string in the array and then `free` the array.

## Documentation (split.c)

    char **split_on_unescaped_newlines(const char *txt);

Given a string, which might contain unescaped linebreaks (and thus contain
multiple lines of CSV), get a `NULL`-terminated array of strings, each of which
does not contain unescaped linebreaks.

Both the array and the strings in the array are `malloc`'d.

## Documentation (fread_csv_line.c)

    char *fread_csv_line(FILE *fp, int max_line_size, int *done, int *err)

Given a file pointer, extract a line of CSV from it.

Other arguments:
  int max_line_size:  a maximum line size.  Lines longer than this will
    cause fread_csv_line to return NULL.
  int *done:  Pointer to an int which will be set to 1 if the end of fp is
    reached.
  int *err:  Pointer to an int where error codes will be
    written.  The two error codes, defined in `csv.h`, are:
    CSV_ERR_LONGLINE and CSV_ERR_NO_MEMORY.

Warning: `fread_csv_line` is optimized for the use case where you repeatedly
call it until the file is exhausted.  It tampers with the file position (in the
`fseek` sense) in unpredictable ways, and will break if other things tamper with
the file position in between calls to fread_csv_line.

Warning: `fread_csv_line` will not work correctly if called on different files
in parallel.  (Hopefully sometime in the future we'll add a proper `init`
system to deal with this).

Warning: Calling `fread_csv_line` on `fp` after a previous call exhausted the
file (indicated by `*done`), is undefined behavior.

## TODO

In `split.c` and `fread_csv_line.c`:  Deal with carriage returns in OS's where
"linebreak" doesn't mean "\n"