/**
 * @file   pixel.h
 * @brief  This file contains the function definitions for pixel.c.
 * @author Matthew C. Lindeman
 * @date   January 30, 2024
 * @bug    None known
 * @todo   Nothing
 */
#ifndef PIX_H
#define PIX_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_COL 255
#define MIN_COL 0

typedef struct PIXEL_T {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} pixel;

void debug_pixel(pixel the_pixel);
void ppm_print(pixel the_pixel, FILE * fp);

#endif
