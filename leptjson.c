/* 头文件顺序：自己->C->C++->第三方库*/

#include "leptjson.h"

#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL, strtod() malloc() free() realloc()*/
#include <errno.h> /* errno, ERANGE*/
#include <math.h> /* HUGE_VAL*/
#include <string.h> /* memcpy() */

#ifndef LEPT_PARSE_STACK_INIT_SIZE
    #define LEPT_PARSE_STACK_INIT_SIZE 256
#endif

#define EXPECT(c, ch) do { assert(*c->json == (ch)); c->json ++; } while(0)
#define ISDIGIT(ch) ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch) ((ch) >= '1' && (ch) <= '9')
/* lept_context_push返回的是栈顶位置 PUTC对栈顶的位置赋值*/
#define PUTC(c, ch) do { *(char*)lept_context_push(c, sizeof(char)) = (ch); } while(0)

typedef struct {
    const char* json;
    char* stack;
    size_t size, top;
} lept_context;

/*

*/
static void* lept_context_push(lept_context* c, size_t size) {
    void* ret;
    assert(size > 0);
    /* 栈顶指针+要分配的空间超过c的原配额 则需要扩展c的配额*/
    if (c->top + size >= c->size) {
        /* 刚开始初始化 c没有分配空间*/
        if (c->size == 0) {
            c->size = LEPT_PARSE_STACK_INIT_SIZE;
        }
        /* 不然的话 一直按照1.5倍的速度扩容 直到配额够放入新内容*/
        while (c->top + size >= c->size) {
            c->size += c->size >> 1; /* 扩容到1.5倍*/
        }
        /* c的配额确定后 分配内存*/
        c->stack = (char*)realloc(c->stack, c->size);
    }
    ret = c->stack + c->top;
    c->top += size;
    return ret;
}

/*

*/
static void* lept_context_pop(lept_context* c, size_t size) {
    assert(c->top >= size);
    return c->stack + (c->top -= size);
}

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

/*
    解析字符串
*/
static int lept_parse_string(lept_context* c, lept_value* v) {
    size_t head = c->top, len;
    const char* p;
    EXPECT(c, '\"');
    p = c->json;
    for( ; ; ) {
        char ch = *p++;
        switch(ch) {
            case '\"':  /* 遇到第二个双引号*/
                len = c->top - head; /* 检查字符串长度*/
                lept_set_string(v, (const char*)lept_context_pop(c, len), len);
                c->json = p;
                return LEPT_PARSE_OK;
            case '\\':
                switch(*p++) {
                    case '\"': PUTC(c, '\"'); break;
                    case '\\': PUTC(c, '\\'); break;
                    case '/': PUTC(c, '/'); break;
                    case 'b': PUTC(c, '\b'); break;
                    case 'f': PUTC(c, '\f'); break;
                    case 'n': PUTC(c, '\n'); break;
                    case 'r': PUTC(c, '\r'); break;
                    case 't': PUTC(c, '\t'); break;
                    default:
                        c->top = head;
                        return LEPT_PARSE_INVALID_STRING_ESCAPE;
                }
                break;
            case '\0':
                c->top = head;
                return LEPT_PARSE_MISS_QUOTATION_MARK;
            default:
                if ((unsigned char)ch < 0x20) {
                    c->top = head;
                    return LEPT_PARSE_INVALID_STRING_CHAR;
                }
                PUTC(c, ch);
        }
    }
}

/*
    写入解析出来的根值
*/
static int lept_parse_value(lept_context* c, lept_value* v) {
    switch (c->json[0]) {
        case 'n': return lept_parse_literal(c, v, "null", LEPT_NULL);
        case 't': return lept_parse_literal(c, v, "true", LEPT_TRUE);
        case 'f': return lept_parse_literal(c, v, "false", LEPT_FALSE);
        case '"': return lept_parse_string(c, v);
        /* \0 是字符串结束符 */
        case '\0': return LEPT_PARSE_EXPECT_VALUE;
        default: return lept_parse_number(c, v);
    }
}

/*
    解析JSON文本
*/
int lept_parse(lept_value* v, const char* json_str) {
    int ret;
    assert(v != NULL);
    lept_context c;
    c.json = json_str;
    c.stack = NULL;
    c.top = c.size = 0;
    lept_init(v);
    lept_parse_whitespace(&c);
    if ((ret = lept_parse_value(&c, v)) == LEPT_PARSE_OK) {
        lept_parse_whitespace(&c);
        if (c.json[0] != '\0') {
            v->type = LEPT_NULL;
            ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
        }
    }
    assert(c.top == 0);
    free(c.stack);
    return ret;
}

/*
    如果传入的是字符串，则释放v可能已经分配到的内存,将其类型设置为LEPT_NULL
    如果是其他不需要释放资源的类型，将其类型设置为LEPT_NULL
*/
void lept_free(lept_value* v) {
    /* 首先断言v是不是空指针*/
    assert(v != NULL);
    /* 只有给定的v是字符串对象的时候 才执行释放操作*/
    if (v->type == LEPT_STRING) {
        free(v->u.s.s);
    }
    /* 释放后将v的类型设置为LEPT_NULL*/
    v->type = LEPT_NULL;
}

/*
    返回value的类型
*/
lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}

/*
    读写API实现
*/
int lept_get_boolean(const lept_value* v) {
    /* 断言*/
    assert(v != NULL && (v->type == LEPT_TRUE || v->type == LEPT_FALSE));
    return v->type == LEPT_TRUE;
    
}

void lept_set_boolean(lept_value* v, int b) {
    lept_free(v); /* 此时type是NULL 也就是0*/
    v->type = b ? LEPT_TRUE : LEPT_FALSE;
}

double lept_get_number(const lept_value* v) {
    assert(v->type == LEPT_NUMBER);
    return v->u.n;
}

void lept_set_number(lept_value* v, double n) {
    lept_free(v);
    v->type = LEPT_NUMBER;
    v->u.n = n;
}

const char* lept_get_string(const lept_value* v) {
    assert(v != NULL && v->type == LEPT_STRING);
    return v->u.s.s;
}

size_t lept_get_string_length(const lept_value* v) {
    assert(v != NULL && v->type == LEPT_STRING);
    return v->u.s.len;
}

void lept_set_string(lept_value* v, const char* s, size_t len) {
    assert(v!= NULL && (s != NULL || len == 0));
    /* 首先释放可能的内存*/
    lept_free(v);
    /* 为字符串s申请内存 多申请一个作为终止符*/
    v->u.s.s = (char*) malloc(len + 1);
    /* 复制内容*/
    memcpy(v->u.s.s, s, len);
    /* 在结尾加上终止符*/
    v->u.s.s[len] = '\0';
    /* 设置长度*/
    v->u.s.len = len;
    /* 设置类型*/
    v->type = LEPT_STRING;
}


/* leptjson.c */