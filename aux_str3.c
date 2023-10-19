#include "myshell.h"

/**
 * rev_string - Reverses a string in place.
 * @s: this is theinput string to be reversed.
 * Return: nothing.
 */
void rev_string(char *s)
{
    int count = 0, inix, ji;
    char *str, temp;

    while (count >= 0)
    {
        if (s[count] == '\0')
            break;
        count++;
    }
    str = s;

    for (inix = 0; inix < (count - 1); inix++)
    {
        for (ji = inix + 1; ji > 0; ji--)
        {
            temp = *(str + ji);
            *(str + ji) = *(str + (ji - 1));
            *(str + (ji - 1)) = temp;
        }
    }
}

