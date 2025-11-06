# 🤖 TP2 IoT UTN

## 📋 Descripción del Proyecto
Sistema IoT basado en ESP32 que integra sensores DHT22, display OLED, y comunicación con ThingSpeak y Telegram para monitoreo remoto.

## 🚀 Características
- 📊 Lectura de temperatura y humedad (DHT22)
- 🔧 Control de LEDs remotamente
- 📱 Bot de Telegram con teclado interactivo
- ☁️ Envío de datos a ThingSpeak
- 🖥️ Display OLED para información local
- 🎛️ Lectura de potenciómetro

## ⚙️ Configuración Inicial

### 1️⃣ Configurar API Keys
```bash
# 1. Copia el archivo de ejemplo
cp include/config_example.h include/config.h

# 2. Edita el archivo config.h con tus credenciales reales
```

### 2️⃣ ThingSpeak Setup
1. Crear cuenta en [ThingSpeak](https://thingspeak.com/)
2. Crear un nuevo canal (Channel)
3. Configurar 2 campos:
   - Field 1: Temperatura
   - Field 2: Humedad
4. Copiar el **Channel ID** y **Write API Key**

### 3️⃣ Telegram Bot Setup
1. Buscar **@BotFather** en Telegram
2. Enviar `/newbot` y seguir instrucciones
3. Guardar el **Bot Token**
4. Para obtener tu **Chat ID**:
   - Envía un mensaje a tu bot
   - Visita: `https://api.telegram.org/bot<TU_BOT_TOKEN>/getUpdates`
   - Copia el valor de `chat.id`

## 🔧 Hardware Required
- ESP32 Development Board
- DHT22 (Sensor de temperatura y humedad)
- Display OLED SSD1306 (128x64)
- 2x LEDs (Verde y Azul)
- 1x Potenciómetro
- Resistencias y cables de conexión

## 📱 Comandos del Bot

| Comando | Descripción |
|---------|-------------|
| `/start` | Inicia el bot y muestra el menú |
| `/menu` | Muestra el teclado de comandos |
| `/dht22` | Lee temperatura y humedad |
| `/pote` | Lee el valor del potenciómetro |
| `/led23on/off` | Controla LED Verde (Pin 23) |
| `/led2on/off` | Controla LED Azul (Pin 2) |
| `/platiot` | Envía datos a ThingSpeak |
| `/displayled` | Muestra estado LEDs en OLED |
| `/displaypote` | Muestra voltaje en OLED |
| `/displaydht22` | Muestra sensor data en OLED |

## 🔌 Pinout
```cpp
#define LED_VERDE_PIN 23
#define LED_AZUL_PIN  2
#define POTE_PIN      36
#define DHT_PIN       15
#define OLED_SDA_PIN  21
#define OLED_SCL_PIN  22
```

## 📁 Estructura del Proyecto
```
TP2_IoT_UTN/
├── src/
│   └── main.cpp              # Código principal
├── include/
│   ├── config.h              # ⚠️ API Keys (NO subir a Git)
│   └── config_example.h      # Plantilla de configuración
├── platformio.ini            # Configuración PlatformIO
├── .gitignore               # Archivos ignorados por Git
└── README.md                # Este archivo
```

## 🛠️ Instalación y Uso

### Prerequisitos
- [PlatformIO](https://platformio.org/) instalado
- VS Code con extensión PlatformIO

### Pasos
1. **Clonar el repositorio**
   ```bash
   git clone <tu-repositorio>
   cd TP2_IoT_UTN
   ```

2. **Configurar credenciales**
   ```bash
   cp include/config_example.h include/config.h
   # Editar include/config.h con tus API keys
   ```

3. **Compilar y subir**
   ```bash
   pio run --target upload
   ```

4. **Monitor serie**
   ```bash
   pio device monitor
   ```

## 🔒 Seguridad
- ❌ **NUNCA** subas el archivo `config.h` a GitHub
- ✅ Solo sube `config_example.h` como plantilla
- 🔐 Las API keys están protegidas por `.gitignore`

## Tecnologias
- Integración de servicios en la nube
- Control remoto via Telegram

## 📝 Notas
- El proyecto está configurado para **Wokwi-GUEST** WiFi
- Para uso real, modificar credenciales WiFi en el código
- ThingSpeak permite máximo 1 envío cada 15 segundos

---
**🎓 Universidad Tecnológica Nacional - Facultad Regional Cordoba**