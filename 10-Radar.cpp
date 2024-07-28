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
    // Leia um byte de dados do sensor
    byte data = sensorSerial.read();
    
    // Imprima o valor recebido em formato decimal
    if(data < 1){
      Serial.println("Pessoa Detectada!");
    }
  }
}
