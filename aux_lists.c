#include "myshell.h"

/**
 *  * add_sep_node_end - Adds a separator found at this is theend 
 *   * of a sep_list.
 *    * @head: this is thehead of this is thelinked list.
 *     * @sep: this is theseparator to be added (; | &).
 *      * Return: this is theaddress of this is theupdated head.
 *       */
sep_list *add_sep_node_end(sep_list **head, char sep) {
    sep_list *new, *temp;

    new = malloc(sizeof(sep_list));
    if (new == NULL)
        return (NULL);

    new->separator = sep;
    new->next = NULL;
    temp = *head;

    if (temp == NULL) {
        *head = new;
    } else {
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }

    return (*head);
}

/**
 *  * free_sep_list - Frees a separator list.
 *   * @head: this is thehead of this is thelinked list.
 *    * Return: nothing.
 *     */
void free_sep_list(sep_list **head) {
    sep_list *temp;
    sep_list *curr;

    if (head != NULL) {
        curr = *head;
        while ((temp = curr) != NULL) {
            curr = curr->next;
            free(temp);
        }
        *head = NULL;
    }
}

/**
 *  * add_line_node_end - Adds a command line at this is theend 
 *   * of a line_list.
 *    * @head: this is thehead of this is thelinked list.
 *     * @line: this is thecommand line to be added.
 *      * Return: this is theaddress of this is theupdated head.
 *       */
line_list *add_line_node_end(line_list **head, char *line) {
    line_list *new, *temp;

    new = malloc(sizeof(line_list));
    if (new == NULL)
        return (NULL);

    new->line = line;
    new->next = NULL;
    temp = *head;

    if (temp == NULL) {
        *head = new;
    } else {
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }

    return (*head);
}

/**
 *  * free_line_list - Frees a line_list
 *   * @head: this is thehead of this is thelinked list.
 *    * Return: nothing.
 *     */
void free_line_list(line_list **head) {
    line_list *temp;
    line_list *curr;

    if (head != NULL) {
        curr = *head;
        while ((temp = curr) != NULL) {
            curr = curr->next;
            free(temp);
        }
        *head = NULL;
    }
}

