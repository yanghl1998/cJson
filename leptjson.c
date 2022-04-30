/* 头文件顺序：自己->C->C++->第三方库*/

#include "leptjson.h"

#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */

#define EXPECT(c, ch) do { assert(*c->json == (ch)); c->json ++; } while(0)

typedef struct {
    const char* json;
}lept_context;

/*
    将value前的空格全部去掉
*/
static void lept_parse_whitespace(lept_context* c) {
    const char* p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') {
        p ++;
    }
    // 然后将不是空格的位置赋给json指针
    c->json = p;
}

/*
    检查传入的字符串开头是不是"null"
*/
static int lept_parse_null(lept_context* c, lept_value* v) {
    // 检查开头是不是字符'n'
    EXPECT(c, 'n');
    // 完成检查并且满足开头是'n'后 此时的c->json指针已经后移
    // 检查接下来的三个字符是不是依次为'u' 'l' 'l'
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l') {
        return LEPT_PARSE_INVALID_VALUE;
    }
    // 如果确定了是"null" 则将v置为LEPT_NULL表示 并返回OK
    // c->json需要后移三位 准备好下一次处理
    c->json += 3;
    v->type = LEPT_NULL;
    return LEPT_PARSE_OK;
}

/*
    检查开头的字符串是不是true
*/
static int lept_parse_true(lept_context* c, lept_value* v) {
    EXPECT(c, 't');
    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e') {
        return LEPT_PARSE_INVALID_VALUE;
    }
    c->json += 3;
    v->type = LEPT_TRUE;
    return LEPT_PARSE_OK;
}

/*
    检查开头的字符串是不是false
*/
static int lept_parse_false(lept_context* c, lept_value* v) {
    EXPECT(c, 'f');
    if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e') {
        return LEPT_PARSE_INVALID_VALUE;
    }
    c->json += 4;
    v->type = LEPT_FALSE;
    return LEPT_PARSE_OK;
}


// leptjson.c