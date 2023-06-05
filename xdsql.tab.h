/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_XDSQL_TAB_H_INCLUDED
# define YY_YY_XDSQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    STRING = 259,
    NUMBER = 260,
    CHAR = 261,
    INT = 262,
    CREATE = 263,
    SHOW = 264,
    DROP = 265,
    USE = 266,
    INSERT = 267,
    SELECT = 268,
    DELETE = 269,
    UPDATE = 270,
    SET = 271,
    INTO = 272,
    FROM = 273,
    WHERE = 274,
    DATABASE = 275,
    DATABASES = 276,
    TABLE = 277,
    TABLES = 278,
    VALUES = 279,
    SELECT_ALL = 280,
    SINGLE_QUOTE = 281,
    COMMA = 282,
    LPAREN = 283,
    RPAREN = 284,
    SEMICOLON = 285,
    OR = 286,
    AND = 287,
    EQUAL = 288,
    NOT_EQUAL = 289,
    MORE = 290,
    LESS = 291,
    NOT = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 67 "xdsql.y" /* yacc.c:1921  */

    int intval;
    double dval;
    char* strval;
    struct CreateField *create_field; //字段定义
    struct CreateFields *create_fields; //字段定义列表
    struct CreateTable *create_table; //整个create语句

#line 105 "xdsql.tab.h" /* yacc.c:1921  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_XDSQL_TAB_H_INCLUDED  */
