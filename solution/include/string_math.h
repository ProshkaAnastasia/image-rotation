#pragma once
#include <stdbool.h>
#include <stdlib.h>

#include "none_types.h"

size_t string_length(const char* str);
bool is_space(const char ch);
struct int64_or_none getint64_from_string(const char* str);
