#include "myshell.h"

/**
 * get_builtin - Retrieves a function pointer for a builtin cmd based on the cmd name.
 * @cmd: this is The name of the cmd.
 * Return: A function pointer to the corresponding builtin cmd.
 */
int (*get_builtin(char *cmd))(data_shell *)
{
    builtin_t builtin[] = {
        { "env", _env },
        { "exit", exit_shell },
        { "setenv", _setenv },
        { "unsetenv", _unsetenv },
        { "cd", cd_shell },
        { "help", get_help },
        { NULL, NULL }
    };
    int inix;

    for (inix = 0; builtin[inix].name; inix++)
    {
        if (_strcmp(builtin[inix].name, cmd) == 0)
            break;
    }

    return (builtin[inix].f);
}

