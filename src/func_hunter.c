/*
** EPITECH PROJECT, 2024
** Semester_1
** File description:
** func_hunter
*/
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <SFML/Window/Event.h>
#include <SFML/Audio.h>
#include <stdio.h>
#include "include.h"

void anim_weapon(player_t *p)
{
    sfTime time;
    float second = 0.0;

    time = sfClock_getElapsedTime(p->clock);
    second = time.microseconds / 1000000.0;
    if (second > 0.2 && p->is_shooting == 1) {
        if (p->rect.left <= 1000 && p->is_shooting != 0)
            p->rect.left += 500;
        if (p->rect.left > 1400 && p->rect.top == 420){
            p->is_shooting = 0;
            p->rect.left = 0;
            p->rect.top = 0;
        }
        if (p->rect.left > 1400 && p->rect.top == 0){
            p->rect.left = 0;
            p->rect.top = 420;
        }
        sfClock_restart(p->clock);
    }
}

static int verify_touch_h(player_t *p, coin_t *c)
{
    int hit_b_x1 = c->pos.x + 70;
    int hit_b_x2 = c->pos.x + 110;
    int hit_b_y1 = c->pos.y + 20;
    int hit_b_y2 = c->pos.y + 70;

    if (p->pos.x > hit_b_x1 && p->pos.x < hit_b_x2 &&
        p->pos.y > hit_b_y1 && p->pos.y < hit_b_y2)
        return 1;
    return 0;
}

static int verify_touch(player_t *p, coin_t *c)
{
    int hit_b_x1 = c->pos.x;
    int hit_b_x2 = c->pos.x + c->rect.width;
    int hit_b_y1 = c->pos.y;
    int hit_b_y2 = c->pos.y + c->rect.height;

    if (verify_touch_h(p, c) == 1)
        return 2;
    if (p->pos.x > hit_b_x1 && p->pos.x < hit_b_x2 &&
        p->pos.y > hit_b_y1 && p->pos.y < hit_b_y2)
        return 1;
    return 0;
}

static int update_touch(player_t *p, node_t *c)
{
    int verif = verify_touch(p, (coin_t *)c->data);

    if (verif == 2) {
        p->score += 1000;
        if (p->life != 3)
            p->life++;
        return 1;
    }
    if (verif == 1) {
        p->score += 500;
        return 1;
    }
    return 0;
}

void shoot(player_t *p, list_t *l)
{
    int len = l->size;
    node_t *current = l->head;

    p->is_shooting = 1;
    sfSound_play(p->s_sound);
    while (current != NULL) {
        if (update_touch(p, current) == 1){
            destroy_coin(current->data);
            destroy_nodes(l, current);
            break;
        }
        current = current->next;
    }
    if (len == l->size)
        p->life--;
    p->ammo--;
}

void manage_mouse_move(player_t *p, sfMouseMoveEvent *e)
{
    p->pos.x = e->x;
    p->pos.y = e->y;
    if (p->pos.y < 900 && p->in_menu == 0)
        p->pos_scope.y = e->y - 30;
    if (p->in_menu != 0)
        p->pos_scope.y = e->y - 30;
    p->pos_scope.x = e->x - 30;
    sfSprite_setPosition(p->scope, p->pos_scope);
}

void analyse_e(sfEvent *e, list_t *l, player_t *p)
{
    if (e->type == sfEvtMouseMoved)
        manage_mouse_move(p, &e->mouseMove);
    if (e->type == sfEvtMouseButtonPressed && p->ammo > 0
        && e->mouseButton.button == sfMouseLeft && p->is_shooting == 0
        && p->d_round == 0)
        shoot(p, l);
    if (e->type == sfEvtKeyPressed && e->key.code == sfKeyR &&
    p->is_shooting == 0 && p->d_round == 0)
        p->ammo = 3;
    if (e->type == sfEvtKeyPressed && e->key.code == sfKeyEscape)
        p->in_menu = 2;
}
