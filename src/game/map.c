/*
 *   Copyright (C) 2023 YouLanjie
 *
 *   文件名称：map.c
 *   创 建 者：youlanjie
 *   创建日期：2023年01月23日
 *   描    述：地图相关
 *
 */


#include "game.h"

/*
 * 获取地图焦点
 */
int map_get(int pos_y, int pos_x)
{
	while (game_data.focus->down != NULL && game_data.focus->pos_y < pos_y) {
		game_data.focus = game_data.focus->down;
	}
	while (game_data.focus->up != NULL && game_data.focus->pos_y > pos_y) {
		game_data.focus = game_data.focus->up;
	}
	while (game_data.focus->right != NULL && game_data.focus->pos_x < pos_x) {
		game_data.focus = game_data.focus->right;
	}
	while (game_data.focus->left != NULL && game_data.focus->pos_x > pos_x) {
		game_data.focus = game_data.focus->left;
	}
	/* 设置返回值 */
	if (pos_y > game_data.focus->pos_y && pos_x > game_data.focus->pos_x) {
		return 1;
	} else if (pos_y > game_data.focus->pos_y) {
		return 2;
	} else if (pos_x > game_data.focus->pos_x) {
		return 3;
	}
	return 0;
}


/*
 * 设置地图存储信息
 */
int map_set(int type, int id, int pos_y, int pos_x)
{
	map_get(pos_y, pos_x);
	if (type == 1 && id < BLOCK_LIST_MAX) {    /* 方块 */
		game_data.focus->block = &game_data.block_list[id];
	} else if (type == 2 && id < ENTITY_LIST_MAX &&
		   game_data.entity_list[id].opt == 1) {    /* 友好生物 */
		game_data.focus->friendly->data = &game_data.entity_list[id];
	} else if (type == 3 && id < ENTITY_LIST_MAX &&
		   game_data.entity_list[id].opt == 2) {    /* 敌对生物 */
		game_data.focus->monsters->data = &game_data.entity_list[id];
	} else if (type == 4 && id < DROP_LIST_MAX) {    /* 掉落物 */
		game_data.focus->drop->data = &game_data.drop_list[id];
	}
	return 0;
}

/*
 * 创建房间
 */
int map_mk_room(int y, int x)
{
	struct timeval gettime;
	int point[2] = {0, 0};
	int y2 = 0,
	    x2 = 0;
	long usec = 0;
	short BORE = 1;

	if (y < 0 || y > MAP_HEIGHT || x < 0 || x > MAP_WIDTH) {
		return -1;
	}
	mvprintw(0, 0, "Debug info:");
	mvprintw(1, 0, "Y:%3d X:%3d", game_data.player.pos_y, game_data.player.pos_x);
	refresh();
	while (BORE == 1) {
		while (point[0] <= 0 || y - point[0] < 1) {
			gettimeofday(&gettime, NULL);
			usec = gettime.tv_usec;
			srand(usec + gettime.tv_sec);
			point[0] = y - (y <= 2 ? 0: rand() % 3) - 1;
			usleep(10 + rand() % 1000);
		}
		while (point[1] <= 0 || x - point[1] < 1) {
			gettimeofday(&gettime, NULL);
			usec = gettime.tv_usec;
			srand(usec + gettime.tv_sec);
			point[1] = x - (x <= 2 ? 0: rand() % 2) - 1;
			usleep(10 + rand() % 1000);
		}
		while ((y2 == 0 && x2 == 0) || y2 >= MAP_HEIGHT || x2 >= MAP_WIDTH) {
			while (y2 == 0 || y2 >= MAP_HEIGHT) {
				gettimeofday(&gettime, NULL);
				usec = gettime.tv_usec;
				srand(usec + gettime.tv_sec);
				y2 = (y >= MAP_HEIGHT - 2 ? 0: (rand() % 2)) + y + 2;
				usleep(10 + rand() % 1000);
			}
			while (x2 == 0 || x2 >= MAP_WIDTH) {
				gettimeofday(&gettime, NULL);
				usec = gettime.tv_usec;
				srand(usec + gettime.tv_sec);
				x2 = (x >= MAP_WIDTH - 2 ? 0:(rand() % 5)) + x + (y2 - point[0] >= 4 ? 5: 2);
				usleep(10 + rand() % 1000);
			}
		}
		BORE = 0;
		for (int i = point[0]; i <= y2; ++i) {
			for (int i2 = point[1]; i2 <= x2; ++i2) {
				map_get(i, i2);
				if (i != point[0] && i != y2 &&
				    i2 != point[1] && i2 != x2) {
					if (game_data.focus->block != &game_data.block_list[0]) {
						BORE = 1;
						break;
					} else {
						BORE--;
					}
				}
			}
		}
	}

	BORE = 0 - BORE;
	gettimeofday(&gettime, NULL);
	srand(gettime.tv_usec);
	BORE = rand() % (BORE - 1) + 1;

	/* 创建房间 */
	for (int i = point[0]; i <= y2; ++i) {
		for (int i2 = point[1]; i2 <= x2; ++i2) {
			map_get(i, i2);
			if (i == point[0] || i == y2 ||
			    i2 == point[1] || i2 == x2) {
				if (BORE == 0) {
					game_data.focus->block = &game_data.block_list[3];
					BORE--;
				} else {
					game_data.focus->block = &game_data.block_list[1];
					BORE--;
				}
			} else {
				game_data.focus->block = &game_data.block_list[2];
			}
		}
	}
	return 0;
}

#define map (game_data.focus)
/*
 * 地图打印
 */
int map_print(void)
{
	clear();
	attron(COLOR_PAIR(C_WHITE_BLUE));
	map_get(1, 1);
	for (int i = 1; map->down != NULL; ++i) {
		map_get(i, 1);
		for (int i2 = 1; map->right != NULL; ++i2) {
			map_get(i, i2);
			if (map->block->opt == 0) {
				attroff(COLOR_PAIR(C_WHITE_BLUE));
			}
			/* 打印方块 */
			mvprintw(i - 1, i2 - 1, "%c",
				 map->block->print_ch);
			if (map->block->opt == 0) {
				attron(COLOR_PAIR(C_WHITE_BLUE));
			}
			/* 打印掉落物 */
			if (map->drop != NULL) {
				mvprintw(i - 1, i2 - 1, "%c",
					 map->drop->data->print_ch);
			}
			/* 打印实体 */
			if (map->friendly != NULL) {
				mvprintw(i - 1, i2 - 1, "%c",
					 map->friendly->data->print_ch);
			} else if (map->monsters != NULL) {
				mvprintw(i - 1, i2 - 1, "%c",
					 map->monsters->data->print_ch);
			}
		}    /* for Levle X */
	}    /* for Level Y */
	attroff(COLOR_PAIR(C_WHITE_BLUE));
	/* 打印玩家 */
	attron(COLOR_PAIR(C_YELLOW_BLUE));
	mvprintw(game_data.player.pos_y - 1,
		 game_data.player.pos_x - 1,
		 "%c", game_data.player.data.data->print_ch);
	attroff(COLOR_PAIR(C_YELLOW_BLUE));
	mvprintw(MAP_HEIGHT, 0,
		 "Name:%s Signature:%s",
		 game_data.player.data.data->name,
		 game_data.player.data.data->describe);
	mvprintw(MAP_HEIGHT + 1, 0,
		 "HP:%3d AC:%3d %3d AT:%3d %3d XP:%4d Level:%d",
		 game_data.player.data.HP,
		 game_data.player.data.AC[0],
		 game_data.player.data.AC[1],
		 game_data.player.data.AT[0],
		 game_data.player.data.AT[1],
		 game_data.player.XP,
		 game_data.player.level);
	mvprintw(MAP_HEIGHT + 2, 0,
		 "Hand:%s %s",
		 game_data.player.data.hand[0]->name,
		 game_data.player.data.hand[1]->name);
	mvprintw(MAP_HEIGHT + 3, 0,
		 "Armour:%s %s %s %s",
		 game_data.player.data.armour[0]->name,
		 game_data.player.data.armour[1]->name,
		 game_data.player.data.armour[2]->name,
		 game_data.player.data.armour[3]->name);
	mvprintw(MAP_HEIGHT + 4, 0,
		 "Y:%3d X:%3d",
		 game_data.player.pos_y,
		 game_data.player.pos_x);
	refresh();
	return 0;
}
#undef id
