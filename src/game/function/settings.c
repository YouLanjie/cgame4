/*
 *   Copyright (C) 2023 YouLanjie
 *
 *   文件名称：settings.c
 *   创 建 者：youlanjie
 *   创建日期：2023年02月25日
 *   描    述：从游戏内部调用设置
 *
 */


#include "../game.h"

/*
 * 从游戏的内部调用函数
 */
int setting_ingame(void)
{
	alarm(0);
	game_data.running = 0;
	setting();
	setitimer(ITIMER_REAL, &tick, NULL);
	game_data.running = 1;
	return 0;
}

