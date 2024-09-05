#include <stdio.h>

#include "bmp_file_processing.h"
#include "image_format.h"
#include "inttypes.h"
#include "none_types.h"
#include "rotation.h"
#include "string_math.h"

void print_image(struct image *image){
    for (size_t i = 0; i < image->height; i++){
        for (size_t j = 0; j < image->width; j++){
            printf(" %x %x %x |", (image->data)[i][j].r, (image->data)[i][j].g, (image->data)[i][j].b);
        }
        printf("\n");
    }
}

int main( int argc, char** argv ) {
    (void) argc; (void) argv; // supress 'unused parameters' warning
    if (argc != 4){
        printf("Wrong arguments");
        return 0;
    }
    struct int64_or_none none_or_angle = getint64_from_string(argv[3]);
    if (!none_or_angle.valid){
        printf("Wrong angle");
        return 0;
    }
    int64_t angle = none_or_angle.value;
    FILE *file = fopen(argv[1], "rb");
    if (!file){
        return 0;
    }
    struct image image;
    image.data = NULL;
    from_bmp(file, &image);
    fclose(file);
    file = fopen(argv[2], "wb");
    //file = fopen("/Users/anastasiapronina/Desktop/out1.bmp", "wb");
    if (!file){
        return 0;
    }
    struct image res = rotate(angle, &image);
    to_bmp(file, &res);
    fclose(file);
    free_image_data(&image);
    free_image_data(&res);
    return 0;
}
