# Linux Shell in C

## Introduction

This is an implementation of a Linux shell written in C language.


## Run the shell

1. Clone this directory and `cd` into it.
2. Run the command `make`
3. Run `./shell` to get a prompt of the form `username@system_name:path`
4. Run any command in the shell. It can entail as many number of tabs and spaces, the shell accounts for those.
5. In order to exit, run `quit`

## Features

### Built-in commands

These commands have been defined by me and are contained within the shell itself.

1. `pwd`
    
    - Displays the name of the working directory.
    - Implemented in [pwd.c](pwd.c)

2. `ls [-l -a] [file]`
    
    - Lists all the files and directories in the specified directory in alphabetical order.
    - Variations such as `ls, ls . , ls ..` also work.
    - Implemented in [ls.c](ls.c)

3. `cd [file]`
    
    - Changes directory to the directory specified, throws an error if the directory does not exist.
    - Implemented in [cd.c](cd.c)

4. `echo [arguments]`
    
    - Displays whatever is specified in [arguments]. 
    - Accounts for double quotes as well.
    - Implemented in [echo.c](echo.c)

### Foreground and Background Processes

- All other commands are treated as system commands like emacs, vim etc.
- To run a process in the background, follow the command with a '&' symbol. Eg. `emacs &`
- Upon termination of a background process, the shell prints its PID and exit status.
- Implemented in [run.c](run.c) 

### Additional Commands

1. `pinfo [PID]`

    - Prints numerous details about the process such as its status, memory, and executable path
    - Just `pinfo` with no arguments gives details of the shell.
    - Implemented in [pinfo.c](pinfo.c)

2. `history [num]`

    - Lists the last [num] commands. If no arguments are specified, it displays the last 10 commands.
    - Implemented in [history.c](history.c)



### Coding style

The code is completely modular with different `.c` files for each command, and a `main.c` binding them all together. `headers.h` entails all the necessary header files, and global variables. 


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE) file for details

