// INCLUINDO A BIBLIOTECA IRREMOTE
#include <IRremote.h>

// CHAMANDO O OBJETO
IRsend irsend;

// SETUP
void setup() {
  Serial.begin(9600); // Inicializa a Serial
}

void loop() {
  // CONTROLA A TV SE TIVER DADOS NO SERIAL
  if (Serial.available() > 0) {
    controlarTV();
  }
}

// ENVIA OS DADOS
void enviarDados(unsigned long hexControl) {
  irsend.sendNEC(hexControl, 32); // Envia o código IR usando o protocolo NEC
  delay(1000); // Espera 1 segundo entre envios
}

// FUNÇÃO PARA CONTROLAR A TV
void controlarTV() {
  char tecla = Serial.read(); // Captura o Serial para a Variavel Tecla

  // CONDICIONAL PARA CONTROLAR A TV
  switch (tecla) {
    
    // LIGAR E DESLIGAR
    case 'P':
      enviarDados(0x20DF10EF);
      break;
    
    // NÚMEROS DE 0 A 9
    case '0':
      enviarDados(0x20DF08F7);
      break;
    case '1':
      enviarDados(0x20DF8877);
      break;
    case '2':
      enviarDados(0x20DF48B7);
      break;
    case '3':
      enviarDados(0x20DFC837);
      break;
    case '4':
      enviarDados(0x20DF28D7);
      break;
    case '5':
      enviarDados(0x20DFA857);
      break;
    case '6':
      enviarDados(0x20DF6897);
      break;
    case '7':
      enviarDados(0x20DFE817);
      break;
    case '8':
      enviarDados(0x20DF18E7);
      break;
    case '9':
      enviarDados(0x20DF9867);
      break;

    // VOLUME
    case '+':
      enviarDados(0x20DF40BF);
      break;
    case '-':
      enviarDados(0x20DFC03F);
      break;

    // CANAL +
    case 'W':
      enviarDados(0x20DF00FF);
      break;

    // CANAL -
    case 'S':
      enviarDados(0x20DF807F);
      break;

    // MUTE
    case 'M':
      enviarDados(0x20DF906F);
      break;
  }
}
