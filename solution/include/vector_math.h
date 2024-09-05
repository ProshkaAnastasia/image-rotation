#pragma once
#include <stdint.h>

struct vector_2d {
    int64_t x, y;
};

struct matrix2_2 {
    double a11, a12, a21, a22;
};

struct vector_2d mul2_matrix_vector(struct matrix2_2 *mtx, struct vector_2d *v);
void inverse_rotation_matrix(struct matrix2_2 *mtx);
struct matrix2_2 get_rotation_matrix(int64_t angle);
