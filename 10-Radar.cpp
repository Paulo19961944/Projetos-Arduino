#include <SoftwareSerial.h>

// Crie um objeto SoftwareSerial para os pinos 10 e 11
SoftwareSerial sensorSerial(10, 11); // RX, TX

void setup() {
  // Inicialize a comunicação serial com o monitor serial a 9600 bps
  Serial.begin(9600);
  
  // Inicialize a comunicação serial com o sensor a 256000 bps
  sensorSerial.begin(256000);
}

void loop() {
  // Verifique se há dados disponíveis do sensor
  if (sensorSerial.available()) {
    byte data = sensorSerial.read();
    
    // Imprime o valor recebido em decimal e hexadecimal
    Serial.print("Dados recebidos (Decimal): ");
    Serial.print(data);
    Serial.print("  (Hexadecimal): ");
    Serial.println(data, HEX);
    
    // Exemplo de lógica para detectar valores específicos
    int detectionThreshold = 50; // Ajuste conforme necessário
    if (data < detectionThreshold) {
      Serial.println("Pessoa Detectada!");
    }
  }
}
