#include <stdio.h>
#include <string.h>
#include "csv.h"

void test_parse_csv(void);
void test_split_on_unescaped_newlines(void);

int main(void) {
  test_parse_csv();

  test_split_on_unescaped_newlines();
}

void test_parse_csv(void)
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

  return;
}

void test_split_on_unescaped_newlines(void) {
  const char *txt =
    "Blah, blah, blah\n"
    "Foo, \"Bar\", \"Foo, Bar\"\n"
    "Foo, \"B\na\nr\", Baz\n"
    "Foo, \"B\"\"ar\", Baz\n"
    ;
  char **result = split_on_unescaped_newlines(txt);

  if ( !result[0] || !result[1] || !result[2] || !result[3] || result[4] ) {
    printf( "test_split_on_unescaped_newlines failed! (1)\n" );
    return;
  }

  if ( !strcmp(result[0], "Blah, blah, blah")
  ||   !strcmp(result[1], "Foo, \"Bar\", \"Foo, Bar\"")
  ||   !strcmp(result[2], "Foo, \"B\na\nr\", Baz")
  ||   !strcmp(result[3], "Foo, \"B\"\"ar\", Baz") ) {
    printf( "test_split_on_unescaped_newlines failed! (2)\n" );
    return;
  }
}