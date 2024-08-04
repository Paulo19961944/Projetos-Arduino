// INCLUSÃO DA BIBLIOTECA
#include <IRremote.h>

// CHAMANDO O OBJETO
IRsend irsend;

// DECLARANDO VARIÁVEIS GLOBAIS
byte botaoTV = 7;
bool estadoBotao = false;

void setup() {
  Serial.begin(9600); // Inicializa a Serial
  pinMode(botaoTV, INPUT_PULLUP); // Define o Botão como Entrada
}

void loop() {
  estadoBotao = digitalRead(botaoTV);
  if(estadoBotao == LOW){
    irsend.sendNEC(0x20DF10EF, 32);
    Serial.println("Emitindo Sinais");
    delay(100);
  }
}
