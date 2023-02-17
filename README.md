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

An example of an addressable LED strip (the one I'm using):

![0](https://user-images.githubusercontent.com/97436308/219700656-ca91c5d3-d009-4289-9387-325d7530a159.jpg)

This part is a bit more tricky but definitely achievable.
We need to connect the LED strip to an external power supply as well as to the Arduino board.
#### Supplying Power:
- Please note that electricity is very dangerous. Do not attemp anything that you are not sure is safe 

First, look at your LED strip to determine what Voltage it requires. My LED strip, for example, requires 12v. Chances are you have a supplier of that voltage lying around from an old router or something but they are not very expensive and relatively easy to find. 

- Note that it needs to be DC and not AC

Now all that's left is to connect it to the LEDs. to do this, determine which part of the power supplier cable is the possitive and which is the negative and connect the possitive to the possitive part (in my case it's the part labled "12V") on the LED strip and the negative part to the part labled "GROUND".
#### Connecting to the board:
Connect the remaining cable of the LED strip, which shoud be labled "Din" or "D" or "DATA", to one of the Data pins on you Arduino board.
And also connext the "GROUND" cable of the LED strip to one of the "GND" pins on the arduino. This is important for science reasons. 

