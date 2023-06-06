#ifndef UTIL_H
#define UTIL_H

#include <iostream>

/*
delete sql
*/
typedef struct Expr {
    // 0 CHAR(string) ; 1 int ; 2 id ; 'a' and ; 'o' or
    // 3 = ; 4 != ; 5 < ; 6 > ; 7 <= ; 8 >= 
    int type;
    char* strval;
    int intval;
    int judge; //0 false;1 true;-1 null
    struct Expr *left, *right;
} Expr;
typedef struct DeleteRecord {
	char* table_name;
	Expr *where_case;
} DeleteRecord;

void delete_row(DeleteRecord* delete_record_ctx);

#endif  // CPP_UTIL_H