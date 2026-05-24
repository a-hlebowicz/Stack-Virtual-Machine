# Stack Virtual Machine

A stack-based virtual machine with its own bytecode, plus a compiler front-end for a small C-like language. Written in C17, built from scratch with no parser generators and nothing outside the standard library.

A program is just text. It gets turned into tokens, then into a syntax tree, then compiled down to bytecode, and the VM runs the bytecode.

## the language

Statically typed, integers only. Variables, arithmetic, comparisons, if/else, while, print. Nothing else.

```
int x = 6;
if (x + 7 == 13) {
    print(x);
} else {
    print(0);
}
```

## pipeline

```
text -> lexer -> tokens -> parser -> AST -> compiler -> bytecode -> VM
```

### lexer

Walks the source one character at a time and produces a flat array of tokens, terminated by an EOF token. It handles integer literals, identifiers, the five keywords (`int`, `if`, `else`, `while`, `print`), one- and two-character operators (`==`, `!=`, `<=`, and so on), `//` line comments and whitespace. Keywords are separated from identifiers with a small trie.

### parser (todo)



### compiler (todo)



### vm 

Runs the bytecode. A plain fetch-decode-execute loop over an array of instructions: read the instruction the pointer is on, switch on its opcode, do the work, advance. The operand stack is an array of `int64`; every operation pops its arguments off the top and pushes the result back.

instruction set:

- `push` / `pop`
- `add`, `sub`, `mul`, `div`, `neg`
- `eq`, `neq`, `lt`, `gt`, `le`, `ge` (each leaves 1 or 0 on the stack)
- `jmp`, `jmp_if_false` (relative offsets)
- `load_local`, `store_local` (variables, addressed by stack slot)
- `print`, `stop`

## bytecode

Fixed-width instructions: an opcode and a 64-bit argument. Most instructions ignore the argument. `push` uses it for the literal value, jumps use it for the offset, `load_local` / `store_local` use it for the slot index. .

## stack

- C17
- standard library only, no dependencies
- MinGW (gcc) on Windows

## build

```
.\build.bat
```

tests build:

```
.\test.bat
```
