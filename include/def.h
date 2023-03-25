/*
 *   Copyright (C) 2023 YouLanjie
 *
 *   文件名称：def.h
 *   创 建 者：youlanjie
 *   创建日期：2023年01月24日
 *   描    述：定义数据结构
 *
 */

#ifndef DEF_H
#define DEF_H

/*
 * 基本数据存储结构定义
 */

typedef struct {
	char   key;
	int  (*v)(char *arg);
	char  *arg;
}Key;

/* 基本信息 */
typedef struct Info_t {
	char          *const name;        /* 名字 */
	char           const print_ch;    /* 打印使用字符 */
	char          *const describe;    /* 描述 */
	char          *const opt;         /* 选项 */
	int          (*const hook)();     /* Hook */
	struct Info_t *const next;
}Info;

/* 实体 */
typedef struct {
	Info  *data;          /* 基本信息 */
	short  HP;            /* 血量 */
	short  AC[2];         /* 防御值 */
	short  AT[2];         /* 力量值（攻击力） */
	Info  *bag[32];       /* 背包 */
}Entity;

/* 掉落物 */
typedef struct game_drop Drop;
typedef struct game_drop {
	Info  *data;
	short  num;    /* 数量 */
	Drop  *next;
}Drop;

/*
 * 地图
 */
typedef struct game_map Map;
typedef struct game_map {
	/* base info */
	short pos_x;
	short pos_y;
	/* data in this point */
	Info   *block;       /* 地图方块 */
	Drop   *drop;        /* 掉落物 */
	Entity *friendly;    /* 友好生物 */
	Entity *monsters;    /* 怪物 */
	/* Link to other points */
	Map *up;
	Map *down;
	Map *left;
	Map *right;
}Map;

/* 玩家 */
typedef struct {
	Entity data;      /* 基本信息 */
	short  pos_y;
	short  pos_x;
	short  hungry;    /* 饥饿度 */
	short  XP;        /* 经验值 */
	short  level;     /* 等级 */
}Player;

/* 游戏信息访问接口 */
typedef struct {
	Map    *map;         /* 地图信息 */
	Map    *focus;       /* 地图光标 */
	Player  player;      /* 玩家 */
	short   diffcult;    /* 难度 */
	short   running;
}Data;


extern Info L_Block[];
extern char *const L_B_Rule;
extern Info L_Entity[];
extern Info L_Drop[];

#endif
