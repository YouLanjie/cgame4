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

#define BLOCK_LIST_MAX 5
#define ENTITY_LIST_MAX 1
#define DROP_LIST_MAX 1

#define BLOCK_OPT_MAX 2
/* 可移动？ */
#define BLOCK_OPT_N_MOV 0
/* 可使用？攻击？ */
#define BLOCK_OPT_N_USE 1

#define BLOCK_HOOK_MAX 3
/* 运行 */
#define BLOCK_HOOK_N_RUN 0
/* 使用 */
#define BLOCK_HOOK_N_USE 1
/* 攻击 */
#define BLOCK_HOOK_N_ATK 2

/*
 * 基本数据存储结构定义
 */
/* 基本信息 */
struct game_info {
	const char  *name;        /* 名字 */
	const char   print_ch;    /* 打印使用字符 */
	const char  *describe;    /* 描述 */
	/* Action */
	int (*const hook[BLOCK_HOOK_MAX])();
	/* Option */
	const short opt[BLOCK_OPT_MAX];
};

/* 实体 */
struct game_entity {
	struct game_info   *data;          /* 基本信息 */
	short               HP;            /* 血量 */
	short               AC[2];         /* 防御值 */
	short               AT[2];         /* 力量值（攻击力） */
	struct game_info   *hand[2];       /* 手持物品 */
	struct game_info   *armour[4];     /* 装备 */
	struct game_info   *bag[26];       /* 背包 */
};

/* 掉落物 */
struct game_drop {
	struct game_info *data;
	short             num;
	struct game_drop *next;
};

/*
 * 地图
 */
struct game_map {
	/* base info */
	short pos_x;
	short pos_y;
	/* data in this point */
	struct game_info   *block;       /* 地图方块(id) */
	struct game_drop   *drop;        /* 掉落物 */
	struct game_entity *friendly;    /* 友好生物 */
	struct game_entity *monsters;    /* 怪物 */
	/* Link to other points */
	struct game_map *up;
	struct game_map *down;
	struct game_map *left;
	struct game_map *right;
};

/* 玩家 */
struct game_player {
	struct game_entity data;      /* 基本信息 */
	short              pos_y;
	short              pos_x;
	short              hungry;    /* 饥饿度 */
	short              XP;        /* 经验值 */
	short              level;     /* 等级 */
};

/* 游戏信息访问接口 */
struct game_data {
	struct game_map    *map;         /* 地图信息 */
	struct game_map    *focus;       /* 地图光标 */
	struct game_player  player;      /* 玩家 */
	short               diffcult;    /* 难度 */
	struct game_info    drop_list[DROP_LIST_MAX];
	struct game_info    entity_list[ENTITY_LIST_MAX];
	struct game_info    block_list[BLOCK_LIST_MAX];
};

#endif
