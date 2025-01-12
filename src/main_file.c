/*
** EPITECH PROJECT, 2024
** Semester_1
** File description:
** window_manage
*/
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "include.h"

static int parsing(int ac, char **av)
{
    if (ac == 2 && my_strcmp(av[1], "-h") == 0){
        my_cat("description.txt");
        return 1;
    } else if (ac > 1) {
        return 84;
    }
    return 0;
}

void poll_e(sfRenderWindow *w, player_t *p, sfEvent *e, list_t *l)
{
    while (sfRenderWindow_pollEvent(w, e)) {
        analyse_e(e, l, p);
        if (e->type == sfEvtClosed)
            sfRenderWindow_close(w);
    }
}

void set_list(list_t *l, player_t *p)
{
    if (l->size != 0 || p->d_round == 1)
        return;
    p->c_speed += 0.6;
    for (int i = 0; i < (p->round + 2); i++)
        push_front(l, set_coin());
    p->round++;
    p->ammo = 3;
}

static void in_game(sfRenderWindow *w, asset_t *a, player_t *p, list_t *l)
{
    sfEvent e;

    set_list(l, p);
    poll_e(w, p, &e, l);
    if (p->life == 0) {
        sfMusic_stop(p->music);
        handle_h_s(p->score);
        p->in_menu = 3;
    }
    if (l->size == 0){
        p->d_round = 1;
    }
    sfRenderWindow_clear(w, sfBlack);
    animation(l, p, w, a);
    sfRenderWindow_drawSprite(w, p->scope, NULL);
    sfRenderWindow_display(w);
}

static void in_menu(sfRenderWindow *w, player_t *p, menu_t *m, asset_t *a)
{
    sfEvent e;

    while (sfRenderWindow_pollEvent(w, &e)) {
        analyse_e_menu(w, p, m, &e);
        if (e.type == sfEvtClosed)
            sfRenderWindow_close(w);
    }
    sfRenderWindow_clear(w, sfBlack);
    sfRenderWindow_drawSprite(w, a->back, NULL);
    display_menu(w, m, p, a);
    sfRenderWindow_drawSprite(w, p->scope, NULL);
    sfRenderWindow_display(w);
}

void restart(sfRenderWindow *w, player_t **p, list_t **l, asset_t *a)
{
    sfVector2f pos_text = {850, 900};
    node_t *current = (*l)->head;
    node_t *tmp;

    sfRenderWindow_clear(w, sfBlack);
    while (current != NULL){
        tmp = current->next;
        destroy_coin(current->data);
        destroy_nodes(*l, current);
        current = tmp;
    }
    sfText_setString(a->score, "0000000");
    sfText_setPosition(a->score, pos_text);
    free(*p);
    free(*l);
    *l = list_create();
    *p = set_player();
    sfMusic_play((*p)->music);
    (*p)->in_menu = 0;
}

int main(int argc, char **argv)
{
    asset_t *asset = set_asset();
    sfRenderWindow* window = set_window();
    list_t *list = list_create();
    player_t *player = set_player();
    menu_t *menu = set_menu();

    if (parsing(argc, argv) == 84)
        return 84;
    sfMusic_play(menu->music);
    while (sfRenderWindow_isOpen(window) && parsing(argc, argv) == 0) {
        if (player->in_menu == 0)
            in_game(window, asset, player, list);
        if (player->in_menu != 0 && player->in_menu != 4)
            in_menu(window, player, menu, asset);
        if (player->in_menu == 4)
            restart(window, &player, &list, asset);
    }
    destroy(list, asset, player, menu);
    sfRenderWindow_destroy(window);
    return 0;
}
