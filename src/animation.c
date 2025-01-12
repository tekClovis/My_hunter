/*
** EPITECH PROJECT, 2024
** Semester_1
** File description:
** coincoin
*/
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include "include.h"

static void clock_coin(coin_t *c)
{
    sfTime time;
    float second = 0.0;

    time = sfClock_getElapsedTime(c->clock);
    second = time.microseconds / 1000000.0;
    if (second > 0.135) {
        if (c->rect.left < 330)
            c->rect.left += 110;
        if (c->rect.left >= 330)
            c->rect.left = 0;
        sfClock_restart(c->clock);
    }
    sfSprite_setTextureRect(c->sprite, c->rect);
}

static void move_coin(coin_t *c, player_t *p)
{
    if ((int)rand() % 2 == 0)
        c->pos.y += ((int)rand() % 2);
    else
        c->pos.y -= ((int)rand() % 2);
    c->pos.x += (1 * p->c_speed);
    if (c->pos.x > 1920)
        c->pos.x = -110;
    if (c->pos.y < -110){
        c->pos.y = 560;
        c->pos.x = -110;
    }
    if (c->pos.y > 900){
        c->pos.y = 560;
        c->pos.x = -110;
    }
    sfSprite_setPosition(c->sprite, c->pos);
}

static void verify_asset_sprite(asset_t *a, player_t *p)
{
    if (p->ammo == 3)
        a->rect_a.top = 0;
    if (p->ammo == 2)
        a->rect_a.top = 120;
    if (p->ammo == 1)
        a->rect_a.top = 240;
    if (p->ammo == 0)
        a->rect_a.top = 360;
    if (p->life == 3)
        a->rect_l.top = 0;
    if (p->life == 2)
        a->rect_l.top = 60;
    if (p->life == 1)
        a->rect_l.top = 120;
    if (p->life == 0)
        a->rect_l.top = 180;
    sfSprite_setTextureRect(a->ammo, a->rect_a);
    sfSprite_setTextureRect(a->life, a->rect_l);
}

static void draw_sprite(player_t *p, sfRenderWindow *w, asset_t *a)
{
    sfRenderWindow_drawSprite(w, p->weapon, NULL);
    sfRenderWindow_drawSprite(w, a->ammo, NULL);
    sfRenderWindow_drawSprite(w, a->life, NULL);
    sfRenderWindow_drawText(w, a->score, NULL);
}

void clock_round(player_t *p)
{
    sfTime time;
    float second = 0.0;

    time = sfClock_getElapsedTime(p->clock);
    second = time.microseconds / 1000000.0;
    if (p->round == 1 && second > 2.1){
        sfClock_restart(p->clock);
        time = sfClock_getElapsedTime(p->clock);
        second = time.microseconds / 1000000.0;
    }
    if (second > 2){
        sfClock_restart(p->clock);
        p->d_round = 0;
    }
}

static void set_round(player_t *player, sfRenderWindow *window)
{
    sfText *round = sfText_create();
    sfText *nb_round = sfText_create();
    sfVector2f pos_round = (sfVector2f){725, 300};
    sfVector2f pos_nb_round = (sfVector2f){1150, 300};

    sfText_setFont(round, sfFont_createFromFile("pixel.ttf"));
    sfText_setString(round, "ROUND");
    sfText_setPosition(round, pos_round);
    sfText_setCharacterSize(round, 100);
    sfText_setFont(nb_round, sfFont_createFromFile("pixel.ttf"));
    sfText_setString(nb_round, get_round(player->round));
    sfText_setPosition(nb_round, pos_nb_round);
    sfText_setCharacterSize(nb_round, 100);
    sfRenderWindow_drawText(window, round, NULL);
    sfRenderWindow_drawText(window, nb_round, NULL);
    clock_round(player);
    sfText_destroy(round);
    sfText_destroy(nb_round);
}

void animation(list_t *l, player_t *p, sfRenderWindow *w, asset_t *a)
{
    sfVector2f weapon_pos = {1920 -450, 1080 -375};
    node_t *current = l->head;

    sfRenderWindow_drawSprite(w, a->back, NULL);
    anim_weapon(p);
    verify_asset_sprite(a, p);
    sfText_setString(a->score, my_get_score(p->score));
    sfSprite_setTextureRect(p->weapon, p->rect);
    sfSprite_setPosition(p->weapon, weapon_pos);
    sfRenderWindow_drawSprite(w, a->cloud2, NULL);
    if (p->d_round == 1)
        set_round(p, w);
    while (current != NULL){
        clock_coin(current->data);
        move_coin(current->data, p);
        sfRenderWindow_drawSprite(w, current->data->sprite, NULL);
        current = current->next;
    }
    sfRenderWindow_drawSprite(w, a->cloud1, NULL);
    draw_sprite(p, w, a);
}
