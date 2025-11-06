#ifndef CONFIG_EXAMPLE_H
#define CONFIG_EXAMPLE_H

// ==============================================
//       CONFIGURACIÓN DE API KEYS - EJEMPLO
// ==============================================
// 📋 INSTRUCCIONES PARA CONFIGURAR EL PROYECTO:
// 
// 1. Copia este archivo y renómbralo a "config.h"
// 2. Reemplaza los valores de ejemplo con tus credenciales reales
// 3. NO subas el archivo "config.h" a GitHub (está en .gitignore)
// 
// ==============================================

// --- CONFIGURACIÓN DE THINGSPEAK ---
// 📍 Obtén estos valores en: https://thingspeak.com/
// 1. Crea una cuenta en ThingSpeak
// 2. Crea un nuevo canal (Channel)
// 3. Ve a la pestaña "API Keys"
#define TS_CHANNEL_ID 1234567                    // 🔄 Reemplaza con tu Channel ID
#define TS_WRITE_API_KEY "TU_WRITE_API_KEY_AQUI" // 🔄 Reemplaza con tu Write API Key

// --- CONFIGURACIÓN DE TELEGRAM ---
// 📍 Obtén estos valores de BotFather en Telegram:
// 1. Busca @BotFather en Telegram
// 2. Envía /newbot y sigue las instrucciones
// 3. Guarda el token que te proporcione
// 4. Para obtener tu CHAT_ID, envía un mensaje a tu bot y usa:
//    https://api.telegram.org/bot<TU_BOT_TOKEN>/getUpdates
#define BOT_TOKEN "123456789:ABCDEFGHIJKLMNOPQRSTUVWXYZ"  // 🔄 Reemplaza con tu Bot Token
#define CHAT_ID "123456789"                               // 🔄 Reemplaza con tu Chat ID

// ==============================================
//                    NOTAS
// ==============================================
// 🔒 IMPORTANTE: Nunca compartas estas credenciales públicamente
// 📁 El archivo config.h está excluido del repositorio via .gitignore
// 🔧 Si necesitas regenerar las keys, hazlo desde las plataformas oficiales
// ==============================================

#endif // CONFIG_EXAMPLE_H