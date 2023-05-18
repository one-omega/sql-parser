%{
//记号类别
#define ID 0
#define NUMBER 1
#define CREATE 2
#define DATABASE 3
#define SHOW 4
#define DATABASES 5
#define DROP 6
#define USE 7
#define TABLE 8
#define INSERT 9
#define INTO 10
#define VALUES 11
#define SELECT 12
#define FROM 13
#define WHERE 14
#define AND 15
#define OR 16
#define NOT 17
#define DELETE 18
#define UPDATE 19
#define SET 20
#define CHAR 21
#define INT 22

// 符号 1xx
#define COMMA 100
#define LPAREN 101
#define RPAREN 102
#define SEMICOLON 103
#define MORE 104
#define LESS 105
#define ERUAL 106
#define NOT_ERUAL 107
#define STAR 108
#define SINGLE_QUOTE 109
%}

/* declarations section */
letter	[a-zA-Z]
digit	[0-9]
digits	{digit}+
optional_fraction	("."{digits})?
optional_exponent	(E[+-]?{digits})?
identifier ({letter}|_)(({letter}|{digit}|_)*) 
create create
database database
show show
databases databases
drop drop
use use
table table
insert insert
into into
values values
select select
from from
where where
and and
or or
not not
delete delete
update update
set set
char char
int int

/* place any declarations here */

%%

{create}					{
										printf("识别CREATE");
										return CREATE;
									}
{database}				{
										printf("识别DATABASE");
										return DATABASE;
									}
{show}						{
										printf("识别SHOW");
										return SHOW;
									}
{databases}				{
										printf("识别DATABASES");
										return DATABASES;
									}
{drop}						{
										printf("识别DROP");
										return DROP;
									}
{use}							{
										printf("识别USE");
										return USE;
									}
{table}						{
										printf("识别TABLE");
										return TABLE;
									}
{insert}					{
										printf("识别INSERT");
										return INSERT;
									}
{into}						{
										printf("识别INTO");
										return INTO;
									}
{values}					{
										printf("识别VALUES");
										return VALUES;
									}
{select}					{
										printf("识别SELECT");
										return SELECT;
									}
{from}						{
										printf("识别FROM");
										return FROM;
									}
{where}						{
										printf("识别WHERE");
										return WHERE;
									}
{and}							{
										printf("识别AND");
										return AND;
									}
{or}							{
										printf("识别OR");
										return OR;
									}
{not}							{
										printf("识别NOT");
										return NOT;
									}
{delete}					{
										printf("识别DELETE");
										return DELETE;
									}
{update}					{
										printf("识别UPDATE");
										return UPDATE;
									}
{set}							{
										printf("识别SET");
										return SET;
									}
{char}						{
										printf("识别CHAR");
										return CHAR;
									}
{int}							{
										printf("识别INT");
										return INT;
									}

"," { printf("识别逗号\n"); return COMMA; }
"(" { printf("识别左括号\n"); return LPAREN; }
")" { printf("识别右括号\n"); return RPAREN; }
";" { printf("识别分号\n"); return SEMICOLON; }
">" { printf("识别大于号\n"); return MORE; }
"<" { printf("识别小于号\n"); return LESS; }
"=" { printf("识别等于号\n"); return ERUAL; }
"!=" { printf("识别不等于号\n"); return NOT_ERUAL; }
"*" { printf("识别星号\n"); return STAR; }
"'" { printf("识别单引号\n"); return SINGLE_QUOTE; }


{identifier}                                    {
                                                    printf("识别标识符%s：长度为%d\n", yytext, yyleng);
                                                    return ID;
                                                }

{digits}{optional_fraction}{optional_exponent}  {
                                                    printf("识别数字%s：长度为%d\n", yytext, yyleng);
                                                    return NUMBER;
                                                }

[ \t\n] ; /* 匹配空格、制表符、换行符等空白字符 */

%%

// programs section

int main(void)
{
    printf("词法分析成功，返回记号类别为%d\n", yylex());
    return 0;
}
