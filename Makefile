OS1-Shell.out: src/main.o src/command.o
	gcc -o OS1-Shell.out src/main.o src/command.o

src/main.o : src/main.c src/command.h
	gcc -o src/main.o -c src/main.c

src/command.o : src/command.c src/command.h
	gcc -o src/command.o -c src/command.c
