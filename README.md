# minish
A tiny Unix shell written in C as a side project.

The goal is to build a shell from scratch and learn how processes, file
descriptors, input handling, pipes, redirection, and system calls work.

## To Build

```bash
make ./minish
```

## To Run

```bash
./minish
```

## Features

### Phase 1 - Input Loop
* Interactive and non-interactive modes
* Command-line input using `getline()`
* `isatty()` detection
* `exit` and EOF handling

### Phase 2 - External Commands
* Execute external programs
* Command arguments
* Process creation with `fork()`
* Program execution with `execvp()`
* Parent synchronization with `waitpid()`

Examples:

```bash
minish$ ls
minish$ ls -la
minish$ echo hello
minish$ pwd
```

### Phase 3 — Built-ins
* `cd` — change working directory
* `env` — display environment variables
* `exit` — exit the shell

Built-ins are handled directly by Minish rather than executed as separate processes.

## Project Structure
```text
minish/
├── include/
│   └── minish.h
├── src/
│   ├── main.c
│   ├── input.c
│   ├── executor.c
│   └── builtins.c
├── Makefile
├── .gitignore
├── LICENSE
└── README.md
```

## Build
```bash
make
```

To perform a clean rebuild: `make re`


## Run
```bash
./minish
```

## Clean

```bash
make clean
```

Remove all build files and the executable: `make fclean`

## Current Limitations
Minish does not yet support:
* Quoting
* I/O redirection
* Pipes
* Environment variable expansion
* Signal handling
* Command history
* Advanced parsing

These will be implemented progressively in later phases.

## License
MIT License