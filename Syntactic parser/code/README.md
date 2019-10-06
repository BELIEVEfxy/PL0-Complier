bison -d parse.y
flex lex.l
gcc lex.yy.c parse.tab.c
./a.out

