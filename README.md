# Sound Reactive RGB IC LEDs using an AUX cable as input
## Table of Content:
- Connections
- Softwere
- Troubleshooting 

### Connections
AUX schematic:
![TRS-Audio-Plug-Connections-2](https://user-images.githubusercontent.com/97436308/219695002-8713755d-f3dd-4077-8f7a-8ea37924d5f2.png)
An example for an Arduino board:
![Nano](https://user-images.githubusercontent.com/97436308/219695943-70b446d0-6a21-4a61-9afc-91aaedef7a0a.png)
As you can see from the AUX schematic above, the basic AUX connector contains 3 separate parts: Ground, Left audio, and Right audio.
It is important to connect the Ground part to a "GND" labled pin on the Arduino board. The other Two lines: Left audio and Right audio; should be connected to an analog pin on the Arduino board. Those pins are usaully labled with the letter A. (Connect the left and right audio parts to the same analog pin)

