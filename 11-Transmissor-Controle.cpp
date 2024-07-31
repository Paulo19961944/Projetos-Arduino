#include <IRremote.h>

// Definições de pinos
const int receiverPin = 11;    // Pino do receptor IR
const int transmitterPin = 3;  // Pino do emissor IR

IRrecv irrecv(receiverPin); // Objeto IRrecv para receber sinais IR
IRsend irsend; // Objeto IRsend para enviar sinais IR

decode_results results; // Variável para armazenar os resultados da decodificação

unsigned long tvCode = 0; // Variável para armazenar o código IR da televisão
unsigned long otherCode = 0; // Variável para armazenar o código IR do outro controle

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial
  irrecv.enableIRIn(); // Habilita o receptor IR
  pinMode(transmitterPin, OUTPUT);  // Configura o pino do emissor IR como saída
}

void loop() {
  // Parte 1: Capturar o botão do controle da televisão
  if (irrecv.decode(&results)) {  // Se um sinal IR for recebido
    tvCode = results.value;  // Armazena o valor do código IR capturado da televisão

    // Exibe informações sobre o sinal recebido no monitor serial
    Serial.print("TV Remote - Received ");
    Serial.print(results.decode_type);
    Serial.print(" : ");
    Serial.print(tvCode, HEX);
    Serial.print(" (");
    Serial.print(results.bits);
    Serial.println(" bits)");

    delay(100); // Aguarda um breve intervalo antes de receber o próximo sinal
    irrecv.resume(); // Reinicia o receptor para aguardar o próximo sinal
  }

  // Parte 2: Capturar o botão do outro controle
  if (irrecv.decode(&results)) {  // Se um sinal IR for recebido
    otherCode = results.value;  // Armazena o valor do código IR capturado do outro controle

    // Exibe informações sobre o sinal recebido no monitor serial
    Serial.print("Other Remote - Received ");
    Serial.print(results.decode_type);
    Serial.print(" : ");
    Serial.print(otherCode, HEX);
    Serial.print(" (");
    Serial.print(results.bits);
    Serial.println(" bits)");

    delay(100); // Aguarda um breve intervalo antes de receber o próximo sinal
    irrecv.resume();  // Reinicia o receptor para aguardar o próximo sinal
  }

  // Parte 3: Configurar esse valor no outro controle
  if (tvCode != 0 && otherCode != 0) {
    // Configura o código capturado do controle da televisão no outro controle (Arduino com emissor IR)
    irsend.sendNEC(tvCode, results.bits);  // Envia o código IR da televisão para o outro controle
    Serial.println("Configured TV Code on Other Remote");

    tvCode = 0;  // Reinicia a variável para evitar reenvios contínuos
    otherCode = 0;  // Reinicia a variável do outro controle

    delay(1000);  // Aguarda 1 segundo antes de enviar novamente (para evitar transmissões rápidas)
  }

  // Parte 4: Fazer a ação que foi definida no controle da televisão
  // No caso do Arduino com emissor IR, a ação seria enviar o código IR para o dispositivo alvo (TV)
  // Isso já está sendo feito na parte 3, onde enviamos o código IR da televisão para o outro controle
}
