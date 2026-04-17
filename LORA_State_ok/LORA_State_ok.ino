//Mini Protoboard receptor

/*
Este programa inicializa un ESP32 con un módulo LoRa SX1262 utilizando la
librería RadioLib. En el setup, se establece la comunicación serial y se
intenta iniciar el módulo de radio en la frecuencia de 433 MHz.

Si la inicialización es exitosa, se muestra el mensaje "LoRa OK" en el
monitor serial. En caso contrario, se imprime el código de error correspondiente
para facilitar el diagnóstico.

El loop permanece vacío, ya que este código solo tiene como objetivo verificar
si el módulo LoRa está funcionando correctamente.
*/

#include <RadioLib.h>

SX1262 radio = new Module(5, 26, 14, 25);

void setup() {
  Serial.begin(115200);

  int state = radio.begin(433.0);

  if (state == RADIOLIB_ERR_NONE) {
    Serial.println("LoRa OK");
  } else {
    Serial.print("Error: ");
    Serial.println(state);
  }
}

void loop() {}

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
NRST → GPIO14
BUSY → GPIO25
DIO1 → GPIO26

4. Pines RF (déjalos simple por ahora)
RXEN → GND
TXEN → GND

Instalar libreria
RadioLib
RadioLib by Jan Gromes

*/