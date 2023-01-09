#include "tools.h"                         //头文件
#include "specialChar.h"
#include <sys/time.h>

/* 实体基本信息 */
struct Game_objects {
	char * name;        /* 名字 */
	int    type;        /* 属性 */
	int    pox_y;       /* 横坐标 */
	int    pox_x;       /* 纵坐标 */
};

struct Game_objects_life {
	struct Game_objects data;        /* 基本信息 */
	int                 HP;          /* 血量 */
	int                 power[2];    /* 力量值（攻击力） */
	int                 ac[2];       /* 防御值 */
};

/* 玩家背包（暂时） */
struct Game_player_bag {
	int *hand;        /* 手持物品 */
	int armour[4];    /* 盔甲（自上而下） */
	int other[26];    /* 物品栏 */
};

/* 玩家 */
struct Game_player {
	struct Game_objects_life data;      /* 基本信息 */
	int                      hungry;    /* 饥饿度 */
	int                      XP;        /* 经验值 */
	int                      level;     /* 等级 */
	struct Game_player_bag   bag;       /* 背包 */
};

/* 怪物 */
struct Game_monsters {
	struct Game_objects_life   data;    /* 基本信息 */
	int                        num;     /* 怪物编号 */
	struct Game_monsters     * next;    /* 下一位 */
}

struct Game_objects_link {
	struct Game_objects        data;    /* 基本信息 */
	int                        num;     /* 怪物编号 */
	struct Game_objects_link * next;    /* 下一位 */
};

/* 游戏信息访问接口 */
struct Game_data {
	int                        map[100][200];    /* 地图信息（1-100地板，100-200实体，>200物品） */
	int                        diffcult;         /* 难度 */
	struct Game_player         player;           /* 玩家 */
	struct Game_monsters     * monsters;         /* 怪物 */
	struct Game_objects_link * monsters;         /* 怪物 */
};

