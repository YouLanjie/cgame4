/*
 *   Copyright (C) 2023 YouLanjie
 *   
 *   文件名称：use.c
 *   创 建 者：youlanjie
 *   创建日期：2023年02月25日
 *   描    述：手动使用
 *
 */

#include "../game.h"

/*
 * 手动使用某个方向的对象
 */
int use(Arg arg)
{
	mvprintw(MAP_WIDTH + 7, 0, "Which direction?");
	refresh();
	
	return 0;
}


