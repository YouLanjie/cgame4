/*
 *   Copyright (C) 2023 YouLanjie
 *
 *   文件名称：door.c
 *   创 建 者：youlanjie
 *   创建日期：2023年02月01日
 *   描    述：关于门的反应函数
 *
 */


#include "../../game.h"

/*
 * 门的反应
 */
int block_n4_open_door(void)
{
	game_data.focus->block = &game_data.block_list[4];
	return 0;
}

