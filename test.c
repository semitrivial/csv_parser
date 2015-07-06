#include <stdio.h>

void free_csv_line( char **parsed );
char **parse_csv( const char *line );

int main(void)
{
  char *test = "a,b,\"c,d\",\"e,f,\"\",g\",h";
  char **parsed = parse_csv( test );
  char **ptr;

  for ( ptr = parsed; *ptr; ptr++ )
    printf( "%s\n", *ptr );

  return 1;
}
