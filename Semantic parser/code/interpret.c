#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userdef.h"
#define LIT 1  //对指令定义常数
#define LOD 2
#define STO 3
#define CAL 4
#define INT 5
#define JMP 6
#define JPC 7
#define OPR 8
#define STACKSIZE 100


int base(int level, int *s, int b){
    int b_temp = b;
    while(level > 0){
        b_temp = s[b_temp];
        level --;
    }
    return b_temp;
}


struct instruction *code;



void interpret() 
{
    int p, b, t;
    struct instruction i;  
    int s[STACKSIZE];

    printf("start pl0\n");
    t=0; b=1;  
    p=0;	
    s[1]=1; s[2]=1; s[3]=0;
    do {
	
        i=code[p++];
        //printf("DEBUG %d\n",p-1);
        switch (i.f) 
        {
        case LIT: 
            t=t+1;
            s[t]=i.a;
            break;
        case OPR: 
            switch(i.a) 
            {
                case 0:
                    t=b-1;
                    p=s[t+3];
                    b=s[t+2];
                    break;
                case 1: 
                    s[t]=-s[t];
                    break;
                case 2: 
                    t=t-1;
                    s[t]=s[t] + s[t+1];
                    break;
                case 3:
                    t=t-1;
                    s[t]=s[t] - s[t+1];
                    break;
                case 4: 
                    t=t-1;
                    s[t]=s[t] * s[t+1];
                    break;
                case 5: 
                    t=t-1;
                    s[t]=s[t] / s[t+1];
                    break;
                case 6: 
                    s[t]=(s[t] % 2 == 1);
                    break;
                case 8: 
                    t=t-1;
					
                    s[t]=(s[t] == s[t+1]);
                    break;
                case 9:
                    t=t-1;
                    s[t]=(s[t] != s[t+1]);
                    break;
                case 10:
                    t=t-1;
                    s[t]=(s[t]<s[t+1]);
                    break;
                case 11: 
                    t=t-1;
                    s[t]=(s[t]>=s[t+1]);
                    break;
                case 12: 
                    t=t-1;
                    s[t]=(s[t]>s[t+1]);
                    break;
                case 13: 
                    t=t-1;
                    s[t]=(s[t]<=s[t+1]);
                    break;
                case 14: 
                    printf(" %d", s[t]);
                    t=t-1;
                    break;
                case 15: 
                    printf("\n");
                    break;
                case 16: 
                    t=t+1;
                    printf(" please enter : ");
                    scanf("%d", &s[t]);
                    break;
            }
		    break;
        case LOD: 
            t=t+1;
            s[t]=s[base(i.l, s, b)+i.a];
            break;
        case STO: 
            s[base(i.l, s, b)+i.a]=s[t];
            t=t-1;
            break;
        case CAL:
            s[t+1]=base(i.l, s, b);
            s[t+2]=b;
            s[t+3]=p;
            b=t+1;
            p=i.a;
            break;
        case INT: 
            t=t+i.a;
            break;
        case JMP: 
            p=i.a;
            break;
        case JPC: 
            if (s[t]==0) 
            {
                p=i.a;
            }
            t=t-1;
            break;
        }
    }while (p!=0);
}



int main(){
    int total_line;
    FILE *num_file;
    FILE *code_in;
    num_file = fopen("number.txt","r");  //读入文件
    code_in = fopen("pcode.txt","r");
    fscanf(num_file,"%d",&total_line);
    printf("%d\n",total_line);
    code = (struct instruction*)malloc(sizeof(struct instruction)*total_line);  //存放类PCODE代码

    char f[10];
    char line[10];
    int l;
    int a;
    for(int i=0;i<total_line;++i){
        for(int j=0;j<10;++j){  //初始化
            f[j] = '\0';
            line[j] = '\0';
        }
        fscanf(code_in,"%s\t%s\t%d\t%d\t",line,f,&l,&a);  //输入
        if(strcmp("LIT",f) == 0){  //将指令全部存入code结构体中
            code[i].f = LIT;
            code[i].l = l;
            code[i].a = a; 
        }
        else if(strcmp("LOD",f) == 0){
            code[i].f = LOD;
            code[i].l = l;
            code[i].a = a; 
        }
        else if(strcmp("STO",f) == 0){
            code[i].f = STO;
            code[i].l = l;
            code[i].a = a; 
        }
        else if(strcmp("CAL",f) == 0){
            code[i].f = CAL;
            code[i].l = l;
            code[i].a = a; 
        }
        else if(strcmp("INT",f) == 0){
            code[i].f = INT;
            code[i].l = l;
            code[i].a = a; 
        }
        else if(strcmp("JMP",f) == 0){
            code[i].f = JMP;
            code[i].l = l;
            code[i].a = a; 
        }
        else if(strcmp("JPC",f) == 0){
            code[i].f = JPC;
            code[i].l = l;
            code[i].a = a; 
        }
        else if(strcmp("OPR",f) == 0){
            code[i].f = OPR;
            code[i].l = l;
            code[i].a = a; 
        }
        else {
            printf("error input\n");
            exit(1);
        }
    }
    interpret();  //翻译


}
