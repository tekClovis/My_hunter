/*
** EPITECH PROJECT, 2024
** Semester_1
** File description:
** my_get_round
*/
#include "include.h"

char *get_round(int nb)
{
    char *round;
    int len = my_nbrlen(nb);
    int i = 0;

    if (malloc(sizeof(my_nbrlen(nb) + 1)) != NULL)
        round = malloc(sizeof(my_nbrlen(nb) + 1));
    for (; i < len + 1; i++){
        round[len - i] = nb % 10 + 48;
        nb /= 10;
    }
    round[i] = '\0';
    return round;
}
