#include <Arduino.h>
String dadosSerial = ""; // Recupera a String

void setup()
{
  Serial.begin(9600); // Inicializa a Serial
}

void loop()
{ 
  // Verifica se há pelo menos 8 bytes disponíveis
  if(Serial.available() >= 8){
    // Lê os dados da porta serial
    while (Serial.available() > 0) {
      char c = Serial.read(); // Armazena os caracteres do Serial
      dadosSerial += c; // Concatena os caracteres para formar a string completa
      delay(5); // Aguarda um breve período para receber o próximo caractere
    }
    
    // Extrai e converte os valores
    char initialCommand = dadosSerial.charAt(0); // Captura o Comando Inicial (Primeiro Caractere)
    int id = dadosSerial.substring(1, 3).toInt(); // Captura os 3 primeiros indices
    int relay = dadosSerial.substring(3, 5).toInt(); // Captura os 2 indices seguintes
    int module = dadosSerial.substring(5, 7).toInt(); // Captura os 2 indices seguintes
    char code = dadosSerial.charAt(7); // Obtém o caractere na posição 7

    // Espera antes de enviar a resposta
    delay(3000);

    // Envia os dados de volta pela porta serial
    Serial.print("ID:");
    Serial.println(id);
    Serial.print("Relay:");
    Serial.println(relay);
    Serial.print("Module:");
    Serial.println(module);
    Serial.print("Code:");
    Serial.println(code);
    Serial.println("Content:");
    Serial.print(dadosSerial); // Mostra a string completa recebida
  }
}
