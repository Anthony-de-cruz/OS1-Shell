# OS1 - Shell
A very basic command shell written in C.

## Usage
Build with:
```sh
❯ make
gcc src/main.c -o OS1-Shell.out
```
- Has built in commands:
    - cd <dir>
        Change working directory
    - exit 
        End session
- Runs any command added to PATH

Example:
```sh
❯ ./OS1-Shell.out

>mkdir hi

>cd hi

>touch bi

>cd ..

>tree
.
├── hi
│   └── bi
├── Makefile
├── OS1-Shell.out
├── README.md
└── src
    └── main.c

3 directories, 5 files

>rm -r hi

>tree
.
├── Makefile
├── OS1-Shell.out
├── README.md
└── src
    └── main.c

2 directories, 4 files

>exit
```
