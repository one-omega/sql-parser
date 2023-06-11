#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

/*
一次数据库连接的信息
*/
typedef struct Session
{
    char *db;
} Session;

int check_use_db();

struct FieldInfo
{
    int type;
    int length = 0;
};
typedef struct TmpValue
{
    int type;
    char* strvalue = NULL;
    int intvalue;
} TmpValue;

/*
delete sql
*/
typedef struct Expr
{
    // 0 STR(string) ; 1 int ; 2 id ; 'a' and ; 'o' or
    // 3 = ; 4 != ; 5 < ; 6 > ; 7 <= ; 8 >=
    int type;
    char *strval = NULL;
    int intval = -1;
    int judge = -1; // 0 false;1 true;-1 null
    struct Expr *left = NULL;
    struct Expr *right = NULL;
} Expr;

enum ExprType
{
    _CHAR = 0,
    _INT = 1,
    _ID = 2,
    _EQUAL = 3,
    _NOT_EQUAL = 4,
    _LESS = 5,
    _MORE = 6,
    _LESS_EQUAL = 7,
    _MORE_EQUAL = 8,
    _AND = 'a',
    _OR = 'o'
};

typedef struct DeleteRecord
{
    char *table_name;
    Expr *where_case;
} DeleteRecord;

void delete_row(DeleteRecord *delete_record_ctx);
typedef struct SelectRecord
{
    char *table_name;
    std::vector<std::string> select_names;
    Expr *where_case; 
} SelectRecord;

void select_rows(SelectRecord* select_record_ctx);

typedef struct UpdateMap {
    std::map<std::string, TmpValue> update_map;
} UpdateMap;

typedef struct UpdateRecord
{
    char* table_name;
    // std::map<std::string, TmpValue> update_map;
    UpdateMap* update_map_wrap;
    Expr *where_case;
} UpdateRecord;

void update_rows(UpdateRecord* update_record_ctx);
#endif // CPP_UTIL_H