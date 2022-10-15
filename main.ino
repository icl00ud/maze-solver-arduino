#include <SharpIR.h> // Sensor da frente (Sharp IR GP2Y0A21YK0F)
#include <QTRSensors.h> // Sensor de linha (QTR-8RC)

#define ir A0; // IR pino de onde o sensor está na placa ------- tem que ser analógico
#define model 1080; // Modelo do sensor que é um SHARP 2Y0A21

SharpIR sharpIR(ir, model); // Cria o objeto do sensor
QTRSensors qtr; // Cria o objeto do sensor de linha

const uint8_t numSensors = 2; // Número de sensores
uint16_t sensorValues[numSensors]; // Valores dos sensores

void setup() {
  // put your setup code here, to run once:

  // --------------------------------- Configuração dos sensores de linha (qtr) ---------------------------------


  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1}, numSensors);
  qtr.setEmitterPins((const uint8_t[]){2, 3}, numSensors);

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // Liga o led do arduino dizendo que entrou no modo de calibração do sensor de linha

  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate(); // Calibra o sensor de linha
  }
  digitalWrite(LED_BUILTIN, LOW); // Desliga o led do arduino dizendo que saiu do modo de calibração do sensor de linha
  
  Serial.begin(9600);
  // Aqui printa os valores mínimos mensurados quando emissores estão em contato com a linha
  for (uint8_t i = 0; i < numSensors; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(" | ");
  }
  Serial.println();

  // Aqui printa os valores máximos mensurados quando emissores estão em contato com a linha
  for (uint8_t i = 0; i < numSensors; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(" | ");
  }
  Serial.println();
  delay(1000);
  

  // --------------------------------- Fim da configuração dos sensores de linha (qtr) ---------------------------------

}
  
void loop() {
  // put your main code here, to run repeatedly:

  // ------------------------------------------ Configuração do sensor SharpIR ------------------------------------------


  unsigned long pepe1 = millis();

  int dis = sharpIR.distance(); // Aqui retorna a distância do objeto a frente em cm
  Serial.print("Distância: "); // Printa a distância no monitor serial
  Serial.print(dis);

  unsigned long pepe2 = millis(); - pepe1; // Nos dá o tempo que levou para medir a distância do objeto a frente
  Serial.print(" Tempo (ms): ");
  Serial.println(pepe2);


  // Usei como referência https://github.com/guillaume-rico/SharpIR
  // --------------------------------------- Fim da configuração do sensor SharpIR ---------------------------------------

  // ------------------------------------------ Configuração do sensor de linha ------------------------------------------

  uint16_t position = qtr.readlineWhite(sensorValues); // Aqui lê os valores dos sensores de linha para linha branca


}
