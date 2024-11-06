/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

// Replace the next variables with your SSID/Password combination
const char* ssid = "MiFibra-1BB8";
const char* password = "R7vCrtyV";

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.128";
const char* mqtt_server = "192.168.1.128";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

//uncomment the following lines if you're using SPI
/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/

//Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI
//float temperature = 0;
//float humidity = 0;
float tension = 0;
int analogicOutput = 0;
//int potValor = 0;
int DURACION;
float DISTANCIA;


// LED Pin
const int ledPinStart = 4;
const int ledPinStop = 32;
//const int potPin = 34;
const int DAC = 25;
int TRIG = 14;			// trigger en pin 14
int ECO = 12;			// echo en pin 12
int ledSensor = 15;	


void setup() {
  Serial.begin(115200);
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  //status = bme.begin();  
  //if (!bme.begin(0x76)) {
    //Serial.println("Could not find a valid BME280 sensor, check wiring!");
    //while (1);
  //}
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(ledPinStart, OUTPUT);
  pinMode(ledPinStop, OUTPUT);
  pinMode(TRIG, OUTPUT); 	// trigger como salida
  pinMode(ECO, INPUT);		// echo como entrada
  pinMode(ledSensor, OUTPUT);		// LED como salida
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "esp32/outputStart") {
    Serial.print("Changing output Start to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPinStart, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPinStart, LOW);
    }
  }
    if (String(topic) == "esp32/outputStop") {
    Serial.print("Changing output Stop to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPinStop, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPinStop, LOW);
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/outputStart");
      client.subscribe("esp32/outputStop");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  //potValor = analogRead(potPin);
  
  digitalWrite(TRIG, HIGH); 		// generacion del pulso a enviar
  delay(1);				// al pin conectado al trigger
  digitalWrite(TRIG, LOW);		// del sensor
  
  DURACION = pulseIn(ECO, HIGH);	// con funcion pulseIn se espera un pulso
  					// alto en Echo
  DISTANCIA = DURACION / 58.2;		// distancia medida en centimetros

  analogicOutput=map(DISTANCIA, 75, 5, 0, 255);
  dacWrite(DAC,analogicOutput);
  tension=analogicOutput*0.01196+0.11;



  if (DISTANCIA <= 100 && DISTANCIA >= 0){	// si distancia entre 0 y 80 cms.
    digitalWrite(ledSensor, HIGH);			// enciende LED
    delay(DISTANCIA * 10);			// demora proporcional a la distancia
    digitalWrite(ledSensor, LOW);			// apaga LED
    delay(DISTANCIA * 10);   	// demora proporcional a la distancia
    }
   

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 500) {
    lastMsg = now;
    
    // Temperature in Celsius
    //temperature = bme.readTemperature();   
    // Uncomment the next line to set temperature in Fahrenheit 
    // (and comment the previous temperature line)
    //temperature = 1.8 * bme.readTemperature() + 32; // Temperature in Fahrenheit
    
    // Convert the value to a char array
    //char tempString[8];
    //dtostrf(temperature, 1, 1, tempString);
    //Serial.print("Temperature: ");
    //Serial.println(tempString);
    //client.publish("esp32/temperature", tempString);

    //humidity = bme.readHumidity();
    
    // Convert the value to a char array
    //char humString[8];
    //dtostrf(humidity, 1, 1, humString);
    //Serial.print("Humidity: ");
    //Serial.println(humString);
    //client.publish("esp32/humidity", humString);
 

    char tensionString[8];
    dtostrf(tension, 1, 1, tensionString);
    Serial.print("Tension: ");
    Serial.println(tensionString);
    client.publish("esp32/tension", tensionString);

    char distanciaString[8];
    dtostrf(DISTANCIA, 1, 1, distanciaString);
    Serial.print("Distancia: ");
    Serial.println(DISTANCIA);	
    client.publish("esp32/distancia", distanciaString);

  }

}


