#!/bin/bash
bison -d xdsql.y
flex -i xdsql.l
gcc -o xdsql xdsql.tab.c lex.yy.c -lfl