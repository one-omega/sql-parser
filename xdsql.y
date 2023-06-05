%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <dirent.h>
#define true 1
#define false 0
int yyerror(const char *s, ...);

/*
db 相关函数
*/
void create_db(char* dbname);
void drop_db(char* dbname);
void show_db();
void use_db(char* dbname);
int check_use_db();

/*
工具函数
*/
void remove_directory(const char* path);
int check_file_exists(const char *filepath);
void create_file(const char *filepath);

extern int yylex();
extern int yyparse();
void printf_red(const char *s)
{
    printf("\033[0m\033[1;31m%s\033[0m", s);
}

/*
一次数据库连接的信息
*/
typedef struct Session {
    char* db;
} Session;
Session session;

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
%}

%union {
    int intval;
    double dval;
    char* strval;
    struct CreateField *create_field; //字段定义
    struct CreateFields *create_fields; //字段定义列表
    struct CreateTable *create_table; //整个create语句
}

%token <strval> IDENTIFIER
%token <strval> STRING
%token <dval> NUMBER
%token <intval> CHAR INT

%token CREATE SHOW DROP USE INSERT SELECT DELETE UPDATE SET INTO FROM WHERE DATABASE DATABASES TABLE TABLES VALUES
%token SELECT_ALL
%token SINGLE_QUOTE COMMA LPAREN RPAREN SEMICOLON
%token OR
%token AND
%token EQUAL NOT_EQUAL
%token MORE LESS
%token NOT

%left OR
%left AND
%right NOT

%left '+' '-'
%left '*' '/'

%type <create_table> create_table_stmt
%type <create_field> column_def
%type <create_fields> column_def_list
%%

stmt_list: /* empty */
         | stmt_list stmt SEMICOLON
         ;

stmt: create_db_stmt
    | drop_db_stmt
    | use_db_stmt
    | show_dbs_stmt
    | table_stmt
    | insert_stmt
    | select_stmt
    | delete_stmt
    | update_stmt
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
;

create_table_stmt: CREATE TABLE IDENTIFIER LPAREN column_def_list RPAREN
{
    // struct CreateTable { /*create语法树根节点*/
    //     char *table; //基本表名称
    //     struct CreateFields *fdef; //字段定义
    // };
    $$ = malloc(sizeof(struct CreateTable));
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
    $$ = malloc(sizeof(struct CreateFields));
    $$->fdef = $1;
    $$->next_fdef = NULL;
}
| column_def_list COMMA column_def
{
    CreateFields* fields = $1;

    CreateFields* temp = fields;
    while (temp->next_fdef != NULL) temp = temp->next_fdef;
    CreateFields* next_fields = (CreateFields*) malloc(sizeof(struct CreateFields));
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
    struct CreateField *tmp = (CreateField*)malloc(sizeof(struct CreateField));
    tmp->field = $1;
    tmp->type = $2;
    tmp->length = $4;
    $$ = tmp;
}
| IDENTIFIER INT
{
    struct CreateField *tmp = (CreateField*)malloc(sizeof(struct CreateField));
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

insert_stmt: INSERT INTO IDENTIFIER LPAREN identifier_list RPAREN VALUES LPAREN term_list RPAREN
            {
                printf_red("Insert into with values\n");
            }
            | INSERT INTO IDENTIFIER VALUES LPAREN term_list RPAREN
            {
                printf_red("Insert into with all values\n");
            }
            ;

identifier_list: IDENTIFIER
             | identifier_list COMMA IDENTIFIER
             ;

select_stmt: SELECT select_list FROM identifier_list where_clause
            {
                printf_red("Select from with columns\n");
            }
            ;

select_list: SELECT_ALL
           | term_list
           ;

term: NUMBER
    | STRING
    | IDENTIFIER

expr: term
    | term EQUAL term
    | term NOT_EQUAL term
    | term MORE term
    | term LESS term
    ;

term_list: term
         | term_list COMMA term
         ;

expr_list: expr
         | expr_list AND expr_list
         | expr_list OR expr_list
         | NOT expr_list
         | LPAREN expr_list RPAREN
         ;

where_clause: /* empty */
            | WHERE expr_list
            {
                printf_red("where clause\n");
            }
            ;

delete_stmt: DELETE FROM IDENTIFIER where_clause
            {
                printf_red("Delete from\n");
            }
            ;

update_stmt: UPDATE IDENTIFIER SET update_list where_clause
            {
                printf_red("Update table with values\n");
            }
            ;

update_list: IDENTIFIER EQUAL term
           | update_list COMMA IDENTIFIER EQUAL term
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

int check_use_db() {
    if (session.db == NULL) {
        printf("have not use database\n");
        return 0;
    }
    return 1;
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

int main()
{
    session.db = NULL;
    yyparse();
	return 0;
}

int yyerror(const char *s, ...)
{
    printf_red(s);
    return -1;
}
