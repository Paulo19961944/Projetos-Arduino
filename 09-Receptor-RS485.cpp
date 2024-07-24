#include <SoftwareSerial.h>

unsigned int tempoAnterior = 0;
#define Pino_RS485_RX 10 // DO (Direct Output)
#define Pino_RS485_TX 11 // DI (Direct Input)
#define SSerialTxControl 3
#define RS485Transmit HIGH
#define RS485Receive LOW

SoftwareSerial RS485Serial(Pino_RS485_RX, Pino_RS485_TX);

String inputString = "";

void setup() {
  Serial.begin(9600);
  Serial.println("Módulo Receptor");
  Serial.println("Aguardando dados...");
  pinMode(SSerialTxControl, OUTPUT);
  digitalWrite(SSerialTxControl, RS485Receive);
  RS485Serial.begin(4800);
}

void loop() {
  if (RS485Serial.available()) {
    while (RS485Serial.available()) {
      char inChar = (char)RS485Serial.read();
      inputString += inChar;
      if (inChar == '\n') {
        bufferPrint(inputString, tempoAnterior);
        inputString = "";
      }
    }
  }
}

void bufferPrint(String codigo, unsigned int leituraAnterior){
  // Verifica se passaram 500 ms desde a última impressão
  if (millis() - tempoAnterior >= leituraAnterior && codigo.length() > 0) {
    // Encontra a posição do primeiro caractere de vírgula
    int posVirgula = codigo.indexOf(',');
    if (posVirgula != -1) {
      // Imprime a parte da string até a vírgula
      Serial.println(codigo.substring(1, posVirgula));
      // Imprime 500 em uma nova linha
      Serial.println(leituraAnterior);
      // Remove a parte impressa da string
      inputString = codigo.substring(posVirgula + 1);
    }
    
    // Verifica se ainda há dados para enviar
    if (inputString.length() == 0) {
      Serial.println("\nDados enviados com sucesso!");
    }
    
    tempoAnterior = millis(); // Atualiza o tempo anterior para o atual
  }
}
