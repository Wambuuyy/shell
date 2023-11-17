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
		exitcheck = _erratoi(input->argv[1]);
		if (exitcheck == -1)
		{
			input->status = 2;
			print_error(input, "Illegal number: ");
			_eputs(input->argv[1]);
			_eputchar('\n');
			return (1);
		}

		input->err_num = _erratoi(input->argv[1]);
		return (-2);
	}
	input->err_num = -1;
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
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!input->argv[1])
	{
		dir = _getenv(input, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(input, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(input->argv[1], "-") == 0)
	{
		if (!_getenv(input, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(input, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(input, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(input->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(input, "can't cd to ");
		_eputs(input->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(input, "OLDPWD", _getenv(input, "PWD="));
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
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

