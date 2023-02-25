/*
 *   Copyright (C) 2023 YouLanjie
 *
 *   文件名称：key.c
 *   创 建 者：youlanjie
 *   创建日期：2023年02月25日
 *   描    述：设置游戏按键
 *
 */


#include "game.h"

const Key Keys[] = {
	{'h',  Move,           {.i = 'h'} },
	{'j',  Move,           {.i = 'j'} },
	{'k',  Move,           {.i = 'k'} },
	{'l',  Move,           {.i = 'l'} },
	{'o',  setting_ingame, {.i = 0}   },
	/* {'p',  game_pause,     {.i = 0}   }, */
	{'\0', NULL,           {.i = 0}   }
};


