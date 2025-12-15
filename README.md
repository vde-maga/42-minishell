# 42 - Minishell

[![Language](https://img.shields.io/badge/Language-C-blue.svg?style=for-the-badge)](https://en.wikipedia.org/wiki/C_(programming_language))
[![42 Porto](https://img.shields.io/badge/42%20Porto-School-blue?style=for-the-badge&logo=42)](https://www.42porto.com)
[![Status](https://img.shields.io/badge/Status-Completed-brightgreen.svg?style=for-the-badge)](https://projects.intra.42.fr/)

## About

Minishell is a project developed as part of the 42 school curriculum. It is an implementation of a Unix shell in the C language that offers basic command interpreter functionality, including parsing, command execution, redirection, pipes, and environment variable manipulation.

In this project, I had to work with advanced concepts such as memory management, processes, signals, and complex data structures such as abstract syntax trees (AST).

## Evaluation


![Evaluation Screenshot](/screenshots/evaluation.png)

## Features

### Main Features

- **Lexer**: Tokenization of user input
- **Parser**: Abstract syntax tree (AST) construction
- **Executor**: Command execution with support for pipes and redirections
- **Builtins**: Implemented internal commands (echo, cd, pwd, export, unset, env, exit)
- **Expander**: Expansion of environment variables and wildcards
- **Heredoc**: Support for heredoc with conditional variable expansion
- **Signals**: Proper handling of signals (SIGINT, SIGQUIT)
- **History**: Command history with readline

### Technical Features

- **Process Management**: Fork, exec, wait
- **Redirections**: `<`, `>`, `>>`, `<<`
- **Pipes**: Communication between processes
- **Logical Operators**: `&&`, `||` with short-circuiting
- **Subshells**: Execution in subprocesses with parentheses
- **Environment Variables**: Complete environment manipulation
- **Wildcards**: Pattern expansion with `*`


## Installation and Compile

### Dependencies

- GCC Compiler
- Readline Library
- Make
- Libft Library (already included)

### Compiling

```bash
# Compile
make

# Clean Object Files
make clean

# Clean All
make fclean

# Recompile
make re

# Debugging
make valgrind
```

## Instructions

### Use

```bash
./minishell
```

### Commands Examples

```bash
# Basic Command
ls -la
echo "Hello World"
pwd

# Redirects
echo "test" > file.txt
cat < file.txt

# Pipes
ls -la | grep ".c"

# Heredoc
cat << EOF
Hello
World
EOF

# Logic Operators
echo "success" && echo "also success"
echo "fail" || echo "this will print"

# Environment Variables
export MY_VAR="value"
echo $MY_VAR
unset MY_VAR

# Subshells
(cd /tmp && ls)
```

## Builtins

| Command | Description | Features |
|---------|-----------|----------------|
| `echo` | Displays arguments | Supports `-n` flag, multiple arguments |
| `cd` | Changes directory | Supports `~`, `-`, `--`, updates `PWD`/`OLDPWD` |
| `pwd` | Displays current directory | Absolute path |
| `export` | Sets/exports variables | Creates/updates environment variables |
| `unset` | Removes variables | Removes variables from the environment |
| `env` | Displays environment | Lists all environment variables |
| `exit` | Exits shell | Optional exit code, resource cleanup |

## Execution Flow

![Execution Flow](/screenshots/chart.png)