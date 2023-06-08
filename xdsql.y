%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <dirent.h>
#include <iostream>
#include "utils.hpp"
#include <map>
#include <string>
#define true 1
#define false 0

void yyerror(const char *s);
int yylex();
int yyparse();

/*
db 相关函数
*/
void create_db(char* dbname);
void drop_db(char* dbname);
void show_db();
void use_db(char* dbname);

/*
工具函数
*/
void remove_directory(const char* path);
int check_file_exists(const char *filepath);
void create_file(const char *filepath);

void printf_red(const char *s)
{
    printf("\033[0m\033[1;31m%s\033[0m", s);
}

extern Session session;
/*
create table sql
*/
typedef struct CreateField {
    char *field; //字段名称
    int type; //字段类型 char为0;int为1
    int length; //字段长度
} CreateField;
typedef struct CreateFields { /*create语句中的字段定义*/
    struct CreateField *fdef;
    struct CreateFields *next_fdef; //下一字段
} CreateFields;
typedef struct CreateTable { /*create语法树根节点*/
    char *table; //基本表名称
    struct CreateFields *fdef; //字段定义
} CreateTable;
void do_create_table(struct CreateTable* create_table_ctx);
/* show table */
void show_tables();
/* drop table */
void drop_table(char* table);

/*
insert sql
*/
typedef struct FieldList {
    char* field_name;
    struct FieldList* next;
} FieldList;
typedef struct FieldValueList {
    Expr* expr;
    struct FieldValueList* next;
} FieldValueList;
typedef struct TableMetaData {
    char* table_name; //表名称
    FieldList* field_list;
} TableMetaData;
typedef struct InsertRecord {
	TableMetaData *table_meta_data;
	FieldValueList *val_list;
} InsertRecord;
void insert_rows(InsertRecord* insert_record);
%}

%union {
    int intval;
    double dval;
    char* strval;
    struct CreateField *create_field; //字段定义
    struct CreateFields *create_fields; //字段定义列表
    struct CreateTable *create_table; //整个create语句
    struct FieldValueList* filed_value_list; //插入字段的值
    struct FieldList* field_list; //插入字段的字段名
    struct InsertRecord *insert_record; //插入sql语句
    struct TableMetaData* table_meta_data; //table元数据
    struct Expr* _expr; //表达式:可以是一个数字,也可以是一个运算式
    struct DeleteRecord* delete_record;
    struct SelectRecord* select_record;
    struct UpdateMap* _update_map;
    struct UpdateRecord* update_record;
}

%token <strval> IDENTIFIER
%token <strval> STRING
%token <dval> NUMBER
%token <intval> CHAR INT

%token CREATE SHOW DROP USE INSERT SELECT DELETE UPDATE SET INTO FROM WHERE DATABASE DATABASES TABLE TABLES VALUES
%token SELECT_ALL
%token SINGLE_QUOTE COMMA LPAREN RPAREN SEMICOLON
%token ADD SUB
%token MUL DIV
%token <intval> OR
%token <intval> AND
%token <intval> EQUAL NOT_EQUAL MORE LESS MORE_EQUAL LESS_EQUAL

%left OR
%left AND

%left ADD SUB
%left MUL DIV

%type <create_table> create_table_stmt
%type <create_field> column_def
%type <create_fields> column_def_list
%type <field_list> field_name_list
%type <filed_value_list> term_list
%type <insert_record> insert_stmt
%type <_expr> term
%type <_expr> expr
%type <_expr> expr_list
%type <_expr> where_clause
%type <delete_record> delete_stmt
%type <intval> equal_op
%type <select_record> select_stmt;
%type <field_list> select_field_list;
%type <_update_map> update_list;
%type <update_record> update_stmt;
%%

stmt_list: /* empty */
         | stmt_list stmt SEMICOLON
         ;

stmt: create_db_stmt
    | drop_db_stmt
    | use_db_stmt
    | show_dbs_stmt
    | table_stmt
    ;

create_db_stmt: CREATE DATABASE IDENTIFIER
{
    char* dbname = $3;
    create_db(dbname);
}
;

drop_db_stmt: DROP DATABASE IDENTIFIER
{
    char* dbname = $3;
    drop_db(dbname);
}
;

use_db_stmt: USE IDENTIFIER
{
    char* dbname = $2;
    use_db(dbname);
}
;

show_dbs_stmt: SHOW DATABASES
{
    show_db();
}
;

table_stmt: create_table_stmt
{
    do_create_table($1);
}
| show_tables_stmt
| drop_table_stmt
| insert_stmt
{
    insert_rows($1);
}
| delete_stmt
{
    delete_row($1);
}
| select_stmt
{
    select_rows($1);
}
| update_stmt
{
    update_rows($1);
}
;

create_table_stmt: CREATE TABLE IDENTIFIER LPAREN column_def_list RPAREN
{
    // struct CreateTable { /*create语法树根节点*/
    //     char *table; //基本表名称
    //     struct CreateFields *fdef; //字段定义
    // };
    $$ = new CreateTable;
    $$->table = $3;
    $$->fdef = $5;
    // printf_red("Create table with columns\n");
}
;

column_def_list: column_def
{
    // struct CreateFields { /*create语句中的字段定义*/
    //     struct CreateField *fdef;
    //     struct CreateFields *next_fdef; //下一字段
    // };
    $$ = new CreateFields;
    $$->fdef = $1;
    $$->next_fdef = NULL;
}
| column_def_list COMMA column_def
{
    CreateFields* fields = $1;

    CreateFields* temp = fields;
    while (temp->next_fdef != NULL) temp = temp->next_fdef;
    CreateFields* next_fields = new CreateFields;
    next_fields->fdef = $3;
    next_fields->next_fdef = NULL;

    temp->next_fdef = next_fields;

    $$ = fields;
}
;

column_def: IDENTIFIER CHAR LPAREN NUMBER RPAREN
{
    // struct CreateField {
    //     char *field; //字段名称
    //     enum TYPE type; //字段类型
    //     int length; //字段长度
    // }
    struct CreateField *tmp = new CreateField;
    tmp->field = $1;
    tmp->type = $2;
    tmp->length = $4;
    $$ = tmp;
}
| IDENTIFIER INT
{
    struct CreateField *tmp = new CreateField;
    tmp->field = $1;
    tmp->type = $2;
    $$ = tmp;
}
;

drop_table_stmt: DROP TABLE IDENTIFIER
{
    drop_table($3);
}
;

show_tables_stmt: SHOW TABLES
{
    show_tables();
}
;

insert_stmt: INSERT INTO IDENTIFIER LPAREN field_name_list RPAREN VALUES LPAREN term_list RPAREN
{
    // typedef struct TableMetaData {
    //     char* table_name; //表名称
    //     FieldList* field_list;
    // } TableMetaData;
    // struct InsertRecord{
    //     TableMetaData *table_meta_data;
    //     struct FieldValueList *val_list;
    // };
    $$ = new InsertRecord;
    TableMetaData* table_meta_data = new TableMetaData;
    table_meta_data->table_name = $3;
    table_meta_data->field_list = $5;
    $$->table_meta_data = table_meta_data;
    $$->val_list = $9;
}
| INSERT INTO IDENTIFIER VALUES LPAREN term_list RPAREN
{
    $$ = new InsertRecord;
    TableMetaData* table_meta_data = new TableMetaData;
    table_meta_data->table_name = $3;
    table_meta_data->field_list = NULL;
    $$->table_meta_data = table_meta_data;
    $$->val_list = $6;
}
;

field_name_list: IDENTIFIER
{
    // typedef struct FieldList {
    //     char* field_name;
    //     struct FieldList* next;
    // } FieldList;
    $$ = new FieldList;
    $$->field_name = $1;
    $$->next = NULL;
}
| field_name_list COMMA IDENTIFIER
{
    FieldList* list = $1;
    FieldList* tmp = list;
	while (tmp->next != NULL) tmp = tmp->next;
	struct FieldList* next_field = new FieldList;
	next_field->field_name = $3;
	next_field->next = NULL;
	tmp->next = next_field;
	$$ = list;
}
;

select_stmt: SELECT select_field_list FROM IDENTIFIER where_clause
            {
                $$ = new SelectRecord;

                std::vector<std::string> field_names;
                FieldList* temp = $2;
                while (temp != NULL) {
                    std::string field_name(temp->field_name);
                    field_names.push_back(field_name);
                    temp = temp->next;
                }
                $$->select_names = field_names;
                $$->table_name = $4;
                $$->where_case = $5;
                // printf_red("Select from with columns\n");
            }
            ;

select_field_list: SELECT_ALL
{
    $$ = NULL;
}
| field_name_list
{
    $$ = $1;
}
;

term: NUMBER
{
    Expr* _expr = new Expr;
    _expr->type = 1;
    _expr->intval = $1;
    $$ = _expr;
    // printf("%d\n", $$->intval);
}
| STRING
{
    Expr* _expr = new Expr;
    _expr->type = 0;
    _expr->strval = $1;
    $$ = _expr;
    // printf("%s\n", $$->strval);
}
| IDENTIFIER
{
    Expr* _expr = new Expr;
    _expr->type = 2;
    _expr->strval = $1;
    $$ = _expr;
    // printf("%s\n", $$->strval);
} 

expr: term
{
    $$ = $1;
}
| term equal_op term
{
    $$ = new Expr;
    $$->left = $1;
    $$->type = $2;
    $$->right = $3;
    // printf("%s %d %d\n", $$->left->strval, $$->type, $$->right->intval);
}
| term ADD term
{
    $$ = new Expr;
    $$->intval = $1->intval + $3->intval;
    $$->type = $1->type;
}
| term SUB term
{
    $$ = new Expr;
    $$->intval = $1->intval + $3->intval;
    $$->type = $1->type;
}
| term MUL term
{
    $$ = new Expr;
    $$->intval = $1->intval * $3->intval;
    $$->type = $1->type;
}
| term DIV term
{
    $$ = new Expr;
    $$->intval = $1->intval / $3->intval;
    $$->type = $1->type;
}
;

equal_op: EQUAL { $$ = $1; }
| NOT_EQUAL { $$ = $1; }
| MORE { $$ = $1; }
| LESS { $$ = $1; }
| MORE_EQUAL { $$ = $1; }
| LESS_EQUAL { $$ = $1; }

term_list: term
{
    // typedef struct FieldValueList {
    //     Expr* expr;
    //     struct FieldValueList* next;
    // } FieldValueList;
    FieldValueList* value_list = new FieldValueList;
    value_list->expr = $1;
    value_list->next = NULL;
    $$ = value_list;
}
| term_list COMMA term
{
    FieldValueList* value_list = $1;
    FieldValueList* temp = value_list;
    while (temp->next != NULL) temp = temp->next;
    FieldValueList* next_value = new FieldValueList;
    next_value->expr = $3;
    next_value->next = NULL;
    temp->next = next_value;
    $$ = value_list;
}
;

// Expr
// {
//     // 0 STR(string) ; 1 int ; 2 id ; 'a' and ; 'o' or
//     // 3 = ; 4 != ; 5 < ; 6 > ; 7 <= ; 8 >=
//     int type;
//     char *strval = NULL;
//     int intval = -1;
//     int judge = -1; // 0 false;1 true;-1 null
//     struct Expr *left, *right;
// } Expr;
expr_list: expr
{
    $$ = $1;
}
| expr_list AND expr_list
{
    $$ = new Expr;
    $$->left = $1;
    $$->type = $2;
    $$->right = $3;
}
| expr_list OR expr_list
{
    $$ = new Expr;
    $$->left = $1;
    $$->type = $2;
    $$->right = $3;
}
| LPAREN expr_list RPAREN
{
    $$ = $2;
}
;

where_clause: /* empty */
{
    $$ = NULL;
}
| WHERE expr_list
{
    $$ = $2;
}
;

delete_stmt: DELETE FROM IDENTIFIER where_clause
{
    $$ = new DeleteRecord;
    $$->table_name = $3;
    $$->where_case = $4;
}
;

update_stmt: UPDATE IDENTIFIER SET update_list where_clause
            {
                $$ = new UpdateRecord;
                std::string table_name($2);
                $$->table_name = table_name;
                UpdateMap* update_map_wrap = $4;
                $$->update_map = update_map_wrap->update_map;
                // std::cout << $$->update_map.size() << std::endl;
                // auto it = $$->update_map.begin();
                // std::cout << it->first << ":" << (it->second).intvalue
                //     << std::endl;

                $$->where_case = $5;
                // printf_red("Update table with values\n");
            }
            ;

update_list: IDENTIFIER EQUAL term
{
    UpdateMap* update_map_wrap = new UpdateMap;

    TmpValue* tmp = new TmpValue;
    tmp->type = $3->type;
    tmp->strvalue = $3->strval;
    tmp->intvalue = $3->intval;

    std::map<std::string, TmpValue> update_map;
    $$->update_map = update_map;
    std::string field_name($1);
    update_map[field_name] = *tmp;
    update_map_wrap->update_map = update_map;
    $$ = update_map_wrap;
}
| update_list COMMA IDENTIFIER EQUAL term
{
    TmpValue* tmp = new TmpValue;
    tmp->type = $5->type;
    tmp->strvalue = $5->strval;
    tmp->intvalue = $5->intval;

    UpdateMap* update_map_wrap = $1;
    std::map<std::string, TmpValue> update_map = update_map_wrap->update_map;
    std::string field_name($3);
    update_map[field_name] = *tmp;
    update_map_wrap->update_map = update_map;
    $$ = update_map_wrap;
}
;

%%
void create_db(char* dbname)
{
    char folderPath[100];
    sprintf(folderPath, "./data/%s", dbname);
    const char* sysFilePath = "./data/sys.dat";

    // 检查文件夹是否存在
    if (access(folderPath, 0) == -1) {
        // 文件夹不存在，创建文件夹
        int status = mkdir(folderPath, 0700);
        if (status == 0) {
            printf("Create database %s success\n", dbname);

            // 创建 sys.dat 文件
            char filePath[100];
            sprintf(filePath, "%s/sys.dat", folderPath);
            FILE* file = fopen(filePath, "w");
            if (file != NULL) {
                printf("sys.dat file created\n");
                fclose(file);
            } else {
                printf("Failed to create sys.dat file\n");
            }

            // 在文件中写入 dbname
            FILE* sysFile = fopen(sysFilePath, "a");
            if (sysFile != NULL) {
                fprintf(sysFile, "%s\n", dbname);
                fclose(sysFile);
            } else {
                printf("Failed to open data/sys.dat\n");
            }
        } else {
            printf("Failed to create database %s\n", dbname);
        }
    } else {
        printf("Database %s already exists\n", dbname);
    }
}

void drop_db(char* dbname)
{
    // printf("drop %s\n", dbname);
    char folderPath[100];
    char sysFilePath[100];

    sprintf(folderPath, "./data/%s", dbname);
    sprintf(sysFilePath, "./data/sys.dat");

    // 检查 sys.dat 文件中是否存在 dbname 记录
    FILE* sysFile = fopen(sysFilePath, "r");
    if (sysFile != NULL) {
        // 创建临时文件以保存除 dbname 记录之外的内容
        FILE* tempFile = fopen("./data/temp.dat", "w");
        if (tempFile != NULL) {
            char line[100];
            int deleted = 0;

            // 遍历 sys.dat 文件中的每一行
            while (fgets(line, sizeof(line), sysFile)) {
                size_t len = strlen(line);
                while (len > 0 && (isspace(line[len-1]) || line[len-1] == '\n')) {
                    line[--len] = '\0';
                }
                // 检查行是否与 dbname 相等
                if (strcmp(line, dbname) != 0) {
                    // 不是 dbname 记录，将行写入临时文件
                    // printf("%s %s\n",line,dbname);
                    fputs(line, tempFile);
                } else {
                    // 是 dbname 记录，标记为已删除
                    deleted = 1;
                }
            }
            fclose(tempFile);
            if (deleted) {
                // 删除 sys.dat 文件
                remove(sysFilePath);

                // 重命名临时文件为 sys.dat
                // char c = getchar();
                rename("./data/temp.dat", sysFilePath);

                // 删除数据库文件夹
                remove_directory(folderPath);
                printf("Database %s dropped\n", dbname);
            } else {
                // 没有找到 dbname 记录
                remove("./data/temp.dat");
                printf("Database %s not found\n", dbname);
            }
            fclose(sysFile);
        } else {
            printf("Failed to open temp.dat\n");
            fclose(sysFile);
        }
    } else {
        printf("sys.dat file not found\n");
    }
}

void remove_directory(const char* path) {
    char command[100];
    sprintf(command, "rm -rf \"%s\"", path);
    system(command);
}

void show_db() {
    FILE *file;
    char line[256];

    // 打开文件
    file = fopen("./data/sys.dat", "r");

    if (file == NULL) {
        printf("无法打开文件.\n");
        return;
    }

    // 逐行读取并打印文件内容
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    // 关闭文件
    fclose(file);
}

void use_db(char* dbname) {
    // printf("%s\n", dbname);
    const char* filename = "./data/sys.dat";
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, dbname) != NULL) {
            session.db = dbname;
            printf("Use database %s\n", session.db);
            fclose(file);
            return;
        }
    }

    printf("Database %s does not exist\n", dbname);
    fclose(file);
}

void do_create_table(struct CreateTable* create_table_ctx) {
    if (!check_use_db()) {
        return;
    }

    char *db = session.db;

    FILE *file = NULL;
    char filepath[100];
    
    // 构建文件路径
    sprintf(filepath, "./data/%s/%s.txt", db, create_table_ctx->table);

    // 检查文件是否存在
    if (check_file_exists(filepath)) {
        printf("%s already exist\n", create_table_ctx->table);
        return;
    }
    
    // 创建表文件
    create_file(filepath);

    sprintf(filepath, "./data/%s/sys.dat", db);

    // 打开文件以追加方式写入
    file = fopen(filepath, "a");

    if (file == NULL) {
        printf("无法打开文件%s\n", filepath);
        return;
    }

    // 遍历字段定义链表
    struct CreateFields *curr_field = create_table_ctx->fdef;
    
    int i = 1;
    while (curr_field != NULL) {
        struct CreateField *field = curr_field->fdef;

        // 写入表名、字段名、类型和长度到文件
        if (field->type == 0) { //char
            fprintf(file, "%s %d %s char %d\n",
                create_table_ctx->table, i, field->field, field->length);
        } else if (field->type == 1) { //int
            fprintf(file, "%s %d %s int\n",
                create_table_ctx->table, i, field->field);
        }

        ++i;
        curr_field = curr_field->next_fdef;
    }
    
    // 关闭文件
    fclose(file);
    printf("create table success\n");
}

int check_file_exists(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file != NULL) {
        fclose(file);
        return true;
    }
    return false;
}

void create_file(const char *filepath) {
    FILE *file = fopen(filepath, "w");
    if (file != NULL) {
        fclose(file);
    } else {
        printf("无法创建%s\n", filepath);
    }
}

void show_tables() {
    if (!check_use_db()) {
        return;
    }

    char *db = session.db;

    char dirpath[100];
    sprintf(dirpath, "./data/%s", db);

    DIR *dir = opendir(dirpath);
    if (dir == NULL) {
        printf("无法打开目录：%s\n", dirpath);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // DT_REG:常规文件
        if (entry->d_type == DT_REG && strstr(entry->d_name, ".txt") != NULL) {
            // 使用 strtok 分割文件名,获取前面部分
            char *filename = strtok(entry->d_name, ".");
            printf("%s\n", filename);
        }
    }

    closedir(dir);
}

void drop_table(char* table) {
    if (!check_use_db()) {
        return;
    }
    char *db = session.db; // 假设数据库名称为 your_database_name
    
    // 构建文件路径
    char table_filepath[100];
    sprintf(table_filepath, "./data/%s/%s.txt", db, table);
    
    // 删除表文件
    if (remove(table_filepath) != 0) {
        printf("无法删除表文件：%s\n", table_filepath);
        return;
    }

    // 删除 sys.dat 相关信息
    char sysdat_filepath[100];
    sprintf(sysdat_filepath, "./data/%s/sys.dat", db);
    
    FILE *sysdat_file = fopen(sysdat_filepath, "r");
    if (sysdat_file == NULL) {
        printf("无法打开 sys.dat 文件\n");
        return;
    }
    
    // 创建临时文件
    char temp_filepath[100];
    sprintf(temp_filepath, "./data/%s/sys_temp.dat", db);
    
    FILE *temp_file = fopen(temp_filepath, "w");
    if (temp_file == NULL) {
        printf("无法创建临时文件\n");
        fclose(sysdat_file);
        return;
    }
    
    char line[256];
    char table_prefix[50];
    sprintf(table_prefix, "%s", table);
    
    // 遍历 sys.dat 文件的每一行
    while (fgets(line, sizeof(line), sysdat_file)) {
        // 比较两个字符串的前缀部分是否相等
        if (strncmp(line, table_prefix, strlen(table_prefix)) != 0) {
            // 将不属于要删除的表的行写入临时文件
            fputs(line, temp_file);
        }
    }
    
    fclose(sysdat_file);
    fclose(temp_file);

    // 删除原 sys.dat 文件
    if (remove(sysdat_filepath) != 0) {
        printf("无法删除 sys.dat 文件\n");
        return;
    }
    
    // 重命名临时文件为 sys.dat
    if (rename(temp_filepath, sysdat_filepath) != 0) {
        printf("无法重命名临时文件\n");
        return;
    }
    
    printf("已成功删除表：%s\n", table);
}

void insert_rows(InsertRecord* insert_record) {
    if (!check_use_db()) {
        return;
    }
    char* db = session.db;
    // 获取表名
    char* table_name = insert_record->table_meta_data->table_name;

    // 构建 sys.dat 文件路径
    char sys_dat_path[100];
    snprintf(sys_dat_path, sizeof(sys_dat_path), "./data/%s/sys.dat", db);

    // 打开 sys.dat 文件
    FILE* sys_dat_file = fopen(sys_dat_path, "r");
    if (sys_dat_file == NULL) {
        printf("Failed to open sys.dat\n");
        return;
    }

    // 查找表名对应的字段信息
    char line[100];

    // 打开表数据文件
    char table_data_path[100];
    snprintf(table_data_path, sizeof(table_data_path), "./data/%s/%s.txt", db, table_name);
    FILE* table_data_file = NULL;
    if (access(table_data_path, 0) == 0) {
        table_data_file = fopen(table_data_path, "a");
    } else {
        printf("table %s not found\n", table_name);
        return;
    }

    FieldList* field_list = insert_record->table_meta_data->field_list;
    FieldValueList* value_list = insert_record->val_list;
    while (fgets(line, sizeof(line), sys_dat_file)) {
        // printf("%s", line);
        // 解析每行记录的字段信息
        char current_table_name[100];
        int index;
        char field_name[100];
        char type[10];
        int length;

        sscanf(line, "%s %d %s %s %d", current_table_name, &index, field_name, type, &length);

        // 判断是否为目标表名的字段信息
        if (strcmp(current_table_name, table_name) == 0) {

            if (field_list == NULL) {
                if (value_list->expr->type == 0) { // char 类型
                    // 截断字符串，确保长度不超过定义的字段长度
                    if (strlen(value_list->expr->strval) > length) {
                        value_list->expr->strval[length] = '\0';
                    }

                    // 写入到表数据文件中
                    fprintf(table_data_file, "%s ", value_list->expr->strval);
                } else if (value_list->expr->type == 1) { // int 类型
                    // 写入到表数据文件中
                    fprintf(table_data_file, "%d ", value_list->expr->intval);
                }
                value_list = value_list->next;
                continue;
            }
            // 创建一个临时的 FieldList 指针，用于遍历 field_list
            FieldList* temp_field_list = field_list;
            FieldValueList* temp_value_list = value_list;

            // 遍历字段列表
            int field_found = 0;
            while (temp_field_list != NULL) {
                // 获取字段名
                char* _field_name = temp_field_list->field_name;

                if (strcmp(field_name, _field_name) != 0) {
                    temp_field_list = temp_field_list->next;
                    temp_value_list = temp_value_list->next;
                    continue;
                }
                field_found = 1;
                // 检查 value_list 是否为空
                if (temp_value_list == NULL) {
                    fprintf(table_data_file, "NULL ");
                } else {
                    // 获取当前字段值的表达式
                    Expr* expr = temp_value_list->expr;

                    // 检查表达式的类型并进行相应处理
                    if (expr->type == 0) { // CHAR 类型
                        // 截断字符串，确保长度不超过定义的字段长度
                        if (strlen(expr->strval) > length) {
                            expr->strval[length] = '\0';
                        }

                        // 写入到表数据文件中
                        fprintf(table_data_file, "%s ", expr->strval);
                    } else if (expr->type == 1) { // INT 类型
                        // 写入到表数据文件中
                        fprintf(table_data_file, "%d ", expr->intval);
                    }
                }
                break;
            }
            if (field_found == 0) {
                fprintf(table_data_file, "NULL ");
            }
        }
    }
    fprintf(table_data_file, "\n");
    fclose(table_data_file);

    // 关闭 sys.dat 文件
    fclose(sys_dat_file);
    printf("insert into %s success\n", table_name);
}

int main()
{
    session.db = NULL;
    yyparse();
	return 0;
}

void yyerror(const char *s)
{
    printf_red(s);
}
