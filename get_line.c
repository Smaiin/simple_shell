#include "myshell.h"

/**
 * bring_line - Assigns the line variable for get_line.
 * @lineptr: the Pointer to a buffer that stores the input string.
 * @buffer: The string that is being assigned to the line.
 * @ni: Size of the line.
 * @ji: Size of the buffer.
 */
void bring_line(char **lineptr, size_t *ni, char *buffer, size_t ji)
{
    if (*lineptr == NULL)
    {
        if (ji > BUFSIZE)
            *ni = ji;
        else
            *ni = BUFSIZE;
        *lineptr = buffer;
    }
    else if (*ni < ji)
    {
        if (ji > BUFSIZE)
            *ni = ji;
        else
            *ni = BUFSIZE;
        *lineptr = buffer;
    }
    else
    {
        _strcpy(*lineptr, buffer);
        free(buffer);
    }
}
/**
 * get_line - Reads input from stream.
 * @lineptr: the Pointer to a buffer that stores the input.
 * @ni: Size of the line buffer.
 * @stream: The stream to read from.
 * Return: The number of bytes read.
 */
ssize_t get_line(char **lineptr, size_t *ni, FILE *stream)
{
    int inix;
    static ssize_t input;
    ssize_t retval;
    char *buffer;
    char t = 'z';

    if (input == 0)
        fflush(stream);
    else
        return (-1);
    input = 0;

    buffer = malloc(sizeof(char) * BUFSIZE);
    if (buffer == 0)
        return (-1);
    while (t != '\n')
    {
        inix = read(STDIN_FILENO, &t, 1);
        if (inix == -1 || (inix == 0 && input == 0))
        {
            free(buffer);
            return (-1);
        }
        if (inix == 0 && input != 0)
        {
            input++;
            break;
        }
        if (input >= BUFSIZE)
            buffer = _realloc(buffer, input, input + 1);
        buffer[input] = t;
        input++;
    }
    buffer[input] = '\0';
    bring_line(lineptr, ni, buffer, input);
    retval = input;
    if (inix != 0)
        input = 0;
    return (retval);
}


