#ifndef LEPTJSON_H__
#define LEPTJSON_H__

/*  声明数据类型 使用枚举*/
typedef enum {
    LEPT_NULL,
    LEPT_FALSE,
    LEPT_TRUE,
    LEPT_NUMBER,
    LEPT_STRING,
    LEPT_ARRAY,
    LEPT_OBJECT
} lept_type;

/* 声明数据结构 使用结构体 */
typedef struct {
    lept_type type;
}lept_value;

/* 声明一个传入字符串的数据类型*/
typedef struct {
    const char* json;
}lept_context;


/* 声明解析返回值枚举*/
enum {
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR
};

/* 函数声明：解析JSON
   传入一个不可更改的字符串JSON文本
   以及一个根结点指针
*/
int lept_parse(lept_context* c, lept_value* v);

/* 函数声明：访问结果 获取类型*/
lept_type lept_get_type(const lept_value* v);

#endif /* LEPTJSON_H__ */