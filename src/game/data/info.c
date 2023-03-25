/*
 *   Copyright (C) 2023 YouLanjie
 *
 *   文件名称：info.c
 *   创 建 者：youlanjie
 *   创建日期：2023年03月25日
 *   描    述：获取列表信息
 *
 */


#include "../game.h"

/*
 * 根据给定的列表获取信息节点
 */
Info *get_info(Info *list, char const *name)
{
	while (list != NULL && name != NULL) {
		if (strcmp(list->name, name) == 0) {
			return list;
		}
		list = list->next;
	}
	return NULL;
}

