/* 头文件顺序：自己->C->C++->第三方库*/

#include "leptjson.h"

#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL, strtod() */
#include <errno.h> /* errno, ERANGE*/
#include <math.h> /* HUGE_VAL*/

#define EXPECT(c, ch) do { assert(*c->json == (ch)); c->json ++; } while(0)
#define ISDIGIT(ch) ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch) ((ch) >= '1' && (ch) <= '9')
/*
    将value前的空格全部去掉
*/
static void lept_parse_whitespace(lept_context* c) {
    const char* p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') {
        p ++;
    }
    /* 然后将不是空格的位置赋给json指针 */
    c->json = p;
}

/*
    重构：将TRUE FALSE NULL的解析统一到一个框架下
*/
static int lept_parse_literal(lept_context* c, lept_value* v, const char* literal, lept_type type) {
    size_t i;
    /*现在就是需要核对c->json和给定的literal字面量是不是一致*/
    for(i = 0; literal[i] != '\0'; i++) {
        // 如果不一致 说明是非法值
        if (c->json[i] != literal[i]) {
            return LEPT_PARSE_INVALID_VALUE;
        }
    }
    /*检查全部通过后 首先将c->json指针后移*/
    c->json += i;
    v->type = type;
    return LEPT_PARSE_OK;
}

/*
    解析数字
*/
static int lept_parse_number(lept_context* c, lept_value* v) {
    const char* p = c->json;
    if (*p == '-') p++; // 可以是负数
    // 接下来要么是0 要么是1-9
    if (*p == '0') {
        p++;
    } else {
        if (!ISDIGIT1TO9(*p)) {
            return LEPT_PARSE_INVALID_VALUE;
        }
        // 第一个是1-9 后面的只要是数字都是合法的
        for(p++; ISDIGIT(*p); p++);
    }
    // 接下来看有没有小数点
    if (*p == '.') {
        p++;
        // 有的话 小数点后面的连续的数字都是合法的
        if (!ISDIGIT(*p)) {
            return LEPT_PARSE_INVALID_VALUE;
        }
        for (p++; ISDIGIT(*p); p++);
    }
    // 接下来看有没有科学计数法标志
    if (*p == 'E' || *p == 'e') {
        p++;
        // 后面可以跟+ -号
        if (*p == '+' || *p == '-') {
            p++;
        }
        // 然后就是数字
        if (!ISDIGIT(*p)) {
            return LEPT_PARSE_INVALID_VALUE;
        }
        // 所有的数字都是合法的
        for (p++; ISDIGIT(*p); p++);
    }
    // 到这个位置的时候 p指向的就是非数字字符了
    errno = 0;
    v->u.n = strtod(c->json, NULL);
    if (errno == ERANGE && (v->u.n == HUGE_VAL || v->u.n == -HUGE_VAL)) {
        return LEPT_PARSE_NUMBER_TOO_BIG;
    }
    // 数字没有问题
    v->type = LEPT_NUMBER;
    c->json = p;
    return LEPT_PARSE_OK;
}

// /*
//     检查传入的字符串开头是不是"null"
// */
// static int lept_parse_null(lept_context* c, lept_value* v) {
//     /* 检查开头是不是字符'n' */
//     EXPECT(c, 'n');
//     /* 完成检查并且满足开头是'n'后 此时的c->json指针已经后移
//        检查接下来的三个字符是不是依次为'u' 'l' 'l' */
//     if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l') {
//         return LEPT_PARSE_INVALID_VALUE;
//     }
//     /* 如果确定了是"null" 则将v置为LEPT_NULL表示 并返回OK
//        c->json需要后移三位 准备好下一次处理 */
//     c->json += 3;
//     v->type = LEPT_NULL;
//     return LEPT_PARSE_OK;
// }

// /*
//     检查开头的字符串是不是true
// */
// static int lept_parse_true(lept_context* c, lept_value* v) {
//     EXPECT(c, 't');
//     if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e') {
//         return LEPT_PARSE_INVALID_VALUE;
//     }
//     c->json += 3;
//     v->type = LEPT_TRUE;
//     return LEPT_PARSE_OK;
// }

// /*
//     检查开头的字符串是不是false
// */
// static int lept_parse_false(lept_context* c, lept_value* v) {
//     EXPECT(c, 'f');
//     if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e') {
//         return LEPT_PARSE_INVALID_VALUE;
//     }
//     c->json += 4;
//     v->type = LEPT_FALSE;
//     return LEPT_PARSE_OK;
// }

/*
    写入解析出来的根值
*/
static int lept_parse_value(lept_context* c, lept_value* v) {
    switch (c->json[0]) {
        case 'n': return lept_parse_literal(c, v, "null", LEPT_NULL);
        case 't': return lept_parse_literal(c, v, "true", LEPT_TRUE);
        case 'f': return lept_parse_literal(c, v, "false", LEPT_FALSE);
        /* \0 是字符串结束符 */
        case '\0': return LEPT_PARSE_EXPECT_VALUE;
        default: return lept_parse_number(c, v);
    }
}

/*
    解析JSON文本
*/
int lept_parse(lept_context* c, lept_value* v) {
    int ret;
    assert(v != NULL);
    v->type = LEPT_NULL;
    lept_parse_whitespace(c);
    if ((ret = lept_parse_value(c, v)) == LEPT_PARSE_OK) {
        lept_parse_whitespace(c);
        if (c->json[0] != '\0') {
            v->type = LEPT_NULL;
            ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
        }
    }
    return ret;
}

/*
    返回value的类型
*/
lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}

/*
    如果是一个数字对象 返回解析出来的数字
*/
double lept_get_number(const lept_value* v) {
    /* 首先使用断言 */
    assert(v != NULL && v->type == LEPT_NUMBER);
    return v->u.n;
}

/* leptjson.c */