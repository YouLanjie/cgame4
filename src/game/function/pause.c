/*
 *   Copyright (C) 2023 YouLanjie
 *
 *   文件名称：pause.c
 *   创 建 者：youlanjie
 *   创建日期：2023年02月25日
 *   描    述：暂停函数
 *
 */


#include "../game.h"

/*
 * 暂停函数
 */
int game_pause(void)
{
	if (game_data.running == 0) {
		setitimer(ITIMER_REAL, &tick, NULL);
		game_data.running = 1;
	} else {
		alarm(0);
		game_data.running = 0;
	}
	return 0;
}

