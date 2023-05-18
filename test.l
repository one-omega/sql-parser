%{
#include <stdio.h>
#include <stdlib.h>

/* declarations section */

/* 记号类别 */
#define CREATE 1
#define TABLE 2
#define INT 3
#define CHAR 4
#define FLOAT 5
#define COMMA 6
#define LPAREN 7
#define RPAREN 8
#define SEMICOLON 9
#define ID 12
#define NUMBER 13
%}

/* 正则表达式 */
digit	[0-9]
digits {digit}+(\.{digit}+)?([Ee][-+]?{digit}+)?
letter	[a-zA-Z]
identifier ({letter}|_)(({letter}|{digit}|_)*) 

%%

"/".?"/" ; /* 匹配注释 */

"//".* ; /* 匹配单行注释 */

"create" {
    printf("识别关键字 CREATE\n");
    return CREATE;
}

"table" {
    printf("识别关键字 TABLE\n");
    return TABLE;
}

"int" {
    printf("识别关键字 INT\n");
    return INT;
}

"char" { printf("识别关键字 CHAR\n"); return CHAR; }

"float" { printf("识别关键字 FLOAT\n"); return FLOAT; }

"," { printf("识别逗号\n"); return COMMA; }
"(" { printf("识别左括号\n"); return LPAREN; }
")" { printf("识别右括号\n"); return RPAREN; }
";" { printf("识别分号\n"); return SEMICOLON; }

{identifier} { printf("识别标识符 %s\n", yytext); return ID; } /* 匹配标识符 */

{digits} { printf("识别数字 %s\n", yytext); return NUMBER; } /* 匹配数字 */

[ \t\n] ; /* 匹配空格、制表符、换行符等空白字符 */

%%

/////////////////////////////////////////////////////////////////////////////
// programs section

int main(void)
{
	printf("词法分析成功，返回记号类别为%d\n", yylex());
	return 0;
}
