#pragma once
#include <stdbool.h>
#include <stdint.h>

struct int64_or_none {
    int64_t value;
    char sign;
    bool valid;
};

extern const struct int64_or_none none_int64;
