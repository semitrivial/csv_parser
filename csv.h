#ifndef CSV_DOT_H_INCLUDE_GUARD
#define CSV_DOT_H_INCLUDE_GUARD
char **parse_csv( const char *line );
void free_csv_line( char **parsed );
char **split_on_unescaped_newlines(const char *txt);

#define READ_BLOCK_SIZE 65536

#define QUICK_GETC( ch, fp )\
do\
{\
    if ( read_ptr == read_end )\
    {\
        fread_len = fread( read_buf, sizeof(char), READ_BLOCK_SIZE, fp );\
        if ( fread_len < READ_BLOCK_SIZE )\
            read_buf[fread_len] = '\0';\
        read_ptr = read_buf;\
    }\
    ch = *read_ptr++;\
}\
while(0)

#endif
