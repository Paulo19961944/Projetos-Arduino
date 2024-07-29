/******************************************************* AJUSTES A SER FEITO ***************************************************
********************************************************************************************************************************
/************************************************************** INICIO *********************************************************
/***** Foi constatado que sempre que envia um pulso negativo, o led acende e o serial manda uma resposta para o serial *********
/***** Preciso implementar apenas o pulso negativo na hora certa. Consultar o Datasheet de forma mais detalhada ****************
/***** O Comando utilizado está na variável comandoDetectaMovimento ************************************************************
********************************************************************************************************************************
/**************************************************************** FIM **********************************************************
*/


#include <SoftwareSerial.h>

// Configurações
const int pinoRadarRx = 10;
const int pinoRadarTx = 11;
const int pinoLed = 7;
const int velocidadeSerial = 256000; // Ajuste a taxa de transmissão para uma mais segura

// Comando para detectar movimento
const byte comandoDetectaMovimento[] = {0x00, 0x61}; // Ajuste conforme o datasheet

SoftwareSerial radarSerial(pinoRadarRx, pinoRadarTx);

void setup() {
  Serial.begin(9600);
  radarSerial.begin(velocidadeSerial);
  pinMode(pinoLed, OUTPUT);
  digitalWrite(pinoLed, LOW); // Garante que o LED esteja apagado inicialmente
}

void loop() {
  // Envia o comando para detectar movimento
  radarSerial.write(comandoDetectaMovimento, sizeof(comandoDetectaMovimento));

  // Lê a resposta do radar
  String resposta = "";
  while (radarSerial.available()) {
    char c = radarSerial.read();
    resposta += c;
  }

  // Exibe a resposta no monitor serial para depuração
  if (resposta.length() > 0) {
    Serial.println("Resposta do radar: " + resposta);
    digitalWrite(pinoLed, HIGH);
  }

  delay(500); // Aguarda antes de enviar o próximo comando
}
