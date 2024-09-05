#pragma once
#include "image_format.h"
#include <stdint.h>
#include <stdio.h>

//__attribute__((packed))

struct __attribute__((packed)) bmp_header {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize; //bytes required for this part of structure
    uint32_t biWidth; //width of the picture in pixels
    uint32_t biHeight; //height of the picture in pixels
    uint16_t biPlanes; //planes count, must be 1
    uint16_t biBitCount; //bits for pixel
    uint32_t biCompression; //type of compression
    uint32_t biSizeImage; //size of the picture (may be set 0)
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t  biClrImportant;
};

uint8_t getPadding(uint64_t width);

enum read_status  {
  READ_OK = 0,
  READ_INVALID_SIGNATURE,
  READ_INVALID_BITS,
  READ_INVALID_HEADER,
  READ_INVALID_DATA
};

enum read_status from_bmp( FILE* in, struct image *image );

enum  write_status  {
  WRITE_OK = 0,
  WRITE_ERROR
};

enum write_status to_bmp( FILE* out, const struct image *image );
