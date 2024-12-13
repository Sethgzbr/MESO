#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
int LED1 = 32; 
int LED2 = 33; 

int retard = 2000; 


#define SS_PIN 5
#define RST_PIN 0

MFRC522 mfrc522(SS_PIN, RST_PIN);

const char* ssid = "WifiProva";
const char* password = "mandarinas";  

const char* mqttServer = "a2lg3qizupe1nw-ats.iot.us-east-1.amazonaws.com";
const int mqttPort = 8883;
const char* mqttClientId = "esp32/pub";
const char* topic = "esp32/pub";

static const char rootCA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

static const char certificate[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUfepc2s4Ylx7bKvR4OH//KftxeeowDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI0MTIwMjE0MzA0
MVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAL1Sdw1HU7MjsoBnJe9z
MF5ayox8W+lcKowuGqBKQUCodNWPQfcyUw8HrT6RNNmcH7YNCWkKuaUrAwbcn+U4
R3noyBFeVl4PXh1NUBgIoGy3lkZqNL6KsjAN7iVsogPGIQZCfgg4BKLE6U4Vo5B9
2oM7D/BsaC+/hlT8qMZ0HDYU2z1zmCXFBayeZ1JsJK/M4ioYZ4Y7CRdnibj4KFEc
3NFKatcHUK43srZxZvLme4JFbVJxdScMXVpgONFNiPZYC8CSEErdA/3H3ZEM45OM
9zsR+Rbxz7G7asQD+zDpLC++5wYl1/XoX30UDDAfJ7P5MvzNXFHfIySEptVsSUzv
wckCAwEAAaNgMF4wHwYDVR0jBBgwFoAUW8ZUWQVZt1btoVRUkVDj7PEeHt4wHQYD
VR0OBBYEFGbm8bdTH2QQaRWYgWQ5HvfgcKXHMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCgyuZolzptOnafYGW6U0toSNFY
LX3wIOIEXNqLXs3wc7QrM3myrU6pwkOUiALldf0xzuXl3V/HRuoVo2Edepo4R7JN
2SeU4v3L6AxGDCZlSPY/qhShgB31Fryiu+3ZMS+1TcdB0nRV2Rbr3gCbr0SK5Y4S
j+OE1ZRlN/qqOeCxu3VeprbQ2/yF/Zan6w5ovmx3ONrmDxtgS+au9V3A0dRF9PNr
RmX28RqXYuieF+VWVCmXpllOKFKO/Zu0Poar02R8zq++g6ry0i2rn5Oc+irnmN7F
WNNK9NQL8W18uWp+5K8dyXJk5SCJ9haXo8CIXQIMof7k+K+72SJ8wNOwmxqo
-----END CERTIFICATE-----
)KEY";
static const char privateKey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEAvVJ3DUdTsyOygGcl73MwXlrKjHxb6VwqjC4aoEpBQKh01Y9B
9zJTDwetPpE02Zwftg0JaQq5pSsDBtyf5ThHeejIEV5WXg9eHU1QGAigbLeWRmo0
voqyMA3uJWyiA8YhBkJ+CDgEosTpThWjkH3agzsP8GxoL7+GVPyoxnQcNhTbPXOY
JcUFrJ5nUmwkr8ziKhhnhjsJF2eJuPgoURzc0Upq1wdQrjeytnFm8uZ7gkVtUnF1
JwxdWmA40U2I9lgLwJIQSt0D/cfdkQzjk4z3OxH5FvHPsbtqxAP7MOksL77nBiXX
9ehffRQMMB8ns/ky/M1cUd8jJISm1WxJTO/ByQIDAQABAoIBAFTPEkHCh/4hqZ7X
lijT4wEBjuar9shs3yp4pLjVSrHaRKw+RoCj7I05FSSIC7LHu3TkFikWAt+4ityS
DJa0RWCZJLaTGgF8xN4/efeqNaM+AnV8sjABFZ1tQBdHuLQUF0skkizAW2NG7nRq
QSFDH5XV6Wf8SBfLpjOAE2MDNHgMzMzPTLqpQSbntWd4RHiuGMkSLWCyp4Wug2ej
lgIj20a2VYrtP8pK56qF7JpQgEjhbEDvG7gOi/fXE9znGyz8C8eGNtfIjo6LR78S
GVppOS45khLDLVbQoAULeWVX3N1vS6zfpJ448eey4VB4qbW4qWp7AV+eVOfa9Jep
iDXxgAECgYEA+yk1TU4goDvz9EBxFJM10iynyM5RvfcZFPZjArJk3lbcpGSioEQZ
TSTASG6b+sklJgDao8aEkCldEfcw4mU64c3Zs02hqFalDFi9UUUGs1HiyiRp16Du
U+PQM88tyTtMLPxIuO4Ccf/TGCIbAFNu7mz513jhwfiwfIyiFh652AECgYEAwPhA
Xyj/1c3Jisc4BA1uDGwNfOCdnrH2yzVPmYuWnoTg8ihap6noYsQqnO+2CCqpiboG
UqGdIVpaZ/SK1csSzEPMWJyewyqZZ+o3ZWl7Q6dyZOLTB4R2dUxVfHzf+T2OAqyV
cp8SIv0899y/ruqgNvdYf9HKJ3GN+7JwhnFtKckCgYEA6jLv0AkVJTUic1UP3Oa0
XipjvjydPm1GhySFCMO+iREoJ2brulQl36hwYFo7umuL51cOiX8Yp7DaZ2E/xSwt
7tbbtHWkU2uP9eZdioW6DMZDmsi/pWEcOz+IKnd7M1TG4H/TdBYEU7cAaVWMJg6m
t08I3eKLaStzroAYuFWoaAECgYEAusxV/AhDR+PSkp3xErMxcaLzl4wT6LhbsDCm
InvmzQLSgngf8affRiShH5RIwTUTMzi5wCmkYtIFLBakgvr28nc7DBho84J8SASJ
pYjrgv1IFnMgV2maBkhjhIOZiLtWii4o6XEk7Gv6JfIyOA/2Ed90cx9RMseQ6zK8
DNkmFEkCgYEA3em8QkLbqxeJ2x7Gil+EbSesRhY+4nu7P6N9fAUl0VvZkVRgp09Q
hxhNsjIGmR6nvoFb4URFuxbY7dkrQQrmxVKZIAHH9IW+CrjYUSAYiCLLo4zC54XI
Ps/D5tnb4WWuunFAFyIPCZHOsCwk8kZ4i+xI0+w9YEThD3DC+JORJSE=
-----END RSA PRIVATE KEY-----
)KEY";

// Cliente WiFi seguro y MQTT
WiFiClientSecure net;
PubSubClient client(net);

void connectToWiFi() {
  Serial.print("Conectando a WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado a WiFi.");
}

void connectToAWS() {
  // Configura los certificados para MQTT
  net.setCACert(rootCA);
  net.setCertificate(certificate);
  net.setPrivateKey(privateKey);

  // Configura el cliente MQTT
  client.setServer(mqttServer, mqttPort);
 
  // Conexión al broker
  Serial.print("Conectando a AWS IoT...");
  while (!client.connect(mqttClientId)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConectado a AWS IoT.");
}

void setup() {
  pinMode(LED1, OUTPUT); // Configurar LED1 como salida
  pinMode(LED2, OUTPUT); // Configurar LED2 como salida
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();

  // Conexión WiFi
  connectToWiFi();

  // Conexión a AWS IoT
  connectToAWS();

  Serial.println("Esperando tarjeta...");
}

void loop() {
  // Verifica si hay una tarjeta presente
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    digitalWrite(LED1, LOW); // Apagar LEDs
    digitalWrite(LED2, LOW);
    return;
  }

  // Lee el UID de la tarjeta
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid += String(mfrc522.uid.uidByte[i], HEX);
    if (i < mfrc522.uid.size - 1) uid += ":";
  }
  Serial.print("UID detectado: ");
  Serial.println(uid);

  // Construye un mensaje JSON
  String payload = "{\"uid\": \"" + uid + "\"}";
  Serial.print("Enviando mensaje a AWS IoT: ");
  Serial.println(payload);

  // Publica el mensaje al tema MQTT
  if (!client.publish(topic, payload.c_str())) {
    Serial.println("Error enviando el mensaje. Intentando reconectar...");
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    connectToAWS();
  } else {
    Serial.println("Mensaje enviado con éxito.");
    digitalWrite(LED2, HIGH);
    digitalWrite(LED1, LOW);
  }

  delay(retard);
  digitalWrite(LED1, LOW); // Apaga LEDs
  digitalWrite(LED2, LOW);
  // Detener la comunicación de la tarjeta
  mfrc522.PICC_HaltA();

}
