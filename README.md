# PROJECT: C - Simple Shell

## AUTHORS: **Basil Bassey** and **Brian Levu**

*In partial fulfillment to course requirements of the ALX Software Engineering Program, `alx-low_level_programming`.*

![The Gates of Shell](https://s3.amazonaws.com/intranet-projects-files/holbertonschool-low_level_programming/235/shell.jpeg)
"The Gates of Shell”, by [Spencer Cheng](https://intranet.alxswe.com/rltoken/AtYRSM03vJDrko9xHodxFQ), featuring [Julien Barbier](https://intranet.alxswe.com/rltoken/-ezXgcyfhc8qU1DeUInLUA)

## Concepts

- [Everything you need to know to start coding your own shell](https://intranet.alxswe.com/concepts/64)
- [Approaching a Project](https://intranet.alxswe.com/concepts/350)

**Read or watch:**

- [Unix shell]
- [Thompson shell]
- [Ken Thompson]
- **Everything you need to know to start coding your own shell** concept page

**man or help:**

- `sh` (*Run `sh` as well*)

## Learning Objectives

At the end of this project, you are expected to be able to [explain to anyone](https://intranet.alxswe.com/rltoken/9LNz86CtOTos9oL3zxIO3A), **without the help of Google**:

### General

- Who designed and implemented the original Unix operating system
- Who wrote the first version of the UNIX shell
- Who invented the B programming **language** (the direct predecessor to the C programming language)
- Who is Ken Thompson
- How does a shell work
- What is a pid and a ppid
- How to manipulate the environment of the current process
- What is the difference between a function and a system call
- How to create processes
- What are the three prototypes of `main`
- How does the shell use the `PATH` to find the programs
- How to execute another program with the `execve` system call
- How to suspend the execution of a process until one of its children terminates
- What is `EOF` / “end-of-file”?

## Copyright - Plagiarism

- You are tasked to come up with solutions for the tasks below yourself to meet with the above learning objectives.
- You will not be able to meet the objectives of this or any following project by copying and pasting someone else’s work.
- You are not allowed to publish any content of this project.
- Any form of plagiarism is strictly forbidden and will result in removal from the program.

## Requirements

### General_2

- Allowed editors: `vi`, `vim`, `emacs`.
- All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options `-Wall -Werror -Wextra -pedantic -std=gnu89`.
- All your files should end with a new line.
- A `README.md` file, at the root of the folder of the project is mandatory.
- Your code should use the Betty style. It will be checked using [betty-style.pl](https://github.com/holbertonschool/Betty/blob/master/betty-style.pl) and [betty-doc.pl](https://github.com/holbertonschool/Betty/blob/master/betty-doc.pl).
- Your shell should not have any memory leaks.
- No more than 5 functions per file.
- All your header files should be include guarded.
Use system calls only when you need to ([why?](https://intranet.alxswe.com/rltoken/EU7B1PTSy14INnZEShpobQ))
- Write a `README` with the description of your project.
- You should have an `AUTHORS` file at the root of your repository, listing all individuals having contributed content to the repository. Format, see [Docker](https://intranet.alxswe.com/rltoken/UL8J3kgl7HBK_Z9iBL3JFg).

### Github

*There should be one project repository per group. If you and your partner have a repository with the same name in both your accounts, you risk a 0% score. Add your partner as a collaborator.*

## More Input

### Output

- Unless specified otherwise, your program **must have the exact same output** as `sh` (`/bin/sh`) as well as the exact same error output.
- The only difference is when you print an error, the name of the program must be equivalent to your `argv[0]`(See below)

Example of error with `sh`:

> $ echo "qwerty" | /bin/sh
>
> /bin/sh: 1: qwerty: not found
>
> $ echo "qwerty" | /bin/../.bin/sh
>
> /bin/../bin/sh: 1: qwerty: not found
> $

Same error with your program `hsh`:

> $ echo "qwerty" | ./hsh
>
> ./hsh: 1: qwerty: not found
> $ echo "qwerty" | ./././hsh
>
> ./././hsh: 1: qwerty: not found\
>
> $

## List of allowed  functions and system calls

- `access` (man 2 access)
- `chdir` (man 2 chdir)
- `close` (man 2 close)
- `closedir` (man 3 closedir)
- `execve` (man 2 execve)
- `exit` (man 3 exit)
- `_exit` (man 2 _exit)
- `fflush`(man 3 fflush)
- `fork` (man 2 fork)
- `free` (man 3 free)
- `getcwd` (man 3 getcwd)
- `getline` (man 3 getline)
- `getpid` (man 2 getpid)
- `isatty` (man 3 isatty)
- `kill` (man 2 kill)
- `malloc` (man 3 malloc)
- `open` (man 2 open)
- `opendir` (man 3 opendir)
- `perror` (man 3 perror)
- `read` (man 2 read)
- `readdir` (man 3 readdir)
- `signal` (man 2 signal)
- `stat` (__xstat) (man 2 stat)
- `lstat` (__lxstat) (man 2 lstat)
- `fstat` (__fxstat) (man 2 fstat)
- `strtok` (man 3 strtok)
- `wait` (man 2 wait)
- `waitpid` (man 2 waitpid)
- `wait3` (man 2 wait3)
- `wait4` (man 2 wait4)
- `write` (man 2 write)

## FILE LISTS

- _getline.c (*Contributor: **Brian Levu***)
- _strtok.c (*Contributor: **Brian Levu***)
- alias_management.c (*Contributor: **Brian Levu***)
- env-var_management.c (*Contributor: **Brian Levu***)
- environ_builtin.c (*Contributor: **Brian Levu***)
- execution.c (*Contributor: **Brian Levu***)
- expand.c (*Contributor: **Brian Levu***)
- extra_builtin.c (*Contributor: **Brian Levu***)
- find_path.c (*Contributor: **Brian Levu***)
- free_mem_management.c (*Contributor: **Brian Levu***)
- listed_builtins.c (*Contributor: **Basil Bassey***)
- numbers_management.c (*Contributor: **Basil Bassey***)
- print_management.c (*Contributor: **Basil Bassey***)
- shell_macros.h (*Contributor: **Basil Bassey***)
- shell_main.c (*Contributor: **Basil Bassey***)
- shell_main.h (*Contributor: **Basil Bassey***)
- simple_shell_manual.txt (*Contributor: **Basil Bassey***)
- string_management.c (*Contributor: **Basil Bassey***)
- README.md (*Contributor: **Basil Bassey***)
- AUTHORS (*Contributor: **Basil Bassey***)
