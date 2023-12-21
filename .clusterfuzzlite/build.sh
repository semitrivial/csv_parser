#!/bin/bash -eu

# Copy all fuzzer executables to $OUT/
$CC $CFLAGS $LIB_FUZZING_ENGINE \
  $SRC/csv_parser/.clusterfuzzlite/parse_fuzzer.c \
  -o $OUT/parse_fuzzer \
  csv.c split.c fread_csv_line.c \
  -I$SRC/csv_parser
