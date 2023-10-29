# DUINOSHOOT
A spaceinvader like game made in C++ for an Atmega328p microcontroller, working with push buttons and oled 128x64 screen.

### DESCRIPTION
The purpose of this project was to create a small space invader-type game using an **Arduino Nano**. I did this to test my skills in algorithmic logic and actor management in a game (collision, shooting, etc.). The electronic part is based on a rather basic setup. I use an Arduino Nano board with an Atmega328p microcontroller, connected to a 128x64 pixel OLED screen and three push buttons, one of which is connected to one of the Arduino's external interrupt pins. The operation is simple. The "v" button allows the spaceship to move down, the "^" button allows it to move up, and the red button allows firing a laser. The player can only shoot three lasers at a time. The goal is to eliminate as many enemies as possible. When the player's score exceeds 30, the enemies speed up to add difficulty. If the player is hit by an enemy, they lose. At startup, a small menu is displayed and asks the player to click one of the buttons, this menu reappears when the player loses.
I chose to use an Arduino Nano because it was the first board I studied and the one I had the most knowledge about. The difficulties I encountered were mainly related to the game's operation, as on such a small screen, it can sometimes be challenging to manage multiple things simultaneously. Collisions, in particular, required multiple revisions. Furthermore, it was a very enjoyable project to create and develop. I will detail the **game's features**, how it works, and the **libraries used**.

### CREDITS
[Adafruit_SSD1306 Library](https://github.com/adafruit/Adafruit_SSD1306)

[Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library)

[Image2cpp](https://javl.github.io/image2cpp/) A tool that allows you to change images into byte arrays (or arrays back into an images) for use with (monochrome) displays such as OLEDs on your Arduino or Raspberry Pi.

### SPRITES
I did the sprites all by myself using paint. There's only two sprites, one for the player's spaceship and one fort the ennemie's. They are both sized 22x20 pixels
Here's the player's spaceship sprite : 
![sapceship sprite made with paint](images/spaceship.bmp)
And this is the ennemies's spaceship sprite : 
![ennemy spaceship sprite made with paint](images/sprite_ennemy.bmp)
