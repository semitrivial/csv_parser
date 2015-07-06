Just a simple C function for parsing CSV.  License: MIT.

--------
Documentation
--------

char **parse_csv( const char *line );

Returns a NULL-terminated array of strings encoded in the indicated line of CSV.

Returns NULL if there was insufficient RAM or if the line is not property encoded CSV.
