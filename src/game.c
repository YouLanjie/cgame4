/*
 *   Copyright (C) 2023 YouLanjie
 *   
 *   文件名称：game.c
 *   创 建 者：youlanjie
 *   创建日期：2023年01月11日
 *   描    述：游戏主程序
 *
 */

#include "game/game.h"

#define INFO &L_Drop[0]
Data game_data = {
	NULL,
	NULL,
	{
		{
			NULL,
			100,
			{10, 10},
			{10, 10},
			{INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO, INFO},
		},
		PLAYER_DEF_Y,    /* 初始Y轴 */
		PLAYER_DEF_X,    /* 初始X轴 */
		0,    /* 饥饿度 */
		0,    /* 经验值 */
		0     /* 等级 */
	},
	0,    /* 难度 */
	0
};

/* def a var to use timer */
struct itimerval tick;

short LOCK;

/*
 * 游戏函数
 */
int game(int start_mode)
{
	struct timeval gettime;
	int input  = 1,
	    l_usec = 0,
	    l_sec  = 0;

	init2();
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
	game_data.running = 1;

	while (input != 0) {
		input = getch();
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
	game_data.running = 0;
	return 0;
}
