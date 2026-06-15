# pipex

A C reimplementation of the Unix shell pipeline. `pipex` reproduces what your
shell does when you write:

```bash
< infile cmd1 | cmd2 | ... | cmdn > outfile
```

It reads from an input file, runs a chain of commands connected by pipes —
each command's standard output becoming the next command's standard input —
and writes the final result to an output file.

This is a [42 School](https://42.fr) project. It is built around the core Unix
process-control system calls: `pipe`, `fork`, `dup2`, `execve`, and `waitpid`.

> Beyond the mandatory two-command pipeline, this implementation includes both
> bonus features: an **unlimited number of piped commands** and a **`here_doc`**
> input mode.

---

## Usage

```bash
# Standard mode
./pipex infile cmd1 cmd2 [...cmdn] outfile

# here_doc mode
./pipex here_doc LIMITER cmd1 cmd2 [...cmdn] outfile
```

### Standard mode

```bash
./pipex infile "grep a" "wc -l" outfile
```

is equivalent to:

```bash
< infile grep a | wc -l > outfile
```

With more than two commands the pipeline simply grows:

```bash
./pipex infile "cat" "grep error" "sort" "uniq" outfile
# < infile cat | grep error | sort | uniq > outfile
```

### here_doc mode

When the first argument is `here_doc`, input is read from the terminal instead
of a file. Lines are collected until a line matching `LIMITER` is entered, then
fed into the pipeline:

```bash
./pipex here_doc END "cat" "wc -w" outfile
> hello world
> here is some text
> END
```

is roughly equivalent to:

```bash
cat << END | wc -w > outfile
```

---

## Build

The project compiles with `make`. The included [`libft`](source/libft) is built
automatically as part of the process.

```bash
make        # build the `pipex` binary (also runs `make bonus` in libft)
make clean  # remove object files
make fclean # remove object files and the binary
make re     # full rebuild
```

| Setting | Value |
| ------- | ----- |
| Compiler | `gcc` |
| Flags | `-Wall -Werror -Wextra -g` |
| Library | `source/libft/libft.a` |

---

## How it works

`main` orchestrates the whole pipeline:

1. **Parse the PATH** — `path_var` pulls the `PATH` variable out of the
   environment and splits it into a list of searchable directories.
2. **Parse arguments** — `ft_parsing` resolves each command name to a full
   executable path (`check_bin`), splits its arguments, and stores everything in
   a `t_all` structure. It also detects `here_doc` mode and prepares the input
   accordingly.
3. **Create pipes** — one `pipe()` is created for every connection between two
   adjacent commands (`n` commands → `n - 1` pipes).
4. **Fork the children** — `ft_forks` forks one child process per command. Each
   child (`child1`) wires up its file descriptors with `dup2` (`dupfd`), closes
   the descriptors it does not need (`closefiledes`), and replaces itself with
   the target program via `execve`.
5. **Wait** — the parent closes all pipe ends and `waitpid`s on every child
   before freeing all allocated memory (`freevars`).

In `here_doc` mode, `ft_here_doc` reads from standard input line by line until
the limiter is reached, buffering the content into a temporary file (`file.tmp`)
that is used as the pipeline's input and unlinked on cleanup.

---

## Project structure

```
pipex/
├── Makefile
├── includes/
│   ├── pipex.h          # structs (t_all, t_cmd, t_pip) and prototypes
│   └── libft.h
└── source/
    ├── pipex.c          # main, fork orchestration, child execution, wait
    ├── parse.c          # argument parsing, command resolution, here_doc
    ├── fd.c             # file-descriptor plumbing (dup2 / close logic)
    ├── utils.c          # PATH handling, binary lookup, memory cleanup
    └── libft/           # the 42 standard C library (built as libft.a)
```

### Key data structures (`includes/pipex.h`)

```c
typedef struct s_cmd {
    char  *name;     // resolved executable path
    char  **args;    // argv for the command
    char  *path;
}   t_cmd;

typedef struct s_pip {
    int   fd[2];     // pipe read/write ends
    int   fdin;      // input file descriptor  (first command)
    int   fdout;     // output file descriptor (last command)
}   t_pip;

typedef struct s_all {
    char  **pathvar;  // directories from PATH
    char  *infile;
    char  *outfile;
    char  *limiter;   // here_doc delimiter (NULL in standard mode)
    t_cmd *cmd;       // one entry per command
    size_t size;      // number of commands
    t_pip *pipes;
}   t_all;
```

---

## Notes & limitations

- Commands must be passed as **single quoted arguments** (e.g. `"grep a"`), so
  the program receives one argument per pipeline stage.
- The input file is opened read-only; the output file is created if missing and
  **truncated** on write.
- Commands are resolved against the directories in your `PATH`.

---

## Author

**ahammoud** ([@m4ntr4r4m4](https://github.com/m4ntr4r4m4)) — 42 cursus.
