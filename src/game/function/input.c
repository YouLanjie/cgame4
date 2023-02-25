/*
 *   Copyright (C) 2023 YouLanjie
 *
 *   文件名称：input.c
 *   创 建 者：youlanjie
 *   创建日期：2023年02月01日
 *   描    述：处理用户的输入
 *
 */


#include "../game.h"

/*
 * 处理用户输入
 */
int game_input(int *input)
{
	const Key (*key) = Keys;
	if (*input == 0 || *input == 'q' || *input == 'Q') {
		*input = 0;
	}
	while (key->key != '\0') {
		if (*input == key->key && key->v != NULL) {
			key->v(key->arg);
		}
		key++;
	}
	return 0;
}
