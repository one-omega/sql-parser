#!/bin/bash
bison -d xdsql.y -o xdsql.tab.cpp
flex -o lex.yy.cpp -i xdsql.l
g++ -o xdsql utils.cpp lex.yy.cpp xdsql.tab.cpp
