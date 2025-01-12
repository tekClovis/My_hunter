/*
** EPITECH PROJECT, 2024
** Semester_1
** File description:
** handle_h_s
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "include.h"

void handle_h_s(int score)
{
    int h_s = my_getnbr(my_cat_char("h_score.txt"));
    FILE *file;

    if (score > h_s) {
        file = fopen("h_score.txt", "w");
        if (file == NULL) {
            write(2, "Error: Could not open h_score file.\n", 36);
            return;
        }
        fwrite(my_get_score(score), sizeof(char), 7, file);
        fclose(file);
    }
}
