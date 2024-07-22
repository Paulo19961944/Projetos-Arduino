#include <Arduino.h>

const byte MAX_DATA_LENGTH = 100; // Tamanho máximo da string de dados recebidos

char dadosSerial[MAX_DATA_LENGTH]; // Array de caracteres para armazenar os dados recebidos
byte dadosIndex = 0; // Índice para o array de caracteres

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
}

void loop() {
  while (Serial.available() > 0) {
    char c = Serial.read();

    // Se encontrar um caractere de nova linha, processa os dados
    if (c == '\n') {
      dadosSerial[dadosIndex] = '\0'; // Adiciona terminador nulo ao final da string
      processarDados(dadosSerial); // Chama a Função Processar Dados
      dadosIndex = 0; // Reinicia o índice para receber novos dados

      // Evita estouro do buffer
    } else if (dadosIndex < MAX_DATA_LENGTH - 1) {
      dadosSerial[dadosIndex++] = c; // Adiciona o caractere ao array
    }
  }
}

void processarDados(char *dados) {
  char *token = strtok(dados, ","); // Primeira chamada para obter o primeiro token
  
  while (token != NULL) {
    // Trata os dados conforme necessário
    String dado = String(token);
    String id = dado.substring(1, 4);
    String rele = dado.substring(4, 6);
    String comando = dado.substring(6, 7);
    String tipo = dado.substring(7, 8);
    
    // Imprime os resultados formatados
    Serial.print("\nID: ");
    Serial.println(id);
    Serial.print("Rele: ");
    Serial.println(rele);
    Serial.print("Comando: ");
    Serial.println(comando);

  
    Serial.print("Tipo: ");
    Serial.println(tipo);
    
    token = strtok(NULL, ","); // Chamadas subsequentes para obter os próximos tokens
  }
}
