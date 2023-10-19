#include "myshell.h"

/**
 * without_comment - Removes comments from the input string.
 *
 * @in: this is The input string.
 * Return: The input string without comments.
 */
char *without_comment(char *in)
{
    int inix, up_to;

    up_to = 0;
    for (inix = 0; in[inix]; inix++)
    {
        if (in[inix] == '#')
        {
            if (inix == 0)
            {
                free(in);
                return (NULL);
            }

            if (in[inix - 1] == ' ' || in[inix - 1] == '\t' || in[inix - 1] == ';')
                up_to = inix;
        }
    }

    if (up_to != 0)
    {
        in = _realloc(in, inix, up_to + 1);
        in[up_to] = '\0';
    }

    return (in);
}


/**
 * shell_loop - Main loop of the shell.
 * @datash: Data structure relevant (av, input, args)
 *
 * Return: No return value.
 */
void shell_loop(data_shell *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			loop = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
