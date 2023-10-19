#include "myshell.h"

/**
 * free_data - data structure frees
 *
 * @datash: the Pointer to the data structure to be initialized
 * Return: nothing
 */
void free_data(data_shell *datash)
{
	unsigned int inix;

	for (inix = 0; datash->_environ[inix]; inix++)
	{
		free(datash->_environ[inix]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @datash:  the Pointer to the data structure to be initialized
 * @av: Argument vector containing initialization data
 * Return: no return is expected
 */
void set_data(data_shell *datash, char **av)
{
	unsigned int inix;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (inix = 0; environ[inix]; inix++)
		;

	datash->_environ = malloc(sizeof(char *) * (inix + 1));

	for (inix = 0; environ[inix]; inix++)
	{
		datash->_environ[inix] = _strdup(environ[inix]);
	}

	datash->_environ[inix] = NULL;
	datash->pid = aux_itoa(getpid());
}

/**
 * main - this is the starting point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 in success.
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&datash, av);
	shell_loop(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
