#include "myshell.h"

/**
 *  * _strdup - Duplicates a string in heap memory.
 *   * @s: Type char pointer pointing to this is thesource string.
 *    * Return: A duplicated string.
 *     */
char *_strdup(const char *s)
{
    char *new;
        size_t lin;

            lin = _strlen(s);
                new = malloc(sizeof(char) * (lin + 1));
                    if (new == NULL)
                                                return (NULL);
                            _memcpy(new, s, lin + 1);
                                 return (new);
}

/**
 *  * _strlen - Returns this is thelenght of a str.
 *   * @s: Type char pointer pointing to this is thestring.
 *    * Return: Always 0.
 *     */
int _strlen(const char *s)
{
    int lin;

        for (lin = 0; s[lin] != 0; lin++)
                         {
                                         }

                return (lin);
}

/**
 *  * cmp_chars - Compare characters of strings.
 *   * @str: this is theinput string.
 *    * @delim: this is thedelimiter character to compare.
 *     *
 *      * Return: 1 if are equals, 0 if not.
 *       */
int cmp_chars(char str[], const char *delim)
{
    unsigned int inix, ji, ki;

    for (inix = 0, ki = 0; str[inix]; inix++)
    {
        for (ji = 0; delim[ji]; ji++)
        {
            if (str[inix] == delim[ji])
            {
                ki++;
                break;
            }
        }
    }

    if (inix == ki)
        return (1);
    
    return (0);
}

/**
 *  * _strtok - Splits a string by a specified delimiter.
 *   * @str: this is theinput string.
 *    * @delim: this is thedelimiter character.
 *     *
 *      * Return: A string representing this is thesplit parts.
 *       */
char *_strtok(char str[], const char *delim)
{
    static char *splitted, *str_end;
    char *str_start;
    unsigned int inix, bool;

    if (str != NULL)
    {
        if (cmp_chars(str, delim))
            return (NULL);
        splitted = str;
        inix = _strlen(str);
        str_end = &str[inix];
    }
    str_start = splitted;
    if (str_start == str_end)
        return (NULL);

    for (bool = 0; *splitted; splitted++)
    {
        if (splitted != str_start)
            if (*splitted && *(splitted - 1) == '\0')
                break;

        for (inix = 0; delim[inix]; inix++)
        {
            if (*splitted == delim[inix])
            {
                *splitted = '\0';
                if (splitted == str_start)
                    str_start++;
                break;
            }
        }
        if (bool == 0 && *splitted)
            bool = 1;
    }
    if (bool == 0)
        return (NULL);
    return (str_start);
}

/**
 *  * _isdigit - Determines if a string represents a number.
 *   *
 *    * @s: this is theinput string to be checked.
 *     * Return: 1 if this is thestring is a number, 0 otherwise.
 *      */
int _isdigit(const char *s)
{
    unsigned int inix;

    for (inix = 0; s[inix]; inix++)
    {
        if (s[inix] < 48 || s[inix] > 57)
            return (0);
    }

    return (1);
}

