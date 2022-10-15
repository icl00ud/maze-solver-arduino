#include <SharpIR.h> // Sensor da frente (Sharp IR GP2Y0A21YK0F).
#include <QTRSensors.h> // Sensor de linha (QTR-8RC).

#define ir A0; // IR pino de onde o sensor está na placa ------- tem que ser analógico.
#define model 1080; // Modelo do sensor que é um SHARP 2Y0A21.

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
    // Aqui printa os valores mínimos mensurados quando emissores estão em contato com a linha.
    for (uint8_t i = 0; i < numSensors; i++)
    {
      Serial.print(qtr.calibrationOn.minimum[i]);
      Serial.print(" | ");
    }
    Serial.println();

    // Aqui printa os valores máximos mensurados quando emissores estão em contato com a linha.
    for (uint8_t i = 0; i < numSensors; i++)
    {
      Serial.print(qtr.calibrationOn.maximum[i]);
      Serial.print(" | ");
    }
    Serial.println();
    delay(1000);
  
  // Usei como referência https://github.com/pololu/qtr-sensors-arduino
  // --------------------------------- Fim da configuração dos sensores de linha QTRSensors ---------------------------------

}
  
void loop() {
  // put your main code here, to run repeatedly:

  // ------------------------------------------ Configuração do sensor SharpIR ------------------------------------------


    unsigned long pepe1 = millis();

    int dis = sharpIR.distance(); // Aqui retorna a distância do objeto a frente em cm. O valor máximo é 80cm.
    Serial.print("Distância: "); // Printa a distância no monitor serial.
    Serial.print(dis); // Provavelmente usaremos isso pra fazer o algorítimo.

    unsigned long pepe2 = millis(); - pepe1; // Nos dá o tempo que levou para medir a distância do objeto a frente.
    Serial.print(" Tempo (ms): ");
    Serial.println(pepe2);


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
    Serial.println(position);

    delay(500);

    // Usei como referência https://github.com/pololu/qtr-sensors-arduino
  // ---------------------------------------- Fim da configuração do sensor de linha QTRSensors ----------------------------------------
}

// ------------------------------------------ Funções do motor ------------------------------------------

  void PraFrente() {
    // Função para o robô ir para frente.
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    // só arrumar conforme for botando os motores
  }

  void PraEsquerda() {
    // Função para o robô ir para esquerda.
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    // só arrumar conforme for botando os motores
  }

  void PraDireita() {
    // Função para o robô ir para direita.
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    // só arrumar conforme for botando os motores
  }

  void PraTras() {
    // Função para o robô ir para trás.
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    // só arrumar conforme for botando os motores
  }

// ------------------------------------------ Fim das funções do motor ------------------------------------------