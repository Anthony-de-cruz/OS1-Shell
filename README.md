# OS1 - Shell
A very basic command shell written in C.

## Usage
Build with:
```sh
❯ make
gcc src/main.c -o OS1-Shell.out
```
- Has built in commands:
    - cd {dir}
        - Change working directory
    - exit 
        - End session
    - quit
        - End session
- Runs any command added to PATH
- Can only run 1 command at a time

Example:
```sh
❯ ./OS1-Shell.out
❯ mkdir example
❯ cd example
❯ touch file
❯ ls
file
❯ cd ..
❯ tree
.
├── example
│   └── file
├── Makefile
├── OS1-Shell.out
├── README.md
└── src
    ├── command.c
    ├── command.h
    ├── command.o
    ├── main.c
    └── main.o

3 directories, 9 files
❯ rm -r example
❯ tree
.
├── Makefile
├── OS1-Shell.out
├── README.md
└── src
    ├── command.c
    ├── command.h
    ├── command.o
    ├── main.c
    └── main.o

2 directories, 8 files
❯ quit
```
