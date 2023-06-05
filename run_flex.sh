#!/bin/bash
flex -i xdsql.l
gcc lex.yy.c -o xdsql -lfl
./xdsql
