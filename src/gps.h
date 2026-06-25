#ifndef GPS_H
#define GPS_H

typedef struct {
    double latitude;
    double longitude;
    double altitude;
    int    is_active; // 信号を受信中か
} GPSState;

// GPSデータを更新・取得する関数
void gps_update(double lat, double lon);
void gps_get_coords(double *lat, double *lon);

#endif
