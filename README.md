# PL0-Complier
用C语言实现PL0语言编译器，借助flex工具

## 测试文件
test_file：为PL0测试文件

## 词法分析器
Lexical analyzer

利用flex工具生成一个PL/0语言的词法分析程序，对PL/0语言的源程序进行扫描，识别出单词符号的类别，输出各种符号的信息。

## 语法分析器
Syntactic parser

⽤bison⼯具⽣成⼀个PL/0语⾔的语法分析程序，对PL/0源程序进⾏语法分析。

## 语义分析器
Semantic parser

通过C语言编写PL/0编译程序，将PL/0语言程序转换为类Pcode代码，然后用interpret.c文件的程序检查类Pcode代码的正确性。
