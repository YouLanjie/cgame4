/*
 *   Copyright (C) 2023 YouLanjie
 *
 *   文件名称：map.c
 *   创 建 者：youlanjie
 *   创建日期：2023年01月23日
 *   描    述：地图相关
 *
 */


#include "../game.h"

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
int map_set(int type, char const * name, int pos_y, int pos_x)
{
	map_get(pos_y, pos_x);
	if (type == 1) {    /* 方块 */
		game_data.focus->block = get_info(L_Block, name);
	} else if (type == 2 && Opt_get(get_info(L_Entity, name), NULL, "type")[0] == '1') {    /* 友好生物 */
		game_data.focus->friendly->data = get_info(L_Entity, name);
	} else if (type == 3 && Opt_get(get_info(L_Entity, name), NULL, "type")[0] == 2) {    /* 敌对生物 */
		game_data.focus->monsters->data = get_info(L_Entity, name);
	} else if (type == 4) {    /* 掉落物 */
		game_data.focus->drop->data = get_info(L_Drop, name);
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
					if (game_data.focus->block != get_info(L_Block, "Null")) {
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
	BORE = rand() % (BORE - 5) + 1;

	/* 创建房间 */
	for (int i = point[0]; i <= y2; ++i) {
		for (int i2 = point[1]; i2 <= x2; ++i2) {
			map_get(i, i2);
			if (i == point[0] || i == y2) {
				if (BORE == 0) {
					if (i2 != point[1] && i2 != x2) {
						game_data.focus->block = get_info(L_Block, "H_Door_c");
						BORE--;
					} else {
						game_data.focus->block = get_info(L_Block, "H_Wall");
					}
				} else {
					game_data.focus->block = get_info(L_Block, "H_Wall");
					BORE--;
				}
			} else if (i2 == point[1] || i2 == x2) {
				if (BORE == 0) {
					if (i != point[0] && i != y2) {
						game_data.focus->block = get_info(L_Block, "V_Door_c");
						BORE--;
					} else {
						game_data.focus->block = get_info(L_Block, "H_Wall");
					}
				} else {
					game_data.focus->block = get_info(L_Block, "V_Wall");
					BORE--;
				}
			} else {
				game_data.focus->block = get_info(L_Block, "Floor");
			}
		}
	}
	return 0;
}

/*
 * 创建房间
 */
int map_mk_corridor(int y, int x)
{
	/* struct timeval gettime; */
	/* gettimeofday(&gettime, NULL); */
	/* srand(gettime.tv_usec + gettime.tv_sec); */
	/* point[0] = y - (y <= 2 ? 0: rand() % 3) - 1; */
	/* usleep(10 + rand() % 1000); */
	/* while (point[0] <= 0 || y - point[0] < 1) { */
	/* 	gettimeofday(&gettime, NULL); */
	/* 	srand(gettime.tv_usec + gettime.tv_sec); */
	/* 	point[0] = y - (y <= 2 ? 0: rand() % 3) - 1; */
	/* 	usleep(10 + rand() % 1000); */
	/* } */
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
			if (Opt_get(map->block, L_B_Rule, "Color")[0] == 'f') {
				attroff(COLOR_PAIR(C_WHITE_BLUE));
			}
			/* 打印方块 */
			if (map->block != NULL) {
				mvprintw(i - 1, i2 - 1, "%c",
					 map->block->print_ch);
			} else {
				mvprintw(i - 1, i2 - 1, "?");
			}
			if (Opt_get(map->block, L_B_Rule, "Color")[0] == 'f') {
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
		 "L_hand:%s\tR_hand:%s\tR_hand_describe:%s",
		 game_data.player.data.bag[0]->name,
		 game_data.player.data.bag[1]->name,
		 game_data.player.data.bag[1]->describe);
	mvprintw(MAP_HEIGHT + 3, 0,
		 "Head:%s\tBody:%s\tLeg:%s\tFoot:%s",
		 game_data.player.data.bag[2]->name,
		 game_data.player.data.bag[3]->name,
		 game_data.player.data.bag[4]->name,
		 game_data.player.data.bag[5]->name);
	mvprintw(MAP_HEIGHT + 4, 0,
		 "Y:%3d X:%3d",
		 game_data.player.pos_y,
		 game_data.player.pos_x);
	map_get(game_data.player.pos_y, game_data.player.pos_x);
	if (game_data.focus->block != NULL) {
		mvprintw(MAP_HEIGHT + 5, 0,
			 "Block Name:%s",
			 game_data.focus->block->name);
		mvprintw(MAP_HEIGHT + 6, 0,
			 "Block Describe:%s",
			 game_data.focus->block->describe);
		mvprintw(MAP_HEIGHT + 7, 0, "规则探测结果:%s",
			 Opt_get(game_data.focus->block, L_B_Rule, "Color"));
		mvprintw(MAP_HEIGHT + 8, 0, "规则探测结果:%x",
			 Opt_get(game_data.focus->block, L_B_Rule, "Color")[0]);
		mvprintw(MAP_HEIGHT + 9, 0, "规则集:%s",
			 game_data.focus->block->opt);
		mvprintw(MAP_HEIGHT + 10, 0, "规则集2:%s",
			 L_B_Rule);
	}
	refresh();
	return 0;
}
