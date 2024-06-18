#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define SSID "TP-Link_AIOL"
#define PASSWORD "AIOL2018"
#define UDP_PORT 12345

#define LED_WiFi_CONNECTED D1

WiFiUDP udp;
// IPAddress serverIP(192, 168, 0, 153); // コメントアウト: PCのIPアドレス
const char* serverHostname = "tomixrm-2.local"; // 送信先のホスト名

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_WiFi_CONNECTED, OUTPUT);
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
    digitalWrite(LED_WiFi_CONNECTED, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
}

int wifilevel(bool getRaw = false) {
    if (WiFi.status() != WL_CONNECTED)
        return 0;
    else {
        int rssi = WiFi.RSSI();
        if (getRaw)
            return rssi;
        int siglevel;
        if (rssi <= -96)
            siglevel = 1;
        else if (rssi <= -85)
            siglevel = 2;
        else if (rssi <= -75)
            siglevel = 3;
        else
            siglevel = 4;
        return siglevel;
    }
}

void loop() {
    static int i = 0;
    i++;
    Serial.printf("Hello, world! %d\n", wifilevel(true));
    delay(10);

    IPAddress serverIP;
    if (WiFi.hostByName(serverHostname, serverIP)) {
        udp.beginPacket(serverIP, UDP_PORT); // 送信先のIPアドレスとポート番号を指定

        char buf[128];
        sprintf(buf, "Hello, world! %d", i);
        udp.write(buf); // 送信するデータ
        udp.endPacket();
    } else {
        Serial.println("Hostname resolution failed");
    }
    delay(10);
}
