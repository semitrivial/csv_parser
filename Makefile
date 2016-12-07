all:
	gcc -g -Wall csv.c split.c fread_csv_line.c test.c -o test
