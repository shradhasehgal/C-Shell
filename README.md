# Nash - Linux Shell in C

## Introduction

This is an implementation of a Linux shell written in C language.


## Run the shell

1. Clone this directory and `cd` into it.
2. Run the command `make`.
3. Run `./shell` to get a prompt of the form `username@system_name:path`.
4. Run any command in the shell. It can entail as many number of tabs and spaces, the shell accounts for those.
5. In order to exit, run `quit`.

## Features

### Built-in commands

These commands have been defined by me and are contained within the shell itself.

1. `pwd`
    
    - Displays the name of the working directory.
    - Implemented in [pwd.c](pwd.c)

2. `ls [-l -a] [directory]`
    
    - Lists all the files and directories in the specified directory in alphabetical order.
    - Variations such as `ls, ls . , ls ..` also work.
    - Also handles multiple directories as arguments. eg. `ls -l dir1 dir2 dir3`.
    - Throws error if you try to `ls` on anything except a directory. 
    - Also highlights directories in blue and executable files in green.
    - Implemented in [ls.c](ls.c)

3. `cd [file]`
    
    - Changes directory to the directory specified, throws an error if the directory does not exist.
    - Implemented in [cd.c](cd.c)

4. `echo [arguments]`
    
    - Displays whatever is specified in [arguments]. 
    - Accounts for double quotes as well.
    - Implemented in [echo.c](echo.c)

5. `quit`

    - Exits the shell with return status as success, and adds updates [history.txt](history.text).

6. `setenv var[value]` & `unset var`

    - Creates an enviornmental variable `var` if it doesn't already exist and assigns it the value given
    - `unset var` destroys that environmental variable

7.  `jobs`

    - Prints a list of all currently running jobs along with their pid in order of their creation
    - Gives the state of the job – Running, Sleeping, Stopped or Defunct
    - Implemented in [jobs.c](jobs.c)

8. `kjob <jobNumber> <signalNumber>` 
    
    - Takes the job id of a running job and sends a signal value to that process
    - Implemented in [kjob.c](kjob.c)

9. `fg <jobNumber>`
    
    - Brings a running or a stopped background job with given job number to foreground.
    - Implemented in [fg.c](fg.c)

10. `bg <jobNumber>`

    - Changes a stopped background job to a running background job.
    - Implemented in [bg.c](bg.c)

11. `overkill`

    - ​ Kills all background process at once.
    - Implemented in [overkill.c](overkill.c)

### Foreground and Background Processes

- All other commands are treated as system commands like emacs, vim etc.
- To run a process in the background, follow the command with a '&' symbol. Eg. `emacs &`.
- Upon termination of a background process, the shell prints its PID and exit status.
- Handles `&` no matter where it is in the end. eg. `emacs& , emacs         &, ls -l&`.
- Also returns number of background processes running currently.
- Implemented in [run.c](run.c) 

### Additional Commands

1. `pinfo [PID]`

    - Prints numerous details about the process such as its status, memory, and executable path.
    - Just `pinfo` with no arguments gives details of the shell.
    - Implemented in [pinfo.c](pinfo.c)

2. `history [num]`

    - Lists the last [num] commands. If no arguments are specified, it displays the last 10 commands.
    - Retains the `history` even upon Shell exit - uses [history.txt](history.text).
    - Implemented in [history.c](history.c) 

3. `nightswatch -n [seconds] [dirty/interrupt]`

    - `interrupt` argument prints the number of times CPU has been interrupted by keyboard.
    - `dirty` argument prints size of the dirty part of memory.
    - Executes every `n` number of seconds as specified by user.
    - Exits when symbol `q` is pressed.
    - Error handling done for incorrect arguments.

5. `cronjob -c [command] -t [time_period] -p [duration]`

    - Runs the command every t seconds until p time gets over.
    - Cron runs in the background so you can continue using the shell whilst the command is executed periodically

## Additional Features

1. `​CTRL-Z`

    - Changes the status of currently running job to stop, and pushes it to the background.

2. `CTRL-C`

    - Sends SIGINT signal to the current foreground job of the shell​.
    - If there is no foreground job, then the signal does not have any effect.

3. Command Recall using ‘UP’ arrow key

    - ‘UP’ key with the ‘ENTER’ key causes a new prompt to be displayed with the previous command and then that command is
executed. (similar to normal Ubuntu environment).
    - Pressing ‘UP’ key ‘K’ times consecutively leads to the K​th ​ previous command getting executed.

4. Input-Output Redirection & Piping

    - Handles `<`, `>`, `>>`, and `|` operators appropriately, wherever they are in the command
    - Throws error if syntax is incorrect


### Coding style

The code is completely modular with different `.c` files for each command, and a `main.c` binding them all together. `headers.h` entails all the necessary header files, and global variables. 


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE) file for details.

