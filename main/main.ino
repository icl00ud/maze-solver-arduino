#include <SharpIR.h> // Sensor da frente (Sharp IR GP2Y0A21YK0F).
#include <QTRSensors.h> // Sensor de linha (QTR-8RC).



// Portas e modelo do sensor SharpIR
#define ir A0; // IR pino de onde o sensor está na placa ------- tem que ser analógico.
#define model 1080; // Modelo do sensor que é um SHARP 2Y0A21.



// Portas drive do motor
#define PININ1 2
#define PININ2 4
#define PININ3 5
#define PININ4 7
#define PINENA 3
#define PINENB 6

// Velocidades
#define SPEED0 255    // Valor de 0 a 255 para velocidade
#define SPEED1 255    // Valor de 0 a 255 para velocidade

// Definições gerais
#define s 12; // Altera aqui quantos segundos quer que o robô funcione.
#define RUNTIME s*1000 // Quantos segundos o robô vai andar.
#define TRESHOLD 750 // Referência para linha branca




SharpIR sharpIR(ir, model); // Cria o objeto do sensor de distância.
QTRSensors qtr; // Cria o objeto do sensor de linha.

const uint8_t numSensors = 2; // Número de sensores. No caso, 2.
uint16_t sensorValues[numSensors]; // Valores dos sensores.






void setup() {
  // put your setup code here, to run once:

  // --------------------------------- Configuração dos sensores de linha QTRSensors ---------------------------------

    qtr.setTypeAnalog();
    qtr.setSensorPins((const uint8_t[]){A0, A1}, numSensors); // Pinos dos sensores de linha. Tem que ser analógico.
    qtr.setEmitterPins(2); // Digital 2 é o pino do emissor de luz.

    delay(500);
    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(LED_BUILTIN, HIGH); // Liga o led do arduino dizendo que entrou no modo de calibração do sensor de linha.

    for (uint16_t i = 0; i < 400; i++)
    {
      qtr.calibrate(); // Calibra o sensor de linha
    }

    digitalWrite(LED_BUILTIN, LOW); // Desliga o led do arduino dizendo que saiu do modo de calibração do sensor de linha.
    
    Serial.begin(9600);

  // Usei como referência https://github.com/pololu/qtr-sensors-arduino
  // --------------------------------- Fim da configuração dos sensores de linha QTRSensors ---------------------------------
}

  





  
void loop() {
  // put your main code here, to run repeatedly:

  // ------------------------------------------ Configuração do sensor SharpIR ------------------------------------------

    int dis = sharpIR.distance(); // Aqui retorna a distância do objeto a frente em cm. O valor máximo é 80cm.
    Serial.print("Distância: "); // Printa a distância no monitor serial.
    Serial.print(dis); // Provavelmente usaremos isso pra fazer o algorítimo.

  // Usei como referência https://github.com/guillaume-rico/SharpIR
  
  // --------------------------------------- Fim da configuração do sensor SharpIR ---------------------------------------

  // ------------------------------------------ Configuração do sensor de linha QTRSensors ------------------------------------------

    uint16_t position = qtr.readlineWhite(sensorValues); // Aqui lê os valores dos sensores de linha para linha branca.

    // Aqui printa os valores dos sensores de linha de 0 a 1000. Quanto mais próximo de 1000, mais próximo da linha.
    for (uint8_t i = 0; i < numSensors; i++)
    {
      Serial.print(sensorValues[i]);
      Serial.print(" \t ");
    }
    Serial.println("Position: ??");
    Serial.println(position);

    // Usei como referência https://github.com/pololu/qtr-sensors-arduino
  // ---------------------------------------- Fim da configuração do sensor de linha QTRSensors ----------------------------------------

  Labirinto();
}





// ------------------------------------------ Funções do motor ------------------------------------------

  void controleMotor(int velocidadeEsquerdo, int velocidadeDireito) {
    // Função para controlar a velocidade dos motores.

    // Definições das portas digitais 
    pinMode(PININ1, OUTPUT); 
    pinMode(PININ2, OUTPUT); 
    pinMode(PININ3, OUTPUT); 
    pinMode(PININ4, OUTPUT); 
    pinMode(PINENA, OUTPUT); 
    pinMode(PINENB, OUTPUT); 

    // Ajustes motor da esquerda 

    if (speedLeft < 0)
    { 
      speedLeft = -speedLeft; 
      digitalWrite (PININ1, HIGH); 
      digitalWrite (PININ2, LOW); 
    }
    else
    { 
    digitalWrite (PININ1, LOW); 
    digitalWrite (PININ2, HIGH); 
    }

    // Ajustes motor da direita 

    if(speedRight < 0)
    { 
    speedRight = -speedRight; 
    digitalWrite (PININ3, HIGH); 
    digitalWrite (PININ4, LOW); 
    }
    else
    { 
    digitalWrite (PININ3, LOW); 
    digitalWrite (PININ4, HIGH); 
    }
 
    analogWrite (PINENA, velocidadeEsquerdo); 
    analogWrite (PINENB, velocidadeDireito);
  }

  void opcaoMotor(int opcao, int velocidadeEsquerdo, int velocidadeDireito) {
    // Função para controlar a direção dos motores.

    switch (opcao) {
      case 1: // Frente
        controleMotor(velocidadeEsquerdo, velocidadeDireito);
        break;

      case 2: // Trás
        controleMotor(-velocidadeEsquerdo, -velocidadeDireito);
        break;

      case 3: // Direita
        controleMotor(velocidadeEsquerdo, -velocidadeDireito);
        break;

      case 4: // Esquerda
        controleMotor(-velocidadeEsquerdo, velocidadeDireito);
        break;

      case 5: // Parar
        controleMotor(0, 0);
        break;
    }
  }

  void PraFrente() {
    // Função para o robô ir para frente.
    opcaomotor(1, SPEED0, SPEED0);
  }

  void PraEsquerda() {
    // Função para o robô ir para esquerda.
    opcaomotor(4, SPEED0, SPEED1);
  }

  void PraDireita() {
    // Função para o robô ir para direita.
    opcaomotor(3, SPEED1, SPEED0);
  }

  void PraTras() {
    // Função para o robô ir para trás.
    opcaomotor(2, 0, 0);
  }

  bool pararMotor(long runTime, long currentTime) {
    // Função para parar o robô.
    if (currentTime >= runTime) {
      opcaomotor(5);
      return true;
    }
  }

// ------------------------------------------ Fim das funções do motor ------------------------------------------

// ------------------------------------------ Lógica do resolvedor de labirinto ------------------------------------------

  void Labirinto() {
    // Função para o robô resolver o labirinto.

    if (sensorValues[0] <= TRESHOLD && sensorValues[1] <= TRESHOLD) { 
      PraFrente();
      // leitura do sensor (0 1) 

    } else if ( sensorValues[0] >= TRESHOLD && sensorValues[1] <= TRESHOLD) { 
      PraDireita();
      // leitura do sensor (1 0) 

    } else if ( sensorValues[0] <= TRESHOLD && sensorValues[1] >= TRESHOLD ) { 
      PraEsquerda();
      // leitura do sensor (0 0) 
     
    } else if (sensorValues[0] >= TRESHOLD && sensorValues[1] >= TRESHOLD ) { 
      // SEGUE EM FRENTE
      PraFrente();
    } 
  }

// ------------------------------------------ Fim Lógica do resolvedor de labirinto ------------------------------------------






