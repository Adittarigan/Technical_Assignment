#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <HTTPClient.h>

const char* ssid = "Tarigeng";
const char* password = "17022004";
const char* serverAddress = "http://192.168.1.37:5000/data";
int sensorPin = 33;

int getAirQualityData() {
  int analog_data = analogRead(sensorPin);
  Serial.print("Air Quality: ");
  Serial.println(analog_data);
  delay(300);  // Allow sensor to stabilize
  return analog_data;
}

void postSensorData(){
  WiFiClient client;
  HTTPClient http;

  int airQualityData = getAirQualityData();
  http.begin(client, serverAddress);
  http.addHeader("Content-Type", "application/json");

  String payload = "{\"Air Quality\": " + String(airQualityData) + "}";

  int httpResponseCode = http.POST(payload);

  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
  Serial.println(payload);

  http.end();

  delay(5000);
}

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA); //setting wifi chip sebagai station/client
  WiFi.begin(ssid, password);

  // Cek status koneksi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Tampilkan pesan sukses
  Serial.println("");
  Serial.println("WiFi connected!");
}

void loop() {
  postSensorData();
}
