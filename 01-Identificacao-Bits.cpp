#include <Arduino.h>
String dadosSerial = ""; // Recupera a String

void setup()
{
  Serial.begin(9600); // Inicializa a Serial
}

void loop()
{ 
  if(Serial.available() >= 8){ // Verifica se há pelo menos 8 bytes disponíveis
    // Lê os dados da porta serial
    while (Serial.available() > 0) {
      char c = Serial.read();
      dadosSerial += c; // Concatena os caracteres para formar a string completa
      delay(5); // Aguarda um breve período para receber o próximo caractere
    }
    
    // Extrai e converte os valores
    char initialCommand = dadosSerial.charAt(0); // Adiciona ponto e vírgula aqui
    int id = dadosSerial.substring(1, 3).toInt(); // Corrige os índices para pegar dois caracteres
    int relay = dadosSerial.substring(3, 5).toInt(); // Corrige os índices para pegar dois caracteres
    int module = dadosSerial.substring(5, 7).toInt(); // Corrige os índices para pegar dois caracteres
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
