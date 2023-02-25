/*
 *   Copyright (C) 2023 YouLanjie
 *
 *   文件名称：opt.c
 *   创 建 者：youlanjie
 *   创建日期：2023年02月24日
 *   描    述：控制选项的系统
 *
 */


#include "../game.h"

Opt *Opt_add(Opt **obj, char *name, Arg var)
{
	if (*obj == NULL) {
		*obj = malloc(sizeof(Opt));
	} else {
		while ((*obj)->next != NULL) {
			obj = &(*obj)->next;
		}
		(*obj)->next = malloc(sizeof(Opt));
		obj = &(*obj)->next;
	}
	(*obj)->name = malloc(strlen(name));
	(*obj)->var  = var;
	(*obj)->next = NULL;
	strcpy((*obj)->name, name);
	return *obj;
}

Opt *Opt_get(Opt *Obj, char * name)
{
	Opt **obj = &Obj;
	if (*obj == NULL) {
		return NULL;
	}
	while (*obj != NULL && strcmp((*obj)->name, name) != 0) {
		obj = &(*obj)->next;
	}
	return *obj;
}

/*
 * 获得最大值
 */
int Opt_Mget(Opt *Obj)
{
	Opt **obj = &Obj;
	int count = 0;
	if (*obj == NULL) {
		return 0;
	}
	while (*obj != NULL) {
		obj = &(*obj)->next;
		count++;
	}
	return count;
}
