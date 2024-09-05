#include "rotation.h"
#include "stdlib.h"
#include "vector_math.h"

const struct pixel black_pixel = {0, 0, 0};

static struct vector_2d get_coord_from_index(const struct vector_2d *v, uint64_t width, uint64_t height){
    struct vector_2d res;
    res.x = (int64_t)(v->x - width / 2 + (width % 2 == 0) * (v->x >= width / 2));
    res.y = - (int64_t)(v->y - height / 2 + (height % 2 == 0) * (v->y >= height / 2));
    return res;
}

static struct vector_2d get_index_from_coord(const struct vector_2d *v, uint64_t width, uint64_t height){
    struct vector_2d res;
    res.x = (int64_t)(v->x + width / 2 - (width % 2 == 0) * (v->x > 0));
    res.y = (int64_t)((- v->y) + height / 2 - (height % 2 == 0) * (v->y < 0));
    return res;
}

struct image rotate(int64_t angle, const struct image *image){
    struct image res = {0};
    if (angle % 180){
        res.width = image->height;
        res.height = image->width;
    } else {
        res.width = image->width;
        res.height = image->height;
    }
    create_image_data(&res);
    struct matrix2_2 mtx = get_rotation_matrix(- angle);
    for (size_t y = 0; y < res.height; y++){
        for (size_t x = 0; x < res.width; x++){
            struct vector_2d coord = get_coord_from_index(&(struct vector_2d){.x = (int64_t)x, .y = (int64_t)y}, res.width, res.height);
            coord = mul2_matrix_vector(&mtx, &coord);
            coord = get_index_from_coord(&coord, image->width, image->height);
            if (llabs(coord.x) >= image->width || llabs(coord.y) >= image->height){
                res.data[y][x] = black_pixel;
            } else {
                res.data[y][x] = image->data[coord.y][coord.x];
            }
        }
    }
    return res;
}
