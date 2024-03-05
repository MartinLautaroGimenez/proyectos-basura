#include <ESP8266WiFi.h>

// Configuración de la red WiFi
const char* ssid = "AP-MCP";
const char* password = "5010867250";

// Dirección IP y puerto del servidor al que enviaremos la solicitud GET
const char* serverIP = "192.168.54.247";
const int serverPort = 5000;

// Pin del botón en la NodeMCU (D4 en este caso)
const int buttonPin = D4;

void setup() {
  Serial.begin(115200);

  // Conectar a la red WiFi
  connectToWiFi();

  // Configurar el pin del botón como entrada con resistencia de pull-up
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Verificar si el botón está presionado
  if (digitalRead(buttonPin) == LOW) {
    Serial.println("Botón presionado, preparando solicitud GET...");

    // Enviar la solicitud GET al servidor
    sendGetRequest("/test"); // Cambiado a "/test" para propósitos de prueba

    // Esperar un tiempo antes de enviar otra solicitud
    delay(10000);  // Aumentar el tiempo de espera a 10 segundos
  }
}

void connectToWiFi() {
  Serial.println("Conectando a la red WiFi...");

  // Intentar la conexión a la red WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando...");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Conectado a la red WiFi");
    Serial.print("Dirección IP asignada: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Error al conectar a la red WiFi");
  }
}

void sendGetRequest(const char* getRequest) {
  // Crear una instancia de WiFiClient
  WiFiClient client;

  Serial.print("Conectando a la URL: ");
  Serial.print(serverIP);
  Serial.print(":");
  Serial.println(serverPort);

  // Conectar al servidor
  if (client.connect(serverIP, serverPort)) {
    Serial.println("Conectado al servidor");

    // Enviar la solicitud GET
    client.print("GET ");
    client.print(getRequest);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(serverIP);
    client.println("Connection: close");
    client.println();

    // Esperar a que el servidor responda
    while (client.connected() && !client.available()) delay(10);

    // Leer y mostrar la respuesta del servidor
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
    }

    Serial.println();
    Serial.println("Respuesta del servidor recibida");

    // Cerrar la conexión
    client.stop();
  } else {
    Serial.println("Error al conectar al servidor");
  }
}
