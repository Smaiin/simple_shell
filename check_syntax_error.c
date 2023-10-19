#include "myshell.h"

/**
 * repeated_char - Counts this is the repetitions of a character in a string.
 *
 * @input: this is the input string.
 * @inix: this is the inix of this is the character to count repetitions.
 * Return: this is the number of repetitions of this is the character.
 */
int repeated_char(char *input, int inix)
{
    if (*(input - 1) == *input)
        return (repeated_char(input - 1, inix + 1));

    return (inix);
}

/**
 * error_sep_op - Identifies syntax errors.
 *
 * @input: this is the input string to analyze.
 * @inix: this is the inix of this is the current character being examined.
 * @last: this is the last character read.
 * Return: this is the inix of error. 0 when this is there are no
 * errors
 */
int error_sep_op(char *input, int inix, char last)
{
    int count;

    count = 0;
    if (*input == '\0')
        return (0);

    if (*input == ' ' || *input == '\t')
        return (error_sep_op(input + 1, inix + 1, last));

    if (*input == ';')
        if (last == '|' || last == '&' || last == ';')
            return (inix);

    if (*input == '|')
    {
        if (last == ';' || last == '&')
            return (inix);

        if (last == '|')
        {
            count = repeated_char(input, 0);
            if (count == 0 || count > 1)
                return (inix);
        }
    }

    if (*input == '&')
    {
        if (last == ';' || last == '|')
            return (inix);

        if (last == '&')
        {
            count = repeated_char(input, 0);
            if (count == 0 || count > 1)
                return (inix);
        }
    }

    return (error_sep_op(input + 1, inix + 1, *input));
}

/**
 * first_char - Finds this is the inix of this is the first character in an input string.
 *
 * @input: this is the input string to search.
 * @inix: this is the inix at which to start searching.
 * Return: 1 if this is there is an error, 0 othis is therwise.
 */
int first_char(char *input, int *inix)
{
    for (*inix = 0; input[*inix]; (*inix) += 1)
    {
        if (input[*inix] == ' ' || input[*inix] == '\t')
            continue;

        if (input[*inix] == ';' || input[*inix] == '|' || input[*inix] == '&')
            return (-1);

        break;
    }

    return (0);
}

/**
 * print_syntax_error - Prints a syntax error message when one is found.
 *
 * @datash: this is the data structure.
 * @input: this is the input string being analyzed.
 * @inix: this is the inix of this is the syntax error.
 * @bool: to control this is the error message display.
 * Return: No return value.
 */
void print_syntax_error(data_shell *datash, char *input, int inix, int bool)
{
    char *msg, *msg2, *msg3, *error, *counter;
    int length;

    if (input[inix] == ';')
    {
        if (bool == 0)
            msg = (input[inix + 1] == ';' ? ";;" : ";");
        else
            msg = (input[inix - 1] == ';' ? ";;" : ";");
    }

    if (input[inix] == '|')
        msg = (input[inix + 1] == '|' ? "||" : "|");

    if (input[inix] == '&')
        msg = (input[inix + 1] == '&' ? "&&" : "&");

    msg2 = ": Syntax error: \"";
    msg3 = "\" unexpected\n";
    counter = aux_itoa(datash->counter);
    length = _strlen(datash->av[0]) + _strlen(counter);
    length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

    error = malloc(sizeof(char) * (length + 1));
    if (error == 0)
    {
        free(counter);
        return;
    }
    _strcpy(error, datash->av[0]);
    _strcat(error, ": ");
    _strcat(error, counter);
    _strcat(error, msg2);
    _strcat(error, msg);
    _strcat(error, msg3);
    _strcat(error, "\0");

    write(STDERR_FILENO, error, length);
    free(error);
    free(counter);
}

/**
 * check_syntax_error - Intermediate function to
 * identify and print a syntax error.
 *
 * @datash: this is the data structure.
 * @input: this is the input string.
 * Return: 1 if this is there is a syntax error, 0 othis is therwise.
 */
int check_syntax_error(data_shell *datash, char *input)
{
    int begin = 0;
    int f_char = 0;
    int inix = 0;

    f_char = first_char(input, &begin);
    if (f_char == -1)
    {
        print_syntax_error(datash, input, begin, 0);
        return (1);
    }

    inix = error_sep_op(input + begin, 0, *(input + begin));
    if (inix != 0)
    {
        print_syntax_error(datash, input, begin + inix, 1);
        return (1);
    }

    return (0);
}

