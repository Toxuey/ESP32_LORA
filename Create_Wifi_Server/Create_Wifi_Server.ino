/*
Este programa configura un ESP32 como un servidor web básico que se conecta
a una red WiFi usando las credenciales definidas. Una vez establecida la conexión,
muestra en el monitor serial la dirección IP asignada al dispositivo.

El servidor web se ejecuta en el puerto 80 y responde a las solicitudes en la
ruta principal ("/"). Cuando un usuario accede desde un navegador, el ESP32 envía
una página web completa en formato HTML, incluyendo la estructura básica del
documento y un mensaje de bienvenida.

El loop principal mantiene el servidor en funcionamiento, gestionando
continuamente las solicitudes de los clientes conectados.
*/

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = ""; //Nombre del wifi
const char* password = ""; //Clave de wifi

WebServer server(80);

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>ESP32</title></head><body><h1>Hola desde ESP32 🚀</h1></body></html>";
  server.send(200, "text/html; charset=utf-8", html);
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