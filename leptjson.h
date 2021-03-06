#ifndef LEPTJSON_H__
#define LEPTJSON_H__

#include <stddef.h> /* size_t */

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
typedef struct lept_value lept_value;

typedef struct lept_member lept_member;

struct lept_value {
    /* 当且仅当解析对象是数字的时候，成员n用于存储解析出的数字*/
    /* 现在增加了字符串对象 因为不可能同时为数字和字符串 使用union节省内存*/
    union {
        struct { lept_member* m; size_t size; }o; /* object*/
        struct { lept_value* e; size_t size; }a; /* array */
        struct { char* s; size_t len; }s; /* string */
        double n; /* number */
    }u;
    lept_type type;
};

/* member结构体是一个JSON键值对*/
struct lept_member {
    char* key; /* key 一个字符串*/
    size_t klen; /* key字符串的长度*/
    lept_value val; /* val */
};

/* 声明解析返回值枚举*/
enum {
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR,
    LEPT_PARSE_NUMBER_TOO_BIG,
    LEPT_PARSE_MISS_QUOTATION_MARK,
    LEPT_PARSE_INVALID_STRING_ESCAPE,
    LEPT_PARSE_INVALID_STRING_CHAR,
    LEPT_PARSE_INVALID_UNICODE_HEX,
    LEPT_PARSE_INVALID_UNICODE_SURROGATE,
    LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET
};

/* 访问所有类型之前 都需要初始化 初始化将其设置为NULL类型即可*/
#define lept_init(v) do { (v)->type = LEPT_NULL; } while(0)

/* 函数声明：解析JSON
   传入一个不可更改的字符串JSON文本
   以及一个根结点指针
*/
int lept_parse(lept_value* v, const char* json_str);

/* 释放内存并将类型设置为NULL*/
void lept_free(lept_value* v);

/* 函数声明：访问结果 获取类型*/
lept_type lept_get_type(const lept_value* v);

/* 因为我们定义了lept_free()函数 所以lept_set_null()可以直接借用*/
#define lept_set_null(v) lept_free(v)

/* 提供读取和写入的API*/
int lept_get_boolean(const lept_value* v);
void lept_set_boolean(lept_value* v, int b);

double lept_get_number(const lept_value* v);
void lept_set_number(lept_value* v, double n);

const char* lept_get_string(const lept_value* v);
size_t lept_get_string_length(const lept_value* v);
void lept_set_string(lept_value* v, const char* s, size_t len);

size_t lept_get_array_size(const lept_value* v);
lept_value* lept_get_array_element(const lept_value* v, size_t index);

size_t lept_get_object_size(const lept_value* v);
const char* lept_get_object_key(const lept_value* v, size_t index);
size_t lept_get_object_key_length(const lept_value* v, size_t index);
lept_value* lept_get_object_value(const lept_value* v, size_t index);

#endif /* LEPTJSON_H__ */