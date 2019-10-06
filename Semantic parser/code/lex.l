%{
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "userdef.h"
#include "parse.tab.h"
extern varIndex strMem[256];  
extern int iMaxIndex; 
extern int iCurIndex; 
extern int code_line;
extern int error_cnt;
void add_var(char *mask);
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

[" "]+  {}
[\t]+   {}
[\n]+   {
	code_line += yyleng;   //换行标识符，line的个数加一
	}
{keyword} {
        if(strcmp(yytext,"if") == 0){return IF;}
        else if(strcmp(yytext,"do") == 0){return DO;}
        else if(strcmp(yytext,"end") == 0){return END;}
        else if(strcmp(yytext,"var") == 0){return VAR;}
        else if(strcmp(yytext,"odd") == 0){return ODD;}
        else if(strcmp(yytext,"then") == 0){return THEN;}
        else if(strcmp(yytext,"read") == 0){return READ;}
        else if(strcmp(yytext,"call") == 0){return CALL;}
        else if(strcmp(yytext,"while") == 0){return WHILE;}
        else if(strcmp(yytext,"begin") == 0){return BEGINN;}
        else if(strcmp(yytext,"const") == 0){return CONST;}
        else if(strcmp(yytext,"write") == 0){return WRITE;}
        else if(strcmp(yytext,"procedure") == 0){return PROCEDURE;}
        else if(strcmp(yytext,"for") == 0){return FOR;}
        else if(strcmp(yytext,"to") == 0){return TO;}
        else if(strcmp(yytext,"downto") == 0){return DOWNTO;}
        }

{identifier} {
        add_var(yytext);
        yylval = iCurIndex;
        return IDENTIFIER;
}

{num} {
        yylval = atoi(yytext);
        return NUMBER;
}


:=      {  //以下定义特殊符号
        yylval = *yytext;
        return ASSIGNMENT;
	}

\<=     {
        yylval = *yytext;
        return *yytext;
	}
\>      {
        yylval = *yytext;
        return *yytext;
	}
\>=     {
        yylval = *yytext;
        return *yytext;
	}

[+]     {
        yylval = *yytext;
        return *yytext;
	}
[-]     {
        yylval = *yytext;
        return *yytext;
	}
[*]     {
        yylval = *yytext;
        return *yytext;
	}
[/]     {
        yylval = *yytext;
        return *yytext;
	}

[=]     {
        yylval = *yytext;
        return *yytext;
	}
[#]     {	
        yylval = *yytext;
        return *yytext;
	}
[<]     {
        yylval = *yytext;
        return *yytext;
	}

[,]     {
        yylval = *yytext;
        return *yytext;
	}
[.]     {
        yylval = *yytext;
        return *yytext;
	}
[;]     {
        yylval = *yytext;
        return *yytext;
	}
[(]     {	
        yylval = *yytext;
        return *yytext;
	}
[)]     {
        yylval = *yytext;
        return *yytext;
	}


[0-9]+ {
	printf("error in line %d , wrong number.\n", code_line);	
        exit(1);
	}
[0-9a-zA-Z]+ {
	printf("error in line %d , wrong id.\n", code_line);
        exit(1);	
	}
{notes} {
    /* empty */
}

%%
/*把ID添加到strMem中，结构体，包含标识符本身和数值*/
void add_var(char *mask){   
    if(iMaxIndex == 0){
        strcpy(strMem[0].sMark,mask);
        iMaxIndex++;
        iCurIndex = 0;
        return;
    }
    for(int i=0;i<=iMaxIndex-1;i++) {
        if(strcmp(strMem[i].sMark,mask)==0) {
            iCurIndex=i;
            return;
        }
    }
    strcpy(strMem[iMaxIndex].sMark,mask);
    iCurIndex = iMaxIndex;
    iMaxIndex ++;

}



