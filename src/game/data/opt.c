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

#define OPT_MAX_LEN 125

static char var_name[OPT_MAX_LEN];
static char var[OPT_MAX_LEN];
static char const *ch = NULL;

static int g_opt(char const * const name);

#define COND(name) (name == NULL || *name == '\0' || *name == '=' || *name == ';')

char *Opt_get(Info const *list, char const * rule, char const * const name)
{
	if (list == NULL || name == NULL) {
		return "传入参数为空";
	}
	if (COND(list->opt)) {
		if (COND(rule)) {
			return "普通和默认规则集为空";
		}
		ch = rule;
		if (g_opt(name) == -2) {
			return "默认规则集没有匹配的设置";
		}
		return var;
	} else {
		ch = list->opt;
		if (g_opt(name) == -2) {
			ch = rule;
			if (COND(rule) || g_opt(name) == -2) {
				return "所有规则集均未有匹配的设置";
			}
		}
		return var;
	}
	return "None";
}

/*
 * 获取对应名字的变量值
 */
static int g_opt(char const * const name)
{
	char **a = &ch;
	char *b = var_name,
	*c = var;
	while (*ch != '\0') {
		int i2 = 0;
		var_name[0] = '\0';
		var[0]      = '\0';

		for (i2 = 0; *ch != '=' && *ch != '\0' && i2 < OPT_MAX_LEN - 1; ++i2) {
			var_name[i2] = *ch;
			ch++;
		}    /* 读取变量名 */
		var_name[i2] = '\0';
		ch++;

		for (i2 = 0; *ch != ';' && *ch != '\0' && i2 < OPT_MAX_LEN - 1; ++i2) {
			var[i2] = *ch;
			ch++;
		}    /* 读取变量值 */
		var[i2] = '\0';

		if (*ch != '\0') {
			ch++;
		}

		if (var_name[0] == '\0' || var[0] == '\0') {
			return -1;
		}
		if (strcmp(var_name, name) == 0) {
			return 0;
		}
	}    /* 一级遍历全部 */
	return -2;
}

