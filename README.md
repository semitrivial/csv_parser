Just a simple C function for parsing CSV (assuming UNIX-style linebreaks; a future
update will remove this restriction).

--------
License: MIT
--------

--------
Documentation
--------

char **parse_csv( const char *line );

Returns a NULL-terminated array of strings encoded in the indicated line of CSV.

Returns NULL if there was insufficient RAM or if the line is not property encoded CSV.

The return value of parse_csv is malloc'd, and each string in the array is also malloc'd.

---

void free_csv_line( char **parsed );

Convenience function to free the output of the parse_csv command.  All this function
does is free each string in the array and then free the array.
