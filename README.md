# 🤖 ESP32 IoT Remote Control System

## 🌐 Language / Idioma
- [🇺🇸 English](#english-documentation)
- [🇪🇸 Español](#documentación-en-español)

---

## 🇺🇸 English Documentation

### 📋 Project Description
ESP32-based IoT system integrating DHT22 sensors, OLED display, and communication with ThingSpeak and Telegram for comprehensive remote monitoring and control capabilities.

### 🚀 Features
- 📊 Real-time temperature and humidity monitoring (DHT22 sensor)
- 🔧 Remote LED control via Telegram commands
- 📱 Interactive Telegram bot with custom keyboard
- ☁️ Cloud data logging to ThingSpeak platform
- 🖥️ Local OLED display for real-time information
- 🎛️ Analog potentiometer reading and simulation capabilities
- 🔄 Dual data modes: real sensor data and simulated values

### ⚙️ Initial Setup

#### 1️⃣ Configure API Keys
```bash
# 1. Copy the example configuration file
cp include/config_example.h include/config.h

# 2. Edit config.h with your real credentials
```

#### 2️⃣ ThingSpeak Setup
1. Create account at [ThingSpeak](https://thingspeak.com/)
2. Create a new channel
3. Configure 2 fields:
   - Field 1: Temperature
   - Field 2: Humidity
4. Copy the **Channel ID** and **Write API Key**

#### 3️⃣ Telegram Bot Setup
1. Search for **@BotFather** on Telegram
2. Send `/newbot` and follow instructions
3. Save the **Bot Token**
4. To get your **Chat ID**:
   - Send a message to your bot
   - Visit: `https://api.telegram.org/bot<YOUR_BOT_TOKEN>/getUpdates`
   - Copy the `chat.id` value

### 🔧 Required Hardware
- ESP32 Development Board
- DHT22 (Temperature and humidity sensor)
- SSD1306 OLED Display (128x64)
- 2x LEDs (Green and Blue)
- 1x Potentiometer (10kΩ)
- Resistors and connection wires

### 📱 Bot Commands

| Command | Description |
|---------|-------------|
| `/start` | Initialize bot and display menu |
| `/menu` | Show command keyboard |
| `/dht22` | Read temperature and humidity |
| `/pote` | Read potentiometer value |
| `/led23on/off` | Control Green LED (Pin 23) |
| `/led2on/off` | Control Blue LED (Pin 2) |
| `/platiot` | Send real data to ThingSpeak |
| `/platiotpote` | Send simulated data to ThingSpeak |
| `/displayled` | Show LED status on OLED |
| `/displaypote` | Show voltage on OLED |
| `/displaydht22` | Show sensor data on OLED |

### 🔌 Pin Configuration
```cpp
#define LED_VERDE_PIN 23    // Green LED
#define LED_AZUL_PIN  2     // Blue LED
#define POTE_PIN      36    // Potentiometer (ADC)
#define DHT_PIN       15    // DHT22 sensor
#define OLED_SDA_PIN  21    // I2C SDA
#define OLED_SCL_PIN  22    // I2C SCL
```

### 📁 Project Structure
```
TP2_IoT_UTN/
├── src/
│   └── main.cpp              # Main source code
├── include/
│   ├── config.h              # ⚠️ API Keys (DO NOT upload to Git)
│   └── config_example.h      # Configuration template
├── platformio.ini            # PlatformIO configuration
├── .gitignore               # Git ignored files
├── wokwi.toml               # Wokwi simulator config
├── diagram.json             # Circuit diagram
└── README.md                # This file
```

### 🛠️ Installation and Usage

#### Prerequisites
- [PlatformIO](https://platformio.org/) installed
- VS Code with PlatformIO extension

#### Steps
1. **Clone the repository**
   ```bash
   git clone https://github.com/EliasKarimRaueh/TP2-IoT.git
   cd TP2-IoT
   ```

2. **Configure credentials**
   ```bash
   cp include/config_example.h include/config.h
   # Edit include/config.h with your API keys
   ```

3. **Build and upload**
   ```bash
   pio run --target upload
   ```

4. **Monitor serial output**
   ```bash
   pio device monitor
   ```

### 🔒 Security
- ❌ **NEVER** upload `config.h` to GitHub
- ✅ Only upload `config_example.h` as template
- 🔐 API keys are protected by `.gitignore`

### 🛡️ Technologies Used
- **Platform:** ESP32 DevKit C V4
- **Framework:** Arduino Core for ESP32
- **Build System:** PlatformIO
- **Simulation:** Wokwi Online Simulator
- **Cloud Integration:** ThingSpeak IoT Platform
- **Communication:** Telegram Bot API with HTTPS

### 📝 Technical Notes
- Project configured for **Wokwi-GUEST** WiFi network
- For real hardware, modify WiFi credentials in code
- ThingSpeak rate limit: maximum 1 upload every 15 seconds
- Telegram polling interval: 1 second for real-time response

---

## 🇪🇸 Documentación en Español

### 📋 Descripción del Proyecto
Sistema IoT basado en ESP32 que integra sensores DHT22, display OLED, y comunicación con ThingSpeak y Telegram para monitoreo y control remoto integral.

### 🚀 Características
- 📊 Monitoreo en tiempo real de temperatura y humedad (sensor DHT22)
- 🔧 Control remoto de LEDs vía comandos de Telegram
- 📱 Bot de Telegram interactivo con teclado personalizado
- ☁️ Registro de datos en la nube ThingSpeak
- 🖥️ Display OLED local para información en tiempo real
- 🎛️ Lectura de potenciómetro analógico y capacidades de simulación
- 🔄 Modos duales de datos: datos reales del sensor y valores simulados

### ⚙️ Configuración Inicial

#### 1️⃣ Configurar API Keys
```bash
# 1. Copia el archivo de ejemplo
cp include/config_example.h include/config.h

# 2. Edita config.h con tus credenciales reales
```

#### 2️⃣ Configuración de ThingSpeak
1. Crear cuenta en [ThingSpeak](https://thingspeak.com/)
2. Crear un nuevo canal (Channel)
3. Configurar 2 campos:
   - Campo 1: Temperatura
   - Campo 2: Humedad
4. Copiar el **Channel ID** y **Write API Key**

#### 3️⃣ Configuración del Bot de Telegram
1. Buscar **@BotFather** en Telegram
2. Enviar `/newbot` y seguir instrucciones
3. Guardar el **Bot Token**
4. Para obtener tu **Chat ID**:
   - Envía un mensaje a tu bot
   - Visita: `https://api.telegram.org/bot<TU_BOT_TOKEN>/getUpdates`
   - Copia el valor de `chat.id`

### 🔧 Hardware Requerido
- Placa de Desarrollo ESP32
- DHT22 (Sensor de temperatura y humedad)
- Display OLED SSD1306 (128x64)
- 2x LEDs (Verde y Azul)
- 1x Potenciómetro (10kΩ)
- Resistencias y cables de conexión

### 📱 Comandos del Bot

| Comando | Descripción |
|---------|-------------|
| `/start` | Inicializa el bot y muestra el menú |
| `/menu` | Muestra el teclado de comandos |
| `/dht22` | Lee temperatura y humedad |
| `/pote` | Lee el valor del potenciómetro |
| `/led23on/off` | Controla LED Verde (Pin 23) |
| `/led2on/off` | Controla LED Azul (Pin 2) |
| `/platiot` | Envía datos reales a ThingSpeak |
| `/platiotpote` | Envía datos simulados a ThingSpeak |
| `/displayled` | Muestra estado LEDs en OLED |
| `/displaypote` | Muestra voltaje en OLED |
| `/displaydht22` | Muestra datos del sensor en OLED |

### 🔌 Configuración de Pines
```cpp
#define LED_VERDE_PIN 23    // LED Verde
#define LED_AZUL_PIN  2     // LED Azul
#define POTE_PIN      36    // Potenciómetro (ADC)
#define DHT_PIN       15    // Sensor DHT22
#define OLED_SDA_PIN  21    // I2C SDA
#define OLED_SCL_PIN  22    // I2C SCL
```

### 🛠️ Instalación y Uso

#### Prerequisitos
- [PlatformIO](https://platformio.org/) instalado
- VS Code con extensión PlatformIO

#### Pasos
1. **Clonar el repositorio**
   ```bash
   git clone https://github.com/EliasKarimRaueh/TP2-IoT.git
   cd TP2-IoT
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

### 🔒 Seguridad
- ❌ **NUNCA** subas el archivo `config.h` a GitHub
- ✅ Solo sube `config_example.h` como plantilla
- 🔐 Las API keys están protegidas por `.gitignore`

### 🛡️ Tecnologías Utilizadas
- **Plataforma:** ESP32 DevKit C V4
- **Framework:** Arduino Core para ESP32
- **Sistema de Construcción:** PlatformIO
- **Simulación:** Simulador Online Wokwi
- **Integración en la Nube:** Plataforma IoT ThingSpeak
- **Comunicación:** API de Bot de Telegram con HTTPS

### 📝 Notas Técnicas
- Proyecto configurado para red WiFi **Wokwi-GUEST**
- Para hardware real, modificar credenciales WiFi en el código
- Límite de ThingSpeak: máximo 1 envío cada 15 segundos
- Intervalo de sondeo de Telegram: 1 segundo para respuesta en tiempo real

---
**🎓 Universidad Tecnológica Nacional - Facultad Regional Córdoba**