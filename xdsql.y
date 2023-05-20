%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int yyerror(const char *s, ...);
extern int yylex();
extern int yyparse();
void printf_red(const char *s)
{
    printf("\033[0m\033[1;31m%s\033[0m", s);
}
%}

%token CREATE SHOW DROP USE INSERT SELECT DELETE UPDATE SET INTO FROM WHERE DATABASE DATABASES TABLE TABLES VALUES
%token IDENTIFIER NUMBER STRING SELECT_ALL
%token INT CHAR
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
%left UMINUS

%%

stmt_list: /* empty */
         | stmt_list stmt SEMICOLON
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
                    printf_red("Create database\n");
               }
               ;

drop_db_stmt: DROP DATABASE IDENTIFIER
            {
                printf_red("Drop database\n");
            }
            ;

use_db_stmt: USE IDENTIFIER
           {
               printf_red("Use database\n");
           }
           ;

show_dbs_stmt: SHOW DATABASES
             {
                 printf_red("Show databases\n");
             }
             ;

create_table_stmt: CREATE TABLE IDENTIFIER LPAREN column_def_list RPAREN
                  {
                      printf_red("Create table with columns\n");
                  }
                  ;

column_def_list: column_def
               | column_def_list COMMA column_def
               ;

column_def: IDENTIFIER CHAR LPAREN NUMBER RPAREN
          {
              printf_red("CHAR COLUMN\n");
          }
          | IDENTIFIER INT
          {
              printf_red("INT COLUMN\n");
          }
          ;

drop_table_stmt: DROP TABLE IDENTIFIER
                {
                    printf_red("Drop table\n");
                }
                ;

show_tables_stmt: SHOW TABLES
                 {
                     printf_red("Show tables\n");
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
int main()
{
    printf("> "); 
    yyparse();
    return 0;
}

int yyerror(const char *s, ...)
{
    printf_red(s);
    return -1;
}