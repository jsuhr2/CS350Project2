all: prog2tree

parser.o: parser.c
	gcc -c parser.c

prog2tree.o: prog2tree.c
	gcc -c prog2tree.c

prog2tree: prog2tree.o parser.o
	gcc prog2tree.o parser.o -o prog2tree

clean:
	rm prog2tree.o
	rm prog2tree
	rm parser.o
	rm -fv *~ \#*\# *.swp
	rm -fv *.txt
