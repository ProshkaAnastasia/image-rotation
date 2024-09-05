#include <stdbool.h>

#include "string_math.h"

size_t string_length(const char* str){
    size_t res = 0;
    while (*str != '\0'){
        res++;
        str++;
    }
    return res;
}

bool is_space(const char ch){
    if (ch == '\t' || ch == ' ' || ch == '\n'){
        return true;
    }
    return false;
}

struct int64_or_none getint64_from_string(const char* str){
    size_t length = string_length(str);
    struct int64_or_none res = none_int64;
    if (*str == '+' || *str == '-'){
        length--;
        res.sign = *str;
        str++;
    }
    if (length == 0){
        return res;
    } 
    if (*str < '0' || *str > '9'){
        return res;
    }  
    int64_t mult = 1;
    for (size_t i = length - 1; i >= 0; i--){
        if (str[i] < '0' || str[i] > '9'){
            return res;
        }  
        res.value += (str[i] - '0') * mult;
        mult *= 10;
        if (i == 0){
            break;
        }
    }
    res.valid = true;
    if (res.sign == '-'){
        res.value = - res.value;
    }
    return res;
}
