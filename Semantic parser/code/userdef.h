typedef struct {  //标识符结构体
    int iValue; //标识符赋予的数值
    char sMark[12]; //标识符本身
} varIndex;
varIndex strMem[256];
struct code_struct{   //代码结构
        int line;  //行数
        int f;  //对应指令功能表
        int l;
        int a;
};
struct sign{  //符号表结构体
        char name[11];  //名字
        int type;  //类型
        int layer;  //层数
        int previous;  //上一层过程
};
struct procedure_pos{   //记录程序位置
        char name[11];  //程序名字
        int pos;  //位置
        int var_number;  //变量个数
};



