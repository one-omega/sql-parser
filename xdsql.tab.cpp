/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "xdsql.y" /* yacc.c:337  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <dirent.h>
#include <iostream>
#include "utils.hpp"
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
int check_use_db();

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

#line 160 "xdsql.tab.cpp" /* yacc.c:337  */
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "xdsql.tab.hpp".  */
#ifndef YY_YY_XDSQL_TAB_HPP_INCLUDED
# define YY_YY_XDSQL_TAB_HPP_INCLUDED
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
    MORE_EQUAL = 292,
    LESS_EQUAL = 293
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 91 "xdsql.y" /* yacc.c:352  */

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

#line 257 "xdsql.tab.cpp" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_XDSQL_TAB_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   100

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  56
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  109

#define YYUNDEFTOK  2
#define YYMAXUTOK   293

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    41,    39,     2,    40,     2,    42,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   138,   138,   139,   142,   143,   144,   145,   146,   147,
     148,   151,   158,   165,   172,   178,   182,   183,   184,   188,
     194,   207,   217,   233,   246,   255,   261,   267,   284,   295,
     305,   318,   324,   325,   328,   335,   342,   350,   354,   363,
     364,   365,   366,   367,   368,   370,   381,   394,   398,   405,
     412,   419,   422,   428,   436,   442,   443
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "STRING", "NUMBER", "CHAR",
  "INT", "CREATE", "SHOW", "DROP", "USE", "INSERT", "SELECT", "DELETE",
  "UPDATE", "SET", "INTO", "FROM", "WHERE", "DATABASE", "DATABASES",
  "TABLE", "TABLES", "VALUES", "SELECT_ALL", "SINGLE_QUOTE", "COMMA",
  "LPAREN", "RPAREN", "SEMICOLON", "OR", "AND", "EQUAL", "NOT_EQUAL",
  "MORE", "LESS", "MORE_EQUAL", "LESS_EQUAL", "'+'", "'-'", "'*'", "'/'",
  "$accept", "stmt_list", "stmt", "create_db_stmt", "drop_db_stmt",
  "use_db_stmt", "show_dbs_stmt", "table_stmt", "create_table_stmt",
  "column_def_list", "column_def", "drop_table_stmt", "show_tables_stmt",
  "insert_stmt", "field_name_list", "select_stmt", "select_list", "term",
  "expr", "equal_op", "term_list", "expr_list", "where_clause",
  "delete_stmt", "update_stmt", "update_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,    43,
      45,    42,    47
};
# endif

#define YYPACT_NINF -64

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-64)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -64,     7,   -64,    29,    -9,    30,     8,    15,     5,    25,
      51,    27,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,
     -64,   -64,   -64,   -64,    59,    67,   -64,   -64,    68,    69,
     -64,    70,   -64,   -64,   -64,   -64,    56,   -64,    48,    73,
      61,   -64,   -64,    50,   -64,   -64,    18,    76,    21,    63,
      77,    80,    57,    76,   -64,   -14,   -64,    -1,   -64,    53,
       4,    60,    26,   -64,    21,    31,    81,   -64,    -1,     0,
     -64,    37,    21,    84,   -64,    62,   -64,    80,   -64,    32,
      64,   -64,    16,   -64,   -64,   -64,   -64,   -64,   -64,    21,
      -1,    -1,   -64,    58,    87,   -64,   -64,    65,   -64,   -64,
      66,   -64,    21,    71,    21,   -64,   -64,    36,   -64
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     4,     5,     6,     7,     8,    15,    17,    16,
      18,     9,    19,    10,     0,     0,    14,    26,     0,     0,
      13,     0,    36,    35,    34,    32,     0,    45,    33,     0,
       0,     3,    11,     0,    12,    25,     0,     0,     0,    51,
       0,     0,     0,     0,    29,    51,    46,     0,    53,     0,
      51,     0,     0,    21,     0,     0,     0,    31,     0,    37,
      47,    52,     0,     0,    54,     0,    24,     0,    20,     0,
       0,    30,     0,    39,    40,    41,    42,    43,    44,     0,
       0,     0,    55,     0,     0,    22,    28,     0,    50,    38,
      49,    48,     0,     0,     0,    56,    23,     0,    27
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,
      12,   -64,   -64,   -64,    42,   -64,   -64,    -8,   -64,   -64,
     -63,   -62,   -16,   -64,   -64,   -64
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    11,    12,    13,    14,    15,    16,    17,    62,
      63,    18,    19,    20,    55,    21,    36,    69,    70,    89,
      38,    71,    58,    22,    23,    60
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      37,    79,    32,    33,    34,    57,    82,     2,    32,    33,
      34,    30,    26,    66,    27,     3,     4,     5,     6,     7,
       8,     9,    10,    57,    32,    33,    34,    68,   100,   101,
      35,    73,    31,    83,    84,    85,    86,    87,    88,    67,
      56,   107,    52,    39,    74,    98,    53,    90,    91,    24,
      28,    25,    29,    77,    40,    78,    37,    41,    66,    48,
      80,    96,    42,    48,    92,   108,    75,    76,    90,    91,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    54,
      59,    99,    57,    61,    81,    64,    72,    93,    97,    95,
      94,   102,   103,   104,   105,    65,    37,     0,    91,     0,
     106
};

static const yytype_int8 yycheck[] =
{
       8,    64,     3,     4,     5,    19,    68,     0,     3,     4,
       5,     3,    21,    27,    23,     8,     9,    10,    11,    12,
      13,    14,    15,    19,     3,     4,     5,    28,    90,    91,
      25,    27,    17,    33,    34,    35,    36,    37,    38,    55,
      48,   104,    24,    18,    60,    29,    28,    31,    32,    20,
      20,    22,    22,    27,     3,    29,    64,    30,    27,    27,
      29,    29,     3,    27,    72,    29,     6,     7,    31,    32,
       3,     3,     3,     3,    18,    27,     3,    16,    28,     3,
       3,    89,    19,     3,     3,    28,    33,     3,    24,    77,
      28,    33,     5,    28,   102,    53,   104,    -1,    32,    -1,
      29
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    44,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    45,    46,    47,    48,    49,    50,    51,    54,    55,
      56,    58,    66,    67,    20,    22,    21,    23,    20,    22,
       3,    17,     3,     4,     5,    25,    59,    60,    63,    18,
       3,    30,     3,     3,     3,     3,     3,    18,    27,     3,
      16,    28,    24,    28,     3,    57,    60,    19,    65,     3,
      68,     3,    52,    53,    28,    57,    27,    65,    28,    60,
      61,    64,    33,    27,    65,     6,     7,    27,    29,    63,
      29,     3,    64,    33,    34,    35,    36,    37,    38,    62,
      31,    32,    60,     3,    28,    53,    29,    24,    29,    60,
      64,    64,    33,     5,    28,    60,    29,    63,    29
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    44,    45,    45,    45,    45,    45,    45,
      45,    46,    47,    48,    49,    50,    50,    50,    50,    50,
      51,    52,    52,    53,    53,    54,    55,    56,    56,    57,
      57,    58,    59,    59,    60,    60,    60,    61,    61,    62,
      62,    62,    62,    62,    62,    63,    63,    64,    64,    64,
      64,    65,    65,    66,    67,    68,    68
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     2,     2,     1,     1,     1,     1,     1,
       6,     1,     3,     5,     2,     3,     2,    10,     7,     1,
       3,     5,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     3,     3,
       3,     0,     2,     4,     5,     3,     5
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 11:
#line 152 "xdsql.y" /* yacc.c:1652  */
    {
    char* dbname = (yyvsp[0].strval);
    create_db(dbname);
}
#line 1427 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 12:
#line 159 "xdsql.y" /* yacc.c:1652  */
    {
    char* dbname = (yyvsp[0].strval);
    drop_db(dbname);
}
#line 1436 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 13:
#line 166 "xdsql.y" /* yacc.c:1652  */
    {
    char* dbname = (yyvsp[0].strval);
    use_db(dbname);
}
#line 1445 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 14:
#line 173 "xdsql.y" /* yacc.c:1652  */
    {
    show_db();
}
#line 1453 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 15:
#line 179 "xdsql.y" /* yacc.c:1652  */
    {
    do_create_table((yyvsp[0].create_table));
}
#line 1461 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 18:
#line 185 "xdsql.y" /* yacc.c:1652  */
    {
    insert_rows((yyvsp[0].insert_record));
}
#line 1469 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 19:
#line 189 "xdsql.y" /* yacc.c:1652  */
    {
    delete_row((yyvsp[0].delete_record));
}
#line 1477 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 20:
#line 195 "xdsql.y" /* yacc.c:1652  */
    {
    // struct CreateTable { /*create语法树根节点*/
    //     char *table; //基本表名称
    //     struct CreateFields *fdef; //字段定义
    // };
    (yyval.create_table) = (CreateTable*) malloc(sizeof(struct CreateTable));
    (yyval.create_table)->table = (yyvsp[-3].strval);
    (yyval.create_table)->fdef = (yyvsp[-1].create_fields);
    // printf_red("Create table with columns\n");
}
#line 1492 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 21:
#line 208 "xdsql.y" /* yacc.c:1652  */
    {
    // struct CreateFields { /*create语句中的字段定义*/
    //     struct CreateField *fdef;
    //     struct CreateFields *next_fdef; //下一字段
    // };
    (yyval.create_fields) = (CreateFields*) malloc(sizeof(struct CreateFields));
    (yyval.create_fields)->fdef = (yyvsp[0].create_field);
    (yyval.create_fields)->next_fdef = NULL;
}
#line 1506 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 22:
#line 218 "xdsql.y" /* yacc.c:1652  */
    {
    CreateFields* fields = (yyvsp[-2].create_fields);

    CreateFields* temp = fields;
    while (temp->next_fdef != NULL) temp = temp->next_fdef;
    CreateFields* next_fields = (CreateFields*) malloc(sizeof(struct CreateFields));
    next_fields->fdef = (yyvsp[0].create_field);
    next_fields->next_fdef = NULL;

    temp->next_fdef = next_fields;

    (yyval.create_fields) = fields;
}
#line 1524 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 23:
#line 234 "xdsql.y" /* yacc.c:1652  */
    {
    // struct CreateField {
    //     char *field; //字段名称
    //     enum TYPE type; //字段类型
    //     int length; //字段长度
    // }
    struct CreateField *tmp = (CreateField*)malloc(sizeof(struct CreateField));
    tmp->field = (yyvsp[-4].strval);
    tmp->type = (yyvsp[-3].intval);
    tmp->length = (yyvsp[-1].dval);
    (yyval.create_field) = tmp;
}
#line 1541 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 24:
#line 247 "xdsql.y" /* yacc.c:1652  */
    {
    struct CreateField *tmp = (CreateField*)malloc(sizeof(struct CreateField));
    tmp->field = (yyvsp[-1].strval);
    tmp->type = (yyvsp[0].intval);
    (yyval.create_field) = tmp;
}
#line 1552 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 25:
#line 256 "xdsql.y" /* yacc.c:1652  */
    {
    drop_table((yyvsp[0].strval));
}
#line 1560 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 26:
#line 262 "xdsql.y" /* yacc.c:1652  */
    {
    show_tables();
}
#line 1568 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 27:
#line 268 "xdsql.y" /* yacc.c:1652  */
    {
    // typedef struct TableMetaData {
    //     char* table_name; //表名称
    //     FieldList* field_list;
    // } TableMetaData;
    // struct InsertRecord{
    //     TableMetaData *table_meta_data;
    //     struct FieldValueList *val_list;
    // };
    (yyval.insert_record) = (InsertRecord*) malloc(sizeof(struct InsertRecord));
    TableMetaData* table_meta_data = (TableMetaData*) malloc(sizeof(TableMetaData));
    table_meta_data->table_name = (yyvsp[-7].strval);
    table_meta_data->field_list = (yyvsp[-5].field_list);
    (yyval.insert_record)->table_meta_data = table_meta_data;
    (yyval.insert_record)->val_list = (yyvsp[-1].filed_value_list);
}
#line 1589 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 28:
#line 285 "xdsql.y" /* yacc.c:1652  */
    {
    (yyval.insert_record) = (InsertRecord*) malloc(sizeof(struct InsertRecord));
    TableMetaData* table_meta_data = (TableMetaData*) malloc(sizeof(TableMetaData));
    table_meta_data->table_name = (yyvsp[-4].strval);
    table_meta_data->field_list = NULL;
    (yyval.insert_record)->table_meta_data = table_meta_data;
    (yyval.insert_record)->val_list = (yyvsp[-1].filed_value_list);
}
#line 1602 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 29:
#line 296 "xdsql.y" /* yacc.c:1652  */
    {
    // typedef struct FieldList {
    //     char* field_name;
    //     struct FieldList* next;
    // } FieldList;
    (yyval.field_list) = (struct FieldList*) malloc(sizeof(FieldList));
    (yyval.field_list)->field_name = (yyvsp[0].strval);
    (yyval.field_list)->next = NULL;
}
#line 1616 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 30:
#line 306 "xdsql.y" /* yacc.c:1652  */
    {
    FieldList* list = (yyvsp[-2].field_list);
    FieldList* tmp = list;
	while (tmp->next != NULL) tmp = tmp->next;
	struct FieldList* next_field = (struct FieldList*) malloc(sizeof(FieldList));
	next_field->field_name = (yyvsp[0].strval);
	next_field->next = NULL;
	tmp->next = next_field;
	(yyval.field_list) = list;
}
#line 1631 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 31:
#line 319 "xdsql.y" /* yacc.c:1652  */
    {
                printf_red("Select from with columns\n");
            }
#line 1639 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 34:
#line 329 "xdsql.y" /* yacc.c:1652  */
    {
    Expr* _expr = (Expr*) malloc(sizeof(Expr));
    _expr->type = 1;
    _expr->intval = (yyvsp[0].dval);
    (yyval._expr) = _expr;
}
#line 1650 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 35:
#line 336 "xdsql.y" /* yacc.c:1652  */
    {
    Expr* _expr = (Expr*) malloc(sizeof(Expr));
    _expr->type = 0;
    _expr->strval = (yyvsp[0].strval);
    (yyval._expr) = _expr;
}
#line 1661 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 36:
#line 343 "xdsql.y" /* yacc.c:1652  */
    {
    Expr* _expr = (Expr*) malloc(sizeof(Expr));
    _expr->type = 2;
    _expr->strval = (yyvsp[0].strval);
    (yyval._expr) = _expr;
}
#line 1672 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 37:
#line 351 "xdsql.y" /* yacc.c:1652  */
    {
    (yyval._expr) = (yyvsp[0]._expr);
}
#line 1680 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 38:
#line 355 "xdsql.y" /* yacc.c:1652  */
    {
    (yyval._expr) = (Expr*) malloc(sizeof(Expr));
    (yyval._expr)->left = (yyvsp[-2]._expr);
    (yyval._expr)->type = (yyvsp[-1].intval);
    (yyval._expr)->right = (yyvsp[0]._expr);
}
#line 1691 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 39:
#line 363 "xdsql.y" /* yacc.c:1652  */
    { (yyval.intval) = (yyvsp[0].intval); }
#line 1697 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 40:
#line 364 "xdsql.y" /* yacc.c:1652  */
    { (yyval.intval) = (yyvsp[0].intval); }
#line 1703 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 41:
#line 365 "xdsql.y" /* yacc.c:1652  */
    { (yyval.intval) = (yyvsp[0].intval); }
#line 1709 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 42:
#line 366 "xdsql.y" /* yacc.c:1652  */
    { (yyval.intval) = (yyvsp[0].intval); }
#line 1715 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 43:
#line 367 "xdsql.y" /* yacc.c:1652  */
    { (yyval.intval) = (yyvsp[0].intval); }
#line 1721 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 44:
#line 368 "xdsql.y" /* yacc.c:1652  */
    { (yyval.intval) = (yyvsp[0].intval); }
#line 1727 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 45:
#line 371 "xdsql.y" /* yacc.c:1652  */
    {
    // typedef struct FieldValueList {
    //     Expr* expr;
    //     struct FieldValueList* next;
    // } FieldValueList;
    FieldValueList* value_list = (FieldValueList*) malloc(sizeof(FieldValueList));
    value_list->expr = (yyvsp[0]._expr);
    value_list->next = NULL;
    (yyval.filed_value_list) = value_list;
}
#line 1742 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 46:
#line 382 "xdsql.y" /* yacc.c:1652  */
    {
    FieldValueList* value_list = (yyvsp[-2].filed_value_list);
    FieldValueList* temp = value_list;
    while (temp->next != NULL) temp = temp->next;
    FieldValueList* next_value = (FieldValueList*) malloc(sizeof(FieldValueList));
    next_value->expr = (yyvsp[0]._expr);
    next_value->next = NULL;
    temp->next = next_value;
    (yyval.filed_value_list) = value_list;
}
#line 1757 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 47:
#line 395 "xdsql.y" /* yacc.c:1652  */
    {
    (yyval._expr) = (yyvsp[0]._expr);
}
#line 1765 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 48:
#line 399 "xdsql.y" /* yacc.c:1652  */
    {
    (yyval._expr) = (Expr*)malloc(sizeof(Expr));
    (yyval._expr)->left = (yyvsp[-2]._expr);
    (yyval._expr)->type = (yyvsp[-1].intval);
    (yyval._expr)->right = (yyvsp[0]._expr);
}
#line 1776 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 49:
#line 406 "xdsql.y" /* yacc.c:1652  */
    {
    (yyval._expr) = (Expr*)malloc(sizeof(Expr));
    (yyval._expr)->left = (yyvsp[-2]._expr);
    (yyval._expr)->type = (yyvsp[-1].intval);
    (yyval._expr)->right = (yyvsp[0]._expr);
}
#line 1787 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 50:
#line 413 "xdsql.y" /* yacc.c:1652  */
    {
    (yyval._expr) = (yyvsp[-1]._expr);
}
#line 1795 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 51:
#line 419 "xdsql.y" /* yacc.c:1652  */
    {
    (yyval._expr) = NULL;
}
#line 1803 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 52:
#line 423 "xdsql.y" /* yacc.c:1652  */
    {
    (yyval._expr) = (yyvsp[0]._expr);
}
#line 1811 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 53:
#line 429 "xdsql.y" /* yacc.c:1652  */
    {
    (yyval.delete_record) = (DeleteRecord*) malloc(sizeof(DeleteRecord));
    (yyval.delete_record)->table_name = (yyvsp[-1].strval);
    (yyval.delete_record)->where_case = (yyvsp[0]._expr);
}
#line 1821 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;

  case 54:
#line 437 "xdsql.y" /* yacc.c:1652  */
    {
                printf_red("Update table with values\n");
            }
#line 1829 "xdsql.tab.cpp" /* yacc.c:1652  */
    break;


#line 1833 "xdsql.tab.cpp" /* yacc.c:1652  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 446 "xdsql.y" /* yacc.c:1918  */

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
