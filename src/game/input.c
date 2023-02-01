/*
 *   Copyright (C) 2023 YouLanjie
 *
 *   文件名称：input.c
 *   创 建 者：youlanjie
 *   创建日期：2023年02月01日
 *   描    述：处理用户的输入
 *
 */


#include "game.h"

#define RUN_USE								\
	do {								\
		if (game_data.focus->block->opt[BLOCK_OPT_N_USE] == 1 && \
		    game_data.focus->block->hook[BLOCK_HOOK_N_USE] != NULL) { \
			game_data.focus->block->hook[BLOCK_HOOK_N_USE](); \
		}							\
	} while (0);

/*
 * 处理用户输入
 */
int game_input(int *input)
{
	switch (*input) {
	case 'k':
		if (game_data.player.pos_y > 1) {
			game_data.focus = game_data.focus->up;
			if (game_data.focus->block->opt[0] == 1) {
				game_data.player.pos_y--;
			}
			RUN_USE;
			game_data.focus = game_data.focus->down;

		}
		break;
	case 'j':
		if (game_data.player.pos_y < MAP_HEIGHT) {
			game_data.focus = game_data.focus->down;
			if (game_data.focus->block->opt[0] == 1) {
				game_data.player.pos_y++;
			}
			RUN_USE;
			game_data.focus = game_data.focus->up;
		}
		break;
	case 'h':
		if (game_data.player.pos_x > 1) {
			game_data.focus = game_data.focus->left;
			if (game_data.focus->block->opt[0] == 1) {
				game_data.player.pos_x--;
			}
			RUN_USE;
			game_data.focus = game_data.focus->right;
		}
		break;
	case 'l':
		if (game_data.player.pos_x < MAP_WIDTH) {
			game_data.focus = game_data.focus->right;
			if (game_data.focus->block->opt[0] == 1) {
				game_data.player.pos_x++;
			}
			RUN_USE;
			game_data.focus = game_data.focus->left;
		}
		break;
	case 'q':
	case 'Q':
	case 0x1b:
		*input = 0;
		break;
	default:
		break;
	}
	return 0;
}

#undef RUN_USE
