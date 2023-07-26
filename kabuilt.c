#include "shell1.h"

/**
 * custom_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info->arg_values[0] != "exit"
 */
int custom_exit(ShellInfo *info)
{
    int exit_check;

    if (info->arg_values[1])  /* If there is an exit argument */
    {
        exit_check = custom_error_atoi(info->arg_values[1]);
        if (exit_check == -1)
        {
            info->exit_status = 2;
            print_custom_error(info, "Illegal number: ");
            custom_puts(info->arg_values[1]);
            custom_putchar('\n');
            return (1);
        }
        info->error_num = custom_error_atoi(info->arg_values[1]);
        return (-2);
    }
    info->error_num = -1;
    return (-2);
}

/**
 * custom_cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int custom_cd(ShellInfo *info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
        custom_puts("TODO: >>getcwd failure emsg here<<\n");
    if (!info->arg_values[1])
    {
        dir = _getenv(info, "HOME=");
        if (!dir)
            chdir_ret = /* TODO: what should this be? */
                chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    else if (custom_strcmp(info->arg_values[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            custom_puts(s);
            custom_putchar('\n');
            return (1);
        }
        custom_puts(_getenv(info, "OLDPWD=")), custom_putchar('\n');
        chdir_ret = /* TODO: what should this be? */
            chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
    }
    else
        chdir_ret = chdir(info->arg_values[1]);
    if (chdir_ret == -1)
    {
        print_custom_error(info, "can't cd to ");
        custom_puts(info->arg_values[1]), custom_putchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * custom_help - displays help message
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int custom_help(ShellInfo *info)
{
    char **arg_array;

    arg_array = info->arg_values;
    custom_puts("help call works. Function not yet implemented \n");
    if (0)
        custom_puts(*arg_array); /* temp att_unused workaround */
    return (0);
}
