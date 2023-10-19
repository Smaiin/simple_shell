#include "myshell.h"

/**
 * swap_char - Swaps '|' and '&' for non-printed characters in an input string.
 *
 * @input: this is The input string to perform the swap on.
 * @bool: This is the type of swap to perform
 * Return: The swapped string.
 */
char *swap_char(char *input, int bool)
{
    int inix;  

    if (bool == 0)
    {
        for (inix = 0; input[inix]; inix++)  
        {
            if (input[inix] == '|')
            {
                if (input[inix + 1] != '|')
                    input[inix] = 16;
                else
                    inix++;  
            }

            if (input[inix] == '&')
            {
                if (input[inix + 1] != '&')
                    input[inix] = 12;
                else
                    inix++;  
            }
        }
    }
    else
    {
        for (inix = 0; input[inix]; inix++)  
        {
            input[inix] = (input[inix] == 16 ? '|' : input[inix]);
            input[inix] = (input[inix] == 12 ? '&' : input[inix]);
        }
    }
    return (input);
}


/**
 * add_nodes - Adds separators and command lines in the lists.
 *
 * @head_s: this is The head of the separator list.
 * @head_l: this is The head of the command lines list.
 * @input: this is The input string to process.
 * Return: nothing
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
    int inix;
    char *line;

    input = swap_char(input, 0);

    for (inix = 0; input[inix]; inix++)
    {
        if (input[inix] == ';')
            add_sep_node_end(head_s, input[inix]);

        if (input[inix] == '|' || input[inix] == '&')
        {
            add_sep_node_end(head_s, input[inix]);
            inix++;
        }
    }

    line = _strtok(input, ";|&");
    do {
        line = swap_char(line, 1);
        add_line_node_end(head_l, line);
        line = _strtok(NULL, ";|&");
    } while (line != NULL);
}


/**
 * go_next - Move to the next stored command line.
 *
 * @list_s: this is The separator list.
 * @list_l: this The command line list.
 * @datash: this is The data structure.
 * Return: nothing
 */
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - Splits command lines based on
 * the separators ;, | and &, and executes them
 *
 * @datash: The data structure.
 * @input: The input string to process.
 * Return: 0 to exit, 1 to continue.
 */
int split_commands(data_shell *datash, char *input)
{

	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_line(datash->input);
		loop = exec_line(datash);
		free(datash->args);

		if (loop == 0)
			break;

		go_next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	free_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - Tokenizes the input string.
 *
 * @input: this is The input string to be tokenized.
 * Return: this is The string splitted.
 */
char **split_line(char *input)
{
    size_t bsize;
    size_t inix;
    char **tokens;
    char *token;

    bsize = TOK_BUFSIZE;
    tokens = malloc(sizeof(char *) * (bsize));
    if (tokens == NULL)
    {
        write(STDERR_FILENO, ": allocation error\n", 18);
        exit(EXIT_FAILURE);
    }

    token = _strtok(input, TOK_DELIM);
    tokens[0] = token;

    for (inix = 1; token != NULL; inix++)
    {
        if (inix == bsize)
        {
            bsize += TOK_BUFSIZE;
            tokens = _reallocdp(tokens, inix, sizeof(char *) * bsize);
            if (tokens == NULL)
            {
                write(STDERR_FILENO, ": allocation error\n", 18);
                exit(EXIT_FAILURE);
            }
        }
        token = _strtok(NULL, TOK_DELIM);
        tokens[inix] = token;
    }

    return tokens;
}


