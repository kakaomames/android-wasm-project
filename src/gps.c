#include "gps.h"
#include <stdio.h>

static GPSState current_gps = {0.0, 0.0, 0.0, 1};

void gps_update(double lat, double lon) {
    current_gps.latitude = lat;
    current_gps.longitude = lon;
    printf("[GPS] 座標更新: %.6f, %.6f\n", lat, lon);
}

void gps_get_coords(double *lat, double *lon) {
    *lat = current_gps.latitude;
    *lon = current_gps.longitude;
}
