#include <stdio.h>
#include "csv.h"

int main(void)
{
  /*
   * Test string adapted from https://en.wikipedia.org/wiki/Comma-separated_values
   */
  const char *test = "1996,Jeep,\"Venture \"\"Extended Edition\"\"\",\"MUST SELL!\nair, moon roof, loaded\",4799.00";
  char **parsed = parse_csv( test );
  char **ptr;
  int i = 1;

  for ( ptr = parsed; *ptr; ptr++ )
    printf( "Field %d: %s\n", i++, *ptr );

  free_csv_line( parsed );

  return 1;
}
