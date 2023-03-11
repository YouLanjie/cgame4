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
int block_n4_open_V_door(void)
{
	game_data.focus->block = &L_Block[LN_vDoorO];
	return 0;
}

int block_n4_open_H_door(void)
{
	game_data.focus->block = &L_Block[LN_hDoorO];
	return 0;
}

int block_n4_close_V_door(void)
{
	game_data.focus->block = &L_Block[LN_vDoorC];
	return 0;
}

int block_n4_close_H_door(void)
{
	game_data.focus->block = &L_Block[LN_hDoorC];
	return 0;
}

