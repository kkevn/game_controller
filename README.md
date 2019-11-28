# game_controller

The project utilizes an Arduino Uno for the hardware part of the game system while the games are run on Processing.

The idea was to make a simple controller that interacts with custom software that acts as a mini arcade.

*Note: The included gravity platformer game was found on [OpenProcessing(https://www.openprocessing.org/sketch/554613).*

![Assembled Controller](demo/model_assembled.jpg)

---

## Run Instructions
1. Follow the `/demo/model_circuit.png` design to build a similar controller
    1. *Please note that the LCD wiring was simplified; this project also included a 4pin adapter for the 16x2 LCD*
    1. *Feel free to use the `.STL` files found in the `/model/` folder for the controller shell*
1. Install the `src/arduino/controller/controller.ino` file onto the Arduino
    1. *Be sure to leave the Arduino plugged in via USB*
1. Install the Processing software found here: https://processing.org/download/
1. Open the `src/processing/games/games.pde` file

## Troubleshooting
1. If any issues occur when attempting to launch, any of the following may need to be addressed:
    1. In the `/games.pde` file, find the `myPort` variable and ensure it has the proper port as seen in the Arduino IDE
    1. In the `/controller.ino` file, ensure your Arduino has the specified libraries installed correctly

---

## Specifications

* **Arduino Uno** for hardware support
* **Processing** for interactive software
