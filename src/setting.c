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
	const ctools_menu *m = &CT_MENU;
	struct ctools_menu_t * menu = NULL;

	m->data_init(&menu);
	m->set_title(menu, "游戏设置");
	m->set_type(menu, "setting");
	m->add_text(menu,
			    "Debug Seting",
			    "1.NULL可行走",
			    "2.垂直墙壁可行走",
			    "3.水平墙壁可行走",
			    NULL
	);
	m->add_text_data(menu,
				"describe",
				"n%s%s%s",
				"设置NULL方块能否让玩家行走",
				"设置垂直方向的墙壁方块能让玩家行走",
				"设置水平方向的墙壁方块能让玩家行走"
	);
	m->show(menu);
	return 0;
}

