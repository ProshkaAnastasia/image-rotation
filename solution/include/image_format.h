#pragma once
#include <stdint.h>

struct pixel {
    uint8_t r, g, b;
};

struct image {
    uint64_t height, width;
    struct pixel **data;
};

void free_image_data(struct image *image);
void create_image_data(struct image *image);
