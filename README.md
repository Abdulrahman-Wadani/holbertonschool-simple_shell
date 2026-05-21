# Simple Shell

A simple UNIX command line interpreter written in C, replicating core behaviors of `sh`. Built as part of the Holberton School curriculum.

## Description

`simple_shell` reads commands from standard input, splits them into tokens by whitespace (space, tab, newline), and executes them in a child process using `execve`. It supports executing programs by absolute/relative path or by name via the `PATH` environment variable, and implements the `exit` and `env` built-ins.

## Requirements

- OS: Ubuntu 20.04 LTS
- Compiler: `gcc` 9.3.0 or later
- Style: Betty-compliant

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive mode

```
$ ./hsh
$ /bin/ls
AUTHORS  README.md  env.c  executor.c  hsh  main.c  man_1_simple_shell  shell.h
$ ls
AUTHORS  README.md  env.c  executor.c  hsh  main.c  man_1_simple_shell  shell.h
$ exit
$
```

### Non-interactive mode

```
$ echo "/bin/ls" | ./hsh
AUTHORS  README.md  env.c  executor.c  hsh  main.c  man_1_simple_shell  shell.h
```

## Features

| Feature           | Description                                                           |
| ----------------- | --------------------------------------------------------------------- |
| Prompt            | Displays `$ ` in interactive mode (detected via `isatty`)             |
| Command execution | Runs commands using `execve` after `fork`                             |
| Arguments         | Supports commands with multiple arguments (token buffer of size 64)   |
| `PATH` resolution | Searches each directory listed in `PATH` in order                     |
| Fork optimization | Does not `fork` if the command is not found                           |
| Error handling    | Prints error messages to `stderr`                                     |
| EOF handling      | Exits cleanly on `Ctrl+D`                                             |
| `exit` built-in   | Exits the shell with the last command's exit status                   |
| `env` built-in    | Prints the current environment, one variable per line                 |

## File structure

| File                 | Purpose                                                         |
| -------------------- | --------------------------------------------------------------- |
| `shell.h`            | Header with includes, `extern environ`, and function prototypes |
| `main.c`             | Main read-parse-execute loop and built-in dispatch              |
| `executor.c`         | Tokenizer, `PATH` resolution, `fork`/`execve` execution logic   |
| `env.c`              | `env` built-in implementation                                   |
| `man_1_simple_shell` | Manual page                                                     |
| `AUTHORS`            | List of contributors                                            |

## Examples

```
$ ./hsh
$ /bin/pwd
/home/user/holbertonschool-simple_shell
$ env
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
HOME=/home/user
...
$ nonexistent_command
./hsh: 1: nonexistent_command: not found
$ exit
$
```

## Exit status

- Returns the exit status of the last executed command.
- Returns `127` when a command is not found.
- Returns `0` on `exit` or `Ctrl+D` if no earlier command failed.

## Limitations

- No support for pipes (`|`), redirections (`>`, `<`), or semicolons (`;`).
- No variable expansion or quoting.
- No command history or line editing.
- No job control or background execution (`&`).
- No aliases, functions, or shell scripts.

## Manual page

After cloning, view the manual with:

```bash
man ./man_1_simple_shell
```

## Authors

- Abdulrahman Wadani
- Abdulrahman Asiri

## License

This project is part of the Holberton School curriculum at Tuwaiq Academy.