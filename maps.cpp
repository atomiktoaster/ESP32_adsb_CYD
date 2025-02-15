#include "maps.h"
#include "mapdata.h"

//int mapPoints = 0;

// Function to fill a polygon by breaking it into triangles
void fillPolygon(int *x, int *y, int numPoints, uint16_t color) {
  for (int i = 1; i < numPoints - 1; i++) {
    gfx->fillTriangle(x[0], y[0], x[i], y[i], x[i + 1], y[i + 1], color);
  }
}

// Fill polygon using triangles
void fillPolygonLL(float latLon[][2], int numPoints, uint16_t color) {
  int screenX[numPoints], screenY[numPoints];

  // Convert all lat/lon points to screen coordinates
  for (int i = 0; i < numPoints; i++) {
    lat_lon_to_screen(latLon[i][0], latLon[i][1], screenX[i], screenY[i]);
  }

  // Decompose into triangles
  for (int i = 1; i < numPoints - 1; i++) {
    gfx->fillTriangle(screenX[0], screenY[0],
                      screenX[i], screenY[i],
                      screenX[i + 1], screenY[i + 1], color);
  }
}

void draw_map_outline() {
  int x1, y1, x2, y2;
  for (int n = 0; n < numMapSets; n++) {
    if (!myMapSets[n].fillColor) {
      // Access each mapset's coordinates dynamically.
      for (int j = 0; j < (myMapSets[n].numPoints - 1); j++) {
        x1 = 0;
        y1 = 0;
        x2 = 0;
        y2 = 0;
        if (myMapSets[n].coordinates[j][0] > 0) {
          lat_lon_to_screen(myMapSets[n].coordinates[j][0], myMapSets[n].coordinates[j][1], x1, y1);
          lat_lon_to_screen(myMapSets[n].coordinates[j + 1][0], myMapSets[n].coordinates[j + 1][1], x2, y2);
          gfx->drawLine(x1, y1, x2, y2, WHITE);  // Draw outline in blue
        }
      }
    } else {
      Serial.println("Fill this");
      fillPolygonLL(myMapSets[n].coordinates, myMapSets[n].numPoints, myMapSets[n].fillColor);
    }
  }
}
