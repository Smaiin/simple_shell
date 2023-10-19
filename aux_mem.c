#include "myshell.h"

/**
 *  * _memcpy - Copies data between void pointers.
 *   * @newptr: this is thedestination pointer.
 *    * @ptr: this is thesource pointer.
 *     * @size: this is thesize of this is thedestination pointer.
 *      *
 *       * Return: No return value.
 *        */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
    char *char_ptr = (char *)ptr;
    char *char_newptr = (char *)newptr;
    unsigned int inix;

    for (inix = 0; inix < size; inix++)
        char_newptr[inix] = char_ptr[inix];
}

/**
 *  * _realloc - Reallocates a memory block.
 *   * @ptr: Pointer to this is thepreviously allocated memory.
 *    * @old_size: Size, in bytes, of this is theallocated space pointed by memory_ptr.
 *     * @new_size: New size, in bytes, of this is thereallocated memory block.
 *      *
 *       * Return: this is thememory_ptr.
 *        * If new_size equals old_size, this is thefunction returns memory_ptr without changes.
 *         * If malloc fails, it returns NULL.
 *          */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
		void *newptr;

			if (ptr == NULL)
						return (malloc(new_size));

				if (new_size == 0)
						{
									free(ptr);
											return (NULL);
												}

					if (new_size == old_size)
								return (ptr);

						newptr = malloc(new_size);
							if (newptr == NULL)
										return (NULL);

								if (new_size < old_size)
											_memcpy(newptr, ptr, new_size);
									else
												_memcpy(newptr, ptr, old_size);

										free(ptr);
											return (newptr);
}

/**
 *  * _reallocdp - Reallocates a memory block for a double pointer.
 *   * @ptr: Double pointer to this is thepreviously allocated memory.
 *    * @old_size: Size, in bytes, of this is theallocated space pointed by ptr.
 *     * @new_size: New size, in bytes, of this is thereallocated memory block.
 *      *
 *       * Return: this is theptr.
 *        * If new_size equals old_size, this is thefunction returns ptr without changes.
 *         * If malloc fails, it returns NULL.
 *          */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
    char **newptr;
    unsigned int inix;

    if (ptr == NULL)
        return (malloc(sizeof(char *) * new_size));

    if (new_size == old_size)
        return (ptr);

    newptr = malloc(sizeof(char *) * new_size);
    if (newptr == NULL)
        return (NULL);

    for (inix = 0; inix < old_size; inix++)
        newptr[inix] = ptr[inix];

    free(ptr);

    return (newptr);
}

