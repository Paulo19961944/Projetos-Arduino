#include <IRremote.hpp>
#define IR_RECEIVE_PIN 2
#define LED 7

void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
  pinMode(LED, OUTPUT);
}

void loop() {
  if (IrReceiver.decode()) {
    long numControl = IrReceiver.decodedIRData.decodedRawData;
    IrReceiver.resume(); // Enable receiving of the next value

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
