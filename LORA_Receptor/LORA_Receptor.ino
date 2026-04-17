//Miniprotoboards Receptor

/*
Este programa configura un ESP32 como receptor LoRa utilizando un módulo SX1262
a través de la librería RadioLib. En el setup, se inicializa la comunicación
serial y se configura el módulo de radio en la frecuencia de 433 MHz. Si ocurre
algún error durante la inicialización, se muestra en el monitor serial y el
programa se detiene.

Una vez listo, el dispositivo entra en un ciclo continuo donde intenta recibir
mensajes inalámbricos. Cuando se recibe un mensaje correctamente, este se muestra
en el monitor serial. Si ocurre un error distinto a un tiempo de espera, también
se reporta. De esta forma, el ESP32 funciona como un receptor LoRa básico.
*/

#include <RadioLib.h>

SX1262 radio = new Module(5, 26, 14, 25);

void setup() {
  Serial.begin(115200);

  int state = radio.begin(433.0);

  if (state != RADIOLIB_ERR_NONE) {
    Serial.print("Error al iniciar LoRa: ");
    Serial.println(state);
    while (true);
  }

  Serial.println("Receptor listo");
}

void loop() {
  String mensaje;

  int state = radio.receive(mensaje);

  if (state == RADIOLIB_ERR_NONE) {
    Serial.print("Recibido: ");
    Serial.println(mensaje);
  } else if (state != RADIOLIB_ERR_RX_TIMEOUT) {
    Serial.print("Error al recibir: ");
    Serial.println(state);
  }
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