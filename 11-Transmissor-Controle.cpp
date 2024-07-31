#include <IRremote.h>
#include <RH_ASK.h>
#include <SPI.h>

// DEFINIÇÃO DE PINOS
#define RECV_PIN 11 // Pino do receptor IR
#define TRANSMIT_PIN 3 // Pino do transmissor RF
#define LED_PIN 13 // Pino do LED

// DEFINIÇÃO DE OBJETOS
IRrecv irrecv(RECV_PIN); // Instância do receptor IR
IRsend irsend; // Instância do transmissor IR
RH_ASK rf_driver(2000, 2, TRANSMIT_PIN); // Instância do driver RF

// DEFINIÇÃO DE VARIÁVEIS GLOBAIS
decode_results results; // Armazena os resultados da decodificação IR
bool sendRF = false; // Controle do estado de envio RF

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  irrecv.enableIRIn(); // Inicializa o receptor IR
  rf_driver.init(); // Inicializa o módulo RF
  pinMode(LED_PIN, OUTPUT); // Configura o pino do LED
}

void loop() {
  if (irrecv.decode(&results)) {  // Se um sinal IR for recebido
    Serial.print("Código IR recebido: ");
    Serial.print(results.value, HEX);  // Imprime o código IR no monitor serial
    Serial.println();
    
    // Convertendo o código IR para um formato que pode ser enviado via RF
    String codeString = String(results.value, HEX);
    codeString.toUpperCase();
    codeString = "0x" + codeString;  // Adiciona prefixo "0x" para formato hexadecimal

    // Envia o código via RF
    rf_driver.send((uint8_t*)codeString.c_str(), codeString.length());
    rf_driver.waitPacketSent();  // Aguarda o envio do pacote RF
    Serial.println("Código IR enviado via RF");

    irrecv.resume();  // Prepara para o próximo código IR
  }

  // Para fins de teste, você pode ativar o LED para indicar que o código está sendo enviado
  if (sendRF) {
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    sendRF = false;
  }
}
