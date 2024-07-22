#include <IRremote.hpp>
#define IR_RECEIVE_PIN 2
#define LED 7

void setup()
{
  Serial.begin(9600); // Inicializa a Serial
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Inicializa o IRReceiver
  pinMode(LED, OUTPUT); // Define o Led como Saída
}

void loop() {
  if (IrReceiver.decode()) {
      long numControl = IrReceiver.decodedIRData.decodedRawData; // Armazena o Código do IR
      Serial.println(numControl); // Printa ele na tela
      IrReceiver.resume(); // Espera o Próximo Valor

    // Se clicar no botão power e segurar, então ligar o led
    if(numControl == 0){
      digitalWrite(LED, HIGH); 
    } 
      
    // Se clicar no botão power apenas uma vez, sem segurar. Então desligar o led
    else if(numControl == -16728320){ 
        digitalWrite(LED, LOW);
      }
  } 
}
