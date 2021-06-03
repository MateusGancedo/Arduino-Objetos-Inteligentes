int segE = 7;
int segD = 8;
int segC = 9;
int segB = 13;
int segA = 12;
int segF = 11;
int segG = 10;

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define ID_MQTT  "GancedoAut"
 
#define TOPICO_SUBSCRIBE "MQTTFlopEnvia"     //tópico MQTT de escuta
#define TOPICO_PUBLISH   "MQTTFlopRecebe"    //tópico MQTT de envio de informações para Broker

// WIFI
const char* SSID = "mateusgancedo5g";
const char* PASSWORD = "gancedo152018";

// MQTT
const char* BROKER_MQTT = "iot.eclipse.org";
int BROKER_PORT = 1883;

WiFiClient espClient;
PubSubClient MQTT(espClient);
char EstadoSaida = '0';

void iniciaWifi();
void iniciaMQTT();
void reconectWiFi(); 
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void VerificaConexoesWiFIEMQTT(void);

int pinoTilt = 5;
 
void setup()
{
  pinMode(segE, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segA, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(pinoTilt, INPUT);

  iniciaWifi();
  iniciaMQTT();
  
  Serial.begin(9600);
}

void iniciaWifi() 
{
    delay(10);
    Serial.print("Conectando no WiFi");
    Serial.println(SSID);
     
    reconectWiFi();
}

void iniciaMQTT() 
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);
    MQTT.setCallback(mqtt_callback);
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;

    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }
   
    if (msg.equals("L"))
    {
        EstadoSaida = '1';
    }

    if (msg.equals("D"))
    {
        EstadoSaida = '0';
    }
     
}

void reconnectMQTT() 
{
    while (!MQTT.connected()) 
    {
        Serial.print("Conectando ao MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) 
        {
            Serial.println("Conectado ao topico de SUBSCRIBE do MQTT");
            MQTT.subscribe(TOPICO_SUBSCRIBE); 
        } 
        else
        {
            Serial.println("Falha ao reconectar MQTT");
            Serial.println("Tetando reconexão em 1s");
            delay(1000);
        }
    }
}

void reconectWiFi() 
{
    if (WiFi.status() == WL_CONNECTED)
        return;
         
    WiFi.begin(SSID, PASSWORD);
     
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100);
    }
   
    Serial.println();
    Serial.print("Conectado na rede");
    Serial.print(SSID);
    Serial.println("IP:");
    Serial.println(WiFi.localIP());
}

void VerificaConexoesWiFIEMQTT(void)
{
    if (!MQTT.connected()) 
        reconnectMQTT();
     
     reconectWiFi();
}

void EnviaEstadoOutputMQTT(void)
{
    if (EstadoSaida == '0')
      MQTT.publish(TOPICO_PUBLISH, "D");
 
    if (EstadoSaida == '1')
      MQTT.publish(TOPICO_PUBLISH, "L");
 
    Serial.println("Estado da saida enviado ao broker!");
    delay(1000);
}
 
void loop()
{  
  
  VerificaConexoesWiFIEMQTT();
 
  EnviaEstadoOutputMQTT();

  MQTT.loop();
  
  if(digitalRead(pinoTilt) == HIGH)
  {
    iterarNumeros();
    Serial.println(jogaDado());
    delay(4000);
  }
  
}
 
int jogaDado()
{
  roletar();
  int numero = random(0,10);
  switch(numero) // Escolhe um numero aleatorio entre 0 e 9
  {
    case 0 :
    acende0();
    MQTT.publish(TOPICO_PUBLISH, "0");
    break;
    case 1 :
    acende1();
    MQTT.publish(TOPICO_PUBLISH, "1");
    break;
    case 2 :
    acende2();
    MQTT.publish(TOPICO_PUBLISH, "2");
    break;
    case 3 :
    acende3();
    MQTT.publish(TOPICO_PUBLISH, "3");
    break;
    case 4 :
    acende4();
    MQTT.publish(TOPICO_PUBLISH, "4");
    break;
    case 5 :
    acende5();
    MQTT.publish(TOPICO_PUBLISH, "5");
    break;
    case 6 :
    acende6();
    MQTT.publish(TOPICO_PUBLISH, "6");
    break;
    case 7 :
    acende7();
    MQTT.publish(TOPICO_PUBLISH, "7");
    break;
    case 8 :
    acende8();
    MQTT.publish(TOPICO_PUBLISH, "8");
    break;
    case 9 :
    acende9();
    MQTT.publish(TOPICO_PUBLISH, "9");
    break;
  }
  return numero;
}

void roletar()
{
  for(int i = 3; i > 0; i--)
  {
    //F
    digitalWrite(segA, HIGH);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, HIGH);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, HIGH);
    digitalWrite(segF, LOW);
    digitalWrite(segG, HIGH);
    delay(75);
    //A
    digitalWrite(segA, LOW);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, HIGH);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, HIGH);
    digitalWrite(segF, HIGH);
    digitalWrite(segG, HIGH);
    delay(75);
    //B
    digitalWrite(segA, HIGH);
    digitalWrite(segB, LOW);
    digitalWrite(segC, HIGH);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, HIGH);
    digitalWrite(segF, HIGH);
    digitalWrite(segG, HIGH);
    delay(75);
    //G
    digitalWrite(segA, HIGH);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, HIGH);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, HIGH);
    digitalWrite(segF, HIGH);
    digitalWrite(segG, LOW);
    delay(75);
    //E
    digitalWrite(segA, HIGH);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, HIGH);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, LOW);
    digitalWrite(segF, HIGH);
    digitalWrite(segG, HIGH);
    delay(75);
    //D
    digitalWrite(segA, HIGH);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, HIGH);
    digitalWrite(segD, LOW);
    digitalWrite(segE, HIGH);
    digitalWrite(segF, HIGH);
    digitalWrite(segG, HIGH);
    delay(75);
    //C
    digitalWrite(segA, HIGH);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, LOW);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, HIGH);
    digitalWrite(segF, HIGH);
    digitalWrite(segG, HIGH);
    delay(75);
    //G
    digitalWrite(segA, HIGH);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, HIGH);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, HIGH);
    digitalWrite(segF, HIGH);
    digitalWrite(segG, LOW);
    delay(75);
  }
  digitalWrite(segG, HIGH);
  delay(200);
}
void acende0()
{
  digitalWrite(segE, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segA, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);  
}
void acende1()
{
  digitalWrite(segE, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segC, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segA, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);  
}
void acende2()
{
  digitalWrite(segE, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segC, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segA, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, LOW);  
}
void acende3()
{
  digitalWrite(segE, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segA, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, LOW);
}
void acende4()
{
  digitalWrite(segE, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segC, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segA, HIGH);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}
void acende5()
{
  digitalWrite(segE, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segA, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}
void acende6()
{
  digitalWrite(segE, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segA, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}
void acende7()
{
  digitalWrite(segE, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segC, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segA, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}
void acende8()
{
  digitalWrite(segE, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segA, LOW); 
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}
void acende9()
{
  digitalWrite(segE, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segA, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}
void iterarNumeros()
{
  acende0();
  delay(140);
  acende1();
  delay(140);
  acende2();
  delay(140);
  acende3();
  delay(140);
  acende4();
  delay(140);
  acende5();
  delay(140);
  acende6();
  delay(140);
  acende7();
  delay(140);
  acende8();
  delay(140);
  acende9();
  delay(140);
}
