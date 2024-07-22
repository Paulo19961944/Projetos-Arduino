#include <SoftwareSerial.h>

// Pinos de comunicação serial do módulo RS485
#define Pino_RS485_RX 10 // DI do Módulo RS485
#define Pino_RS485_TX 11 // DO do Módulo RS485

// Pino de controle transmissão/recepção (RE, DE)
#define SSerialTxControl 3

#define RS485Transmit HIGH
#define RS485Receive LOW

// Cria a serial por software para conexão com módulo RS485
SoftwareSerial RS485Serial(Pino_RS485_RX, Pino_RS485_TX);

String dadosSerial = ""; // String para armazenar os dados recebidos

void setup() {
  // Inicializa a serial do Arduino
  Serial.begin(9600);
  Serial.println("Modulo Transmissor");
  Serial.println("Digite um Valor na Serial para enviar os dados ...");

  pinMode(SSerialTxControl, OUTPUT);

  // Inicializa a serial do módulo RS485
  RS485Serial.begin(4800);
}

void loop() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    
    // Verifica se é um caractere imprimível (ignora caracteres de controle)
    if (isPrintable(c)) {
      dadosSerial += c; // Concatena os caracteres para formar a string completa
    }
  }

  // Chama a função para enviar os dados se houver algo na string dadosSerial
  if (dadosSerial.length() > 0) {
    enviarDados(dadosSerial);
    dadosSerial = ""; // Limpa a string após enviar os dados
  }
}

void enviarDados(String dados) {
  // Habilita o módulo para transmissão
  digitalWrite(SSerialTxControl, RS485Transmit);

  // Remove a barra inicial e envia os dados pela serial RS485
  RS485Serial.println(dados.substring(1));

  // Aguarda até que todos os dados sejam enviados
  RS485Serial.flush();

  // Desabilita o módulo para transmissão (configura para recepção)
  digitalWrite(SSerialTxControl, RS485Receive);

  // Feedback para o Serial Monitor
  Serial.println("Dados enviados: " + dados.substring(1));
}

