# Arduino Maze Solver

This project aims to create a code to solve a maze using an Arduino microcontroller. The goal is to control a robot to navigate the maze automatically, find the exit, and report the path followed.

## Required Materials

- Arduino (any compatible model)
- SHARP 2Y0A21 distance sensor
- QTR line sensors
- DC engines
- L298N motor driver or similar
- Jumpers and breadboard

## Assembly Instructions

1. Connect the SHARP 2Y0A21 distance sensor to the Arduino input pins.
2. Connect the QTR line sensors to the Arduino input pins.
3. Connect the DC motors to the motor driver, then connect the motor driver to the Arduino output pins.
4. Assemble the circuit on a breadboard or a custom PCB.

## Usage Instructions

1. Upload the code to the Arduino.
2. Start the program.
3. The robot will begin navigating the maze automatically, using the distance sensor and line sensors to detect obstacles and find the exit.
4. The followed path will be reported.

## Final Considerations

This project is just an example of how to solve a maze using an Arduino microcontroller and different sensors. The specific implementation may vary depending on hardware and software constraints. Feel free to make modifications and improvements to the code to suit your needs.
