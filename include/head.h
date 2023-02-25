#include "tools.h"                         //头文件
#include "def.h"
#include <sys/time.h>
#include <math.h>

/*
 * Auto set the value NULL after free a ptr.
 */
#define free_pro(ptr);\
	free(ptr);\
	ptr = NULL;

#define entity_width 100000
#define drop_width 1000

#define MAP_WIDTH 60
#define MAP_HEIGHT 21

#define PLAYER_DEF_Y 2
#define PLAYER_DEF_X 2

/* 颜色 */
#define C_WHITE_CYAN 10
#define C_YELLOW_CYAN 11
#define C_BLACK_CYAN 12
#define C_BROWN_CYAN 13

#define C_WHITE_BLUE 20
#define C_YELLOW_BLUE 21
#define C_BLACK_BLUE 22
#define C_BROWN_BLUE 23

extern Data game_data;

/* About game data init */
int init(void);

int game(int start_mode);
