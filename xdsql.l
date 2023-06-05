%{
# include "xdsql.tab.h"
extern int yyerror(const char *, ...);
%}

/* declarations section */
letter	[a-zA-Z]
digit	[0-9]
digits	{digit}+
optional_fraction	("."{digits})?
optional_exponent	(E[+-]?{digits})?
identifier ({letter}|_)(({letter}|{digit}|_)*)
string '([^']*)'
create create
database database
show show
databases databases
drop drop
use use
table table
tables tables
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
										// printf("识别CREATE\n");
										return CREATE;
									}
{database}				{
										// printf("识别DATABASE\n");
										return DATABASE;
									}
{show}						{
										// printf("识别SHOW\n");
										return SHOW;
									}
{databases}				{
										// printf("识别DATABASES\n");
										return DATABASES;
									}
{drop}						{
										// printf("识别DROP\n");
										return DROP;
									}
{use}							{
										// printf("识别USE\n");
										return USE;
									}
{table}						{
										// printf("识别TABLE\n");
										return TABLE;
									}
{tables}						{
										// printf("识别TABLES\n");
										return TABLES;
									}
{insert}					{
										// printf("识别INSERT\n");
										return INSERT;
									}
{into}						{
										// printf("识别INTO\n");
										return INTO;
									}
{values}					{
										// printf("识别VALUES\n");
										return VALUES;
									}
{select}					{
										printf("识别SELECT\n");
										return SELECT;
									}
{from}						{
										printf("识别FROM\n");
										return FROM;
									}
{where}						{
										printf("识别WHERE\n");
										return WHERE;
									}
{and}							{
										printf("识别AND\n");
										return AND;
									}
{or}							{
										printf("识别OR\n");
										return OR;
									}
{not}							{
										printf("识别NOT\n");
										return NOT;
									}
{delete}					{
										printf("识别DELETE\n");
										return DELETE;
									}
{update}					{
										printf("识别UPDATE\n");
										return UPDATE;
									}
{set}							{
										printf("识别SET\n");
										return SET;
									}
{char} {
	// printf("识别CHAR\n");
	yylval.intval = 0;
	return CHAR;
}
{int} {
	// printf("识别INT\n");
	yylval.intval = 1;
	return INT;
}

"," {
	// printf("识别逗号\n");
	return COMMA;
}
"(" {
	// printf("识别左括号\n");
	return LPAREN;
}
")" {
	// printf("识别右括号\n");
	return RPAREN;
}
";" {
	// printf("识别分号\n");
	return SEMICOLON;
}
">" { printf("识别大于号\n"); return MORE; }
"<" { printf("识别小于号\n"); return LESS; }
"=" { printf("识别等于号\n"); return EQUAL; }
"!=" { printf("识别不等于号\n"); return NOT_EQUAL; }
"'" { printf("识别单引号\n"); return SINGLE_QUOTE; }
"#" { printf("识别#\n"); return SELECT_ALL; }


{identifier} {
	yylval.strval = strdup(yytext);
	// printf("识别标识符%s：长度为%d\n", yytext, yyleng);
	return IDENTIFIER;
}

{string} {
	yylval.strval = strdup(yytext);
	yylval.strval=(char *)(yylval.strval+1);
	yylval.strval[strlen(yylval.strval)-1]='\0';
	// printf("识别字符串%s：长度为%d\n", yytext, yyleng);
	return STRING;
}

{digits}{optional_fraction}{optional_exponent}  {
	yylval.dval = atof(yytext);
	// printf("识别数字%s\n", yytext);
	return NUMBER;
}

[ \t\n] ; /* 匹配空格、制表符、换行符等空白字符 */

%%
