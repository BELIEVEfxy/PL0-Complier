%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse.tab.h"

%}

keyword (if)|(do)|(end)|(var)|(odd)|(then)|(read)|(call)|(while)|(begin)|(break)|(const)|(write)|(procedure)|(for)|(to)|(downto)
num [1-9][0-9]*|[0-9]
identifier [a-zA-Z_][a-zA-Z0-9_]*
wrong_id [0-9][a-z0-9A-Z]*
delimiters ;|,|:|\(|\)|\.
operator (\+)|(-)|(\*)|(\/)|(:=)|(>)|(<)|(>=)|(<=)|(=)|(#)
notes   (\/\/).*(\n)
newline [\n\r]
%%

{keyword} {
        if(strcmp(yytext,"if") == 0){return IF;}
        else if(strcmp(yytext,"do") == 0){return DO;}
        else if(strcmp(yytext,"end") == 0){return ENDD;}
        else if(strcmp(yytext,"var") == 0){return VAR;}
        else if(strcmp(yytext,"odd") == 0){return ODD;}
        else if(strcmp(yytext,"then") == 0){return THEN;}
        else if(strcmp(yytext,"read") == 0){return READ;}
        else if(strcmp(yytext,"call") == 0){return CALL;}
        else if(strcmp(yytext,"while") == 0){return WHILE;}
        else if(strcmp(yytext,"begin") == 0){return BEG;}
        else if(strcmp(yytext,"break") == 0){return BREAK;}
        else if(strcmp(yytext,"const") == 0){return CONST;}
        else if(strcmp(yytext,"write") == 0){return WRITE;}
        else if(strcmp(yytext,"procedure") == 0){return PROCEDURE;}
        else if(strcmp(yytext,"for") == 0){return FOR;}
        else if(strcmp(yytext,"to") == 0){return TO;}
       
    }
{num} {
    yylval.number = atoi(yytext);
    return NUM;
}
{identifier} {
    yylval.str =  strdup(yytext);
    return ID;
}
{wrong_id} {
    yylval.str = strdup(yytext);
    return WRONGID;
}
{delimiters} {
    yylval.str = strdup(yytext);
    if(strcmp(yytext,";") == 0){return SEMICOLON;}
    else if(strcmp(yytext,",") == 0){return COMMA;}
    else if(strcmp(yytext,":") == 0){return COLON;}
    else if(strcmp(yytext,"(") == 0){return LPARAN;}
    else if(strcmp(yytext,")") == 0){return RPARAN;}
    else if(strcmp(yytext,".") == 0){return EOP;}
}
{operator} {
    yylval.str = strdup(yytext);
    if(strcmp(yytext,"+") == 0){return PLUS;}
    else if(strcmp(yytext,"-") == 0){return MINUS;}
    else if(strcmp(yytext,"*") == 0){return MULTIPLY;}
    else if(strcmp(yytext,"/") == 0){return DIVISION;}
    else if(strcmp(yytext,":=") == 0){return ASSIGN;}
    else if(strcmp(yytext,">") == 0){return GREAT;}
    else if(strcmp(yytext,"<") == 0){return LESS;}
    else if(strcmp(yytext,">=") == 0){return GE;}
    else if(strcmp(yytext,"<=") == 0){return LE;}
    else if(strcmp(yytext,"=") == 0){return EQ;}
    else if(strcmp(yytext,"#") == 0){return NEQ;}
}
{notes} {
    /* empty */
}
{newline} {
    /* empty */
}

%%
