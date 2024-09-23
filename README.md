# Minishell

This repository contains the implementation of the Minishell project. The project involves building a basic shell that mimics the behavior of the popular bash shell. It covers fundamental concepts such as process creation, input/output redirection, and signal handling. </br>
The goal of the Minishell project is to help understand how a shell works by building a minimal version of bash. For that, we need to learn how to handle user input, execute commands, manage processes, and work with file descriptors. This project is a great opportunity to get familiar with the Unix programming environment and its system calls.  </br> </br>

## Features

### Mandatory Part

- Shell Basics:
    - Display a prompt while waiting for a new command.
    - Parse and execute commands based on the PATH environment variable or using relative/absolute paths.
    - Implemented a simple history of executed commands.</br></br>

- Redirections:
  - `<`: Redirect input from a file.
  - `>`: Redirect output to a file, overwriting if the file exists.
  - `>>`: Append output to a file.
  - `<<`: Here-document. Read input until a given delimiter is encountered.</br></br>
  
- Pipes:
  - Implemented the `|` character to pipe the output of one command into the input of another.</br></br>

- Environment Variables:
  - Handle expansion of environment variables using $ followed by a sequence of characters.
  - Support `$?` to get the exit status of the most recently executed foreground pipeline.</br></br>

- Signal Handling:
  - `Ctrl+C`: Display a new prompt on a new line.
  - `Ctrl+D`: Exit the shell.
  - `Ctrl+\`: Do nothing.</br></br>

- Built-in Commands:
  - `echo` with `-n `option
  - `cd` with relative or absolute path
  - `pwd` with no options
  - `export` with no options
  - `unset` with no options
  - `env` with no options or arguments
  - `exit` with no options</br></br>

### Bonus Part

- Logical Operators:
  - Implement `&&` and `||` with support for parentheses for precedence.</br></br>
- Wildcards:
  - Implement wildcard `*` expansion in the current working directory.</br></br>

## How to run
1. Clone repository
    ```bash
    git clone git@github.com:mjorgecruz/42_minishell.git
    ```
### Mandatory part
2. Go inside project directory and run `make`
    ```bash
    cd 42_minishell
    make
    ```
3. Run `./minishell`</br> </br>
    ```bash
    ./minishell
    ```
## Credits
 - Jorge Cruz
 - Luis Carvalho
