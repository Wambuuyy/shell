#include "shell.h"

/**
 * exit_handler - exits the shell
 * @input: Input struct
 * Return: Exits with a given exit status
 * (0) if input->argv[0] != "exit"
 */
int exit_handler(Input *input)
{
	int exitcheck;

	if (input->argv[1]) /* If there is an exit argument */
	{
		exitcheck = atoi(input->argv[1]);
		if (exitcheck == -1)
		{
			input->status = 2;
			print_error(input, "Illegal number: ");
			puts(input->argv[1]);
			putchar('\n');
			return (1);
		}

		input->error = atoi(input->argv[1]);
		return (-2);
	}
	input->error = -1;
	return (-2);
}

/**
 * cd_handler - changes the current directory of the process
 * @input: Input struct
 * Return: Always 0
 */
int cd_handler(Input *input)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		puts("TODO: >>getcwd failure emsg here<<\n");
	if (!input->argv[1])
	{
		dir = getenv("HOME");
		if (!dir)
			chdir_ret = 
				chdir((dir = getenv("PWD")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (strcmp(input->argv[1], "-") == 0)
	{
		if (!getenv("OLDPWD"))
		{
			puts(s);
			putchar('\n');
			return (1);
		}
		puts(getenv("OLDPWD")), putchar('\n');
		chdir_ret =
			chdir((dir = getenv("OLDPWD")) ? dir : "/");
	}
	else
		chdir_ret = chdir(input->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(input, "can't cd to ");
		puts(input->argv[1]), putchar('\n');
	}
	else
	{
		_setenv(input, "OLDPWD", getenv("PWD"));
		_setenv(input, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help_handler - changes the current directory of the process
 * @input: Input struct
 * Return: Always 0
 */
int help_handler(Input *input)
{
	char **arg_array;

	arg_array = input->argv;
	puts("help call works. Function not yet implemented \n");
	if (0)
		puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

