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

### Phase 3 - Built-ins
* `cd` — change working directory
* `env` — display environment variables
* `exit` — exit the shell

Built-ins are handled directly by Minish rather than executed as
separate processes.

### Phase 4 - I/O Redirection
* `<` — redirect standard input
* `>` — redirect standard output
* `>>` — append standard output
* File handling with `open()`
* File descriptor replacement with `dup2()`

Examples:
```bash
minish$ cat < file.txt
minish$ echo hello > file.txt
minish$ echo world >> file.txt
```

### Phase 5 - Pipes
* Unix pipes using `pipe()`
* Multiple commands connected with `|`
* Process communication through file descriptors
* Pipeline synchronization with `waitpid()`

Example:
```bash
minish$ ls | grep .c
minish$ ls | wc -l
```

### Phase 6 - Signals
* `SIGINT` handling for `Ctrl-C`
* `SIGQUIT` handling
* Separate signal behavior for the shell and child processes
* Signal configuration using `sigaction()`

### Phase 7 - Command Parsing
* Dedicated command parser
* Separation of parsing and execution
* Quoted arguments
* Environment variable expansion
* Unmatched quote detection

Examples:
```bash
minish$ echo "hello world"
minish$ echo 'hello world'
minish$ echo $HOME
minish$ echo $USER
```

## Project Structure
```text
minish/
├── include/
│   └── minish.h
├── src/
│   ├── main.c
│   ├── input.c
│   ├── executor.c
│   ├── builtins.c
│   ├── pipes.c
│   ├── signals.c
│   └── parser.c
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
Minish is intentionally developed incrementally.
Advanced shell features such as:

* More complete quoting rules
* Complex command parsing
* Advanced redirection
* Command history
* Job control
* Shell scripting features
* Wildcard expansion

are not yet implemented.

## License
MIT License