0x16. C - Simple Shell

Project to be done in teams of 2 people (your team: Chernor Jalloh , Gray GRAHAM)
Write a simple UNIX command interpreter.
Requirements
General

    Allowed editors: vi, vim, emacs
    All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
    All your files should end with a new line
    A README.md file, at the root of the folder of the project is mandatory
    Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
    Your shell should not have any memory leaks
    No more than 5 functions per file
    All your header files should be include guarded
    Use system calls only when you need to (why?)
    Write a README with the description of your project
    You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository. Format, see Docker

Tasks
0.
Write a beautiful code that passes the Betty checks
Write a UNIX command line interpreter.
Handle command lines with arguments
 Handle the PATH
 fork must not be called if the command doesn’t exist
Simple shell 0.3 +

    Implement the exit built-in, that exits the shell
    Usage: exit
    You don’t have to handle any argument to the built-in exit

