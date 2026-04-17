//Mini Protoboard Receptor

/*
Este programa configura un ESP32 como receptor LoRa con monitoreo avanzado
a través de Bluetooth. Utiliza un módulo SX1262 para recibir mensajes en la
frecuencia de 433 MHz y la librería BluetoothSerial para enviar información
en tiempo real a un celular u otro dispositivo.

Cuando el ESP32 recibe un mensaje, guarda el tiempo de recepción, obtiene la
intensidad de la señal (RSSI) y enciende un LED como indicador. Si pasa más de
5 segundos sin recibir datos, se considera que la conexión se perdió y el LED
se apaga.

Además, el sistema evalúa la calidad de la señal según el RSSI (excelente,
buena, débil o muy mala) y envía continuamente por Bluetooth el estado de la
conexión, el tiempo desde el último mensaje recibido y la calidad de la señal.

De esta forma, el ESP32 funciona como un monitor inalámbrico LoRa, permitiendo
visualizar en tiempo real la estabilidad y calidad de la comunicación desde
un dispositivo móvil.
*/

#include <RadioLib.h>
#include "BluetoothSerial.h"

SX1262 radio = new Module(5, 26, 14, 25);
BluetoothSerial SerialBT;

#define LED 2

unsigned long ultimoMensaje = 0;
const unsigned long TIMEOUT = 5000;

int ultimoRSSI = 0;

String calidadSenal(int rssi) {
  if (rssi >= -60) return "EXCELENTE 🟢";
  else if (rssi >= -80) return "BUENA 🟡";
  else if (rssi >= -95) return "DEBIL 🟠";
  else return "MUY MALA / PERDIDA 🔴";
}

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ReceptorLoRa");

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  if (radio.begin(433.0) != RADIOLIB_ERR_NONE) {
    Serial.println("Error LoRa");
    while (true)
      ;
  }

  Serial.println("Receptor listo");
  SerialBT.println("=== MONITOR LoRa INICIADO ===");
}

void loop() {
  String mensaje;
  int state = radio.receive(mensaje);

  // 📥 Mensaje recibido
  if (state == RADIOLIB_ERR_NONE) {
    ultimoMensaje = millis();
    ultimoRSSI = radio.getRSSI();  // 🔥 clave
    digitalWrite(LED, HIGH);
  }

  unsigned long tiempoSinMensaje = millis() - ultimoMensaje;
  float segundos = tiempoSinMensaje / 1000.0;

  // 🔴 Estado conexión
  bool conexion = tiempoSinMensaje < TIMEOUT;

  // LED
  digitalWrite(LED, conexion ? HIGH : LOW);

  // 📡 Enviar info al celular
  SerialBT.print("Estado: ");
  SerialBT.println(conexion ? "OK" : "SIN SENAL ⚠️");

  SerialBT.print("Ultimo mensaje hace: ");
  SerialBT.print(segundos);
  SerialBT.println(" s");

  SerialBT.print("RSSI: ");
  SerialBT.print(ultimoRSSI);
  SerialBT.print(" dBm | Calidad: ");
  SerialBT.println(calidadSenal(ultimoRSSI));

  SerialBT.println("----------------------");

  delay(1000);  // cada segundo
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