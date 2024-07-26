#include <SoftwareSerial.h>

// Define os pinos RX e TX do radar
const int radarRX = 10;  // Pino RX do radar conectado ao pino TX do Arduino
const int radarTX = 11;  // Pino TX do radar conectado ao pino RX do Arduino

// Cria uma instância da SoftwareSerial
SoftwareSerial radarSerial(radarRX, radarTX);

void setup() {
  // Inicia a comunicação serial com o computador
  Serial.begin(9600); // Taxa de transmissão para o monitor serial

  // Configura a comunicação serial com o radar
  radarSerial.begin(256000); // Taxa de transmissão do radar
}

void loop() {
  // Verifica se há dados disponíveis no radar
  if (radarSerial.available()) {
    // Lê um byte de dados do radar
    char data = radarSerial.read();
    
    // Envia os dados recebidos para o monitor serial
    Serial.print("Dados recebidos do radar: ");
    Serial.println(data);
  }
  
  // Verifica se há dados disponíveis no monitor serial
  if (Serial.available()) {
    // Lê um byte de dados do monitor serial
    char data = Serial.read();
    
    // Envia os dados recebidos para o radar
    radarSerial.write(data);
  }
}
