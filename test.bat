@echo off
gcc -std=c17 -Wall -Wextra -O0 -g -o test.exe tests\test_main.c tests\test_lexer.c src\lexer.c src\vm.c
test.exe