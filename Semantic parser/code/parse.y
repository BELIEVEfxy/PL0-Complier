%{
//display栈、符号表栈、代码地址栈、循环栈、程序栈
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userdef.h"
#define stack_size 128

char infile[32];
char *outfile;
FILE *fin;
FILE *fout;
extern FILE * yyin;
extern FILE * yyout;

int code_line=1;                                                    /*记录代码行数*/
extern varIndex strMem[256];
int error_cnt = 0;

int iMaxIndex=0;  
int iCurIndex=0;  
int yylex(void);
void yyerror(char *);

FILE *CodeOutput;                                                   /*code输出文件指针*/
int total_line=0;                                                   /*pcode总的行数*/
int cur_layer = 1;                                                  /*现在的层数*/
int code_address_stack[stack_size];                                 /*记录代码地址的栈*/
int code_address_stack_point=0;                                     /*代码地址栈顶*/
int loop_stack[stack_size];                                         /*用于循环的栈*/
int loop_stack_point = 0;                                           /*循环栈顶*/

struct code_struct *mycode;                                         /*存储翻译之后的代码*/
struct sign *sign_stack;                                            /*标志（符号）栈*/
int sign_top = 0;                                                   /*标志栈顶*/

int display_stack[stack_size];                                      /*display栈*/
int display_top = 0;                                                /*display的栈顶*/

struct procedure_pos * procedure_position;                          /*过程位置*/
int pro_ct = 0;                                                     /*记录过程的个数*/
int procedure_stack[stack_size];                                            /*过程栈*/
int procedure_stack_point = 0;                                      /*过程栈顶*/
int cur_pro_ct=0;                                                   /*现在过程的代号*/

void PushProcedurePosition(char *c,int p);                          /*将程序的位置记录在procedure_position中*/
int FindProcedurePosition(char *s);                                 /*找到过程位置*/
int CheckSignIsDeclare(char *tag_name);                             /*看定义的标识符之前有没有定义过*/
int FindSign(char *tag_name);                                       /*找sign是否存在*/
void PopSignStack();                                                /*将所有的sign退栈，并且display中最上面的程序也需要退出来*/
void PushSignStack(char *s,int t);                                  /*将s加入sign栈中*/
void AddPcode(int thef, int thel, int thea);                        /*添加类PCODE代码*/
void ChangePcode(int theline, int thef, int thel, int thea);        /*将第theline行代码改为所指的*/
int CaculateA(int pos_flag);                                        /*计算偏移量a*/
void PrintPcode(struct code_struct ToPrint);                        /*按照类PCODE输出代码*/
int cmp(const void *a ,const void *b);                              /*排序函数*/

%}

%token IF THEN WHILE DO READ WRITE CALL BEGINN END CONST VAR PROCEDURE ODD FOR TO DOWNTO 
%token IDENTIFIER NUMBER 
%token ASSIGNMENT
%token ENDD    0    "end of file"

%left "<=" ">=" '>' '<' '=' '#'
%left '+' '-'
%left '*' '/'
%left '(' ')'

%%
/*整个过程开始与结束*/
program :  
                    {
                    display_top++; 
                    display_stack[display_top] = 1; 
                    PushProcedurePosition("program",0); //改变procedure_position
                    cur_pro_ct = pro_ct-1; 
                    procedure_stack[procedure_stack_point] = pro_ct-1; 
                    procedure_stack_point++;
                    }/*在程序开始之前对display栈和程序栈进行初始化*/
        subprogram  
        '.' ENDD    {
                    printf("\nSuccessfully Compiled\n0 error(s) 0 warning(s)\n"); 
                    AddPcode(8,0,0);
                    }
;  

/*子程序*/
subprogram :
        constInstruction 
        variableInstruction  
        procedureInstruction 
                {
                procedure_position[cur_pro_ct].pos = total_line; //记录程序的位置
                AddPcode(5,0,3+procedure_position[cur_pro_ct].var_number);
                }/*在procedure的位置中记录对应行数，并且记下PCODE INT 0 3+var num 在运行栈中为被调用的区域开辟A个单元的区域*/

        sentence
;                

/*****说明语句的翻译*****/
/*常量说明部分*/
constInstruction :  
        CONST  constDeclaration ';'  
|       /*empty*/
;
/*常量定义*/
/*记录常量*/
constDeclaration :   
        IDENTIFIER '=' NUMBER   {
                                if(CheckSignIsDeclare(strMem[$1].sMark) == 1){
                                    PushSignStack(strMem[$1].sMark,$3);
                                }
                                }  
|       IDENTIFIER '=' NUMBER   {
                                if(CheckSignIsDeclare(strMem[$1].sMark) == 1){
                                    PushSignStack(strMem[$1].sMark,$3);
                                }
                                }   
        ',' constDeclaration
;
/*变量说明部分*/
variableInstruction :  
        VAR 
        IDENTIFIER  {
                    if(CheckSignIsDeclare(strMem[$2].sMark) == 1){
                        PushSignStack(strMem[$2].sMark,-1);
                        procedure_position[cur_pro_ct].var_number++;//当前程序变量数目+1
                    } 
                    }  
        variableDeclaration ';'  
|       /*empty*/
;
/*变量定义*/
/*记录变量，同时更新变量的个数*/
variableDeclaration :  
        ','
        IDENTIFIER  {
                    if(CheckSignIsDeclare(strMem[$2].sMark) == 1){
                        PushSignStack(strMem[$2].sMark,-1);
                        procedure_position[cur_pro_ct].var_number++;//当前程序变量数目+1
                    } 
                    }  
        variableDeclaration
|       /*empty*/
;
/*过程说明部分*/
procedureInstruction :  
        procedureHeader  subprogram  
        ';' {
            cur_layer--; /*程序结束后退栈*/
            procedure_stack_point--;  /*指向的是过程栈的顶，没东西，因此要--*/
            cur_pro_ct = procedure_stack[procedure_stack_point-1]; /*获得退栈后所在过程的编号，因此[]中要-1*/
            procedure_stack[procedure_stack_point] = -1; /*清空栈*/
            PopSignStack(); /*把该过程的ID清空*/
            AddPcode(8,0,0); 
            } /*表示一个程序结束，需要将程序退栈，同时加上指令OPR 0 0代表结束*/
        procedureInstruction
|       /*empty*/
;
/*过程首部*/
/*定义一个新的过程，需要将这个过程放入sign栈中记录，同时将这个过程也放在display栈顶，过程栈也需要记录*/
procedureHeader :   
        PROCEDURE IDENTIFIER 
        ';'     {
                if(CheckSignIsDeclare(strMem[$2].sMark) == 1){
                    PushSignStack(strMem[$2].sMark,-2);
                    display_top++; 
                    display_stack[display_top] = sign_top+1; 
                    cur_layer++; 
                    PushProcedurePosition(strMem[$2].sMark,total_line+1);//有pro_ct++
                    cur_pro_ct = pro_ct-1; /*在一个过程开始时，记录这个过程的编号*/
                    procedure_stack[procedure_stack_point] = pro_ct - 1; /*存下这个过程的编号，方便程序中用到procedure_position时直接访问该过程的信息*/
                    procedure_stack_point++; 
                }  
                }  
;
/*语句*/
sentence :  
        assignmentSentence    
|       compoundSentence   
|       conditionSentence      
|       whileLoop    
|       procedureCall   
|       readSentence         
|       writeSentence 
|       forLoop
|
;

/*****赋值语句的翻译*****/
/*赋值语句*/
/*首先需要查找标识符是否存在，合法的话执行指令 STO l a将栈顶内容送入某单元变量中，l为层差，a为偏移量*/
assignmentSentence :  
        IDENTIFIER  {
                    int pos_flag = FindSign(strMem[$1].sMark); //找sign是否存在，返回在sign_stack的位置
                    if(pos_flag > 0){ 
                        if(sign_stack[pos_flag].type != -1){//-1表示为var类型的标识符
                            printf("in line %d illegal name\n",code_line); 
                            exit(1);
                        }  
                    } 
                    }
        ASSIGNMENT  
        expression  {
                    int pos_flag = FindSign(strMem[$1].sMark); 
                    AddPcode(3,cur_layer-sign_stack[pos_flag].layer,CaculateA(pos_flag));/*STO l a*/
                    } 
;

/*复合语句*/
multiSentence : 
        sentence ';'  multiSentence
|       sentence
;
compoundSentence :   BEGINN  multiSentence END 
;
/*****控制流语句的翻译*****/
/*条件语句*/
condition :  
        expression  relationOp  expression {AddPcode(8,0,$2);}  /*执行指令OPR 0 X，判断条件成立，这里X在下面有赋值*/
|       ODD  expression {AddPcode(8,0,6);}  /*指令OPR 0 6，栈顶奇偶元素判断*/
;
/*执行 JPC 0 a条件跳转，并且记录代码地址；then后面改变代码地址*/
conditionSentence :   
        IF  condition   {
                        AddPcode(7,0,-1); /*JPC，条件跳转，栈顶布尔值非真跳转到地址a，条件不满足时转*/
                        code_address_stack[code_address_stack_point] = total_line-1; /*记录条件判断的位置*/
                        code_address_stack_point++;  
                        } 
        THEN sentence  {/*条件满足*/
                        code_address_stack_point--;
                        int target_line = code_address_stack[code_address_stack_point]; 
                        code_address_stack[code_address_stack_point]  = -1; 
                        ChangePcode(target_line,7,0,total_line); /*此时的total_line表示的是if语句结束后的pcode代码的位置*/
                        }
;   
/*while循环语句*/
whileLoop :   
    WHILE           {
                    loop_stack[loop_stack_point] = total_line; /*记录JMP回来的位置*/
                    loop_stack_point++; 
                    } 
    condition       {  
                    AddPcode(7,0,-1); /*JPC 要跳转的地址还没有，先存为-1，后面有ChangePcode()*/
                    code_address_stack[code_address_stack_point] = total_line-1; /*记录条件判断的位置，方便后面ChangePcode找到要修改的位置*/
                    code_address_stack_point++; 
                    } 
    DO sentence    { 
                    loop_stack_point--;  
                    AddPcode(6,0,loop_stack[loop_stack_point]); /*JMP 无条件跳转至a地址*/
                    loop_stack[loop_stack_point] = -1;  
                    code_address_stack_point--; 
                    int target_line = code_address_stack[code_address_stack_point]; 
                    ChangePcode(target_line,7,0,total_line); 
                    code_address_stack[code_address_stack_point]  = -1; 
                    }
;  
/*过程调用语句*/
/*调用过程，首先需要判断过程名之前有没有定义，如果有，找到这个过程的位置，将它加入代码中*/
procedureCall :   
        CALL IDENTIFIER {
                        int pos_flag = FindSign(strMem[$2].sMark); 
                        if(pos_flag > 0){
                            if(sign_stack[pos_flag].type==-2 || sign_stack[pos_flag].type == -3){
                                int target_pos = FindProcedurePosition(strMem[$2].sMark); /*根据procedure的名字来找位置*/
                                AddPcode(4,cur_layer-sign_stack[pos_flag].layer,target_pos); /*CAL l a 调用过程 a为调用地址，l为层差*/
                            }else{
                                printf("error in line %d illegal name\n",code_line); exit(1);
                            }      
                        }  
                        }
; 

/*for循环语句*/
/*例：for i := 1 to 3 do || for i := 5 downto 3 do*/
/*默认循环变量+1*/
forLoop : 
        FOR IDENTIFIER   
        ASSIGNMENT NUMBER   {
                            int pos_flag = FindSign(strMem[$2].sMark); /*返回ID的地址*/
                            if(pos_flag > 0){ /*ID不存在，报错*/
                                if(sign_stack[pos_flag].type == -1){} /*ID为var类型*/
                                else{
                                    printf("error in line %d illegal input\n",code_line);
                                    exit(1);
                                }
                            } 
                            AddPcode(1,0,$4);/*LIT 0 a 把NUMBER的值取到栈顶*/
                            AddPcode(3,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag)); /*STO 0 a 把栈顶的值存到ID中*/
                            loop_stack[loop_stack_point] = total_line; /*loop_stack中存下循环入口指令的地址*/
                            loop_stack_point++; /*如果有多层循环，那么loop_stack中会有多层循环的入口地址*/
                            }     
        TO NUMBER       { 
                        int pos_flag = FindSign(strMem[$2].sMark); /*找到ID的地址*/
                        AddPcode(2,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag)); /*将变量值取到栈顶*/
                        AddPcode(1,0,$7);/*LIT*/
                        AddPcode(8,0,13);/*OPR < */
                        AddPcode(7,0,-1);/*JPC*/
                        code_address_stack[code_address_stack_point] = total_line-1; /*存着上条JPC的位置，方便后面ChangePcode修改地址，因为跳转的地址只有在循环结束后才能知道*/
                        code_address_stack_point++;  
                        } 
        DO  sentence    { 
                        int pos_flag = FindSign(strMem[$2].sMark);   
                        AddPcode(2,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag)); /*把ID的值取到栈顶*/
                        AddPcode(1,0,1);/*把常数1取到栈顶*/
                        AddPcode(8,0,2);/*模拟循环变量+1的操作*/
                        AddPcode(3,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag));  /*将+1后的值存到循环变量里*/
                        loop_stack_point--; /*前面有++，退一层，找到本层循环的入口地址*/
                        AddPcode(6,0,loop_stack[loop_stack_point]); /*JMP 0 a 无条件跳转至a地址（循环开始的位置）*/
                        loop_stack[loop_stack_point] = -1;  /*该层循环结束，清空栈*/
                        code_address_stack_point--;   
                        int target_line = code_address_stack[code_address_stack_point];  /*找到需要修改的代码的地址*/
                        ChangePcode(target_line,7,0,total_line);   /*修改地址*/
                        code_address_stack[code_address_stack_point]  = -1;  /*清空栈*/
                        }
|       FOR IDENTIFIER  
        ASSIGNMENT NUMBER   {
                            int pos_flag = FindSign(strMem[$2].sMark); 
                            if(pos_flag>0){
                                if(sign_stack[pos_flag].type == -1){} 
                                else{
                                    printf("error in line %d illegal input\n",code_line);
                                    exit(1);
                                }
                            } 
                            AddPcode(1,0,$4);
                            AddPcode(3,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag)); 
                            loop_stack[loop_stack_point] = total_line; 
                            loop_stack_point++; 
                            }     
        DOWNTO NUMBER       {  
                            int pos_flag = FindSign(strMem[$2].sMark);  
                            AddPcode(2,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag)); 
                            AddPcode(1,0,$7); 
                            AddPcode(8,0,11);
                            AddPcode(7,0,-1);   
                            code_address_stack[code_address_stack_point] = total_line-1; 
                            code_address_stack_point++; 
                            } 
        DO sentence         { 
                            int pos_flag = FindSign(strMem[$2].sMark);   
                            AddPcode(2,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag));   
                            AddPcode(1,0,1);AddPcode(8,0,3); 
                            AddPcode(3,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag)); 
                            loop_stack_point--; 
                            AddPcode(6,0,loop_stack[loop_stack_point]); 
                            loop_stack[loop_stack_point] = -1;  
                            code_address_stack_point--;  
                            int target_line = code_address_stack[code_address_stack_point]; 
                            ChangePcode(target_line,7,0,total_line);  
                            code_address_stack[code_address_stack_point]  = -1; 
                            }
; 
 

/*读写语句*/
/*循环中标识符的输入，首先需要查找这个标识符是否存在，如果存在，执行OPR 0 16从屏幕中读入一个输入，之后执行STO L A将其送入对应的变量*/
readPara :   
        IDENTIFIER  {
                    int pos_flag = FindSign(strMem[$1].sMark);  
                    if(pos_flag>0){
                        if(sign_stack[pos_flag].type == -1){
                            AddPcode(8,0,16); /*从命令行读入一个并放入栈顶*/
                            AddPcode(3,cur_layer-sign_stack[pos_flag].layer,CaculateA(pos_flag));/*栈顶的值放入变量ID中*/
                        } else {
                            printf("error in line  %d  change a const parameter\n",code_line); 
                            exit(1);
                        }    
                    } 
                    }
|       IDENTIFIER  {
                    int pos_flag = FindSign(strMem[$1].sMark);  
                    if(pos_flag>0){
                        if(sign_stack[pos_flag].type == -1){
                            AddPcode(8,0,16); /*从命令行读入一个并放入栈顶*/
                            AddPcode(3,cur_layer-sign_stack[pos_flag].layer,CaculateA(pos_flag));/*栈顶的值放入变量ID中*/
                        } else {
                            printf("error in line  %d  change a const parameter\n",code_line); 
                            exit(1);
                        }    
                    } 
                    }
        ',' readPara
;  
/*表达式循环，执行OPR 0 14——OPR 0 15，栈顶值输出到屏幕，屏幕输出换行*/
writePara :   
        expression  {
                    AddPcode(8,0,14);
                    AddPcode(8,0,15);
                    }   
|       expression  {
                    AddPcode(8,0,14);
                    AddPcode(8,0,15);
                    }
        ',' writePara
;

readSentence :   
        READ '(' readPara ')' 
;
writeSentence :   
        WRITE '(' writePara ')'
;

/*表达式*/
expression :    
        plusOp  {
                AddPcode(1,0,0);
                } 
        item    {
                AddPcode(8,0,$1);
                }  
        addItem  //加法 OPR
|       item addItem     
;

item : 
        factor mulItem
;

/*关于算符的操作*/
factor : 
        IDENTIFIER  {
                    int pos_flag = FindSign(strMem[$1].sMark); 
                    if(pos_flag > 0) {
                        if(sign_stack[pos_flag].type == -1){
                            AddPcode(2,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag));  /*LOD var*/
                        } else if(sign_stack[pos_flag].type>=0){
                            AddPcode(1,0,sign_stack[pos_flag].type);/*LIT const*/
                        } else{
                            printf("error in line: %d  illegal name\n",code_line);
                            exit(1);
                        } 
                    }  
                    }  /*当pos_flag大于0的时候执行LOD L A将变量值取值栈顶；当类型大于等于0的时候，执行执行LIT 0 A，将常数值取值栈顶*/
|       NUMBER    {
                        AddPcode(1,0,$1); 
                        }  /*执行LIT 0 A将常数值A取值栈顶*/
|       '('  expression ')' 
;
/*加法 OPR*/
addItem : 
        plusOp 
        item {AddPcode(8,0,$1);}  
        addItem 
|       /*empty*/
;
/*乘法 OPR*/
mulItem : 
        mulOp factor {AddPcode(8,0,$1);}  
|       /*empty*/
;
/*对不同运算符赋值，对应OPR指令*/
plusOp : 
        '+' {$$ = 2; }  
|       '-' {$$ = 3; }
;
mulOp : 
        '*' {$$ = 4; }
|       '/' {$$ = 5; }
;
/*对不同大小符号赋予数值，便于上面的条件语句使用得到对应的指令*/
relationOp : 
        '=' {$$ = 8; }  
|       '#' {$$ = 9; }
|       '<' {$$ = 10; }
|       "<="  {$$ = 13; }
|       '>' {$$ = 12; }
|       ">="  {$$ = 11; }
;

%%
/*将程序的位置记录在procedure_position中*/
void PushProcedurePosition(char *c,int p){ 
    for(int i = 0; i < 11; ++i){
        procedure_position[pro_ct].name[i] = '\0';
    }
    strcpy(procedure_position[pro_ct].name, c);  
    procedure_position[pro_ct].pos = p;
    procedure_position[pro_ct].var_number = 0;
    pro_ct ++;  //程序个数加一
}
/*看定义的标识符之前有没有定义过*/
int CheckSignIsDeclare(char *tag_name){  
    int bias = display_stack[display_top];  //栈顶偏差
    while(bias <= sign_top){
        if(strcmp(tag_name,sign_stack[bias].name) == 0){  //定义过，返回错误
            printf("error!!! line %d: declare repeatedly \n",code_line);
            exit(1);
        }
        if(sign_stack[bias].previous == 0){
            break;
        }
        bias ++;
    }
    return 1;
}
/*找sign是否存在*/
int FindSign(char *tag_name){  
    int display_bias = display_top;
    int cur_bias;
    while(display_bias > 0){
        cur_bias = display_stack[display_bias];
        while(cur_bias <= sign_top){
            if(strcmp(tag_name,sign_stack[cur_bias].name) == 0){//find
                return cur_bias;
            }
            if(sign_stack[cur_bias].previous==0){  //代表找到这个程序的底部
                break;
            }
            cur_bias++;
        }
        display_bias --;
    }
    printf("error!!! line %d: no such parameter \n",code_line);  //没找到
    exit(1);
}
/*将该过程的所有的sign退栈，并且display中最上面的程序也需要退出来*/
void PopSignStack(){  
    
    int bias = display_stack[display_top]-1;
    
    for(int i=sign_top; i>bias;--i){  //退sign
        sign_stack[i].type = -10;
        sign_stack[i].layer = -1;
        sign_stack[i].previous = -1;
        for(int j=0;j<11;++j){
            sign_stack[i].name[j] = '\0';
        }
    }
    sign_top = bias;
    sign_stack[sign_top].previous = 0;
    
    sign_stack[sign_top].type = -3;
    display_stack[display_top] = 0;  //退display
    display_top--;
}
/*将s加入sign 栈中*/
void PushSignStack(char *s,int t){ 
    sign_top++;
    for(int i=0;i<11;++i){
        sign_stack[sign_top].name[i] = '\0';
    }
    strcpy(sign_stack[sign_top].name,s);
    sign_stack[sign_top].type = t;
    sign_stack[sign_top].layer = cur_layer;
    sign_stack[sign_top].previous = 0;
    if(sign_top > 1){  //按照实际情况更新previous的值
        int pre_bias = sign_top-1;
        if(sign_stack[pre_bias].type > -2){
            sign_stack[pre_bias].previous = sign_top;
        }
        else if(sign_stack[pre_bias].type == -3){
            sign_stack[pre_bias].previous = sign_top;
        }
    }
}
/*添加类PCODE代码*/
void AddPcode(int thef, int thel, int thea){  
    mycode[total_line].line = total_line;
    mycode[total_line].f = thef;
    mycode[total_line].l = thel;
    mycode[total_line].a = thea;
    total_line++;
    
}
/*将第theline行代码改为所指的*/
void ChangePcode(int theline, int thef, int thel, int thea){   
    mycode[theline].f = thef;
    mycode[theline].l = thel;
    mycode[theline].a = thea;
}
/*计算偏移量*/
int CaculateA(int pos_flag){  
    int target_flag = pos_flag;
    
    if(pos_flag >= 1){
        while(target_flag >= 1){
            if(sign_stack[target_flag].type <= -2 || sign_stack[target_flag].type >= 0){
                return pos_flag-target_flag + 2;
            }
            target_flag--;
        }
        return pos_flag+2;
    }
    else{  //不正确
        printf("error\n");
        exit(1);
    }
}
/*找到过程位置*/
int FindProcedurePosition(char *s){   
    
    for(int i=cur_pro_ct; i<pro_ct; ++i){
        if(strcmp(procedure_position[i].name,s) == 0){
            
            return procedure_position[i].pos;
        }
    }
    printf("error in func FindProcedurePosition\n");  //找不到
    exit(1);
}
/*按照类PCODE输出代码*/
void PrintPcode(struct code_struct ToPrint){   
    int thef = ToPrint.f;
    fprintf(CodeOutput,"(%d)\t", ToPrint.line);
    switch(thef){
        case 1:fprintf(CodeOutput,"LIT\t");break;
        case 2:fprintf(CodeOutput,"LOD\t");break;
        case 3:fprintf(CodeOutput,"STO\t");break;
        case 4:fprintf(CodeOutput,"CAL\t");break;
        case 5:fprintf(CodeOutput,"INT\t");break;
        case 6:fprintf(CodeOutput,"JMP\t");break;
        case 7:fprintf(CodeOutput,"JPC\t");break;
        case 8:fprintf(CodeOutput,"OPR\t");break;
        default:fprintf(CodeOutput,"error");exit(1);
    }
    fprintf(CodeOutput,"%d\t",ToPrint.l);
    fprintf(CodeOutput,"%d\n",ToPrint.a);
}

/*排序函数*/
int cmp(const void *a ,const void *b){   
    return (*(struct code_struct *)a).line > (*(struct code_struct *)b).line ? 1:-1;
}


int main(void) {

    printf("Please enter files name:\n");
	scanf("%s", infile);
    
    fin = fopen(infile, "r");
	if(fin == NULL){
		printf("Cannot open the in file \n");
		return 0;
	}

    CodeOutput = fopen("pcode.txt","w");  //类PCODE存放文件
    mycode = (struct code_struct*)malloc(sizeof(struct code_struct)* 2000);
    sign_stack = (struct sign*)malloc(sizeof(struct sign) * 100);
    procedure_position = (struct procedure_pos*)malloc(sizeof(struct procedure_pos) * 30);
    
    /*初始化*/
    for(int i = 0; i < stack_size; ++i){   
        procedure_stack[i] = -1;
        loop_stack[i] = -1;
        code_address_stack[i] = -1;
    }
   
    yyin = fin;
    yyparse();
    /*含有跳转的指令，都要加上现有过程的数量，即加上前面JMP指令的数量*/
    int code_bias = pro_ct;  
    for(int i = 0; i < total_line; ++i){
        //printf("%d\n",ycode[i].f);
        mycode[i].line += code_bias;
        if(mycode[i].f == 4 ||mycode[i].f == 6 || mycode[i].f == 7 ){
            mycode[i].a += code_bias;
        }
    }

    for(int i = 0; i < pro_ct; ++i){
        procedure_position[i].pos += code_bias;
    }
    /*补上前面的JMP*/
    for(int i = 0; i < pro_ct; ++i){
        mycode[total_line].line = i;
        mycode[total_line].f = 6;
        mycode[total_line].l = 0;
        mycode[total_line].a = procedure_position[i].pos;
        total_line++;
    }

    qsort(mycode,total_line,sizeof(mycode[0]),cmp);  //对代码按照行标号排序


    printf("\n");
    for(int i = 0; i < total_line; ++i){  //输出类PCODE
        PrintPcode(mycode[i]);
    }
    FILE *num_file;
    num_file = fopen("number.txt","w");  //在number文件中写下总的行数
    fprintf(num_file,"%d",total_line);

 
    return 0;
}
int yywrap(){
    return 1;
}
void yyerror(char *s) {
    printf("error in line %d %s\n",code_line-1, s);
    exit(1);
}

