#include <stdio.h>
#include "csv.h"

int main(void)
{
  char *test = "a,b,\"c,d\",\"e,f,\"\",g\",h";
  char **parsed = parse_csv( test );
  char **ptr;

  for ( ptr = parsed; *ptr; ptr++ )
    printf( "%s\n", *ptr );

  free_csv_line( parsed );

  return 1;
}
