#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

#define SSID "TP-Link_AIOL"
#define PASSWORD "AIOL2018"

#define UDP_PORT 12345

WiFiUDP udp;
IPAddress serverIP(192, 168, 0, 135); // PCのIPアドレス

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    delay(10);

    WiFi.mode(WIFI_STA);
    WiFi.printDiag(Serial);
    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");

    // WiFiの状態を表示
    WiFi.printDiag(Serial);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    udp.begin(UDP_PORT);
    delay(1000);

    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
}

void loop() {
    static int i = 0;
    i++;
    Serial.println("Hello, world!");
    delay(10);

    udp.beginPacket(serverIP, UDP_PORT); // 送信先のIPアドレスとポート番号を指定

    char buf[128];
    sprintf(buf, "Hello, world! %d", i);
    udp.write(buf); // 送信するデータ
    udp.endPacket();
}
