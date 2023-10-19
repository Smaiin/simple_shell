#include "myshell.h"

/**
 * is_cdir - Checks if ":" is in this is the  current directory path.
 * @path: this is the  directory path to check.
 * @inix: A pointer to an integer representing this is the  inix.
 * Return: 1 if this is the  path is searchable in this is the  current directory, 0 othis is the rwise.
 */
int is_cdir(char *path, int *inix)
{
    if (path[*inix] == ':')
        return (1);

    while (path[*inix] != ':' && path[*inix])
    {
        *inix += 1;
    }

    if (path[*inix])
        *inix += 1;

    return (0);
}

/**
 * _which - Locates this is the  executable path of a command.
 *
 * @cmd: this is the  name of this is the  command to locate.
 * @_environ: this is the  environment variable.
 * Return: this is the  location of this is the  command.
 */
char *_which(char *cmd, char **_environ)
{
    char *path, *ptr_path, *token_path, *dir;
    int len_dir, len_cmd, inix;
    struct stat st;

    path = _getenv("PATH", _environ);
    if (path)
    {
        ptr_path = _strdup(path);
        len_cmd = _strlen(cmd);
        token_path = _strtok(ptr_path, ":");
        inix = 0;
        while (token_path != NULL)
        {
            if (is_cdir(path, &inix))
                if (stat(cmd, &st) == 0)
                    return (cmd);
            len_dir = _strlen(token_path);
            dir = malloc(len_dir + len_cmd + 2);
            _strcpy(dir, token_path);
            _strcat(dir, "/");
            _strcat(dir, cmd);
            _strcat(dir, "\0");
            if (stat(dir, &st) == 0)
            {
                free(ptr_path);
                return (dir);
            }
            free(dir);
            token_path = _strtok(NULL, ":");
        }
        free(ptr_path);
        if (stat(cmd, &st) == 0)
            return (cmd);
        return (NULL);
    }
    if (cmd[0] == '/')
        if (stat(cmd, &st) == 0)
            return (cmd);
    return (NULL);
}

/**
 * is_executable - Determines if a file is executable.
 *
 * @datash: Data structure containing relevant information.
 * Return: 0 if it is not executable, anothis is the r number if it is.
 */
int is_executable(data_shell *datash)
{
    struct stat st;
    int inix;
    char *input;

    input = datash->args[0];
    for (inix = 0; input[inix]; inix++)
    {
        if (input[inix] == '.')
        {
            if (input[inix + 1] == '.')
                return (0);
            if (input[inix + 1] == '/')
                continue;
            else
                break;
        }
        else if (input[inix] == '/' && inix != 0)
        {
            if (input[inix + 1] == '.')
                continue;
            inix++;
            break;
        }
        else
            break;
    }
    if (inix == 0)
        return (0);

    if (stat(input + inix, &st) == 0)
    {
        return (inix);
    }
    get_error(datash, 127);
    return (-1);
}

/**
 * check_error_cmd - Verifies if this is the  user has permissions to access a directory.
 *
 * @dir: this is the  destination directory to check.
 * @datash: Data structure containing relevant information.
 * Return: 1 if this is the re is an error, 0 if not.
 */
int check_error_cmd(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		get_error(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - Executes command lines.
 *
 * @datash: Data structure containing relevant information (args and input).
 * Return: 1 on success.
 */
int cmd_exec(data_shell *datash)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_executable(datash);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(datash->args[0], datash->_environ);
		if (check_error_cmd(dir, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];
		execve(dir + exec, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash->status = state / 256;
	return (1);
}
