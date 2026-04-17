//Big Protobar transmisor

/*
Este programa configura un ESP32 como transmisor LoRa utilizando un módulo
SX1262 con la librería RadioLib. En la función setup se inicializa la
comunicación serial y se intenta iniciar el módulo de radio en la frecuencia
de 433 MHz. Si ocurre un error durante esta configuración, se muestra en el
monitor serial y el programa se detiene.

Una vez inicializado correctamente, el ESP32 entra en un ciclo continuo donde
envía un mensaje de texto ("Hola desde ESP32 A") cada 2 segundos mediante LoRa.
Después de cada transmisión, se verifica si el envío fue exitoso y se muestra
el resultado en el monitor serial, o en caso de error, se imprime el código
correspondiente.

De esta manera, el ESP32 funciona como un transmisor LoRa básico que envía
mensajes periódicamente para pruebas de comunicación.
*/

#include <RadioLib.h>

SX1262 radio = new Module(5, 22, 4, 21);

void setup() {
  Serial.begin(115200);

  int state = radio.begin(433.0);

  if (state != RADIOLIB_ERR_NONE) {
    Serial.print("Error al iniciar LoRa: ");
    Serial.println(state);
    while (true);
  }

  Serial.println("Transmisor listo");
}

void loop() {
  int state = radio.transmit("Hola desde ESP32 A");

  if (state == RADIOLIB_ERR_NONE) {
    Serial.println("Mensaje enviado");
  } else {
    Serial.print("Error al enviar: ");
    Serial.println(state);
  }

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