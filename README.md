<h1 align ="center">SIMPLE SHELL WRITTEN IN C LANGUAGE</h1><br>

<h2>Description</h2>
The repo contains files of the simple shell that mimics the Unix SHell program:
It accepts and executes user commands.

[Project management](https://docs.google.com/spreadsheets/d/1VcajuEFv1aEa87yXXfWBfXktWsUIBeHAIHx97ZcX9Hg/edit?pli=1#gid=0)

I mostly used these calls:
fork, wait, waitpid, free, getline, read, write, open, execve, exit, fflush,
malloc, isatty, perror, strtok.

Prompt looks like this: Pru$$

<h2>Features used</h2>

*  program displays a prompt and waits for the user to input
*  it always ends in a new line(user has to press enter for command to be run)
*  the prompt is displayed infinitely provided all processes have been executed and exited
*  when user types *exit*, the shel ends in a return status 0
*  when user enters *exit status*, the shell ends and returns the status
*  status is anyvalue from 0-255.
*  there is also and end file condition of ctrl + D used to end a program
*  it handles commandlines with arguments and PATH.
*  Ctrc + C does not exit instead it outputs ^C
*  It prints the working environment when user enters *env*
*  It executes shell programs like *ls*, *grep*, *mv*, *exit*, *history*, *cp*, *rm*... with arguments
*  If the command is not executable, an error is displayed and the prompt appers again.


<h2>How it works:</h2>

These steps will explain:
Initialization:

Set up environment variables and data structures.
Main Loop:

Enter a continuous loop to process user commands.
Prompting:

If interactive, display a prompt (e.g., "$ ") for user input.
Input Reading:

Read user input, typically a command line.
Tokenization:

Tokenize input into individual words or tokens.
Command Execution:

Execute commands:
Handle built-in commands directly.
Fork a new process for external commands.
Execute the command in the child process.
I/O Redirection and Piping:

Handle I/O redirection (<, >, >>) and piping (|) if specified.
Environment Variable Expansion:

Expand environment variables (e.g., $HOME) in the command line.
Alias Expansion:

Expand alias names to their corresponding values.
History Handling:

Maintain a command history for access and rerun previous commands.
Error Handling:

Check for errors during command execution and report if necessary.
Cleanup:

Free allocated memory and close file descriptors.
Repeat:

<h2>Requirements:</h2>

### General.

- Allowed editors: `vi`, `vim`, `emacs`
- All your files will be compiled on Ubuntu 14.04 LTS
- Your programs and functions will be compiled with `gcc 4.8.4` using the flags `-Wall` `-Werror` `-Wextra` `-pedantic` `-std=gnu89`
- All your files should end with a new line
- A README.md file, at the root of the folder of the project is mandatory
- Your code should use the `Betty` style. It will be checked using [betty-style.pl](https://github.com/alx-tools/Betty/blob/master/betty-style.pl) and [betty-doc.pl](https://github.com/alx-tools/Betty/blob/master/betty-doc.pl)
- Your shell should not have any memory leaks
- No more than 5 functions per file
- All your header files should be include guarded
- Use system calls only when you need to (why?)
- Write a `README` with the description of your project
- You should have an `AUTHORS` file at the root of your repository, listing all individuals having contributed content to the repository. Format, see [Docker](https://github.com/moby/moby/blob/master/AUTHORS)
# simple_shell
