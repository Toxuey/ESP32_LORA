//Miniprotoboards Receptor

/*
Este programa configura un ESP32 como receptor LoRa usando un módulo SX1262
y además controla un LED como indicador de recepción. Durante la inicialización,
se configura la comunicación serial, el pin del LED como salida y el módulo
de radio en la frecuencia de 433 MHz. Si ocurre un error al iniciar LoRa,
el programa se detiene.

En el loop principal, el ESP32 intenta recibir mensajes de forma continua.
Cuando se recibe un mensaje correctamente, se registra el tiempo en que llegó
y se enciende el LED. Si pasa un tiempo determinado (5 segundos) sin recibir
ningún mensaje, el LED se apaga automáticamente.

De esta forma, el LED actúa como indicador visual del estado de comunicación:
encendido cuando hay recepción reciente y apagado cuando no hay señal.
*/

#include <RadioLib.h>

SX1262 radio = new Module(5, 26, 14, 25);

#define LED 2

unsigned long ultimoMensaje = 0;
const unsigned long TIMEOUT = 5000; // 5 segundos

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  if (radio.begin(433.0) != RADIOLIB_ERR_NONE) {
    Serial.println("Error LoRa");
    while (true);
  }

  Serial.println("Receptor listo");
}

void loop() {
  String mensaje;

  int state = radio.receive(mensaje);

  // Si recibe mensaje
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println("Mensaje recibido");

    ultimoMensaje = millis();   // guarda tiempo
    digitalWrite(LED, HIGH);    // LED encendido
  }

  // Si pasa mucho tiempo sin mensajes
  if (millis() - ultimoMensaje > TIMEOUT) {
    digitalWrite(LED, LOW);     // LED apagado
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