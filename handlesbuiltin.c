#include "main.h"

/**
 * _myexit - function that exits the shell with a given exit status
 * @information: A structure containing potential arguments used to maintain a
 * constant function prototype.
 * Return: exits with a given exit status (0) if info.argv[0] != "exit".
 */
int _myexit(info_t *information)
{
	int checkexit;

	if (information->argv[1])
	{
		checkexit = _erratoi(information->argv[1]);
		if (checkexit == -1)
		{
			information->status = 2;
			print_error(information, "Illegal number: ");
			_eputs(information->argv[1]);
			_eputchar('\n');
			return (1);
		}
		information->err_num = _erratoi(information->argv[1]);
		return (-2);
	}
	information->err_num = -1;
	return (-2);
}

/**
 * _mycd - a function that changes the current directory
 * @information: a Struct that holds potential arguments for
 *	maintaining a constant function prototype.
 * Return: 0 Always
 */

int _mycd(info_t *information)
{
	char *z, *direct, buffer[1024];
	int chdir_ret;

	z = getcwd(buffer, 1024);
	if (!z)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!information->argv[1])
	{
		direct = _getenv(information, "HOME=");
		if (!direct)
			chdir_ret = chdir((direct = _getenv(information,
				"PWD=")) ? direct : "/");
		else
			chdir_ret = chdir(direct);
	}
	else if (_strcmp(information->argv[1], "-") == 0)
	{
		if (!_getenv(information, "OLDPWD="))
		{
			_puts(z);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(information, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((direct = _getenv(information, "OLDPWD=")) ?
				direct : "/");
	}
	else
		chdir_ret = chdir(information->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(information, "can't cd to ");
		_eputs(information->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(information, "OLDPWD", _getenv(information, "PWD="));
		_setenv(information, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - a function that changes the current directory
 * @information: the structure used to maintain a constant function prototype
 * Return: Always 0
 */

int _myhelp(info_t *information)
{
	char **arg_arr;

	arg_arr = information->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}
