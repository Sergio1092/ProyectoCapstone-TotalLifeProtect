/*
   Envio de JSON por MQTT.
   por: Hugo Escalpelo
   Fecha: 15 de noviembre de 2021

   Editado por: Karen Cruz, Sergio Delgadillo, Tania Zárate
   Fecha: 25 de febrero de 2022

   Proyecto Capstone:
   Monitoreo de la calidad del aire utilizando como indicadores la concentración de 
   CO, CO2 y GLP

   Este programa envía datos por Internet a través del protocolo MQTT. Para poder
   comprobar el funcionamiento de este programa, es necesario conectarse a un broker
   y usar Node-Red para visualzar que la información se está recibiendo correctamente.
   Este programa no requiere componentes adicionales.

   Este programa está basado en "Conexión básica por MQTT del NodeMCU" y explica como
   enviar strings que contengan JSON para enviar mas de una variable a la vez.

   Por otra parte, los datos obtenidos de los sensores MQ-2, MQ-7 y MQ-135 son
   analizados de tal manera que, dependiendo del nivel en el que se encuenten,
   son los mensajes que se enviarán a través de un bot de Telegram.
*/

// Bibliotecas
#include <WiFi.h>  // Biblioteca para el control de Wi-Fi
#include <PubSubClient.h> // Biblioteca para conexion MQTT
#include <Wire.h> // Biblioteca para la comunicación con dispositivos I2C/TWI
#include <WiFiClientSecure.h>
#include <Adafruit_ADS1X15.h> // Biblioteca para ADC ADS1115
#include <UniversalTelegramBot.h> // Biblioteca para la conexión con Telegram
#include <ArduinoJson.h> // Biblioteca para generar datos JSON

// Set pin numbers
#define POWER_PIN  12
#define SIGNAL_PIN 13
#define LED_Y 2
#define LED_G 0
#define LED_R 14
#define BUZZER 15

// I2C
#define I2C_SDA 13 // Conectar SDA a GPIO 13
#define I2C_SCL 12 // Conectar SCL a GPIO 12
TwoWire I2CSensor = TwoWire(0); // Definición de puerto Wire

//Datos de WiFi
#define WIFI_SSID "Nombre" // Nombre de la red
#define WIFI_PASSWORD "Contraseña" // Contraseña de la red

// BOT de Telegram (IDBot y BotFather)
String chatId = "1111111111"; // ID de Telegram
#define BOT_TOKEN "1111111111:11111111111111111111111111111111111" // Token del BOT
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

// Variables globales
float volts0, volts1, volts2;
float MQ2, MQ7, MQ135;
unsigned long t = 0;
unsigned long t2 = 10000; // Retardo de tiempo para el envio de mensajes ok
int n = 10;
int dt = 100;
String msg;
// Rango de voltajes para los sensores MQ2, MQ7 y MQ135
float u[3][3] =
{ {0.9, 0.31, 0.36},
  {1.96, 0.43, 0.57},
  {3.0, 3.0, 3.0}
}; 

//Datos del broker MQTT
const char* mqtt_server = "52.28.133.146"; // Colocar la dirección IP de la red local o pública
IPAddress server(52,28,133,146);

// Objetos
WiFiClient espClient; // Este objeto maneja los datos de conexion Wi-Fi
PubSubClient client(espClient); // Este objeto maneja los datos de conexion al broker
Adafruit_ADS1115 ads;  // ADS1115 16-bit version

// Variables
long timeNow, timeLast; // Variables de control de tiempo no bloqueante
int wait = 5000;  // Indica la espera cada 5 segundos para envío de mensajes MQTT

// Inicialización del programa
void setup() {
  // Iniciar comunicación serial
  Serial.begin (115200);
  pinMode (POWER_PIN, OUTPUT);
  digitalWrite (POWER_PIN, HIGH);

  // Configuración de LED's y Buzzer como salida
  pinMode(LED_G, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Configuración de LED's y Buzzer como apagado
  digitalWrite(BUZZER, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_Y, LOW);

  Serial.println();
  Serial.println();
  Serial.print("Conectar a ");
  Serial.println(WIFI_SSID); // Se indica la red a la cual se va a conectar

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // Esta es la función que realiza la conexión a WiFi
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Agregar certificado raíz para api.telegram.org
  while (WiFi.status() != WL_CONNECTED) { // Este bucle espera a que se realice la conexión
    digitalWrite (POWER_PIN, HIGH);
    delay(500); // Dado que es de suma importancia esperar a la conexión, debe usarse espera bloqueante
    digitalWrite (POWER_PIN, LOW);
    Serial.print(".");  // Indicador de progreso
    delay(5);
  }

  // Cuando se haya logrado la conexión, el programa avanzará, por lo tanto, puede informarse lo siguiente
  Serial.println();
  Serial.println("WiFi conectado");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP()); // Muestra la dirección IP

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // Obtener la hora UTC a través de NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  I2CSensor.begin(I2C_SDA, I2C_SCL, 100000);
  if (!ads.begin(0x48, &I2CSensor)) { // Inicialice ADS1115 en la dirección 0x48
    Serial.println("Couldn't Find sensor ADS1115."); // El sensor ADS1115 no fue encontrado
    bot.sendMessage(chatId, "Couldn't Find sensor ADS1115.\n");
    while(1);
  }
  else {
    bot.sendMessage(chatId, "Modulo TLP 1 listo.");
    Serial.println("Sensor ADS1115 Found");
  }

  //Se enciende tanto el buzzer como el led verde para indicar que el módulo se encuentra listo para usarse
  digitalWrite(BUZZER, HIGH);
  delay(1000);
  digitalWrite(BUZZER, LOW);
  digitalWrite(LED_G, HIGH);
  t = millis();

  delay (1000); // Esta espera es solo una formalidad antes de iniciar la comunicación con el broker

  // Conexión con el broker MQTT
  client.setServer(server, 1883); // Conectarse a la IP del broker en el puerto indicado
  delay(1500);  // Esta espera es preventiva, espera a la conexión para no perder información

  timeLast = millis (); // Inicia el control de tiempo
}// fin del void setup ()

// Cuerpo del programa, bucle principal
void loop(void) {
  MQ2 = 0;
  MQ7 = 0;
  MQ135 = 0;
  // Lectura de sensores
  for (int i = 0; i < n; i++) {
    // Los valores obtenidos por los sensores son convertidos en volts 
    MQ2 += ads.computeVolts(ads.readADC_SingleEnded(0)) / n;
    MQ7 += ads.computeVolts(ads.readADC_SingleEnded(1)) / n;
    MQ135 += ads.computeVolts(ads.readADC_SingleEnded(2)) / n;
    delay(dt);
  }
  Serial.print("MQ2: "); Serial.print(MQ2);
  Serial.print(", MQ7: "); Serial.print(MQ7);
  Serial.print(", MQ135: "); Serial.println(MQ135);

  // Si los sensores sobrepasan el último rango, significa que la calidad del aire es mala
  // Si MQ2, MQ7 o MQ135 es mayor a 3.0 
  if (MQ2 > u[2][0] || MQ7 > u[2][1] || MQ135 > u[2][2]) {
    Serial.println("Calidad del aire MALA, posible contaminación por fuga de gas LP.");
    Serial.println("Ventilar de inmediato y verificar fugas de gas.");
    bot.sendMessage(chatId, "Calidad del aire MALA, posible contaminación por fuga de gas LP.");
    bot.sendMessage(chatId, "Ventilar de inmediato y verificar fugas de gas.");
    // Se enciende el led rojo
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_Y, LOW);
    // Se enciende el buzzer, el sonido es largo
    digitalWrite(BUZZER, HIGH);
    delay(2000);
    digitalWrite(BUZZER, LOW);
    delay(1000);
    digitalWrite(BUZZER, HIGH);
    delay(2000);
    digitalWrite(BUZZER, LOW);

  } 
  // Si los sensores sobrepasan el rango medio, significa que la calidad del aire es baja
  // Si MQ2 > 1.96, o MQ7 > 0.43, o MQ135 > 0.57
  else if (MQ2 > u[1][0] || MQ7 > u[1][1] || MQ135 > u[1][2]) {
    Serial.println("Calidad del aire baja, posible contaminación por falta de ventilación.");
    bot.sendMessage(chatId, "Calidad del aire baja, posible contaminación por falta de ventilación.");
    // Se enciende el led amarillo
    digitalWrite(LED_Y, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_R, LOW);
    // Se enciende el buzzer, el sonido es corto
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    digitalWrite(BUZZER, LOW);
    delay(100);
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    digitalWrite(BUZZER, LOW);
  } 
  // Si los sensores sobrepasan el primer rango, significa que la calidad del aire es media
  // Si MQ2 > 0.9, o MQ7 > 0.31, o MQ135 > 0.36
  else if (MQ2 > u[0][0] || MQ7 > u[0][1] || MQ135 > u[0][2]) {
    Serial.println("Calidad del aire media, posible contaminación por humo.");
    bot.sendMessage(chatId, "Calidad del aire media, posible contaminación por humo.");
    // Se enciende el led amarillo
    digitalWrite(LED_Y, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_R, LOW);
    delay(10000);
  } else {
    // Ciclo para que el mensaje de "Calidad del aire buena" no sea muy repetitivo
    if (millis() > t + t2) {
      t = millis();
      bot.sendMessage(chatId, "Calidad del aire buena.");
      Serial.println("Calidad del aire buena.");
    }
    // Se enciende el led verde
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_Y, LOW);
  }
  //Verificar siempre que haya conexión al broker
  if (!client.connected()) {
    reconnect();  // En caso de que no haya conexión, ejecutar la función de reconexión, definida despues del void setup ()
  }
  else{
  client.loop(); // Esta función es muy importante, ejecuta de manera no bloqueante las funciones necesarias para la comunicación con el broker

  timeNow = millis(); // Control de tiempo para esperas no bloqueantes
  if (timeNow - timeLast > wait) { // Manda un mensaje por MQTT cada cinco segundos
    timeLast = timeNow; // Actualización de seguimiento de tiempo

    //Se construye el string correspondiente al JSON que contiene 4 variables
    String json = "{\"id\":\"Karen\",\"mq2\":" + String(MQ2) + ",\"mq7\":" + String(MQ7) + ",\"mq135\":" + String(MQ135) + "}";
    Serial.println(json); // Se imprime en monitor solo para poder visualizar que el string esta correctamente creado
    int str_len = json.length() + 1; // Se calcula la longitud del string
    char char_array[str_len]; // Se crea un arreglo de caracteres de dicha longitud
    json.toCharArray(char_array, str_len); // Se convierte el string a char array
    client.publish("pCapstone/detector", char_array); // Esta es la función que envía los datos por MQTT, especifica el tema y el valor
  }// fin del if (timeNow - timeLast > wait)
  }
}// fin del void loop ()

// Función para reconectarse
void reconnect() {
    Serial.print("Tratando de contectarse...");
    // Intentar reconexión
    if (client.connect("pCapstoneClient")) { //Pregunta por el resultado del intento de conexión
      Serial.println("Conectado");
      client.subscribe("pCapstone/output"); // Esta función realiza la suscripción al tema
    }// fin del  if (client.connect("pCapstoneClient"))
    else {  //en caso de que la conexión no se logre
      Serial.print("Conexion fallida, Error rc=");
      Serial.print(client.state()); // Muestra el codigo de error
      Serial.println (client.connected ()); // Muestra estatus de conexión
    }// fin del else
}// fin de void reconnect()
