/*
** EPITECH PROJECT, 2024
** Semester_1
** File description:
** struct_init
*/
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "include.h"

static void set_texture(asset_t *asset)
{
    sfTexture *b = sfTexture_createFromFile("./img/background/1.png", NULL);
    sfTexture *c1 = sfTexture_createFromFile("./img/background/3.png", NULL);
    sfTexture *c2 = sfTexture_createFromFile("./img/background/4.png", NULL);
    sfTexture *a = sfTexture_createFromFile("./img/ammo.png", NULL);
    sfTexture *l = sfTexture_createFromFile("./img/life.png", NULL);
    sfVector2f scale_back = {3.66, 3.33};
    sfVector2f scale_life = {3, 3};
    sfVector2f scale_ammo = {1, 1};

    sfSprite_setTexture(asset->back, b, sfTrue);
    sfSprite_setTexture(asset->cloud1, c1, sfTrue);
    sfSprite_setTexture(asset->cloud2, c2, sfTrue);
    sfSprite_setTexture(asset->ammo, a, sfTrue);
    sfSprite_setTexture(asset->life, l, sfTrue);
    sfSprite_setScale(asset->back, scale_back);
    sfSprite_setScale(asset->cloud1, scale_back);
    sfSprite_setScale(asset->cloud2, scale_back);
    sfSprite_setScale(asset->life, scale_life);
    sfSprite_setScale(asset->ammo, scale_ammo);
}

asset_t *set_asset(void)
{
    asset_t *asset;
    sfVector2f pos_text = {850, 900};
    sfVector2f pos_life = {10, 900};
    sfVector2f pos_ammo = {600, 910};

    if (malloc(sizeof(asset_t)) != NULL)
        asset = malloc(sizeof(asset_t));
    *asset = (asset_t){sfSprite_create(), sfSprite_create(), sfSprite_create(),
            sfSprite_create(), sfSprite_create(), sfText_create(),
            (sfIntRect){0, 0, 150, 120}, (sfIntRect){0, 0, 200, 60}};
    sfText_setFont(asset->score, sfFont_createFromFile("pixel.ttf"));
    sfText_setString(asset->score, "0000000");
    sfText_setPosition(asset->score, pos_text);
    sfText_setCharacterSize(asset->score, 100);
    set_texture(asset);
    sfSprite_setTextureRect(asset->ammo, asset->rect_a);
    sfSprite_setTextureRect(asset->life, asset->rect_l);
    sfSprite_setPosition(asset->life, pos_life);
    sfSprite_setPosition(asset->ammo, pos_ammo);
    return asset;
}

sfRenderWindow *set_window(void)
{
    sfVideoMode mode = {1920, 1080, 32};
    sfRenderWindow *window;

    srand(time(NULL));
    window = sfRenderWindow_create(mode, "my_hunt",
        sfFullscreen | sfClose, NULL);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    sfRenderWindow_setFramerateLimit(window, 60);
    return window;
}

player_t *set_player(void)
{
    sfTexture *t_scope = sfTexture_createFromFile("./img/scope.png", NULL);
    sfTexture *weapon = sfTexture_createFromFile("./img/weapon.png", NULL);
    sfSoundBuffer *sound = sfSoundBuffer_createFromFile("./sound/shot.ogg");
    player_t *player;

    if (malloc(sizeof(player_t)) != NULL)
        player = malloc(sizeof(player_t));
    *player = (player_t){(sfVector2f){1080 / 2, 1920 / 2},
        (sfVector2f){1920 / 2 - 30, 1080 / 2 - 30},
        (sfIntRect){0, 0, 500, 420}, sfClock_create(), sfSprite_create(),
        sfSprite_create(), sfSound_create(),
        sfMusic_createFromFile("./sound/i_gmusic.ogg")
        , 0, 3, 3, 0, 1, 1, 4, 1};
    sfSound_setBuffer(player->s_sound, sound);
    sfMusic_setLoop(player->music, sfTrue);
    sfSprite_setTexture(player->scope, t_scope, sfTrue);
    sfSprite_setPosition(player->scope, player->pos_scope);
    sfSprite_setTexture(player->weapon, weapon, sfTrue);
    return player;
}

coin_t *set_coin(void)
{
    sfTexture *texture;
    coin_t *coin;

    if (malloc(sizeof(coin_t)) != NULL)
        coin = malloc(sizeof(coin_t));
    coin->rect = (sfIntRect){0, 0, 110, 110};
    coin->sprite = sfSprite_create();
    coin->clock = sfClock_create();
    texture = sfTexture_createFromFile("./img/canard.png", NULL);
    sfSprite_setTexture(coin->sprite, texture, sfTrue);
    coin->pos = (sfVector2f){((rand() % 1920) * -1) - 110, (rand() % 790)};
    coin->headxl = 60;
    coin->headyt = 0;
    coin->headxr = 110;
    coin->headyb = 40;
    return coin;
}

static void set_texture_menu(menu_t *menu)
{
    sfTexture *t_resu = sfTexture_createFromFile("./menu/resu.png", NULL);
    sfTexture *t_ex = sfTexture_createFromFile("./menu/ex.png", NULL);
    sfTexture *t_go = sfTexture_createFromFile("./menu/go.png", NULL);
    sfTexture *t_rest = sfTexture_createFromFile("./menu/rest.png", NULL);
    sfTexture *t_st = sfTexture_createFromFile("./menu/st.png", NULL);

    sfText_setFont(menu->h_score_nb, sfFont_createFromFile("pixel.ttf"));
    sfText_setCharacterSize(menu->h_score_nb, 100);
    sfText_setString(menu->h_score_nb, my_cat_char("h_score.txt\0"));
    sfText_setFont(menu->title, sfFont_createFromFile("pixel.ttf"));
    sfText_setCharacterSize(menu->title, 200);
    sfText_setString(menu->title, "MY HUNTER");
    sfText_setFont(menu->h_score, sfFont_createFromFile("pixel.ttf"));
    sfText_setCharacterSize(menu->h_score, 90);
    sfText_setString(menu->h_score, "HIGHEST SCORE:");
    sfSprite_setTexture(menu->resume, t_resu, sfTrue);
    sfSprite_setTexture(menu->exit, t_ex, sfTrue);
    sfSprite_setTexture(menu->game_o, t_go, sfTrue);
    sfSprite_setTexture(menu->restart, t_rest, sfTrue);
    sfSprite_setTexture(menu->start, t_st, sfTrue);
}

static void set_pos_menu(menu_t *menu)
{
    sfVector2f pos_title = {375, 50};
    sfVector2f pos_h_score_nb = {725, 400};
    sfVector2f pos_h_score = {525, 300};
    sfVector2f pos_ex = {825, 600};
    sfVector2f pos_go = {400, 100};
    sfVector2f pos_st = {825, 550};
    sfVector2f scale_go = {2, 2};
    sfVector2f scale_res = {0.5, 0.5};

    sfText_setPosition(menu->title, pos_title);
    sfText_setPosition(menu->h_score_nb, pos_h_score_nb);
    sfText_setPosition(menu->h_score, pos_h_score);
    sfSprite_setPosition(menu->resume, pos_st);
    sfSprite_setScale(menu->resume, scale_res);
    sfSprite_setPosition(menu->exit, pos_ex);
    sfSprite_setPosition(menu->game_o, pos_go);
    sfSprite_setScale(menu->game_o, scale_go);
    sfSprite_setPosition(menu->restart, pos_st);
    sfSprite_setPosition(menu->start, pos_st);
}

menu_t *set_menu(void)
{
    menu_t *menu;
    sfVector2f scale_res = {1, 0.8};

    if (malloc(sizeof(menu_t)) != NULL)
        menu = malloc(sizeof(menu_t));
    *menu = (menu_t){sfSprite_create(), sfSprite_create(), sfSprite_create(),
        sfSprite_create(), sfSprite_create(), (sfIntRect){0, 0, 200, 80},
        (sfIntRect){0, 0, 193, 49}, (sfIntRect){0, 0, 194, 63},
        (sfIntRect){0, 0, 199, 45}, sfText_create(), sfText_create(),
        sfText_create(), sfMusic_createFromFile("./sound/menu-music.ogg"), 0};
    set_texture_menu(menu);
    set_pos_menu(menu);
    sfSprite_setScale(menu->restart, scale_res);
    sfText_setColor(menu->title, sfRed);
    sfMusic_setLoop(menu->music, sfTrue);
    return menu;
}
