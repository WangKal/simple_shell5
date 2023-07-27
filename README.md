README, man, AUTHORS
Write a README
Write a man for your shell.
You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository.
Simple shell 0.1
Write a UNIX command line interpreter.
Your Shell should: Display a prompt and wait for the user to type a command. A command line always ends with a new line. The prompt is displayed again each time a command has been executed. The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features. The command lines are made only of one word. No arguments will be passed to programs. If an executable cannot be found, print an error message and display the prompt again. Handle errors. You have to handle the “end of file” condition (Ctrl+D)
You don’t have to: use the PATH implement built-ins handle special characters : ", ', `, , *, &, # be able to move the cursor handle commands with arguments
Simple shell 0.2
Handle command lines with arguments
Simple shell 0.3
Handle the PATH
Simple shell 0.4
Implement the exit built-in, that exits the shell
Usage: exit
You don’t have to handle any argument to the built-in exit
Simple shell 1.0
Implement the env built-in, that prints the current environment
Write a blogpost "What happens when you type ls -l in the shell"
Advanced
Test suite
Contribute to a test suite for your shell
Simple shell 0.2.1
Write your own strtok function
Simple shell 0.4.1
handle arguments for the built-in exit
Simple shell 0.4.2
Handle Ctrl+C: your shell should not quit when the user inputs ^C
setenv, unsetenv
Implement the setenv and unsetenv builtin commands
cd
Implement the builtin command cd
;
Handle the commands separator ;
alias
Implement the alias builtin command
Comments
Handle comments (#)
