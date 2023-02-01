/*
 *   Copyright (C) 2023 YouLanjie
 *
 *   文件名称：running.c
 *   创 建 者：youlanjie
 *   创建日期：2023年01月23日
 *   描    述：Run the game by alrm
 *
 */


#include "game.h"

/*
 * Running the game by alrm
 * It can use another thread to running the game.
 * so it not running one by one.
 */
void game_running(void)
{
	if (LOCK) {
		return;
	} else {
		LOCK = 1;
	}
	map_print();
	LOCK = 0;
	return;
}
