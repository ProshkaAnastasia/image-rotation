#include <math.h>
#include <stdio.h>

#include "vector_math.h"

#define PI 3.14159265

struct vector_2d mul2_matrix_vector(struct matrix2_2 *mtx, struct vector_2d *v){
    struct vector_2d res;
    res.x = (int64_t)(mtx->a11 * (double)v->x + mtx->a12 * (double)v->y);
    res.y = (int64_t)(mtx->a21 * (double)v->x + mtx->a22 * (double)v->y);
    return res;
}

void inverse_rotation_matrix(struct matrix2_2 *mtx){
    mtx->a12 = - mtx->a12;
    mtx->a21 = - mtx->a21;
}

static double cosin(int64_t angle){
    if (angle % 90 == 0){
        if (angle % 360 == 0){
            return 1;
        } else if (angle % 180 == 0){
            return -1;
        } else {
            return 0;
        }
    } else {
        return cos((double)angle * PI / 180);
    }
}

static double sinus(int64_t angle){
    while (angle < 0){
        angle += 360;
    }
    if (angle % 90 == 0){
        if (angle % 180 == 0){
            return 0;
        } else if (angle % 360 == 90){
            return 1;
        } else {
            return -1;
        }
    } else {
        return sin((double)angle * PI / 180);
    }
}

struct matrix2_2 get_rotation_matrix(int64_t angle){
    struct matrix2_2 res;
    res.a11 = cosin(angle);
    res.a12 = sinus(angle);
    res.a21 = - sinus(angle);
    res.a22 = cosin(angle);
    return res;
}
