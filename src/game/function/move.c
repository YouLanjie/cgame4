/*
 *   Copyright (C) 2023 YouLanjie
 *
 *   文件名称：move.c
 *   创 建 者：youlanjie
 *   创建日期：2023年02月25日
 *   描    述：控制玩家移动
 *
 */


#include "../game.h"

static int run_hook();

#define MOV (Opt_get(game_data.focus->block->opt, "Move")->var.i)

/*
 * 控制玩家移动
 */
int Move(Arg arg)
{
	switch (arg.i) {
	case 'k':
		if (game_data.player.pos_y > 1) {
			game_data.focus = game_data.focus->up;
			if (MOV == 1) {
				game_data.player.pos_y--;
			}
			run_hook();
			game_data.focus = game_data.focus->down;

		}
		break;
	case 'j':
		if (game_data.player.pos_y < MAP_HEIGHT) {
			game_data.focus = game_data.focus->down;
			if (MOV == 1) {
				game_data.player.pos_y++;
			}
			run_hook();
			game_data.focus = game_data.focus->up;
		}
		break;
	case 'h':
		if (game_data.player.pos_x > 1) {
			game_data.focus = game_data.focus->left;
			if (MOV == 1) {
				game_data.player.pos_x--;
			}
			run_hook();
			game_data.focus = game_data.focus->right;
		}
		break;
	case 'l':
		if (game_data.player.pos_x < MAP_WIDTH) {
			game_data.focus = game_data.focus->right;
			if (MOV == 1) {
				game_data.player.pos_x++;
			}
			run_hook();
			game_data.focus = game_data.focus->left;
		}
		break;
	}
	return 0;
}

static int run_hook()
{
	game_running_use();
	return 0;
}


