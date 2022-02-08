#include <Wire.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <Adafruit_ADS1X15.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

Adafruit_ADS1115 ads;  // ADS1115 16-bit version

// Global variables
float volts0, volts1, volts2;

// Set pin numbers
#define LED_Y 2
#define LED_G 0
#define LED_R 14
#define BUZZER 15

// -----------------I2C-----------------
#define I2C_SDA 13 // SDA Connected to GPIO 13
#define I2C_SCL 12 // SCL Connected to GPIO 12
TwoWire I2CSensor = TwoWire(0);

// Wifi network station credentials
#define WIFI_SSID "xxxxxxx"
#define WIFI_PASSWORD "xxxxxxxx"

// Telegram BOT Token (Get from Botfather)
String chatId = "xxxxxx";
#define BOT_TOKEN "xxxxxxxxxxx:xxxxxxxxxxxxxxxxxxxxxx"
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

void setup() {
  pinMode(LED_G, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_Y, LOW);
  
  Serial.begin(115200);

  I2CSensor.begin(I2C_SDA, I2C_SCL, 100000);
  // ADS1115 (0x48 will be the address)
  if (!ads.begin(0x48, &I2CSensor)) { // Initialize ADS1115 at address 0x48
    Serial.println("Couldn't Find sensor");
    while (1);
  }
  else {
    Serial.println("Sensor Found");
    Serial.println("Getting single-ended readings from AIN0..3");
    Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV)");
  }

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  Serial.print("Local IP 'http://");
  Serial.print(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  digitalWrite(LED_G, HIGH);
  delay(1000);
  digitalWrite(LED_Y, HIGH);
  delay(1000);
  digitalWrite(LED_R, HIGH);
  delay(1000);
  digitalWrite(LED_G, LOW);
  delay(1000);
  digitalWrite(LED_Y, LOW);
  delay(1000);
  digitalWrite(LED_R, LOW);

  digitalWrite(BUZZER, HIGH);
  delay(1000);
  digitalWrite(BUZZER, LOW);
  delay(1000);
  digitalWrite(BUZZER, HIGH);
  delay(1000);
  digitalWrite(BUZZER, LOW);
  delay(1000);
  digitalWrite(BUZZER, HIGH);
  delay(1000);
  digitalWrite(BUZZER, LOW);
  digitalWrite(LED_G, HIGH);
}

void loop(void) {
  volts0 = ads.computeVolts(ads.readADC_SingleEnded(0));
  volts1 = ads.computeVolts(ads.readADC_SingleEnded(1));
  volts2 = ads.computeVolts(ads.readADC_SingleEnded(2));

  Serial.println("-----------------------------------------------------------");
  Serial.print("AIN0: "); Serial.print(volts0); Serial.println("V");
  Serial.print("AIN1: "); Serial.print(volts1); Serial.println("V");
  Serial.print("AIN2: "); Serial.print(volts2); Serial.println("V");

  String msg = "MQ2= " + String(volts0) + "v.";
  msg += "MQ7= " + String(volts1) + "v.";
  msg += "MQ135= " + String(volts2) + "v.\n";
  bot.sendMessage(chatId, msg);

  delay(1000);
}
