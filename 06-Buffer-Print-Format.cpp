String dadosSerial = ""; // String para armazenar os dados recebidos
unsigned int tempoAnterior = 0; // Tempo da última impressão

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
}

void loop() {
  while (Serial.available() > 0) {
    char c = Serial.read(); 
    
    // Verifica se é um caractere imprimível (ignora caracteres de controle)
    if (isPrintable(c)) {
      dadosSerial += c; // Concatena os caracteres para formar a string completa
    }
  }

  // Chamada da função bufferPrint com a condição de tempo
  bufferPrint(dadosSerial, 500);
}

void bufferPrint(String codigo, unsigned int leituraAnterior){
  // Verifica se passaram 500 ms desde a última impressão
  if (millis() - tempoAnterior >= leituraAnterior && codigo.length() > 0) {
    // Encontra a posição do primeiro caractere de vírgula
    int posVirgula = codigo.indexOf(',');
    String resultado = codigo.substring(1, posVirgula);
    if (posVirgula != -1) {
      // Imprime a String
      Serial.print(resultado);
      // Remove a parte impressa da string
      dadosSerial = codigo.substring(posVirgula + 1);
    }
    tempoAnterior = millis(); // Atualiza o tempo anterior para o atual
  }
