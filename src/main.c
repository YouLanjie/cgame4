/*
 *   Copyright (C) 2023 YouLanjie
 *   
 *   文件名称：main.c
 *   创 建 者：youlanjie
 *   创建日期：2023年01月09日
 *   描    述：
 *
 */


#include "../include/head.h"

struct game_data game_data = {
	NULL,
	NULL,
	{
		{
			NULL,
			100,
			{10, 10},
			{10, 10},
			{&game_data.drop_list[0], &game_data.drop_list[0]},
			{&game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0]},
			{&game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0], &game_data.drop_list[0]},
		},
		PLAYER_DEF_Y,
		PLAYER_DEF_X,
		0,
		0,
		0
	},
	0,
	{{"null", '~', 0, "null", NULL, NULL, NULL, NULL}
	},
	{{"Player", '@', 0, "player", NULL, NULL, NULL, NULL}
	},
	{{"Null", ' ', 0, "null", NULL, NULL, NULL, NULL},
	 {"Wall", '#', 2, "wall", NULL, NULL, NULL, NULL},
	 {"floor", '.', 1, "floor", NULL, NULL, NULL, NULL},
	 {"Door", '+', 2, "This is a door~~~", NULL, NULL, NULL, NULL}
	}
};

static void init_color_pair(void);

int main() {
	ctools_menu_t * menu = NULL;
	int input = 1;

	/* Setting about menu */
	ctools_menu_Init();
	ctools_menu_t_init(&menu);
	ctools_menu_AddText(menu,
			    "1.开始游戏",
			    "2.继续游戏",
			    "3.历史记录",
			    "4.退出",
			    NULL);
	ctools_menu_AddTextData(menu,
				ctools_menu_TextDataDescribe,
				"%s %s %s %s",
				"开始新游戏",
				"从存档加载",
				"查看一些信息",
				"离开游戏");

	init_color_pair();
	game_data.player.data.data = &game_data.entity_list[0];
	while (input != 0) {
		/* 菜单主循环 */
		input = ctools_menu_Show(menu);
		clear();
		refresh();
		switch (input) {
		case 0x1B:
		case 0:
		case 'q':
		case 'Q':
		case '0': {
			input = 0;
			break;
		}
		case '1': {
			game(2);
			break;
		}
		default:
			endwin();
			printf("Unknow Error\nQuit");
			return -1;
			break;
		}
	}
	free_pro(game_data.map);
	endwin();
	return 0;
}

static void init_color_pair(void)
{
	init_pair(C_WHITE_CYAN, 7, 41);
	init_pair(C_YELLOW_CYAN, 226, 41);
	init_pair(C_BLACK_CYAN, 232, 41);
	init_pair(C_BROWN_CYAN, 244, 41);

	init_pair(C_WHITE_BLUE, 7, 39);
	init_pair(C_YELLOW_BLUE, 226, 39);
	init_pair(C_BLACK_BLUE, 232, 39);
	init_pair(C_BROWN_BLUE, 244, 39);
	return;
}

