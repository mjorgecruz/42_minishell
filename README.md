This repository contains the implementation of the Minishell project, a Unix system programming exercise assigned at 42. The project involves building a basic shell that mimics the behavior of the popular bash shell. It covers fundamental concepts such as process creation, input/output redirection, and signal handling.
Table of Contents

    Introduction
    Features
    Mandatory Part
    Bonus Part
    Installation
    Usage
    License

Introduction

The goal of the Minishell project is to help you understand how a shell works by building your own minimal version of bash. You will learn how to handle user input, execute commands, manage processes, and work with file descriptors. This project is a great opportunity to get familiar with the Unix programming environment and its system calls.
Features

    Display a prompt and wait for user input.
    Implement a command history.
    Parse and execute simple commands.
    Support for pipes (|) and redirections (<, >, >>, <<).
    Environment variable expansion (e.g., $HOME).
    Handle special characters like single (') and double quotes (").
    Handle signals such as Ctrl+C, Ctrl+D, and Ctrl+\.
    Implement the following built-in commands:
        echo with -n option
        cd (change directory)
        pwd (print working directory)
        export (set environment variables)
        unset (unset environment variables)
        env (display environment variables)
        exit (exit the shell)

Mandatory Part

    Shell Basics:
        Display a prompt while waiting for a new command.
        Parse and execute commands based on the PATH environment variable or using relative/absolute paths.
        Implement a simple history of executed commands.

    Redirections:
        <: Redirect input from a file.
        >: Redirect output to a file, overwriting if the file exists.
        >>: Append output to a file.
        <<: Here-document. Read input until a given delimiter is encountered.

    Pipes:
        Implement the | character to pipe the output of one command into the input of another.

    Environment Variables:
        Handle expansion of environment variables using $ followed by a sequence of characters.
        Support $? to get the exit status of the most recently executed foreground pipeline.

    Signal Handling:
        Ctrl+C: Display a new prompt on a new line.
        Ctrl+D: Exit the shell.
        Ctrl+\: Do nothing.

    Built-in Commands:
        echo with -n option
        cd with relative or absolute path
        pwd with no options
        export with no options
        unset with no options
        env with no options or arguments
        exit with no options

    Note: The use of more than one global variable is restricted to avoid accessing the main data structures directly from signal handlers.

Bonus Part

If you have completed the mandatory part perfectly, you can implement additional features such as:

    Logical Operators:
        Implement && and || with support for parentheses for precedence.

    Wildcards:
        Implement wildcard * expansion in the current working directory.
