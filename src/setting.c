/*
 *   Copyright (C) 2023 YouLanjie
 *
 *   文件名称：setting.c
 *   创 建 者：youlanjie
 *   创建日期：2023年02月25日
 *   描    述：设置
 *
 */


#include "game/game.h"

/*
 * 设置函数
 */
int setting(void)
{
	ctools_menu_t * menu = NULL;

	ctools_menu_t_init(&menu);
	menu->title = "游戏设置";
	menu->cfg   = ctools_menu_Type_Setting;
	ctools_menu_AddText(menu,
			    "Debug Seting",
			    "1.NULL可行走",
			    "2.垂直墙壁可行走",
			    "3.水平墙壁可行走",
			    NULL
	);
	ctools_menu_AddTextData(menu,
				ctools_menu_TextDataDescribe,
				"n%s%s%s",
				"设置NULL方块能否让玩家行走",
				"设置垂直方向的墙壁方块能让玩家行走",
				"设置水平方向的墙壁方块能让玩家行走"
	);
	ctools_menu_Show(menu);
	return 0;
}

