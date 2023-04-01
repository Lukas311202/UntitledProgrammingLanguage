
prog: reader.c Tokenizer.c Stringfunctions.c basicfunctions.c computation_tree.c Parameter_stack.c
	gcc -o prog Tokenizer.c reader.c Stringfunctions.c basicfunctions.c computation_tree.c Parameter_stack.c

%: %.o
	gcc -o % %.o

%.o: %.c
	gcc -c %.c