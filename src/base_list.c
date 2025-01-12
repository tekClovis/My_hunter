/*
** EPITECH PROJECT, 2024
** Semester_1
** File description:
** my_apply_on_nodes
*/
#include "include.h"

list_t *list_create(void)
{
    list_t *list = malloc(sizeof(list_t));

    if (list == NULL)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

int push_front(list_t *list, void *data)
{
    node_t *current = malloc(sizeof(node_t));

    if (current == NULL)
        return 84;
    current->data = data;
    current->next = NULL;
    current->prev = NULL;
    if (list->head != NULL){
        list->head->prev = current;
        current->next = list->head;
    }
    if (list->tail == NULL)
        list->tail = current;
    list->head = current;
    list->size++;
    return 0;
}

int push_back(list_t *list, void *data)
{
    node_t *current = malloc(sizeof(node_t));

    current->data = data;
    current->next = NULL;
    current->prev = NULL;
    if (list->tail != NULL){
        list->tail->next = current;
        current->prev = list->tail;
    }
    if (list->head == NULL)
        list->head = current;
    list->tail = current;
    list->size++;
    return 0;
}

int destroy_nodes(list_t *list, node_t *current)
{
    if (!list)
        return 84;
    if (current){
        if (current->prev){
            current->prev->next = current->next;
        }
        if (current->next){
            current->next->prev = current->prev;
        }
        if (current == list->tail) {
            list->tail = current->prev;
        }
        if (current == list->head){
            list->head = current->next;
        }
        free(current->data);
    }
    list->size--;
    free(current);
    return 0;
}
