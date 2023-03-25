/*
 *   Copyright (C) 2023 YouLanjie
 *
 *   文件名称：init.c
 *   创 建 者：youlanjie
 *   创建日期：2023年01月24日
 *   描    述：初始化结构体数据
 *
 */


#include "game.h"

static int map_init(int y, int x);

/*
 * 初始化游戏数据
 */
int init(void)
{
	if (game_data.map != NULL) {
		free_pro(game_data.map);
	}
	/* Init map */
	map_init(MAP_HEIGHT, MAP_WIDTH);
	game_data.focus = game_data.map;
	return 0;
}

#define init_data(data, y, x)					\
	do {							\
		data = malloc(sizeof(Map));			\
		data->pos_x = x;				\
		data->pos_y = y;				\
		data->block = get_info(L_Block, "Null");	\
		data->drop  = NULL;				\
		data->friendly = NULL;				\
		data->monsters = NULL;				\
		if (y > 1 && up != NULL) {			\
			data->up       = up;			\
			data->up->down = data;			\
		} else {					\
			data->up = NULL;			\
		}						\
		data->down  = NULL;				\
		data->left  = NULL;				\
		data->right = NULL;				\
	}while(0)
/*
 * 初始化地图
 */
static int map_init(int y, int x)
{
	struct timeval gettime;
	Map	*data = NULL,
		*last = NULL,
		*up   = NULL;
	for (int i = 1; i <= y; ++i) {
		init_data(data, i, 1);
		last = data;
		if (up != NULL) {
			up = up->right;
		}
		if (i == 1) {
			game_data.map = game_data.focus = data;
		}
		for (int i2 = 2; i2 <= x; ++i2) {
			init_data(data, i, i2);
			data->left        = last;
			data->left->right = data;
			last              = data;
			if (i > 1 && up != NULL) {
				up->down  = data;
				up        = up->right;
			}
		}
		up = data;
		i++;
		if (i > y) {
			break;
		}
		init_data(data, i, x);
		last           = data;
		up             = up->left;
		for (int i2 = x - 1; i2 > 0; --i2) {
			init_data(data, i, i2);
			data->right       = last;
			data->right->left = data;
			last              = data;
			up                = up->left;
		}
		up = data;
	}
	gettimeofday(&gettime, NULL);
	srand(gettime.tv_usec + gettime.tv_sec);
	game_data.player.pos_y = rand() % (MAP_HEIGHT - 4) + 2;
	usleep(rand() % 1000);
	gettimeofday(&gettime, NULL);
	srand(gettime.tv_usec + gettime.tv_sec);
	game_data.player.pos_x = rand() % (MAP_WIDTH - 4) + 2;
	map_mk_room(game_data.player.pos_y, game_data.player.pos_x);
	return 0;
}
#undef init_data
