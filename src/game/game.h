/*
 *   Copyright (C) 2023 YouLanjie
 *
 *   文件名称：game.h
 *   创 建 者：youlanjie
 *   创建日期：2023年01月23日
 *   描    述：主程序头文件
 *
 */

#ifndef GAME_H
#define GAME_H

#include "../../include/head.h"
#include "hook/hook.h"
#include "function/function.h"

/* def a var to use timer */
extern struct itimerval tick;

extern short LOCK;

/* About game running */
void game_running();
int game_running_use(void);
int game_input(int *input);

/*
 * 关于选项
 */
Opt *Opt_add(Opt **obj, char *name, Arg var);
Opt *Opt_get(Opt *Obj, char * name);
int Opt_Mget(Opt *Obj);

/*
 * About game map
 */
/* 移动光标 */
int map_get(int pos_y, int pos_x);
int map_set(int type, int name, int pos_y, int pos_x);
int map_print(void);
int map_mk_room(int y, int x);
int map_mk_corridor(int y, int x);

extern const Key Keys[];

#endif

