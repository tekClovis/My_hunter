/*
** EPITECH PROJECT, 2024
** Semester_1
** File description:
** include
*/
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Window/Event.h>
#include <stdlib.h>

#ifndef INCLUDE_H
    #define INCLUDE_H

typedef struct player_s {
    sfVector2f pos;
    sfVector2f pos_scope;
    sfIntRect rect;
    sfClock *clock;
    sfSprite *weapon;
    sfSprite *scope;
    sfSound *s_sound;
    sfMusic *music;
    int is_shooting;
    int life;
    int ammo;
    int score;
    int in_menu;
    int round;
    float c_speed;
    int d_round;
} player_t;

typedef struct coin_s {
    sfIntRect rect;
    sfSprite *sprite;
    sfVector2f pos;
    sfClock *clock;
    int headxl;
    int headyt;
    int headxr;
    int headyb;
} coin_t;

typedef struct asset_s {
    sfSprite *back;
    sfSprite *cloud1;
    sfSprite *cloud2;
    sfSprite *ammo;
    sfSprite *life;
    sfText *score;
    sfIntRect rect_a;
    sfIntRect rect_l;
} asset_t;

typedef struct menu_s {
    sfSprite *resume;
    sfSprite *exit;
    sfSprite *game_o;
    sfSprite *restart;
    sfSprite *start;
    sfIntRect hb_resume;
    sfIntRect hb_exit;
    sfIntRect hb_restart;
    sfIntRect hb_start;
    sfText *h_score_nb;
    sfText *h_score;
    sfText *title;
    sfMusic *music;
    int pause;
} menu_t;

typedef struct node_s {
    coin_t *data;
    struct node_s *next;
    struct node_s *prev;
} node_t;

typedef struct list_s {
    int size;
    node_t *head;
    node_t *tail;
} list_t;

int my_cat(char *file);
char *my_cat_char(char *file);
char *my_strdup(char const *src);
int my_strcmp(char const *s1, char const *s2);
char *get_round(int nb);
int my_nbrlen(int nb);
int my_getnbr(char const *str);
char *my_get_score(int nb);
void handle_h_s(int score);
void analyse_e(sfEvent *e, list_t *c, player_t *p);
void animation(list_t *l, player_t *p, sfRenderWindow *w, asset_t *a);
void anim_weapon(player_t *p);
void analyse_e_menu(sfRenderWindow *w, player_t *p, menu_t *m, sfEvent *e);
void display_menu(sfRenderWindow *w, menu_t *m, player_t *p, asset_t *a);
void manage_mouse_move(player_t *p, sfMouseMoveEvent *e);
menu_t *set_menu(void);
asset_t *set_asset(void);
sfRenderWindow *set_window(void);
player_t *set_player(void);
coin_t *set_coin(void);
list_t *list_create(void);
int push_front(list_t *list, void *data);
int push_back(list_t *list, void *data);
void destroy_coin(coin_t *coin);
int destroy_nodes(list_t *list, node_t *current);
void destroy(list_t *l, asset_t *a, player_t *p, menu_t *m);

#endif /* INCLUDE_H_ */
