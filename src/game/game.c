/*
 *   Copyright (C) 2023 YouLanjie
 *   
 *   文件名称：game.c
 *   创 建 者：youlanjie
 *   创建日期：2023年01月11日
 *   描    述：游戏主程序
 *
 */

#include "game.h"

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
	/* Name Print Describe Hook Option */
	{{"null", '~', "null",
	  {NULL, NULL, NULL},
	  {0, 0}}
	},
	{{"Player", '@', "player",
	  {NULL, NULL, NULL},
	  {0, 0}}
	},
	{{"Null", ' ', "null",
	  {NULL, NULL, NULL},
	  {-1, 0}},
	 {"Wall", '#', "wall",
	  {NULL, NULL, NULL},
	  {0, 0}},
	 {"floor", '.', "floor",
	  {NULL, NULL, NULL},
	  {1, 0}},
	 {"Door close", '+', "This is a close door",
	  {NULL, block_n4_open_door, NULL},
	  {0, 1}},
	 {"Door open", '-', "This is a open door",
	  {NULL, NULL, NULL},
	  {1, 0}}
	 /* hook: run use attack */
	}
};

/* def a var to use timer */
struct itimerval tick;

short LOCK;

static int game_input_key(int *result);

/*
 * 游戏函数
 */
int game(int start_mode)
{
	struct timeval gettime;
	int input  = 1,
	    l_usec = 0,
	    l_sec  = 0;

	init();
	/* Seting of the clock time */
	tick.it_interval.tv_sec  = 0;
	tick.it_interval.tv_usec = 200000;
	/* Setting if the start after time */
	tick.it_value.tv_sec  = 0;
	tick.it_value.tv_usec = 1000;
	/* Set what function the clock should run */
	signal(SIGALRM, game_running);

	if (start_mode == 1) {
		/* read config here */
	}
	/* Start the clock */
	setitimer(ITIMER_REAL, &tick, NULL);

	while (input != 0) {
		game_input_key(&input);
		gettimeofday(&gettime, NULL);
		if (gettime.tv_sec - l_sec < 1 &&
		    gettime.tv_usec - l_usec < 10000) {
			continue;
		}
		gettimeofday(&gettime, NULL);
		l_usec = gettime.tv_usec;
		l_sec  = gettime.tv_sec;
		map_get(game_data.player.pos_y, game_data.player.pos_x);
		game_input(&input);
		if (LOCK) {
			continue;
		} else {
			LOCK = 1;
			map_print();
			LOCK = 0;
		}
	}
	alarm(0);
	return 0;
}

/*
 * 转换输入按键
 */
static int game_input_key(int *result)
{
	*result = getch();
	if (*result == 0x1B && ctools_kbhit() == 1 && getchar() == '[') {
		*result = getchar();
		switch (*result) {
		case 'A':
			*result = 'k';
			break;
		case 'B':
			*result = 'j';
			break;
		case 'C':
			*result = 'l';
			break;
		case 'D':
			*result = 'h';
			break;
		default:
			*result = 0;
			return -1;
			break;
		}
	}
	switch (*result) {
	case 'w':
	case 'W':
	case 'K':
	case 0x10:
		*result = 'k';
		break;
	case 's':
	case 'S':
	case 'J':
	case 0xe:
		*result = 'j';
		break;
	case 'd':
	case 'D':
	case 'L':
	case 0x6:
		*result = 'l';
		break;
	case 'a':
	case 'A':
	case 'H':
	case 0x2:
		*result = 'h';
		break;
	default:
		break;
	}
	return *result;
}
