//Big Protobar transmisor

/*
Este programa configura un ESP32 como un transmisor LoRa básico utilizando
un módulo SX1262 y la librería RadioLib. En la función setup se inicializa
la comunicación con el módulo en la frecuencia de 433 MHz. Si ocurre algún
error durante la inicialización, el programa se detiene.

En el loop principal, el ESP32 envía de forma continua el mensaje "ping"
cada 2 segundos mediante comunicación LoRa, sin mostrar información en el
monitor serial. Este código es útil para pruebas simples de transmisión
periódica entre dispositivos.
*/

#include <RadioLib.h>

SX1262 radio = new Module(5, 22, 4, 21);

void setup() {
  Serial.begin(115200);

  if (radio.begin(433.0) != RADIOLIB_ERR_NONE) {
    while (true);
  }
}

void loop() {
  radio.transmit("ping");
  delay(2000);
}

/*

1. Alimentación (primero siempre)
VCC → 3.3V del ESP32
GND → GND del ESP32

2. SPI (la base de todo)
SCK → GPIO18
MOSI → GPIO23
MISO → GPIO19
NSS → GPIO5

3. Control del módulo
NRST → GPIO4
BUSY → GPIO21
DIO1 → GPIO22

4. Pines RF (déjalos simple por ahora)
RXEN → GND
TXEN → GND

Instalar libreria
RadioLib
RadioLib by Jan Gromes

*/