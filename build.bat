@echo off
gcc -std=c17 -Wall -Wextra -O0 -g -o vm.exe src\main.c src\vm.c src\lexer.c