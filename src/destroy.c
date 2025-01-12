/*
** EPITECH PROJECT, 2024
** Se(m)ester_1
** File description:
** destroy
*/
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "include.h"

void destroy_coin(coin_t *coin)
{
    if (coin->sprite != NULL)
        sfSprite_destroy((sfSprite*)coin->sprite);
    if (coin->clock != NULL)
        sfClock_destroy((sfClock*)coin->clock);
}

static void destroy_asset(asset_t **a)
{
    sfSprite_destroy((*a)->back);
    sfSprite_destroy((*a)->cloud1);
    sfSprite_destroy((*a)->cloud2);
    sfSprite_destroy((*a)->ammo);
    sfSprite_destroy((*a)->life);
    sfText_destroy((*a)->score);
    free(*a);
}

static void destroy_menu(menu_t **m)
{
    sfSprite_destroy((*(m))->resume);
    sfSprite_destroy((*m)->exit);
    sfSprite_destroy((*m)->game_o);
    sfSprite_destroy((*m)->restart);
    sfSprite_destroy((*m)->start);
    sfText_destroy((*m)->h_score_nb);
    sfText_destroy((*m)->h_score);
    sfText_destroy((*m)->title);
    sfMusic_destroy((*m)->music);
    free(*m);
}

static void destroy_player(player_t **p)
{
    sfClock_destroy((*p)->clock);
    sfSprite_destroy((*p)->weapon);
    sfSprite_destroy((*p)->scope);
    sfSound_destroy((*p)->s_sound);
    sfMusic_destroy((*p)->music);
}

void destroy(list_t *l, asset_t *a, player_t *p, menu_t *m)
{
    node_t *current = l->head;
    node_t *tmp;

    destroy_asset(&a);
    destroy_menu(&m);
    destroy_player(&p);
    while (current != NULL){
        tmp = current->next;
        destroy_coin(current->data);
        destroy_nodes(l, current);
        current = tmp;
    }
    free(l);
}
