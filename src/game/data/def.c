/*
 *   Copyright (C) 2023 YouLanjie
 *
 *   文件名称：def.c
 *   创 建 者：youlanjie
 *   创建日期：2023年03月25日
 *   描    述：定义固定数据
 *
 */


#include "../game.h"

#define INFO &L_Drop[0]
Data game_data = {
	NULL,
	NULL,
	{
		{
			&L_Entity[0],
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

char *const L_B_Rule = "Move=f;Use=f;Color=t";

Info L_Block[] = {
	{"H_Wall",   '-', "水平的墙",           NULL,      NULL,                 &L_Block[1]},
	{"V_Wall",   '|', "垂直的墙",           NULL,      NULL,                 &L_Block[2]},
	{"Floor",    '.', "房间内部的地板",     "Move=t",  NULL,                 &L_Block[3]},
	{"V_Door_c", '+', "垂直墙壁上关闭的门", "Use=t",   block_n4_open_V_door, &L_Block[4]},
	{"H_Door_c", '+', "水平墙壁上关闭的门", "Use=t",   block_n4_open_H_door, &L_Block[5]},
	{"V_Door_o", '-', "垂直墙壁上打开的门", "Move=t",  NULL,                 &L_Block[6]},
	{"H_Door_o", '|', "水平墙壁上打开的门", "Move=t",  NULL,                 &L_Block[7]},
	{"Corridor", '#', "这是走廊",           "Move=t",  NULL,                 &L_Block[8]},
	{"Null",     ' ', "虚空",               "Color=f", NULL,                 NULL}
};

Info L_Entity[] = {
	{"Player", '@', "这个是玩家", "type=1", NULL, NULL}
};

Info L_Drop[] = {
	{"NULL", '~', "这只是个垫数的", NULL, NULL, NULL}
};

const Key Keys[] = {
	{'h',  Move,           "h"  },
	{'j',  Move,           "j"  },
	{'k',  Move,           "k"  },
	{'l',  Move,           "l"  },
	{'o',  setting_ingame, NULL },
	{'p',  game_pause,     NULL },
	{'\0', NULL,           NULL }
};
