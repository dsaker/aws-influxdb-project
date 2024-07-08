#if defined(ESP32)
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#define DEVICE "ESP32"
#elif defined(ESP8266)
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#define DEVICE "ESP8266"
#endif

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include "config.h"
#include <DHT.h>

// Declare InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

DHT dht(DHT_PIN, DHT_TYPE);

float celsius;
float humidity;
float fahrenheit;

// Declare Data point
Point sensor("measurements");

void setup() {
  Serial.begin(9600);
  pinMode(DHT_PIN, INPUT);
  dht.begin();
  // Setup wifi
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to wifi");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  // Add tags
  sensor.addTag("location", LOCATION);
  sensor.addTag("sensor_name", SENSOR_NAME);

  // Accurate time is necessary for certificate validation and writing in batches
  // We use the NTP servers in your area as provided by: https://www.pool.ntp.org/zone/
  // Syncing progress and the time will be printed to Serial.
  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  // Check server connection
  if (client.validateConnection()) {
    Serial.print("\nConnected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("\nInfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }
}

void loop() {
  // Clear fields for reusing the point. Tags will remain the same as set above.
  sensor.clearFields();

  // read values from DHT22 sensor
  humidity = dht.readHumidity();
  celsius = dht.readTemperature();

  // add fields for sensor values
  sensor.addField("Celsius", celsius);
  sensor.addField("Humidity", humidity);
  sensor.addField("Fahrenheit", (celsius*1.8) + 32);

  // Print what are we exactly writing
  Serial.print("Writing: ");
  Serial.println(sensor.toLineProtocol());

  // Check WiFi connection and reconnect if needed
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("Wifi connection lost");
  }

  // Write point
  if (!client.writePoint(sensor)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  Serial.printf("Waiting %d minutes\n", INTERVAL_MIN);
  delay(1000*60*INTERVAL_MIN);
 }
