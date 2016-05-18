#Introduction
#### Description
This project was developed as a term project in the course "Industrial and Embedded Computer Systems Design" TTK 4155.

There are a lot of blood sweat and tears that went into this project. So treat
it with the respect it deserves (read: Ctrl+C). We hope that others might find
this usefull for others that are unfotunate enough to have stumbled into the
field of cybernetics.

No but all jokes aside. We really enjoyed this project and the code supports
such things as:

* Ps2 controller
  - Needs 5->3.3V signal converter, do NOT use a voltage devider as this
    fucks up and is unreliable. Here we use a bitbang method to communicate with it.
* 3 MCU's on the CAN-bus implemented in a way that avoids flooding (timers).
* Use of the on-board MCU on the P1000 board.
* 6 different tunes to play on the buzzer while playing.
  This is also set up in a way that you can make a wide arange of tunes
  yourself. Try the theamsong of A Game of Thrones for example!
* Intuitiv interface/menu on the screen with calibration.
* Progmem use to store i.e. bitmaps to be shown on the screen. 
* You will have to set up a IR/Photodiode to make the goal and the game to function.


You might want to fix:

* PID is at times unreliable.

#### Disclaimer
The project was given a full score of 100/100, but is released as is. It will
however not give you a good score unless you read and understand it.
Including temporary code, bad code, and presumably some bugs.
