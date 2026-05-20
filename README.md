# Simple Shell

A simple UNIX command line interpreter written in C, replicating core behaviors of `sh`. Built as part of the Holberton School curriculum.

## Description

`hsh` reads commands from standard input, parses them, and executes them in a child process using `execve`. It supports executing programs by absolute path or by name via `PATH`, handles arguments, and implements the `exit` and `env` built-ins.

## Requirements

- OS: Ubuntu 20.04 LTS
- Compiler: `gcc` 9.3.0 or later
- Style: Betty-compliant

## Compilation

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive mode

```
$ ./hsh
$ /bin/ls
AUTHORS  README.md  hsh
$ ls
AUTHORS  README.md  hsh
$ exit
$
```

### Non-interactive mode

```
$ echo "/bin/ls" | ./hsh
AUTHORS  README.md  hsh
```

## Features

| Feature           | Description                                     |
| ----------------- | ----------------------------------------------- |
| Prompt            | Displays `$ ` and waits for input on each cycle |
| Command execution | Runs commands using `execve` after `fork`       |
| Arguments         | Handles commands with any number of arguments   |
| `PATH` resolution | Searches every directory listed in `PATH`       |
| Fork optimization | Does not `fork` if the command is not found     |
| Error handling    | Prints proper error messages to `stderr`        |
| EOF handling      | Exits cleanly on `Ctrl+D`                       |
| `exit` built-in   | Exits the shell                                 |
| `env` built-in    | Prints the current environment                  |

## File structure

| File                 | Purpose                                          |
| -------------------- | ------------------------------------------------ |
| `shell.h`            | Header file with prototypes and includes         |
| `main.c`             | Main read–parse–execute loop and prompt handling |
| `executor.c`         | `fork`/`execve` logic and PATH resolution        |
| `env.c`              | `env` built-in and environment helpers           |
| `man_1_simple_shell` | Manual page (section 1)                          |
| `AUTHORS`            | List of contributors                             |

## Examples

```
$ ./hsh
$ /bin/pwd
/home/user/simple_shell
$ env
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
HOME=/home/user
...
$ nonexistent_command
./hsh: 1: nonexistent_command: not found
$ exit
$
```

## Manual page

After cloning, view the manual with:

```
man ./man_1_simple_shell
```

## Authors

- Abdulrahman Wadani — [@Abdulrahman-Wadani](https://github.com/Abdulrahman-Wadani)
- Abdulrahman Asiri — [@abdularhman2341](https://github.com/abdularhman2341)

## License

This project is part of the Holberton School curriculum at Tuwaiq Academy.