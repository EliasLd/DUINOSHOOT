//////////////////// LIBRARIES ////////////////////////////

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/////////////////// VARIABLES ////////////////////////////

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define SPACESHIP_WIDTH 22
#define SPACESHIP_HEIGHT 20

const int up_button_pin = 2;
const int down_button_pin = 3;
const int shoot_button_pin = 4;

int up_button_state = LOW;
int last_up_button_state = LOW;

int down_button_state = LOW;
int last_down_button_state = LOW;

int shoot_button_state = LOW;
int last_shoot_button_state = LOW;

int spaceship_x = 0;
int spaceship_y = 0;

int current_y;

volatile int score = 0;

bool defeat = false;
bool start = false;
bool state_of_start = false;
bool is_sped_up = false;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);  // -1 = Reset pin

// 'spaceship', 22x20px
const unsigned char myspaceship[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0xff, 0xf8, 0x00, 0xff, 0xf8, 0x00, 0x1f,
  0xf0, 0x00, 0x03, 0x80, 0x00, 0x0f, 0xff, 0xc0, 0x1f, 0xff, 0xe0, 0x3f, 0xfc, 0xf8, 0x3f, 0xfc,
  0xf8, 0x1f, 0xff, 0xe0, 0x0f, 0xff, 0xc0, 0x03, 0x80, 0x00, 0x1f, 0xf0, 0x00, 0xff, 0xf8, 0x00,
  0xff, 0xf8, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 80)
const int spepd_bitmap_allArray_LEN = 1;
const unsigned char *spepd_bitmap_allArray[1] = {
  myspaceship
};


// 'sprite ennemy', 22x20px
const unsigned char mob[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x03, 0x80, 0x00, 0x07, 0x00, 0x03,
  0x0e, 0x00, 0x06, 0x0e, 0x00, 0x0e, 0x1c, 0x30, 0x1a, 0x1c, 0x60, 0x3f, 0xff, 0xc0, 0x3f, 0xff,
  0xc0, 0x1a, 0x1c, 0x60, 0x0e, 0x1c, 0x30, 0x06, 0x0e, 0x00, 0x03, 0x0e, 0x00, 0x00, 0x07, 0x00,
  0x00, 0x03, 0x80, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 80)
const int epd_bitmap_allArray_LEN = 1;
const unsigned char *epd_bitmap_allArray[1] = {
  mob
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////// Class Mob /////////////////////////
class Mob {
public:
  int x, y;
  int w, h;
  int speed;
  bool killed;

  Mob(int x, int y, int w, int h, int speed, bool killed) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->speed = speed;
    this->killed = killed;
  }

  print() {
    display.drawBitmap(x, y, mob, 22, 20, WHITE);
  }
};
/////////// Class Laser //////////////////////////
class Laser {
public:
  int x, y;
  int w, h;
  int speed;
  bool shoted;


  Laser(int x, int y, int w, int h, int speed, bool shoted) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->speed = speed;
    this->shoted = shoted;
  }

  void print() {
    display.drawRect(x, y, w, h, WHITE);
  }

  bool hit(Mob m) {
    if (x >= m.x && y >= m.y && y <= m.y + m.h) {
      score++;
      return true;
    }
    return false;
  }
};
/////////// GAME FUNCTIONS ////////////////////
void state() {
  if (start == false)
    state_of_start = !state_of_start;
}
bool menu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, SCREEN_HEIGHT / 4);
  display.println("Bienvenue dans");
  display.println("DUINOSHOOT");
  display.print("Appuyez sur v");
  display.drawBitmap(spaceship_x, SCREEN_HEIGHT / 2 + 10, myspaceship, 22, 20, WHITE);
  spaceship_x += 3;
  if (spaceship_x >= SCREEN_WIDTH)
    spaceship_x = 0;
  display.display();
  if (!state_of_start) {
    defeat = false;
    spaceship_x = 0;
    spaceship_y = 0;
    return true;
  } else
    return false;
}
void up() {
  up_button_state = digitalRead(up_button_pin);
  if (up_button_state == HIGH && last_up_button_state == LOW) {
    spaceship_y += SPACESHIP_HEIGHT;
    if (spaceship_y >= SCREEN_HEIGHT)
      spaceship_y -= SPACESHIP_HEIGHT;
  }
  last_up_button_state = up_button_state;
}

void down() {
  down_button_state = digitalRead(down_button_pin);
  if (down_button_state == HIGH && last_down_button_state == LOW) {
    spaceship_y -= SPACESHIP_HEIGHT;
    if (spaceship_y <= 0)
      spaceship_y += SPACESHIP_HEIGHT;
  }
  last_down_button_state = down_button_state;
}

void is_shoted(Laser *shoot, Mob *m1, Mob *m2) {
  if (shoot->shoted) {
    shoot->print();
    shoot->x += shoot->speed;
    m1->killed = shoot->hit(*m1);
    m2->killed = shoot->hit(*m2);
    if (shoot->x > SCREEN_WIDTH || m1->killed || m2->killed) {
      shoot->x = SPACESHIP_WIDTH + 1;
      shoot->y = current_y;
      shoot->shoted = false;
    }
  }
}

void update_mob(Mob *m) {
  if (m->killed || m->x < 0 - m->w) {
    m->x = SCREEN_WIDTH - m->w;
    m->y = random(0, 3) * m->h;
    m->killed = false;
  }

  if (!m->killed) {
    m->print();
    m->x -= m->speed;
  }
}

void shoot_detection(Laser *shoot1, Laser *shoot2, Laser *shoot3) {
  shoot_button_state = digitalRead(shoot_button_pin);
  if (shoot_button_state == HIGH && last_shoot_button_state == LOW) {
    current_y = spaceship_y - SPACESHIP_HEIGHT / 2 - 1;
    if (!shoot1->shoted) {
      shoot1->x = SPACESHIP_WIDTH + 1;
      shoot1->y = current_y;
      shoot1->shoted = true;
    } else if (!shoot2->shoted) {
      shoot2->x = SPACESHIP_WIDTH + 1;
      shoot2->y = current_y;
      shoot2->shoted = true;
    } else if (!shoot3->shoted) {
      shoot3->x = SPACESHIP_WIDTH + 1;
      shoot3->y = current_y;
      shoot3->shoted = true;
    }
  }
  last_shoot_button_state = shoot_button_state;
}
void print_score() {
  display.setCursor(SCREEN_WIDTH / 2 - 30, 57);
  display.print("score : ");
  display.print(score);
}

bool defeat_verification(Mob *m) {
  if (spaceship_x + SPACESHIP_WIDTH - 1 > m->x && spaceship_x <= m->x + m->w) {
    if (spaceship_y - 20 >= m->y && spaceship_y - 20 < m->y + m->h) {
      return true;
    }
  }
  return false;
}

void reset_spaceship() {
  spaceship_x = 0;
  spaceship_y = 0;
}

void reset_shoot(Laser *shoot) {
  shoot->x = SPACESHIP_WIDTH + 1;
  shoot->y = spaceship_y - SPACESHIP_HEIGHT / 2;
  shoot->shoted = false;
}

void reset_mob(Mob *mob) {
  mob->x = SCREEN_WIDTH - 22;
  mob->y = random(1, 4) * mob->h - mob->h;
  mob->killed = false;
}

void reset_game(Laser *s1, Laser *s2, Laser *s3, Mob *m1, Mob *m2) {
  start = false;
  reset_spaceship();
  reset_shoot(s1);
  reset_shoot(s2);
  reset_shoot(s3);
  reset_mob(m1);
  reset_mob(m2);
  delay(1000);
  state_of_start = true;
  score = 0;
}

void speedup_mobs(Mob *m1, Mob *m2) {
  m1->speed++;
  m2->speed++;
  is_sped_up = true;
}

/////////// CLASS INSTANCES ///////////////////////////
Laser shoot1(SPACESHIP_WIDTH + 1, spaceship_y - SPACESHIP_HEIGHT / 2, 5, 2, 3, false);
Laser shoot2(SPACESHIP_WIDTH + 1, spaceship_y - SPACESHIP_HEIGHT / 2, 5, 2, 3, false);
Laser shoot3(SPACESHIP_WIDTH + 1, spaceship_y - SPACESHIP_HEIGHT / 2, 5, 2, 3, false);
Mob mob1(SCREEN_WIDTH - 22, random(1, 4) * 20, 22, 20, 3, false);
Mob mob2(SCREEN_WIDTH - 22, random(1, 4) * 20, 22, 20, 3, false);
//////////////////////////////////////////////////////
////SETUP////
void setup() {
  Serial.begin(9600);
  randomSeed(millis());
  pinMode(up_button_pin, INPUT_PULLUP);
  pinMode(down_button_pin, INPUT_PULLUP);
  pinMode(shoot_button_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(up_button_pin), state, CHANGE);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Echec de l'allocation");
    for (;;)
      ;
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.display();
}
////LOOP////
void loop() {
  while (!start || defeat)
    start = menu();
  unsigned long current_time = millis();
  display.clearDisplay();
  display.drawBitmap(spaceship_x, spaceship_y - SPACESHIP_HEIGHT, myspaceship, 22, 20, WHITE);
  /////// update_mob des tir //////////
  is_shoted(&shoot1, &mob1, &mob2);
  is_shoted(&shoot2, &mob1, &mob2);
  is_shoted(&shoot3, &mob1, &mob2);
  /// Déplacement vertical du vaisseau ///
  up();
  down();
  ////////// Détection du tir & update_mob des mobs ///////////
  shoot_detection(&shoot1, &shoot2, &shoot3);
  update_mob(&mob1);
  if (current_time >= 2000)
    update_mob(&mob2);
  ////////////////////////////////////////
  print_score();
  display.display();
  //////////// defeat verification ///////////////////////////////
  defeat = defeat || defeat_verification(&mob1);
  defeat = defeat || defeat_verification(&mob2);
  if (defeat) {
    reset_game(&shoot1, &shoot2, &shoot3, &mob1, &mob2);
  }
  if (score > 30 && !is_sped_up)
    speedup_mobs(&mob1, &mob2);
  ///////////////////////////////////////////////////////////////
}
