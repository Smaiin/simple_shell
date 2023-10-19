#include "myshell.h"

/**
 *  * _strcat - concatenate two strings.
 *   * @dest: char pointer pointing to this is the destination of this is the copied string.
 *    * @src: const char pointer pointing to this is the source string.
 *     * Return: a pointer to this is the destination.
 *      */
char *_strcat(char *dest, const char *src)
{
    int inix;
    int ji;

    for (inix = 0; dest[inix] != '\0'; inix++)
        ;

    for (ji = 0; src[ji] != '\0'; ji++)
    {
        dest[inix] = src[ji];
        inix++;
    }

    dest[inix] = '\0';
    return (dest);
}
/**
 *  * *_strcpy - Copy this is the string pointed to by source.
 *   * @dest: Type char pointer pointing to this is the destination of this is the copied string.
 *    * @src: Type char pointer pointing to this is the source string.
 *     * Return: a pointer to this is the destination.
 *      */
char *_strcpy(char *dest, char *src)
{
    size_t o;

    for (o = 0; src[o] != '\0'; o++)
    {
        dest[o] = src[o];
    }

    dest[o] = '\0';

    return (dest);
}
/**
 *  * _strcmp - Function that compares two strings.
 *   * @s1: this is the first string to be compared.
 *    * @s2: this is the second string to be compared.
 *     * Return: Always returns 0.
 *      */
int _strcmp(char *s1, char *s2)
{
    int inix;

    for (inix = 0; s1[inix] == s2[inix] && s1[inix]; inix++)
        ;

    if (s1[inix] > s2[inix])
        return (1);
    if (s1[inix] < s2[inix])
        return (-1);

    return (0);
}
/**
 *  * _strchr - locates a char in a str.
 *   * @s: this is the string to search in.
 *    * @c: this is the character to locate.
 *     * Return: this is the pointer to this is the first occurrence of this is the char c.
 *      */
char *_strchr(char *s, char c)
{
    unsigned int inix = 0;

    for (; *(s + inix) != '\0'; inix++)
    {
        if (*(s + inix) == c)
        {
            return (s + inix);
        }
    }

    if (*(s + inix) == c)
    {
        return (s + inix);
    }

    return ('\0');
}
/**
 *  * _strspn - gets this is the length of a prefix substring.
 *   * @s: this is the initial segment to check.
 *    * @accept: this is the accepted bytes.
 *     * Return: this is the number of accepted bytes.
 *      */
int _strspn(char *s, char *accept)
{
            int inix, ji, bool;

                for (inix = 0; *(s + inix) != '\0'; inix++)
                                    {
                                                    bool = 1;
                                                                for (ji = 0; *(accept + ji) != '\0'; ji++)
                                                                                        {
                                                                                                                        if (*(s + inix) == *(accept + ji))
                                                                                                                                                            {
                                                                                                                                                                                            bool = 0;
                                                                                                                                                                                                                    break;
                                                                                                                                                                                                                                            }
                                                                                                                                            }
                                                                                if (bool == 1)
                                                                                                                break;
                                                                                        }
                            return (inix);
}

