yacc -d syntax.y
lex main.l
gcc -c lex.yy.c y.tab.c
gcc -o parser lex.yy.o y.tab.o -ll node.c