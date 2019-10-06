%{
#include "stdio.h"
#include "string.h"

void analyse(int flag);
int main();

struct token{
	char *type;
	char *name;
}entity[1024];
char infile[32];
char *outfile;
int rownum=1;
int colnum=1;//({digit}+){letter}({letter}|{digit})*
int cnt=0;
FILE *fin;
FILE *fout;
%}

digit		[0-9]
letter		[a-zA-Z]
number		{digit}+
identifier	{letter}({letter}|{digit})*
wrong_1		([^\t\n\f\v\r ]*)([_?$&#@\`]+)({letter}|{digit})*
wrong_2		({digit}+){letter}({letter}|{digit})*
wrong_3		({digit}+)([.]+)({digit}+)
newline		[\n\r]
whitespace	[\t\v ]

%%
"procedure" |
"call"  |
"begin"  |
"end"  |
"var"  |
"const"  |
"if"  |
"then"  |
"while"  |
"do"  |
"read"  |
"write"  |
"odd"    |
"for"   {analyse(1);}

{identifier}	{analyse(2);}

{number}		{analyse(3);}

"+"|"-"|"*"|"/"|"#"|"<"|">"|"="	{analyse(4);}
"<>"	{analyse(4);}
"!="	{analyse(4);}
">="	{analyse(4);}
"<="	{analyse(4);}
":="	{analyse(4);}

"("		{analyse(5);}
")"		{analyse(5);}
","		{analyse(5);}
":"		{analyse(5);}
";"		{analyse(5);}
"."		{analyse(5);}

{whitespace}		{analyse(6);}
{wrong_1}|{wrong_2}|{wrong_3}	{analyse(6);}

{newline}	{rownum+=1; colnum=1;}
%%

int yywrap(){
	fclose(fin);
	return 1;
}

void analyse(int flag){
	if(flag == 1){
		entity[cnt].type = "K";
	}else if(flag == 2){
		if(yyleng >= 11){
			entity[cnt].type = "T";
		}else{
			entity[cnt].type = "I";
		}
	}else if(flag == 3){
		if(yyleng >= 15){
			entity[cnt].type = "T";
		}else{
			entity[cnt].type = "C";
		}
	}else if(flag == 4){
		entity[cnt].type = "O";
	}else if(flag == 5){
		entity[cnt].type = "D";
	}else{
		entity[cnt].type = "T";
	}
	entity[cnt].name = yytext;
	fprintf(fout, "\"%s\" :\t%s,\t<%2d,%2d> \n", entity[cnt].name, entity[cnt].type, rownum, colnum);
	colnum += yyleng;
	cnt += 1;
}

int main(){
	printf("Please enter file's name:\n");
	scanf("%s", infile);
	outfile = "result.txt";
	fin = fopen(infile, "r");
	if(fin == NULL){
		printf("Cannot open the in file \n");
		return 0;
	}
	fout = fopen(outfile, "w");
	if(fout == NULL){
		printf("Cannot open the out file \n");
		return 0;
	}

	yyin = fin;
	yylex();

	fclose(fout);
	printf("Finish!\n");
	return 0;
}