#pragma once

// DHT sensor type
#define DHT_TYPE DHT22
// DHT pin
#define DHT_PIN 14
// WiFi AP SSID
#define WIFI_SSID ""
// WiFi password
#define WIFI_PASSWORD ""
// Time zone info
#define TZ_INFO ""

#define INFLUXDB_URL ""
#define INFLUXDB_TOKEN ""
#define INFLUXDB_ORG ""
#define INFLUXDB_BUCKET ""

// Name of sensor for influxdb filter
#define SENSOR_NAME "sunroom"
// Tag of sensor for influxdb filter
#define LOCATION "outside"
// Interval in minutes between measurements
#define INTERVAL_MIN 1