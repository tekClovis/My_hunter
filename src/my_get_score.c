/*
** EPITECH PROJECT, 2024
** Semester_1
** File description:
** my_get_str_nbr
*/
#include <stdlib.h>
#include "include.h"

char *my_get_score(int nbr)
{
    char *str;
    int len = my_nbrlen(nbr);
    int i = 0;

    if (malloc(sizeof(char) * 8) != NULL)
        str = malloc(sizeof(char) * 8);
    for (i = 0; i < 7 - len; i++)
        str[i] = '0';
    for (i = 0; i < len; i++){
        str[6 - i] = nbr % 10 + 48;
        nbr /= 10;
    }
    str[7] = '\0';
    return str;
}
