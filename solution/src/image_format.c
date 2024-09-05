#include "image_format.h"
#include <stdlib.h>

void free_image_data(struct image *image){
    for (size_t i = 0; i < image->height; i++){
        free((image->data)[i]);
    }
    free(image->data);
    image->data = NULL;
}

void create_image_data(struct image *image){
    image->data = malloc(sizeof(struct pixel*) * image->height);
    for (size_t i = 0; i < image->height; i++){
        (image->data)[i] = malloc(sizeof(struct pixel) * image->width);
    }
}
