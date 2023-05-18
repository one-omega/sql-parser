%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%token CREATE DATABASE
%token SHOW DATABASES
%token DROP DATABASE
%token USE DATABASE
%token CREATE TABLE
%token SHOW TABLES
%token DROP TABLE
%token INSERT INTO VALUES
%token SELECT FROM WHERE
%token OR
%token AND
%token NOT
%token IDENTIFIER NUMBER STRING
%token <value> INT CHAR

%left '+' '-'
%left '*' '/'
%left UMINUS

%%

stmt_list: /* empty */
         | stmt_list stmt ';'
         ;

stmt: create_db_stmt
    | drop_db_stmt
    | use_db_stmt
    | show_dbs_stmt
    | create_table_stmt
    | drop_table_stmt
    | show_tables_stmt
    | insert_stmt
    | select_stmt
    | delete_stmt
    | update_stmt
    ;

create_db_stmt: CREATE DATABASE IDENTIFIER
               {
                   printf("Create database %s\n", $3);
               }
               ;

drop_db_stmt: DROP DATABASE IDENTIFIER
            {
                printf("Drop database %s\n", $3);
            }
            ;

use_db_stmt: USE DATABASE IDENTIFIER
           {
               printf("Use database %s\n", $3);
           }
           ;

show_dbs_stmt: SHOW DATABASES
             {
                 printf("Show databases\n");
             }
             ;

create_table_stmt: CREATE TABLE IDENTIFIER '(' column_def_list ')'
                  {
                      printf("Create table %s with columns:\n", $3);
                      $$ = $3;
                  }
                  ;

column_def_list: column_def
               | column_def_list ',' column_def
               ;

column_def: IDENTIFIER CHAR '(' INT ')'
          {
              printf("  %s CHAR(%d)\n", $1, $4);
          }
          | IDENTIFIER INT
          {
              printf("  %s INT\n", $1);
          }
          ;

drop_table_stmt: DROP TABLE IDENTIFIER
                {
                    printf("Drop table %s\n", $3);
                }
                ;

show_tables_stmt: SHOW TABLES
                 {
                     printf("Show tables\n");
                 }
                 ;

insert_stmt: INSERT INTO IDENTIFIER '(' col_name_list ')' VALUES '(' expr_list ')'
            {
                printf("Insert into %s with values:\n", $3);
            }
            ;

col_name_list: IDENTIFIER
             | col_name_list ',' IDENTIFIER
             ;

expr_list: expr
         | expr_list ',' expr
         ;

expr: NUMBER
    | STRING
    | IDENTIFIER
    ;

select_stmt: SELECT select_list FROM IDENTIFIER where_clause
            {
                printf("Select from %s with columns:\n", $4);
            }
            ;

select_list: '*'
           | select_list ',' IDENTIFIER
           ;

where_clause: /* empty */
            | WHERE expr
            ;

delete_stmt: DELETE FROM IDENTIFIER where_clause
            {
                printf("Delete from %s\n", $3);
            }
            ;

update_stmt: UPDATE IDENTIFIER SET update_list where_clause
            {
                printf("Update table %s with values:\n", $2);
            }
            ;

update_list: IDENTIFIER '=' expr
           | update_list ',' IDENTIFIER '=' expr
           ;

%%

int main(void)
{
	return yyparse();
}

void yyerror(char *s){
   printf("error:%s\n", s);
}