#include "bmp_file_processing.h"
#include <stdlib.h>

uint8_t getPadding(uint64_t width){
    return (4 - (width * sizeof(struct pixel)) % 4) % 4;
}

enum read_status from_bmp(FILE *in, struct image *image){
    struct bmp_header header;
    size_t obj_read = fread(&header, sizeof(struct bmp_header), 1, in);
    uint8_t padding = getPadding(header.biWidth);
    if (obj_read != 1){
        return READ_INVALID_HEADER;
    }
    if(header.biBitCount != sizeof(struct pixel) * 8){
        return READ_INVALID_SIGNATURE;
    }
    image->width = header.biWidth;
    image->height = header.biHeight;
    if (image->data != NULL){
        free_image_data(image);
    }
    create_image_data(image);
    fseek(in, header.bOffBits, SEEK_SET);
    for (size_t i = image->height - 1; i >= 0; i--){
        uint64_t pixel_read = fread((image->data)[i], sizeof(struct pixel), image->width, in);
        if (pixel_read != image->width){
            free_image_data(image);
            return READ_INVALID_DATA;
        }
        fseek(in, padding, SEEK_CUR);
        if (i == 0){
            break;
        }
    }
    /*
    if (image->data != NULL){
        free(image->data);
    }
    image->width = header.biWidth;
    image->height = header.biHeight;
    uint64_t size = (header.biWidth * sizeof(struct pixel) + getPadding(header.biWidth)) * header.biHeight;
    printf("%llu\n", size);
    printf("%u\n", header.biSizeImage);
    fseek(in, header.bOffBits, SEEK_SET);
    image->data = malloc(size);
    obj_read = fread(image->data, size, 1, in);
    if (obj_read != 1){
        return READ_INVALID_DATA;
    }
    */
    return READ_OK;
}

enum write_status to_bmp( FILE* out, const struct image *image ){
    uint8_t padding = getPadding(image->width);
    struct bmp_header header = {
        .bfType = 19778,
        .bOffBits = sizeof(struct bmp_header),
        .bfReserved = 0,
        .bfileSize = sizeof(struct bmp_header) + image->width * sizeof(struct pixel) * image->height + getPadding(image->width) * image->height,
        .biSize = 40,
        .biWidth = image->width,
        .biHeight = image->height,
        .biPlanes = 1,
        .biBitCount = 24,
        .biCompression = 0,
        .biSizeImage = image->width * image->height * sizeof(struct pixel) + image->height * padding,
        .biXPelsPerMeter = 2834,
        .biYPelsPerMeter = 2834,
        .biClrUsed = 0,
        .biClrImportant = 0
    };
    fwrite(&header, sizeof(struct bmp_header), 1, out);
    char pad = (char)127;
    for (size_t i = image->height - 1; i >= 0; i--){
        fwrite((image->data)[i], sizeof(struct pixel), image->width, out);
        for (size_t j = 0; j < padding; j++){
            fwrite(&pad, sizeof(char), 1, out);
        }
        if (i == 0){
            break;
        }
    }
    //fwrite(image->data, header.biSizeImage, 1, out);
    return WRITE_OK;
}
