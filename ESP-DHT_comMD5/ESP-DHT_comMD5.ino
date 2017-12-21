#include <DHT11.h>
#include <MD5Builder.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "NOME_DA_REDE";
const char* password = "SENHA_DA_REDE";

#define ORG "3a4ypl"
#define DEVICE_TYPE "WTH001" //TIPO DO DEVICE, IGUAL AO CRIADO NA PLANTA
#define DEVICE_ID "NOME_DEVICE_CADASTRADO"


//função para realizar o HASH
MD5Builder _md5;
String md5(String str) {
  _md5.begin();
  _md5.add(String(str));
  _md5.calculate();
  return _md5.toString();
}

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/evt/weather/fmt/json";
char authMethod[] = "use-token-auth";
char token[50];
String tokenString = md5(DEVICE_ID);

char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;
PubSubClient client(server, 1883, NULL, wifiClient);
int pin = 2;
DHT11 dht11(pin);
int err;
float temp, humi;

void setup()
{
  Serial.begin(115200);
  tokenString.toCharArray(token, 50);
  delay(10);
  Serial.println();
  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.print("WiFi connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{


  if (!!!client.connected()) {
    Serial.print("Reconnecting client to ");
    Serial.println(server);
    while (!!!client.connect(clientId, authMethod, token)) {
      Serial.print(".");
      delay(500);
    }
    Serial.println();
  }

  if ((err = dht11.read(humi, temp)) == 0)
  {
    Serial.print("temperature:");
    Serial.print(temp);
    Serial.print(" humidity:");
    Serial.print(humi);
    Serial.println();
    String payload = "{\"d\":{";
    payload += "\"deviceID\":";
    payload += "\"";
    payload += DEVICE_ID; 
    payload += "\",";
    payload += "\"temperature\":";
    payload += temp;
    payload += ",\"humidity\":";
    payload += humi;
    payload += "}}";
    Serial.print("Sending payload: ");
    Serial.println(payload);

    if (client.publish(topic, (char*) payload.c_str())) {
      Serial.println("Publish ok");
    } else {
      Serial.println("Publish failed");
    }
    delay(10000);
  }
}




