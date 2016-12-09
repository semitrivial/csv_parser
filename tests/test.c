#include <stdio.h>
#include <string.h>
#include "../csv.h"

int test_parse_csv(void);
int test_split_on_unescaped_newlines(void);
int test_fread_csv_line(void);

void run_test(const char *name, int test(void)) {
  int result;
  printf( "Running %s...", name );
  result = test();
  if (result) {
    printf( "Success.\n" );
  } else {
    printf( "Failure!\n" );
  }
}

int main(void) {
  run_test("test_parse_csv", test_parse_csv);

  run_test("test_split_on_unescaped_newlines", test_split_on_unescaped_newlines);

  run_test("test_fread_csv_line", test_fread_csv_line);
}

int test_parse_csv(void)
{
  /*
   * Test string adapted from https://en.wikipedia.org/wiki/Comma-separated_values
   */
  const char *test = 
    "1996,Jeep,\"Venture \"\"Extended Edition\"\"\",\"MUST SELL!\nair, moon roof, loaded\",4799.00";
  char **parsed = parse_csv( test );

  if ( !parsed[0] || !parsed[1] || !parsed[2] || !parsed[3] || !parsed[4] ) {
    return 0;
  }

  if ( parsed[5] ) {
    return 0;
  }

  if ( strcmp(parsed[0], "1996")
  ||   strcmp(parsed[1], "Jeep")
  ||   strcmp(parsed[2], "Venture \"Extended Edition\"")
  ||   strcmp(parsed[3], "MUST SELL!\nair, moon roof, loaded")
  ||   strcmp(parsed[4], "4799.00" ) ) {
    return 0;
  }

  free_csv_line( parsed );

  return 1;
}

int test_split_on_unescaped_newlines(void) {
  const char *txt =
    "Blah, blah, blah\n"
    "Foo, \"Bar\", \"Foo, Bar\"\n"
    "Foo, \"B\na\nr\", Baz\n"
    "Foo, \"B\"\"ar\", Baz\n"
    ;
  char **result = split_on_unescaped_newlines(txt);

  if ( !result[0] || !result[1] || !result[2] || !result[3] || result[4] ) {
    printf( "test_split_on_unescaped_newlines failed! (1)\n" );
    return 0;
  }

  if ( strcmp(result[0], "Blah, blah, blah")
  ||   strcmp(result[1], "Foo, \"Bar\", \"Foo, Bar\"")
  ||   strcmp(result[2], "Foo, \"B\na\nr\", Baz")
  ||   strcmp(result[3], "Foo, \"B\"\"ar\", Baz") ) {
    printf( "test_split_on_unescaped_newlines failed! (2)\n" );
    return 0;
  }

  return 1;
}

int test_fread_csv_line(void) {
  int err, done = 0;
  FILE *fp = fopen("tests/test.csv", "r");

  if ( strcmp( fread_csv_line(fp, 1024, &done, &err), "foo,bar,baz" ) || done ) {
    return 0;
  }
  if ( strcmp( fread_csv_line(fp, 1024, &done, &err), "foo,\"bar\",baz" ) || done ) {
    return 0;
  }
  if ( strcmp( fread_csv_line(fp, 1024, &done, &err), "foo,\"b\"\"ar\",baz" ) || done ) {
    return 0;
  }
  if ( strcmp( fread_csv_line(fp, 1024, &done, &err), "foo,\"b\na\nr\",baz" ) || done ) {
    return 0;
  }
  if ( strcmp( fread_csv_line(fp, 1024, &done, &err), "foo,\"\n\nb\n\n\"\"a\"\"\n\nr\n\n\",baz" ) || done ) {
    return 0;
  }
  if ( strcmp( fread_csv_line(fp, 1024, &done, &err), "foo,bar,\"baz\"" ) || done ) {
    return 0;
  }
  if ( strcmp( fread_csv_line(fp, 1024, &done, &err), "foo,bar,\"\"baz\"\"" ) || done ) {
    return 0;
  }
  if ( strcmp( fread_csv_line(fp, 1024, &done, &err), "foo,bar,\"\"\"baz\"\"\"" ) || done ) {
    return 0;
  }
  if ( strcmp( fread_csv_line(fp, 1024, &done, &err), "foo,bar,baz" ) || done ) {
    return 0;
  }
  if ( strcmp( fread_csv_line(fp, 1024, &done, &err), "" ) || !done ) {
    return 0;
  }
  return 1;
}