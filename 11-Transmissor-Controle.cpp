#include <IRremote.h>
#define RECV_PIN 2

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
      Serial.print("Codigo Recebido: ");
      Serial.println(results.value, HEX);
      irrecv.resume(); // Receive the next value
  }
}
