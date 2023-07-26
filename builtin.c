#include "shell.h"

/**
 * _kaexit - exits the shell
 * @in: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _kaexit(i *in)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi(in->argv[1]);
		if (exitcheck == -1)
		{
			in->status = 2;
			print_kaerror(in, "Illegal number: ");
			_eputs(in->argv[1]);
			_eputchar('\n');
			return (1);
		}
		in->err_num = _erratoi(in->argv[1]);
		return (-2);
	}
	in->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @in: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd(i *in)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_sput("TODO: >>getcwd failure emsg here<<\n");
	if (!in->argv[1])
	{
		dir = _genv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _genv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_cmpstr(in->argv[1], "-") == 0)
	{
		if (!_genv(in, "OLDPWD="))
		{
			_sput(s);
			_putchar('\n');
			return (1);
		}
		_sput(_genv(in, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _genv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_kaerror(in, "can't cd to ");
		_eputs(in->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(in, "OLDPWD", _genv(in, "PWD="));
		_setenv(in, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * usaidizi - changes the current directory of the process
 * @in: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int usaidizi(i *in)
{
	char **ag_arr;

	ag_arr = in->argv;
	_sput("Function not implemented \n");
	if (0)
		_sput(*ag_arr); /* temp att_unused workaround */
	return (0);
}
