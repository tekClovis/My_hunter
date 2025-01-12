/*
** EPITECH PROJECT, 2024
** Semester_1
** File description:
** menu
*/
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "include.h"

void m_s_r(sfRenderWindow *w, player_t *p, menu_t *m, sfMouseButtonEvent *e)
{
    if (e->x > sfSprite_getPosition(m->start).x &&
        e->x < (sfSprite_getPosition(m->start).x + m->hb_start.width) &&
        e->y > sfSprite_getPosition(m->start).y &&
        e->y < (sfSprite_getPosition(m->start).y + m->hb_start.height)){
        sfMusic_stop(m->music);
        sfMusic_play(p->music);
        p->in_menu = 0;
        }
    if (e->x > sfSprite_getPosition(m->exit).x &&
        e->x < (sfSprite_getPosition(m->exit).x + m->hb_exit.width) &&
        e->y > sfSprite_getPosition(m->exit).y &&
        e->y < (sfSprite_getPosition(m->exit).y + m->hb_exit.height))
        sfRenderWindow_close(w);
}

void m_go(sfRenderWindow *w, player_t *p, menu_t *m, sfMouseButtonEvent *e)
{
    if (e->x > sfSprite_getPosition(m->restart).x &&
        e->x < (sfSprite_getPosition(m->restart).x + m->hb_restart.width) &&
        e->y > sfSprite_getPosition(m->restart).y &&
        e->y < (sfSprite_getPosition(m->restart).y + m->hb_restart.height)){
        p->in_menu = 4;
        }
    if (e->x > sfSprite_getPosition(m->exit).x &&
        e->x < (sfSprite_getPosition(m->exit).x + m->hb_exit.width) &&
        e->y > sfSprite_getPosition(m->exit).y &&
        e->y < (sfSprite_getPosition(m->exit).y + m->hb_exit.height))
        sfRenderWindow_close(w);
}

void analyse_e_menu(sfRenderWindow *w, player_t *p, menu_t *m, sfEvent *e)
{
    if (e->type == sfEvtMouseMoved)
        manage_mouse_move(p, &e->mouseMove);
    if (e->type == sfEvtMouseButtonPressed && (p->in_menu == 1 ||
        p->in_menu == 2) && e->mouseButton.button == sfMouseLeft)
        m_s_r(w, p, m, &e->mouseButton);
    if (e->type == sfEvtMouseButtonPressed && p->in_menu == 3
    && e->mouseButton.button == sfMouseLeft)
        m_go(w, p, m, &e->mouseButton);
}

static void draw_go(sfRenderWindow *w, menu_t *m, asset_t *a)
{
    sfVector2f y_score_pos = {600, 700};
    sfVector2f a_score_pos = {725, 800};
    sfText *y_score = sfText_create();

    sfText_setFont(y_score, sfFont_createFromFile("pixel.ttf"));
    sfText_setCharacterSize(y_score, 90);
    sfText_setString(y_score, "YOUR SCORE:");
    sfText_setPosition(y_score, y_score_pos);
    sfText_setString(m->h_score_nb, my_cat_char("h_score.txt"));
    sfText_setPosition(a->score, a_score_pos);
    sfRenderWindow_drawSprite(w, m->game_o, NULL);
    sfRenderWindow_drawText(w, m->h_score, NULL);
    sfRenderWindow_drawText(w, m->h_score_nb, NULL);
    sfRenderWindow_drawSprite(w, m->restart, NULL);
    sfRenderWindow_drawText(w, y_score, NULL);
    sfRenderWindow_drawText(w, a->score, NULL);
}

void display_menu(sfRenderWindow *w, menu_t *m, player_t *p, asset_t *a)
{
    if (p->in_menu == 1) {
        sfRenderWindow_drawText(w, m->title, NULL);
        sfRenderWindow_drawText(w, m->h_score, NULL);
        sfRenderWindow_drawText(w, m->h_score_nb, NULL);
        sfRenderWindow_drawSprite(w, m->start, NULL);
    }
    if (p->in_menu == 2) {
        sfRenderWindow_drawText(w, m->h_score, NULL);
        sfRenderWindow_drawText(w, m->h_score_nb, NULL);
        sfRenderWindow_drawSprite(w, m->resume, NULL);
    }
    if (p->in_menu == 3) {
        draw_go(w, m, a);
    }
    sfRenderWindow_drawSprite(w, m->exit, NULL);
}
