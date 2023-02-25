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

Info L_Block[] = {
	{"H_Wall",   '-', "水平的墙", NULL},
	{"V_Wall",   '|', "垂直的墙", NULL},
	{"Floor",    '.', "房间内部的地板", NULL},
	{"V_Door_c", '+', "对于垂直墙壁的关闭的门", NULL},
	{"H_Door_c", '+', "对于水平墙壁的关闭的门", NULL},
	{"V_Door_o", '-', "对于垂直墙壁的打开的门", NULL},
	{"H_Door_o", '|', "对于水平墙壁的打开的门", NULL},
	{"Corridor", '#', "这是走廊", NULL},
	{"Null",     ' ', "虚空", NULL}
};
Info L_Entity[] = {
	{"Player", '@', "这个是玩家", NULL}
};
Info L_Drop[] = {
	{"NULL", '~', "这只是个垫数的", NULL}
};

/*
 * 初始化结构体数据
 */
int init(void)
{
	Arg arg = {.i = 0};

	game_data.player.data.data = &L_Entity[0];
	/* 列表初始化 */
#define BiARG(id, arg1, arg2)			\
	arg.i = arg1;				\
	Opt_add(&L_Block[id].opt, "Move", arg);	\
	arg.i = arg2;				\
	Opt_add(&L_Block[id].opt, "Use" , arg);

#define BvARG(id, name, arg1)			\
	arg.v = arg1;				\
	Opt_add(&L_Block[id].opt, name, arg);	\

	/*    Name       move use  */
	BiARG(LN_hWall,    0, 0);
	BiARG(LN_vWall,    0, 0);
	BiARG(LN_floor,    1, 0);
	BiARG(LN_vDoorC,   0, 1);
	BvARG(LN_vDoorC,         "Hook Use",
	                         block_n4_open_V_door);
	BiARG(LN_hDoorC,   0, 1);
	BvARG(LN_hDoorC,         "Hook Use",
	                         block_n4_open_H_door);
	BiARG(LN_vDoorO,   1, 0);
	BiARG(LN_hDoorO,   1, 0);
	BiARG(LN_corridor, 1, 0);
	BiARG(LN_null,    -1, 0);
#undef BiARG
#undef BvARG
	return 0;
}

/*
 * 初始化游戏数据
 */
int init2(void)
{
	if (game_data.map != NULL) {
		free_pro(game_data.map);
	}
	/* Init map */
	map_init(MAP_HEIGHT, MAP_WIDTH);
	game_data.focus = game_data.map;
	return 0;
}

#define init_data(data, y, x)				\
	do {						\
		data = malloc(sizeof(Map));		\
		data->pos_x = x;			\
		data->pos_y = y;			\
		data->block = &L_Block[LN_null];	\
		data->drop  = NULL;			\
		data->friendly = NULL;			\
		data->monsters = NULL;			\
		if (y > 1 && up != NULL) {		\
			data->up       = up;		\
			data->up->down = data;		\
		} else {				\
			data->up = NULL;		\
		}					\
		data->down  = NULL;			\
		data->left  = NULL;			\
		data->right = NULL;			\
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
