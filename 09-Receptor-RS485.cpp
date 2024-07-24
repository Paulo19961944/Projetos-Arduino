#include <SoftwareSerial.h>

unsigned long tempoAnterior = 0;
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
        processInput(inputString);
        inputString = "";
      }
    }
  }
}

void processInput(String input) {
  // Remove espaços em branco extras
  input.trim();
  
  // Substitui todas as '/' por '' (vazio)
  input.replace("/", " ");
  
  // Substitui todas as ',' por '' (vazio)
  input.replace(",", " ");

  input.replace("X", "R");
  
  // Verifica se a entrada não está vazia
  if (input.length() > 0) {
    // Divide a entrada em tokens separados por ',' (caso haja algum restante, mas agora deveria estar vazio)
    int startPos = 0;
    int commaPos = input.indexOf(',', startPos);
    while (commaPos != -1) {
      String codigo = input.substring(startPos, commaPos);
      bufferPrint(codigo, tempoAnterior);
      startPos = commaPos + 1;
      commaPos = input.indexOf(',', startPos);
    }
    
    // Processa o último código depois da última vírgula (mas não deve haver mais vírgulas)
    if (startPos < input.length()) {
      String codigo = input.substring(startPos);
      bufferPrint(codigo, tempoAnterior);
    }
  } 
  Serial.println("Buffer: " + input);
}


void bufferPrint(String codigo, unsigned long leituraAnterior){
  // Verifica se passaram 500 ms desde a última impressão
  if (millis() - tempoAnterior >= leituraAnterior && codigo.length() > 0) {
    tempoAnterior = millis(); // Atualiza o tempo anterior para o atual
  }
}
