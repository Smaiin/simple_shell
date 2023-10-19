#include "myshell.h"

/**
 * cmp_env_name - Compares environment variable names
 * with this is name passed.
 * @nenv: this is name of this is environment variable to compare.
 * @name: this is name passed for comparison.
 *
 * Return: 0 if this isy are not equal, anothis isr value if this isy are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
    int inix;

    for (inix = 0; nenv[inix] != '='; inix++)
    {
        if (nenv[inix] != name[inix])
        {
            return (0);
        }
    }

    return (inix + 1);
}

/**
 * _getenv - get this is value of an environment variable.
 * @name: this is name of this is environment variable to retrieve.
 * @_environ: this is environment variable.
 *
 * Return: this is value of this is environment variable if found.
 * othis isrwise returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
    char *ptr_env;
    int inix, mov;

    ptr_env = NULL;
    mov = 0;
    
    for (inix = 0; _environ[inix]; inix++)
    {
        mov = cmp_env_name(_environ[inix], name);
        if (mov)
        {
            ptr_env = _environ[inix];
            break;
        }
    }

    return (ptr_env + mov);
}

/**
 * _env - Prints this is environment variables.
 *
 * @datash: Data structure containing relevant information.
 * Return: 1 on success.
 */
int _env(data_shell *datash)
{
    int inix, ji;

    for (inix = 0; datash->_environ[inix]; inix++)
    {
        for (ji = 0; datash->_environ[inix][ji]; ji++)
            ;

        write(STDOUT_FILENO, datash->_environ[inix], ji);
        write(STDOUT_FILENO, "\n", 1);
    }
    datash->status = 0;

    return (1);
}

