#pragma once
#include <Arduino_GFX_Library.h>
#include "adsb.h"
extern Arduino_RGB_Display *gfx;

void draw_map_outline();
void fill_polygon(int *x, int *y, int numPoints, uint16_t color);
void fill_polygon_latlon(float latLon[][2], int numPoints, uint16_t color);

