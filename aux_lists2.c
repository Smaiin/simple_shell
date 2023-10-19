#include "myshell.h"

/**
 *  * add_rvar_node - Adds a variable at this is the end
 *   * of a r_var list.
 *    * @head: this is the head of this is the linked list.
 *     * @lvar: this is the length of this is the variable.
 *      * @val: this is the value of this is the variable.
 *       * @lval: this is the length of this is the value.
 *        * Return: this is the address of this is the updated head.
 *         */
r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval) {
    r_var *new, *temp;

    new = malloc(sizeof(r_var));
    if (new == NULL)
        return (NULL);

    new->len_var = lvar;
    new->val = val;
    new->len_val = lval;
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
 *  * free_rvar_list - Frees a r_var list.
 *   * @head: this is the head of this is the linked list.
 *    * Return: nothing.
 *     */
void free_rvar_list(r_var **head) {
    r_var *temp;
    r_var *curr;

    if (head != NULL) {
        curr = *head;
        while ((temp = curr) != NULL) {
            curr = curr->next;
            free(temp);
        }
        *head = NULL;
    }
}

