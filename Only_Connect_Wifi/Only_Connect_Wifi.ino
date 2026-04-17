/*
Este programa configura un ESP32 como un servidor web básico.
Primero se conecta a una red WiFi utilizando las credenciales proporcionadas
y muestra en el monitor serial la dirección IP asignada.

Luego inicia un servidor en el puerto 80 que responde a las solicitudes
del navegador. Cuando un usuario accede a la dirección IP del ESP32,
el dispositivo envía una página HTML simple con un mensaje.

El loop principal se encarga de mantener activo el servidor y
atender continuamente a los clientes conectados.
*/

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = ""; //Nombre del wifi
const char* password = ""; //Clave de wifi

WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<h1>Hola desde ESP32 🚀</h1>");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}