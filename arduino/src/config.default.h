
// DHT sensor type
#define DHT_TYPE DHT22
// DHT pin
#define DHT_PIN 14
// Use static IPv4 addressing, disable for DHCPv4
#define WIFI_IPV4_STATIC true
// Static IPv4 gateway address
#define WIFI_IPV4_GATEWAY 192, 168, 1, 1
// Static IPv4 subnet mask
#define WIFI_IPV4_SUBNET_MASK 255, 255, 255, 0
// Static IPv4 primary DNS server
#define WIFI_IPV4_DNS_1 1, 1, 1, 1
// Static IPv4 secondary DNS server
#define WIFI_IPV4_DNS_2 1, 0, 0, 1
// WiFi AP SSID
#define WIFI_SSID ""
// WiFi password
#define WIFI_PASSWORD ""
// Time zone info
#define TZ_INFO "UTC-5"

#define INFLUXDB_URL ""
#define INFLUXDB_TOKEN ""
#define INFLUXDB_ORG ""
#define INFLUXDB_BUCKET ""

// Static IPv4 address
#define WIFI_IPV4_ADDRESS 192, 168, 1, 18
// Name of sensor for influxdb filter
#define SENSOR_NAME "sensor1"
// Tag of sensor for influxdb filter
#define LOCATION "inside"
// Interval in minutes between measurements
#define INTERVAL_MIN 1
