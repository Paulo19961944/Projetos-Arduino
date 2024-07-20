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
      Serial.println(numControl); // Print "old" raw data
      IrReceiver.resume(); // Enable receiving of the next value
    
    if(numControl == 0){
      digitalWrite(LED, HIGH);
    } else if(numControl == -16728320){
        digitalWrite(LED, LOW);
      }
  } 
}
