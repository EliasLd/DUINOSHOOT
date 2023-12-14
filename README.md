# DUINOSHOOT
![](https://img.shields.io/badge/Made_in-C++-red)
![](https://img.shields.io/badge/Arduino-project-yellow)

Un jeu de type spaceinvader réalisé en C++ pour un microcontrôleur Atmega328p, fonctionnant avec des boutons poussoirs et un écran oled 128x64.

### DESCRIPTION
Le but de ce projet était de créer un petit jeu de type Space Invader utilisant une **Arduino Nano**. J'ai fait cela pour tester mes compétences en logique algorithmique et en gestion d'acteurs dans un jeu (collision, tir, etc.). La partie électronique repose sur une configuration assez basique. J'utilise une carte Arduino Nano avec un microcontrôleur Atmega328p, connecté à un écran OLED de 128x64 pixels et trois boutons poussoirs, l'un d'eux est connecté à l'une des broches d'interruption externes de l'Arduino. L'opération est simple. Le bouton "v" permet au vaisseau spatial de descendre, le bouton "^" lui permet de monter et le bouton rouge permet de tirer un laser. Le joueur ne peut tirer que trois lasers à la fois. Le but est d'éliminer un maximum d'ennemis. Lorsque le score du joueur dépasse 30, les ennemis accélèrent pour ajouter de la difficulté. Si le joueur est touché par un ennemi, il perd. Au démarrage, un petit menu s'affiche et demande au joueur de cliquer sur un des boutons, ce menu réapparaît lorsque le joueur perd.
J'ai choisi d'utiliser une Arduino Nano car c'était la première carte que j'ai étudié et celle sur laquelle j'avais le plus de connaissances. Les difficultés que j'ai rencontré étaient principalement liées au fonctionnement du jeu, car sur un si petit écran, il peut parfois être difficile de gérer plusieurs choses simultanément. Les collisions, en particulier, ont nécessité de multiples révisions. De plus, c’était un projet très agréable à créer et à développer. Je détaillerai les **fonctionnalités du jeu**, son fonctionnement et les **bibliothèques utilisées**.

### FONCTIONNEMENT
DUINOSHOOT est programmé en utilisant les principes de programmation orientée objet en C++. Le vaisseau du joueur est une entité (instance de classe) , tout comme les vaisseau ennemis et les lasers tirés. Leur positions, vitesses et évolution dans l'espace sont 
assurés par l'intermédiaire de fonction prenant pour la plupart l'adresse mémoire de ces instances (utilisation de pointeurs). Le jeu prend aussi en compte les boutons sur lesquels il faut appuyer pour jouer. A l'aide d'une petite fonction, on récupère l'état du bouton ainsi que son état précédent pour ne considérer qu'un seul appui et pas le maintien

### CREDITS
[Adafruit_SSD1306 Library](https://github.com/adafruit/Adafruit_SSD1306)

[Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library)

[Image2cpp](https://javl.github.io/image2cpp/) Un outil qui permet de transformer des images en tableaux d'octets (ou des tableaux en images) à utiliser avec des écrans (monochrome) tels que les OLED sur votre Arduino ou Raspberry Pi.

### SPRITES
J'ai réalisé les sprites moi-même avec paint. Il n'y a que deux sprites, un pour le vaisseau spatial du joueur et un pour celui de l'ennemi. Ils mesurent tous deux 22 x 20 pixels.
Voici le sprite du vaisseau spatial du joueur :
![sapceship sprite made with paint](images/spaceship.bmp)

Et voici le sprite du vaisseau spatial ennemi :
![ennemy spaceship sprite made with paint](images/sprite_ennemy.bmp)

### USAGE
Si vous souhaitez tester le DUINOSHOOT, il vous suffit de prendre le code source du .ino et de télécharger les librairies. J'utilise Arduino IDE mais vous pouvez également utiliser Visual Studio Code avec l'extension platformIO.

### PROTOTYPE
Voici le montage électronique protoype sur ma breadboard : 

![first prototype](images/prototype.bmp)

Aperçu des écrans menu/jeu :

![start menu](images/start_menu_prototype.bmp)
![in-game screen](images/game_prototype.bmp)

### VERSION FINALE
J'ai optimisé le montage électronique pour le monter sur deux cartes soudables afin de concrétiser ce petit projet

