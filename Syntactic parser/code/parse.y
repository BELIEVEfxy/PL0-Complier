/* $Id$ -*- mode: c -*- */
/* -*- Whitycatty -*- */

%{ /*** C/C++ Declarations ***/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

/* define max stack size */
#define STACK_MAXN 1024000
/* define max identifier size */
#define ID_MAX_SIZE 102400
/* define max type */
#define TYPE_MAXN 1024

/* stack for node 
********************
* struct node:
* @para int_32 type : type of the node 
* @para int_32 val : int value of the node
* @para char*  id  : string value of the node
* @para int_32 childcnt : child amound
* @para node** child : child node
********************
*/
char infile[32];
char *outfile;
FILE *fin;
FILE *fout;
extern FILE * yyin;
extern FILE * yyout;

Node* stack[STACK_MAXN+1];

/* top of the stack */
int stop;

/* child_type array and cnt for parameter pass */
int child_tp[TYPE_MAXN];
int child_tp_cnt;

/* function for stack */
void push( Node* );
void pop();
void freenode(Node*);
int empty();
Node* top();

/* function for print */
void print_node( Node*, int );
void show_child(Node*);

/* void shift 
* add a new node to the stack
* @para type: new node type.
* @para id: string value of new node.
* @para number: int_32 value of new node.
*/
void shift(int type,char* id,int number);

/* void reduce
* release the node in the stack to form the new node.
* @para type: new node type.
* @para child_type_cnt: amount of child types. type see header.h
* @para child_type[]: type array.
* this function find the new node's child and pop them from the stack
* and push the new node into it.
*/
void reduce(int type, int child_type_cnt, int child_type[TYPE_MAXN]);

/* utils function */
void node_copy(Node* copy,Node* copied);
int inarray(int tp,int tpcnt, int tparray[TYPE_MAXN]);
int yylex();
/* redefine yyerror */
void yyerror(const char *str)
{
        fprintf(stderr,"error: %s\n",str);
}

%}

/* start symbol is named "start" */
%start program

 /*** BEGIN EXAMPLE - Change the example grammars tokens below ***/

%union{
    int number;
    char* str;
}

%token <str> IF         "if"
%token <str> DO         "do"
%token <str> ENDD       "end"
%token <str> VAR        "var"
%token <str> ODD        "odd"
%token <str> THEN       "then"
%token <str> READ       "read"
%token <str> CALL       "call"
%token <str> WHILE      "while"
%token <str> BEG        "begin"
%token <str> BREAK      "break"
%token <str> CONST      "const"
%token <str> WRITE      "write"
%token <str> PROCEDURE  "procedure"
%token <str> FOR        "for"
%token <str> TO         "to"

%token <str> ID         "id"
%token <number> NUM     "number"
%token <str> WRONGID    "wrong_id"

%token <str> SEMICOLON  ";"
%token <str> COMMA      ","
%token <str> EOP        "."
%token <str> COLON      ":"
%token <str> LPARAN     "("
%token <str> RPARAN     ")"
%token <str> PLUS       "+"
%token <str> MINUS      "-"
%token <str> MULTIPLY   "*"
%token <str> DIVISION   "/"
%token <str> ASSIGN     ":="
%token <str> GREAT      ">"
%token <str> LESS       "<"
%token <str> GE         ">="
%token <str> LE         "<="
%token <str> EQ         "="
%token <str> NEQ        "#"

%token      END    0    "end of file"

%left PLUS MINUS
%left MULTIPLY DIVISION
%%

program :   subprogram "."  {shift(EOP_OP, ".", 0);}
            END             {
                            child_tp_cnt = 2;
                            child_tp[0] = SUBPROGRAM;
                            child_tp[1] = EOP_OP;
                            reduce(PROGRAM, child_tp_cnt, child_tp);
                            fprintf(fout, "program -> subprogram.\n");
                            }
    ;

subprogram : constInstruction variableInstruction procedureInstruction sentence { 
                                                                                child_tp_cnt = 4;
                                                                                child_tp[0] = CONST_INSTRUCTION;
                                                                                child_tp[1] = VARIABLE_INSTRUCTION;
                                                                                child_tp[2] = PROCEDURE_INSTRUCTION;
                                                                                child_tp[3] = SENTENCE;
                                                                                reduce(SUBPROGRAM, child_tp_cnt, child_tp);
                                                                                fprintf(fout, "subprogram -> constInstruction variableInstruction procedureInstruction sentence\n");
                                                                                }
    ;

constInstruction :  "const"                 {shift(CONST_KEY,$1,0);}
                    constDeclaration ";"    {
                                            shift(SEMI_OP,";",0);
                                            child_tp_cnt = 3; 
                                            child_tp[0] = CONST_KEY;
                                            child_tp[1] = CONST_DECLARATION; 
                                            child_tp[2] = SEMI_OP;
                                            reduce(CONST_INSTRUCTION,child_tp_cnt,child_tp);
                                            fprintf(fout, "constInstruction -> CONST constDeclaration;\n");
                                            }
                    | /* empty */    
    ;

constDeclaration :  "id"        
                    "="         
                    "number"    {
                                shift(IDENTI, $1, 0);
                                shift(EQ_OP, "=", 0);
                                shift(NUMBER, NULL,$3);
                                child_tp_cnt = 3; 
                                child_tp[0]=IDENTI;
                                child_tp[1]=EQ_OP;
                                child_tp[2]=NUMBER; 
                                reduce(CONST_DECLARATION, child_tp_cnt, child_tp);
                                fprintf(fout, "constDeclaration -> ID = NUMBER\n");
                                }
                |   "id"                 
                    "="                 
                    "number"            {
                                        shift(IDENTI, $1, 0);
                                        shift(EQ_OP, "=", 0);
                                        shift(NUMBER, NULL,$3);
                                        }
                    ","                 {shift(COMMA_OP, ",", 0);}
                    constDeclaration    {
                                        child_tp_cnt = 5;
                                        child_tp[0] = IDENTI;
                                        child_tp[1] = EQ_OP;
                                        child_tp[2] = NUMBER;
                                        child_tp[3] = COMMA_OP;
                                        child_tp[4] = CONST_DECLARATION;
                                        reduce(CONST_DECLARATION, child_tp_cnt, child_tp);
                                        fprintf(fout, "constDeclaration -> ID = NUMBER , constDeclaration\n");
                                        }
    ;

variableInstruction :   "var"                       
                        "id"                        {shift(VAR_KEY,$1,0);shift(IDENTI,$2,0);}
                        variableInstructionSuf ";"  {
                                                    shift(SEMI_OP,";",0);
                                                    child_tp_cnt = 4; 
                                                    child_tp[0] = VAR_KEY;
                                                    child_tp[1] = IDENTI;
                                                    child_tp[2] = VARIABLE_INSTRUCTIONSUF;
                                                    child_tp[3] = SEMI_OP; 
                                                    reduce(VARIABLE_INSTRUCTION,child_tp_cnt,child_tp);
                                                    fprintf(fout, "variableInstruction -> VAR ID variableInstructionSuf ;\n");
                                                    }
                    |  /* empty */                         
    ;

variableInstructionSuf :    ","                         
                            "id"                    {shift(COMMA_OP, ",", 0);shift(IDENTI,$2,0);}
                            variableInstructionSuf  {
                                                    child_tp_cnt = 3;
                                                    child_tp[0] = COMMA_OP;
                                                    child_tp[1] = IDENTI;
                                                    child_tp[2] = VARIABLE_INSTRUCTIONSUF;
                                                    reduce(VARIABLE_INSTRUCTIONSUF, child_tp_cnt, child_tp);
                                                    fprintf(fout, "variableInstructionSuf -> , ID variableInstructionSuf \n");
                                                    }
                            | /* empty */   
    ;

procedureInstruction :   procedureHeader subprogram {
                                                    child_tp_cnt = 2; 
                                                    child_tp[0] = PROCEDURE_HEADER; 
                                                    child_tp[1] = SUBPROGRAM; 
                                                    reduce(PROCEDURE_INSTRUCTION,child_tp_cnt,child_tp);
                                                    }
                        ";" procedureInstruction    {fprintf(fout, "procedureInstruction -> procedureHeader subprogram ; procedureInstruction\n");}
                        |  /* empty */ 
    ;

procedureHeader : "procedure" "id" ";"  {
                                        shift(PROCEDURE_KEY,$1,0);
                                        shift(IDENTI,$2,0);
                                        shift(SEMI_OP,";",0);
                                        child_tp_cnt = 3;
                                        child_tp[0] = PROCEDURE_KEY;
                                        child_tp[1] = IDENTI;
                                        child_tp[2] = SEMI_OP;
                                        reduce(PROCEDURE_HEADER,child_tp_cnt,child_tp);
                                        fprintf(fout, "procedureHeader -> PROCEDURE ID ;\n");
                                        }
    ;

sentence : unemptysentence  {
                            child_tp_cnt = 1;
                            child_tp[0] = UNEMPTY_SENTENCE;
                            reduce(SENTENCE, child_tp_cnt,child_tp);
                            fprintf(fout, "sentence -> unemptysentence\n");
                            }
         | emptysentence    { }
    ;

unemptysentence : assignment    {
                                child_tp_cnt = 1;
                                child_tp[0] = ASSIGNMENT;
                                reduce(UNEMPTY_SENTENCE, child_tp_cnt, child_tp);
                                fprintf(fout, "unemptysentence -> assignment\n");
                                }
            | compound          {
                                child_tp_cnt = 1;
                                child_tp[0] = COMPOUND;
                                reduce(UNEMPTY_SENTENCE, child_tp_cnt, child_tp);
                                fprintf(fout, "unemptysentence -> compound\n");
                                }
            | conditional       {
                                child_tp_cnt = 1;
                                child_tp[0] = CONDITIONAL;
                                reduce(UNEMPTY_SENTENCE, child_tp_cnt, child_tp);
                                fprintf(fout, "unemptysentence -> conditional\n");
                                }
            | whileLoop         {
                                child_tp_cnt = 1;
                                child_tp[0] = WHILELOOP;
                                reduce(UNEMPTY_SENTENCE, child_tp_cnt, child_tp);
                                fprintf(fout, "unemptysentence -> whileLoop\n");
                                }
            | forLoop           {
                                child_tp_cnt = 1;
                                child_tp[0] = FORLOOP;
                                reduce(UNEMPTY_SENTENCE, child_tp_cnt, child_tp);
                                fprintf(fout, "unemptysentence -> forLoop\n");
                                }   
            | procedureCall     {
                                child_tp_cnt = 1;
                                child_tp[0] = PROCEDURE_CALL;
                                reduce(UNEMPTY_SENTENCE, child_tp_cnt, child_tp);
                                fprintf(fout, "unemptysentence -> procedureCall\n");
                                }
            | readSent          {
                                child_tp_cnt = 1;
                                child_tp[0] = READ_SENTENCE;
                                reduce(UNEMPTY_SENTENCE, child_tp_cnt, child_tp);
                                fprintf(fout, "unemptysentence -> readSent\n");
                                }
            | writeSent         {
                                child_tp_cnt = 1;
                                child_tp[0] = WRITE_SENTENCE;
                                reduce(UNEMPTY_SENTENCE, child_tp_cnt, child_tp);
                                fprintf(fout, "unemptysentence -> writeSent\n");
                                }
         
    ;

emptysentence :  /* empty */    
    ;

assignment :    "id"    {shift(IDENTI,$1,0);}
                ":="    {shift(ASSIGN_OP,":=",0);}
                expr    { 
                        child_tp_cnt = 3;
                        child_tp[0] = IDENTI;
                        child_tp[1] = ASSIGN_OP;
                        child_tp[2] = EXPRESSION;
                        reduce(ASSIGNMENT, child_tp_cnt, child_tp);
                        fprintf(fout, "assignment -> ID := expr\n");
                        }
    ;

multsentence :  sentence 
                ";"             {
                                child_tp_cnt = 2;
                                child_tp[0] = SENTENCE;
                                child_tp[1] = SEMI_OP;
                                reduce(MULTI_SENTENCE, child_tp_cnt, child_tp);
                                }
                multsentence    {          
                                
                                }
            |   sentence        {
                                child_tp_cnt = 1;
                                child_tp[0] = SENTENCE;
                                reduce(MULTI_SENTENCE, child_tp_cnt, child_tp);
                                
                                }
    ;

compound :  "begin"             {shift(BEGIN_KEY,"begin",0);}
            multsentence "end"  { 
                                shift(END_KEY,"end",0);
                                child_tp_cnt = 3;
                                child_tp[0] = BEGIN_KEY;
                                child_tp[1] = MULTI_SENTENCE;
                                child_tp[2] = END_KEY;
                                reduce(COMPOUND, child_tp_cnt, child_tp);
                                fprintf(fout, "compound -> BEGIN multsentence END\n");
                                }
    ;

conditional : "if"              {shift(IF_KEY,"if",0);} 
              condition "then"  {shift(THEN_KEY,"then",0);} 
              sentence          {
                                child_tp_cnt = 4;
                                child_tp[0] = IF_KEY;
                                child_tp[1] = CONDITION;
                                child_tp[2] = THEN_KEY;
                                child_tp[3] = SENTENCE;
                                reduce(CONDITIONAL, child_tp_cnt, child_tp);
                                fprintf(fout, "conditional -> IF condition THEN sentence\n");
                                }
    ;

condition : expr relationop expr    {
                                    child_tp_cnt = 3;
                                    child_tp[0] = EXPRESSION;
                                    child_tp[1] = RELATION_OPERATOR;
                                    child_tp[2] = EXPRESSION;
                                    reduce(CONDITION, child_tp_cnt, child_tp);
                                    fprintf(fout, "condition -> expr relationop expr\n");
                                    }
            |   "odd"               {shift(ODD_KEY, "odd", 0);}
                expr                {
                                    child_tp_cnt = 2;
                                    child_tp[0] = ODD_KEY;
                                    child_tp[1] = EXPRESSION;
                                    reduce(CONDITION, child_tp_cnt, child_tp);
                                    fprintf(fout, "condition -> ODD expr\n");
                                    }
    ;

expr :  item itemsuf            {
                                child_tp_cnt = 2;
                                child_tp[0] = ITEM;
                                child_tp[1] = ITEM_SUF;
                                reduce(EXPRESSION, child_tp_cnt, child_tp);
                                fprintf(fout, "expr -> item itemsuf\n");
                                }
        | plusop item itemsuf   {
                                child_tp_cnt = 3;
                                child_tp[0] = PLUS_OPERATOR;
                                child_tp[1] = ITEM;
                                child_tp[2] = ITEM_SUF;
                                reduce(EXPRESSION, child_tp_cnt, child_tp);
                                fprintf(fout, "expr -> plusop item itemsuf\n");
                                }
    ;

item : factor factorsuf {
                        child_tp_cnt = 2;
                        child_tp[0] = FACTOR;
                        child_tp[1] = FACTOR_SUFFIX;
                        reduce(ITEM, child_tp_cnt, child_tp);
                        fprintf(fout, "item -> factor factorsuf\n");
                        }
    ;

factor : "id"       {
                    shift(IDENTI, $1, 0);
                    child_tp_cnt = 1;
                    child_tp[0] = IDENTI;
                    reduce(FACTOR, child_tp_cnt, child_tp);
                    fprintf(fout, "factor -> ID\n");
                    }
        | "number"  {
                    shift(NUMBER, NULL, $1);
                    child_tp_cnt = 1;
                    child_tp[0] = NUMBER;
                    reduce(FACTOR, child_tp_cnt, child_tp);
                    fprintf(fout, "factor -> NUMBER\n");
                    }
        | "("       {shift(LEFTPARAN, "(", 0);}
          expr      
          ")"       {
                    shift(RIGHTPARAN, ")", 0);
                    child_tp_cnt = 3;
                    child_tp[0] = LEFTPARAN;
                    child_tp[1] = EXPRESSION;
                    child_tp[2] = RIGHTPARAN;
                    reduce(FACTOR, child_tp_cnt, child_tp);
                    fprintf(fout, "factor -> (expr) \n");
                    }
    ;

itemsuf : plusop item   
          itemsuf       {
                        child_tp_cnt = 3;
                        child_tp[0] = PLUS_OPERATOR;
                        child_tp[1] = ITEM;
                        child_tp[2] = ITEM_SUF;
                        reduce(ITEM_SUF, child_tp_cnt, child_tp);
                        fprintf(fout, "itemsuf -> plusop item itemsuf\n");
                        }
        | /* empty */  
    ;

factorsuf : mulop factor    {
                            child_tp_cnt = 2;
                            child_tp[0] = MULTIPLY_OPERATOR;
                            child_tp[1] = FACTOR;
                            reduce(FACTOR_SUFFIX, child_tp_cnt, child_tp);
                            fprintf(fout, "factorsuf -> mulop factor factorsuf\n");
                            }   
            | /* empty */  
    ;

plusop :    "+"     {
                    shift(PLUS_OP, "+", 0);
                    child_tp_cnt = 1;
                    child_tp[0] = PLUS_OP;
                    reduce(PLUS_OPERATOR, child_tp_cnt, child_tp);
                    fprintf(fout, "relationop -> +\n");
                    }
        |   "-"     {
                    shift(MINUS_OP, "-", 0);
                    child_tp_cnt = 1;
                    child_tp[0] = MINUS_OP;
                    reduce(PLUS_OPERATOR, child_tp_cnt, child_tp);
                    fprintf(fout, "relationop -> -\n");
                    }
    ;

mulop : "*"     {
                shift(MUL_OP, "*", 0);
                child_tp_cnt = 1;
                child_tp[0] = MUL_OP;
                reduce(MULTIPLY_OPERATOR, child_tp_cnt, child_tp);
                fprintf(fout, "relationop -> *\n");
                }
        | "/"   {
                shift(DIV_OP, "*", 0);
                child_tp_cnt = 1;
                child_tp[0] = DIV_OP;
                reduce(MULTIPLY_OPERATOR, child_tp_cnt, child_tp);
                fprintf(fout, "relationop -> /\n");
                }
    ;

relationop : "="    {
                    shift(EQ_OP, "=", 0);
                    child_tp_cnt = 1;
                    child_tp[0] = EQ_OP;
                    reduce(RELATION_OPERATOR, child_tp_cnt, child_tp);
                    fprintf(fout, "relationop -> =\n");
                    }
            | "#"   {
                    shift(UEQ_OP, "#", 0);
                    child_tp_cnt = 1;
                    child_tp[0] = UEQ_OP;
                    reduce(RELATION_OPERATOR, child_tp_cnt, child_tp);
                    fprintf(fout, "relationop -> #\n");
                    }
            | "<"   {
                    shift(LE_OP, "=", 0);
                    child_tp_cnt = 1;
                    child_tp[0] = LE_OP;
                    reduce(RELATION_OPERATOR, child_tp_cnt, child_tp);
                    fprintf(fout, "relationop -> <\n");
                    }
            | ">"   {
                    shift(GE_OP, "=", 0);
                    child_tp_cnt = 1;
                    child_tp[0] = GE_OP;
                    reduce(RELATION_OPERATOR, child_tp_cnt, child_tp);
                    fprintf(fout, "relationop -> >\n");
                    }
            | ">="  {
                    shift(GEQ_OP, ">=", 0);
                    child_tp_cnt = 1;
                    child_tp[0] = GEQ_OP;
                    reduce(RELATION_OPERATOR, child_tp_cnt, child_tp);
                    fprintf(fout, "relationop -> >=\n");
                    }
            | "<="  {
                    shift(LEQ_OP, "<=", 0);
                    child_tp_cnt = 1;
                    child_tp[0] = LEQ_OP;
                    reduce(RELATION_OPERATOR, child_tp_cnt, child_tp);
                    fprintf(fout, "relationop -> <=\n");
                    }
    ;

whileLoop : "while"     {shift(WHILE_KEY,"while",0);}
            condition 
            "do"        {shift(DO_KEY,"do",0);}
            sentence    {
                        child_tp_cnt = 4;
                        child_tp[0] = WHILE_KEY;
                        child_tp[1] = CONDITION;
                        child_tp[2] = DO_KEY;
                        child_tp[3] = SENTENCE;
                        reduce(WHILELOOP, child_tp_cnt, child_tp);
                        fprintf(fout, "whileLoop -> WHILE condition DO sentence\n");
                        }
    ;

forLoop :   "for"       {shift(FOR_KEY,"for",0);}
            assignment  
            "to"        {shift(TO_KEY,"to",0);}
            condition 
            "do"        {shift(DO_KEY,"do",0);}  
            sentence    {
                        child_tp_cnt = 6;
                        child_tp[0] = FOR_KEY;
                        child_tp[1] = ASSIGNMENT;
                        child_tp[2] = TO_KEY;
                        child_tp[3] = CONDITION;
                        child_tp[4] = DO_KEY;
                        child_tp[5] = SENTENCE;
                        reduce(FORLOOP, child_tp_cnt, child_tp);
                        fprintf(fout, "forLoop -> FOR assignment TO condition DO sentence\n");
                        }
    ;

procedureCall : "call"  
                "id"    {
                        shift(CALL_KEY,$1,0);
                        shift(IDENTI, $2, 0);
                        child_tp_cnt = 2;
                        child_tp[0] = CALL_KEY;
                        child_tp[1] = IDENTI;
                        reduce(PROCEDURE_CALL, child_tp_cnt, child_tp);
                        fprintf(fout, "procedureCall -> CALL ID\n");
                        }
    ;
        
readSent :  "read"          {shift(READ_KEY, "read", 0);}
            "("             {shift(LEFTPARAN, "(", 0);}
            readpara ")"    {
                            shift(RIGHTPARAN, ")", 0);
                            child_tp_cnt = 4;
                            child_tp[0] = READ_KEY;
                            child_tp[1] = LEFTPARAN;
                            child_tp[2] = READ_PARAMETER;
                            child_tp[3] = RIGHTPARAN;
                            reduce(READ_SENTENCE, child_tp_cnt, child_tp);
                            fprintf(fout, "readSent -> READ ( readpara )\n");
                            }
    ;

readpara : "id"                 {
                                shift(IDENTI, $1, 0);
                                child_tp_cnt = 1;
                                child_tp[0] = IDENTI;
                                reduce(READ_PARAMETER, child_tp_cnt, child_tp);
                                fprintf(fout, "readpara -> ID\n");
                                }
        | "id" "," readpara     {
                                shift(IDENTI, $1, 0);
                                shift(COMMA_OP, $2, 0);
                                child_tp_cnt = 3;
                                child_tp[0] = IDENTI;
                                child_tp[1] = COMMA_OP;
                                child_tp[2] = READ_PARAMETER;
                                reduce(READ_PARAMETER, child_tp_cnt, child_tp);
                                fprintf(fout, "readpara -> ID , readpara\n");
                                }
    ;

writeSent : "write"         {shift(WRITE_KEY, "write", 0);}
            "("             {shift(LEFTPARAN, "(", 0);}
            writepara ")"   {
                            shift(RIGHTPARAN, ")", 0);
                            child_tp_cnt = 4;
                            child_tp[0] = WRITE_KEY;
                            child_tp[1] = LEFTPARAN;
                            child_tp[2] = WRITE_PARAMETER;
                            child_tp[3] = RIGHTPARAN;
                            reduce(WRITE_SENTENCE, child_tp_cnt, child_tp);
                            fprintf(fout, "writeSent -> WRITE ( writepara )\n");
                            }
    ;

writepara : expr        {
                        child_tp_cnt = 1;
                        child_tp[0] = EXPRESSION;
                        reduce(WRITE_PARAMETER, child_tp_cnt, child_tp);
                        fprintf(fout, "writepara -> expr\n");
                        }
        | expr ","      {shift(COMMA_OP, $2, 0)}
          writepara     {
                        child_tp_cnt = 3;
                        child_tp[0] = EXPRESSION;
                        child_tp[1] = COMMA_OP;
                        child_tp[2] = WRITE_PARAMETER;
                        reduce(WRITE_PARAMETER, child_tp_cnt, child_tp);
                        fprintf(fout, "writepara -> expr , writepara\n");
                        }
    ;

%% 

void push(Node* s){
    stack[stop] = s;
    stop++;
}

void pop(){
    stop --;
    freenode(stack[stop]);
}

void show_child(Node *p){
    if(p == NULL)return;
    if(p -> childcnt == 0){
            printf("TYPE: %d ,child : 0\n",p -> type);
    } else {
            printf("TYPE: %d ,child : %d\n",p -> type,p -> childcnt);
            for(int i = 0;i < p -> childcnt;++ i){
                    show_child(p -> child[i]);
            }
    }
}

void freenode(Node* p){
    if(p -> id != NULL){
        free(p -> id);
    }
    if(p -> childcnt != 0){
        int i;
        for(i = 0;i < p -> childcnt;++ i){
                freenode(p -> child[i]);
        }
    }
    free(p);
}

void print_node(Node* p,int k){
    if(p == NULL) return;
    int type = p -> type;

    if(type == PROGRAM)                             {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< program >\n"); }
    else if(type == SUBPROGRAM)                     {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< subprogram >\n"); }
    else if(type == CONST_INSTRUCTION)              {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< const_instruction >\n");}
    else if(type == CONST_DECLARATION)              {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< const_declaration >\n");}
    else if(type == VARIABLE_INSTRUCTION)           {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< variable_instruction >\n");}
    else if(type == VARIABLE_INSTRUCTIONSUF)        {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< variable_instructionsuf >\n"); }
    else if(type == PROCEDURE_HEADER)               {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< procedure_header >\n");}
    else if(type == PROCEDURE_INSTRUCTION)          {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< procedure_instruction >\n");}
    else if(type == SENTENCE)                       {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< sentence >\n");}
    else if(type == UNEMPTY_SENTENCE)               {k--;}
    else if(type == EMPTY_SENTENCE)                 {k--;}
    else if(type == ASSIGNMENT)                     {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< assignment_sentence > \n");}
    else if(type == EXPRESSION)                     {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< expression >\n");}
    else if(type == ITEM)                           {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< item >\n");}
    else if(type == ITEM_SUF)                       {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< item_suf >\n");}
    else if(type == FACTOR)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< factor >\n");}
    else if(type == FACTOR_SUFFIX)                  {k--;}
    else if(type == PLUS_OPERATOR)                  {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< plus_operator > \n");}
    else if(type == MULTIPLY_OPERATOR)              {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< multi_operator > \n");}
    else if(type == MULTI_SENTENCE)                 {k--;}
    else if(type == COMPOUND)                       {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< compound_sentence >\n");}
    else if(type == RELATION_OPERATOR)              {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< relation_operator > \n");}
    else if(type == CONDITION)                      {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< condition >\n");}
    else if(type == CONDITIONAL)                    {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< condition_sentence >\n");}
    else if(type == WHILELOOP)                      {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< while_loop_sentence >\n");}
    else if(type == FORLOOP)                        {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< for_loop_sentence >\n");}
    else if(type == PROCEDURE_CALL)                 {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< call_procedure >\n");}
    else if(type == READ_PARAMETER)                 {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< read_parameter > \n");}
    else if(type == READ_SENTENCE)                  {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< read_sentence >\n");}
    else if(type == WRITE_PARAMETER)                {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< write_parameter >\n");}
    else if(type == WRITE_SENTENCE)                 {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< write_sentence >\n");}
    
    
    else if(type == IDENTI)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< ID: %s >\n",p -> id);}
    else if(type == NUMBER)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< NUMBER: %d >\n",p -> value);}
    
    else if(type == CONST_KEY)                      {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< CONST: const >\n");}
    else if(type == VAR_KEY)                        {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< VAR: var >\n"); }
    else if(type == PROCEDURE_KEY)                  {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< PROCEDURE: procedure >\n");}
    else if(type == CALL_KEY)                       {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< CALL: call >\n");}
    else if(type == BEGIN_KEY)                      {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< BEGIN: begin >\n");}
    else if(type == END_KEY)                        {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< END: end >\n");}
    else if(type == IF_KEY)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< IF: if >\n");}
    else if(type == THEN_KEY)                       {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< THEN: then >\n");}
    else if(type == WHILE_KEY)                      {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< WHILE: while >\n");}
    else if(type == DO_KEY)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< DO: do >\n");}
    else if(type == FOR_KEY)                        {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< FOR: for >\n");}
    else if(type == TO_KEY)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< TO: to >\n");}
    else if(type == READ_KEY)                       {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< READ: read >\n");}
    else if(type == WRITE_KEY)                      {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< WRITE: write >\n");}
    else if(type == ODD_KEY)                        {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< ODD: odd >\n");}

    else if(type == EQ_OP)                          {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< EQ_OP: = > \n");}
    else if(type == UEQ_OP)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< UEQ_OP: # >\n");}
    else if(type == LE_OP)                          {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< LE_OP: < >\n");}
    else if(type == GE_OP)                          {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< GE_OP: > >\n");}
    else if(type == LEQ_OP)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< LEQ_OP: <= >\n");}
    else if(type == GEQ_OP)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< GEQ_OP: >= >\n");}
    else if(type == PLUS_OP)                        {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< PLUS_OP: + >\n");}
    else if(type == MINUS_OP)                       {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< MINUS_OP: - >\n");}
    else if(type == MUL_OP)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< MUL_OP: * >\n");}
    else if(type == DIV_OP)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< DIV_OP: / >\n");}
    else if(type == SEMI_OP)                        {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< SEMI_OP: ; >\n");}
    else if(type == ASSIGN_OP)                      {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< ASSIGN_OP: := >\n");}
    else if(type == EOP_OP)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< EOP_OP: . >\n");}
    else if(type == COMMA_OP)                       {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< COMMA_OP: , >\n");}
    else if(type == LEFTPARAN)                      {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< LEFTPARAN: ( >\n");}
    else if(type == RIGHTPARAN)                     {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< RIGHTPARAN: ) >\n");}heng xu
int empty(){
    return stop == 0 ? 1 : 0;   
}

Node* top(){
    return stack[stop-1];
}

int inarray(int tp, int tpcnt, int tparray[TYPE_MAXN]){
    int i;
    for( i = 0;i < tpcnt;++ i){
        if(tp == tparray[i]){
            return 1;
        }
    }
    return 0;
}

void shift(int type,char* id,int number){
    Node* a;
    a = (Node*)malloc(sizeof(Node));
    a->value = number;
    a->type = type;
    if(id == NULL) {
        a->id = NULL;
    } else {
            a->id = (char*)malloc(ID_MAX_SIZE);
            strcpy(a->id, id);
    }
    a->child = NULL;
    a -> childcnt = 0;
    push(a);
}

void reduce(int type,int child_type_cnt,int child_type[TYPE_MAXN]){
    Node* father;
    father = (Node*)malloc(sizeof(Node));
    father -> value = 0;
    father -> id = NULL;
    father -> type = type;

    int cnt = 0;
    int tmptop = stop;
    fflush(stdout);

    while(tmptop > 0 && inarray(stack[tmptop-1]->type, child_type_cnt, child_type) == 1){
        tmptop --;
        cnt ++;
    }
    father -> child = (Node**)malloc(cnt * sizeof(Node*));
    int idx = 0;

    while(!empty() && inarray(top() -> type, child_type_cnt, child_type) == 1 ){
        father -> child[idx] = (Node*)malloc(sizeof(Node));
        node_copy(father -> child[idx], stack[stop-1]);
        pop();
        idx ++;
    }
    father -> childcnt = idx;
    push(father);
}

void node_copy(Node* copy,Node* copied){
    copy -> value = copied -> value;
    copy -> type = copied -> type;
    if(copied -> id == NULL) {
        copy-> id = NULL;
    }
    else {
        copy -> id = (char*)malloc(ID_MAX_SIZE);
        strcpy(copy -> id,copied -> id);
    }
    copy -> childcnt = copied -> childcnt;
    if(copy->childcnt != 0){
        copy -> child = (Node**)malloc(copy->childcnt * sizeof(Node*));
        int i;
        for( i = 0;i < copy-> childcnt;++ i){
                copy -> child[i] = (Node*)malloc(sizeof(Node));
                node_copy(copy->child[i],copied->child[i]);
        }
    }
}

 
int yywrap()
{
    return 1;
} 

int main()
{
    
    printf("Please enter files name:\n");
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
    
    yyparse();
    printf("stop = %d\n",stop);
    fprintf(fout, "\n\n\n******************** tree ********************\n");
    print_node(top(),0);
    if(stop == 1){
        freenode(top());
    }

    fclose(fout);
	printf("Finish!\n");
    return 0;
}