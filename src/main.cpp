#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include "ThingSpeak.h"
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include "config.h"  // Archivo con las API keys (no se sube a GitHub)

// --- DEFINICIÓN DE PINES ---
#define LED_VERDE_PIN 23
#define LED_AZUL_PIN  2
#define POTE_PIN      36
#define DHT_PIN       15
#define DHT_TYPE      DHT22
#define OLED_SDA_PIN  21
#define OLED_SCL_PIN  22

// --- DEFINICIONES DE PANTALLA (CORREGIDO PARA AHORRAR MEMORIA) ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// --- OBJETOS ---
DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
WiFiClient client;              // HTTP p/ ThingSpeak
WiFiClientSecure secureClient;  // HTTPS p/ Telegram
UniversalTelegramBot bot(BOT_TOKEN, secureClient);

// --- VARIABLES GLOBALES DE ESTADO ---
bool  estadoLedVerde = false;
bool  estadoLedAzul  = false;
float estadoVoltaje  = 0.0;
float estadoTemp     = 0.0;
float estadoHum      = 0.0;

// --- VARIABLES GLOBALES DE TELEGRAM ---
unsigned long botLastTime;
const int botRequestDelay = 1000;

// --- Función para limpiar y escribir en el display ---
void printDisplay(String l1, String l2 = "", String l3 = "", String l4 = "") {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(l1);
  display.println(l2);
  display.println(l3);
  display.println(l4);
  display.display();
}

// ===========================
//  NUEVO: Reply Keyboard
// ===========================
// Envia un teclado persistente con tus comandos.
// Al tocar un botón, Telegram envía ese texto tal cual.
void sendMainMenuReplyKB(const String& chatId) {
  // Cada sub-array es una fila de botones
  String kb =
    "["
      "[\"/dht22\",\"/pote\"],"
      "[\"/led2on\",\"/led2off\"],"
      "[\"/led23on\",\"/led23off\"],"
      "[\"/platiot\",\"/platiotpote\"],"
      "[\"/displayled\",\"/displaypote\",\"/displaydht22\"]"
    "]";

  // resize_keyboard = true, one_time_keyboard = false
  bot.sendMessageWithReplyKeyboard(
    chatId,
    "Elegí una acción tocando un botón:",
    "",
    kb,
    true,   // resize
    false   // one_time
  );
}

// ==========================================
//   MANEJO DE MENSAJES DE TELEGRAM
// ==========================================
void handleNewMessages(int numNewMessages) {
  Serial.print("Manejando "); Serial.print(numNewMessages); Serial.println(" mensajes nuevos");

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id   = String(bot.messages[i].chat_id);
    String text      = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;

    Serial.println("Recibido: " + text + " de " + from_name);

    // --- Punto 1: /start (Actualizado para mostrar teclado) ---
    if (text == "/start") {
      String welcome = "¡Bienvenido, " + from_name + "!\n";
      welcome += "Soy el bot de tu proyecto de IoT (UTN 4k01).\n\n";
      welcome += "/led<pin><on/off> - (Ej: /led23on)\n";
      welcome += "/dht22 - Muestra temperatura y humedad\n";
      welcome += "/pote - Muestra el voltaje del potenciómetro\n";
      welcome += "/platiot - Sube datos a la nube\n";
      welcome += "/display<info> - (Ej: /displayled)\n";
      bot.sendMessage(chat_id, welcome, "");
      sendMainMenuReplyKB(chat_id);   // muestra los botones en el chat
    }

    //  /menu para re-mostrar el teclado 
    else if (text == "/menu") {
      sendMainMenuReplyKB(chat_id);
    }

    // --- Punto 2: /led... ---
    else if (text == "/led23on") {
      digitalWrite(LED_VERDE_PIN, HIGH);
      estadoLedVerde = true;
      bot.sendMessage(chat_id, "OK. LED Verde ENCENDIDO", "");
    }
    else if (text == "/led23off") {
      digitalWrite(LED_VERDE_PIN, LOW);
      estadoLedVerde = false;
      bot.sendMessage(chat_id, "OK. LED Verde APAGADO", "");
    }
    else if (text == "/led2on") {
      digitalWrite(LED_AZUL_PIN, HIGH);
      estadoLedAzul = true;
      bot.sendMessage(chat_id, "OK. LED Azul ENCENDIDO", "");
    }
    else if (text == "/led2off") {
      digitalWrite(LED_AZUL_PIN, LOW);
      estadoLedAzul = false;
      bot.sendMessage(chat_id, "OK. LED Azul APAGADO", "");
    }

    // --- Punto 4: /pote ---
    else if (text == "/pote") {
      int valorADC = analogRead(POTE_PIN);
      estadoVoltaje = (valorADC / 4095.0) * 3.3;
      String msg = "Valor del Potenciometro: " + String(estadoVoltaje) + " V";
      bot.sendMessage(chat_id, msg, "");
    }

    // --- Punto 3: /dht22 ---
    else if (text == "/dht22") {
      estadoHum = dht.readHumidity();
      estadoTemp = dht.readTemperature();
      if (isnan(estadoHum) || isnan(estadoTemp)) {
        bot.sendMessage(chat_id, "Error al leer el sensor DHT22", "");
      } else {
        String msg = "Humedad: " + String(estadoHum) + "%\n";
        msg += "Temperatura: " + String(estadoTemp) + " *C";
        bot.sendMessage(chat_id, msg, "");
      }
    }

    // --- Punto 6: /display... ---
    else if (text == "/displayled") {
      bot.sendMessage(chat_id, "Mostrando estado de LEDs en OLED...", "");
      String ledV = "Verde: " + String(estadoLedVerde ? "ON" : "OFF");
      String ledA = "Azul:  " + String(estadoLedAzul ? "ON" : "OFF");
      printDisplay("--- ESTADO LEDs ---", ledV, ledA);
    }
    else if (text == "/displaypote") {
      bot.sendMessage(chat_id, "Mostrando estado de Pote en OLED...", "");
      printDisplay("--- ESTADO POTE ---", "Voltaje:", String(estadoVoltaje) + " V");
    }
    else if (text == "/displaydht22") {
      bot.sendMessage(chat_id, "Mostrando estado de DHT en OLED...", "");
      printDisplay("--- ESTADO DHT22 ---",
                   "Temp: " + String(estadoTemp) + " C",
                   "Hum:  " + String(estadoHum) + " %");
    }
    else if (text.startsWith("/display")) {
      bot.sendMessage(chat_id, "Comando display no reconocido.", "");
      printDisplay("--- ERROR ---", "Comando display", "no reconocido.");
    }

    // --- Punto 5: /platiot ---
    else if (text == "/platiot") {
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      if (isnan(h) || isnan(t)) {
        bot.sendMessage(chat_id, "Error al leer DHT. No se puede enviar.", "");
        printDisplay("ERROR DHT", "No se puede enviar");
      } else {
        estadoHum = h;
        estadoTemp = t;

        bot.sendMessage(chat_id, "Enviando datos a ThingSpeak...", "");
        printDisplay("Enviando datos", "a ThingSpeak...");

        ThingSpeak.setField(1, estadoTemp);
        ThingSpeak.setField(2, estadoHum);
        int httpCode = ThingSpeak.writeFields(TS_CHANNEL_ID, TS_WRITE_API_KEY);

        if (httpCode == 200) {
          bot.sendMessage(chat_id, "Datos enviados a ThingSpeak exitosamente.", "");
          printDisplay("Datos enviados!", "OK");
        } else {
          bot.sendMessage(chat_id, "Error al enviar a ThingSpeak. Codigo: " + String(httpCode), "");
          printDisplay("Error ThingSpeak", "Codigo:", String(httpCode));
        }
      }
    }

    // --- NUEVO: /platiotpote - Envía potenciómetro como temperatura simulada ---
    else if (text == "/platiotpote") {
      int valorADC = analogRead(POTE_PIN);
      estadoVoltaje = (valorADC / 4095.0) * 3.3;
      
      // Convertir voltaje a rango de temperatura (15°C a 35°C)
      float tempSimulada = 15.0 + (estadoVoltaje / 3.3) * 20.0;  // 15-35°C
      float humSimulada = 30.0 + (estadoVoltaje / 3.3) * 40.0;   // 30-70%

      bot.sendMessage(chat_id, "Enviando datos simulados a ThingSpeak...", "");
      String msg = "Pote: " + String(estadoVoltaje) + "V -> Temp: " + String(tempSimulada) + "°C";
      bot.sendMessage(chat_id, msg, "");
      
      printDisplay("Enviando simulacion", "Temp: " + String(tempSimulada), "Hum: " + String(humSimulada));

      ThingSpeak.setField(1, tempSimulada);
      ThingSpeak.setField(2, humSimulada);
      int httpCode = ThingSpeak.writeFields(TS_CHANNEL_ID, TS_WRITE_API_KEY);

      if (httpCode == 200) {
        bot.sendMessage(chat_id, "Datos simulados enviados exitosamente!", "");
        printDisplay("Simulacion OK!", "Temp: " + String(tempSimulada));
      } else {
        bot.sendMessage(chat_id, "Error al enviar simulacion. Codigo: " + String(httpCode), "");
        printDisplay("Error simulacion", "Codigo:", String(httpCode));
      }
    }

    // --- COMANDO NO RECONOCIDO ---
    else {
      bot.sendMessage(chat_id, "Comando no reconocido. Usa /start o /menu para ver los botones.", "");
    }
  }
}

// ==========================================
//             SETUP
// ==========================================
void setup() {
  Serial.begin(115200);
  Serial.println("\n--- TP02 Grupo09  ---");

  // --- Inicializar Hardware ---
  pinMode(LED_VERDE_PIN, OUTPUT);
  pinMode(LED_AZUL_PIN, OUTPUT);
  dht.begin();

  // --- Inicializar Pantalla OLED ---
  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Fallo al iniciar SSD1306"));
  } else {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    Serial.println("Display OLED OK.");
    printDisplay("Display OK", "Conectando WiFi...");
    display.display();
  }

  // --- Conectar a WiFi (Wokwi-GUEST) ---
  Serial.print("Conectando a WiFi (Wokwi-GUEST)...");
  secureClient.setCACert(TELEGRAM_CERTIFICATE_ROOT); // requiere el certificado raíz
  WiFi.begin("Wokwi-GUEST", "");

  unsigned long startAttemptTime = millis();
  const int timeout = 15000;

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeout) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFALLO LA CONEXION WIFI");
    printDisplay("ERROR", "Fallo WiFi");
    while (true);
  }

  Serial.println("\nWiFi conectado!");
  printDisplay("WiFi Conectado!", "IP:", String(WiFi.localIP().toString()));
  delay(1000);

  // --- Inicializar ThingSpeak y Telegram ---
  ThingSpeak.begin(client);
  printDisplay("Conectado!", "Bot en linea.");

  // Saludo por Telegram + (opcional) mostrar teclado desde el arranque
  bot.sendMessage(CHAT_ID, "¡Hola! El ESP32 (Wokwi) se ha reiniciado y está en línea.", "");
  sendMainMenuReplyKB(CHAT_ID); // opcional mostrar teclado al iniciar
  Serial.println("Bot de Telegram en linea.");
}

// ==========================================
//             LOOP
// ==========================================
void loop() {
  if (millis() > botLastTime + botRequestDelay) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    botLastTime = millis();
  }
}
