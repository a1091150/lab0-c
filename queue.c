#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q) {
        return NULL;
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q) {
        return;
    }
    int size = q->size;
    list_ele_t *iter = q->head;
    for (int i = 0; i < size; i++) {
        list_ele_t *next = iter->next;
        free(iter->value);
        free(iter);
        iter = next;
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q) {
        return false;
    }

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        return false;
    }

    size_t size = strlen(s) + 1;
    newh->value = malloc(sizeof(char) * size);
    if (!newh->value) {
        free(newh);
        return false;
    }
    memset(newh->value, 0, size);
    memcpy(newh->value, s, size);

    if (!q->head) {
        q->head = newh;
        q->tail = newh;
        newh->prev = NULL;
        newh->next = NULL;
    } else {
        newh->next = q->head;
        q->head->prev = newh;
        q->head = newh;
        newh->prev = NULL;
    }

    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q) {
        return false;
    }

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        return false;
    }

    size_t size = strlen(s) + 1;
    newh->value = malloc(sizeof(char) * size);
    if (!newh->value) {
        free(newh);
        return false;
    }
    memset(newh->value, 0, size);
    memcpy(newh->value, s, size);

    if (!q->size) {
        q->head = newh;
        q->tail = newh;
        newh->prev = NULL;
        newh->next = NULL;
    } else {
        q->tail->next = newh;
        newh->prev = q->tail;
        q->tail = newh;
        q->tail->next = NULL;
    }

    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q) {
        return false;
    }

    if (q->size == 0) {
        return false;
    }

    list_ele_t *tmp = q->head;
    if (sp) {
        size_t size = strlen(tmp->value);
        size_t fixbufsize = bufsize - 1;
        size_t fixsize = size > fixbufsize ? fixbufsize : size;
        memset(sp, 0, bufsize);
        memcpy(sp, tmp->value, fixsize);
    }

    q->head = q->head->next;
    q->size--;
    if (q->size != 0) {
        q->head->prev = NULL;
    }
    free(tmp->value);
    free(tmp);
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return !q ? 0 : q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!q) {
        return;
    }

    if (!q->size) {
        return;
    }

    int half = q->size >> 1;
    list_ele_t *next = q->head;
    list_ele_t *prev = q->tail;
    for (int i = 0; i < half; i++) {
        char *tmp = next->value;
        next->value = prev->value;
        prev->value = tmp;
        next = q->head->next;
        prev = q->tail->prev;
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
