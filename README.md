# Arduino Maze Solver

Este é um projeto de faculdade que visa criar um código para resolver um labirinto usando um microcontrolador [Arduino](https://www.arduino.cc/). O objetivo é controlar um robô para percorrer o labirinto de maneira automática, encontrar a saída e relatar o percurso que foi seguido.

## Materiais necessários

- Arduino (qualquer modelo compatível)
- Sensor de distância SHARP 2Y0A21
- Sensores de linha QTR
- Motores DC
- Driver de motor L298N ou similar
- Jumpers e placa de prototipagem

## Instruções de montagem

1. Conecte o sensor de distância SHARP 2Y0A21 aos pinos de entrada do Arduino.
2. Conecte os sensores de linha QTR aos pinos de entrada do Arduino.
3. Conecte os motores DC ao driver de motor e, em seguida, conecte o driver de motor aos pinos de saída do Arduino.
4. Monte o circuito em uma placa de prototipagem ou em uma placa personalizada.

## Instruções de uso

1. Faça o upload do código para o Arduino.
2. Inicie o programa.
3. O robô começará a percorrer o labirinto automaticamente, utilizando o sensor de distância e os sensores de linha para detectar obstáculos e encontrar a saída.
4. O percurso seguido será relatado.

## Considerações finais

Este projeto é apenas um exemplo de como resolver um labirinto usando um microcontrolador Arduino e diferentes sensores. A implementação específica pode variar dependendo das restrições de hardware e software. Sinta-se à vontade para fazer modificações e melhorias no código para atender às suas necessidades.
