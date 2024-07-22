#include <SoftwareSerial.h>

unsigned int tempoAnterior = 0; // Tempo da última impressão

// Pinos de comunicação serial do módulo RS485
#define Pino_RS485_RX 10 // DO (Direct Output)
#define Pino_RS485_TX 11 // DI (Direct Input)

// Pino de controle transmissão/recepção
#define SSerialTxControl 3
#define RS485Transmit HIGH
#define RS485Receive LOW

// Cria a serial por software para conexão com módulo RS485
SoftwareSerial RS485Serial(Pino_RS485_RX, Pino_RS485_TX);

// Armazena os dados que chegam pela serial
String inputString = "";

void setup() {
  // Inicializa a serial do Arduino
  Serial.begin(9600);
  Serial.println("Módulo Receptor");
  Serial.println("Aguardando dados...");
  pinMode(SSerialTxControl, OUTPUT);

  // Coloca o módulo RS485 em modo de recepção
  digitalWrite(SSerialTxControl, RS485Receive);

  // Inicializa a serial do módulo RS485
  RS485Serial.begin(4800);
}

void loop() {
  // Recebe os dados do RS485 via porta serial
  if (RS485Serial.available()) {
    while (RS485Serial.available()) {
      // Recebe os dados e monta a string
      char inChar = (char)RS485Serial.read();
      inputString += inChar;
      // Se encontrou o caractere de nova linha, processa a string
      if (inChar == '\n') {
        bufferPrint(inputString, tempoAnterior);
        inputString = ""; // Limpa a string para receber novos dados
      }
    }
  }
}

void bufferPrint(String codigo, unsigned int leituraAnterior) {
  // Verifica se passaram 500 ms desde a última impressão
  if (millis() - tempoAnterior >= leituraAnterior && codigo.length() > 0) {
    // Remove o primeiro caractere "/" e o último caractere que é "X"
    String resultado = codigo.substring(1, codigo.length() - 1) + "R";
    Serial.println(resultado);  // Imprime o resultado modificado
    tempoAnterior = millis();    // Atualiza o tempo anterior para o atual
  }
}
