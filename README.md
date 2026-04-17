# ESP32 LoRa + WiFi + Bluetooth Projects

Este repositorio contiene una colección de ejemplos y pruebas utilizando ESP32 con diferentes tecnologías de comunicación como LoRa, WiFi y Bluetooth. Los códigos están diseñados para aprender, probar y desarrollar sistemas de comunicación inalámbrica básicos y avanzados.

---

## Contenido del repositorio

### Servidor Web con ESP32 (WiFi)

* Conexión a red WiFi
* Creación de servidor web en el puerto 80
* Envío de páginas HTML simples al navegador
* Uso como interfaz web básica

---

### Comunicación LoRa (SX1262)

Incluye varios ejemplos:

Receptor básico:

* Recepción de mensajes LoRa
* Visualización en monitor serial

Receptor con LED:

* Indicación visual de recepción
* Apagado automático si se pierde señal

Receptor con monitoreo avanzado:

* Envío de datos por Bluetooth
* Medición de RSSI (calidad de señal)
* Estado de conexión en tiempo real

Transmisor básico:

* Envío de mensajes periódicos
* Verificación de transmisión

Transmisor simple:

* Envío continuo de mensajes de prueba

---

### Bluetooth (ESP32)

* Comunicación con dispositivos móviles
* Envío de datos en tiempo real

---

## Tecnologías utilizadas

* ESP32
* LoRa SX1262
* WiFi
* Bluetooth Serial
* Librería RadioLib

---

## Requisitos

* Placa ESP32
* Módulo LoRa SX1262
* Arduino IDE o PlatformIO
* Librerías:

  * RadioLib
  * WiFi
  * WebServer
  * BluetoothSerial

---

## Conexiones (ejemplo SX1262)

Los pines pueden variar según el código:

| Función | Pin ESP32 |
| ------- | --------- |
| NSS     | 5         |
| DIO1    | 26 / 22   |
| NRST    | 14 / 4    |
| BUSY    | 25 / 21   |

---

## Uso

1. Cargar el código en el ESP32
2. Abrir el monitor serial (115200 baudios)

Para WiFi:

* Conectarse a la misma red
* Abrir la IP del ESP32 en el navegador

Para LoRa:

* Utilizar un transmisor y receptor compatibles

Para Bluetooth:

* Conectarse desde el celular al dispositivo ESP32

---

## Notas importantes

* No subir credenciales reales de WiFi a repositorios públicos
* Ajustar los pines según el hardware utilizado
* Verificar la frecuencia LoRa permitida en cada país

---

## Propósito

Este repositorio está orientado a:

* Aprendizaje de IoT
* Pruebas de comunicación inalámbrica
* Desarrollo de sistemas embebidos

---

## Autor

Proyecto desarrollado con fines educativos y de experimentación.

---

## Contribuciones

Las contribuciones son bienvenidas. Se pueden mejorar los ejemplos, agregar funcionalidades o ampliar la documentación.
