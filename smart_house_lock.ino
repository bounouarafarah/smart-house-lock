#include <Servo.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo fservo;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char pin[4];
char copin[4] = {'A', '1', 'B', '2'}; // Code utilisateur
char copin_maitre[4] = {'D', '4', '5', '6'}; // Code maître
int i = 0;
int attempts = 0;
bool alarm = false;
bool isUnlocked = false;

unsigned long previousMillis = 0;
const long interval = 1000; // Bips
unsigned long unlockTime = 0;
const long unlockDuration = 5000; // 5 secondes

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Code:");

  fservo.attach(10);
  fservo.write(0);

  pinMode(13, OUTPUT); // Buzzer
  noTone(13);
}

void loop() {
  unsigned long currentMillis = millis();

  if (alarm && currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    tone(13, 1000);
    delay(300);
    noTone(13);
  }

  if (isUnlocked && currentMillis - unlockTime >= unlockDuration) {
    fservo.write(0); // Reverrouiller automatiquement
    isUnlocked = false;
    lcd.clear();
    lcd.print("Verrouille");
    delay(1000);
    lcd.clear();
    lcd.print("Enter Code:");
  }

  char key = keypad.getKey();

  if (key) {
    Serial.println(key);

    if (alarm) {
      if (i < 4 && key != '#') {
        pin[i++] = key;
      } else if (key == '#' && i == 4) {
        if (check_pin(copin) || check_pin(copin_maitre)) {
          lcd.clear();
          lcd.print("Alarme OFF");
          noTone(13);
          alarm = false;
          attempts = 0;
        } else {
          lcd.clear();
          lcd.print("Wrong code!");
        }
        i = 0;
      }
      return;
    }

    if (i < 4 && key != '#') {
      pin[i++] = key;
      lcd.setCursor(0, 1);
      for (int j = 0; j < i; j++) lcd.print("*");
    } else if (key == '#' && i == 4) {
      if (check_pin(copin)) {
        lcd.clear();
        lcd.print("Welcome");
        fservo.write(90);
        unlockTime = millis();
        isUnlocked = true;
        attempts = 0;
      } else {
        lcd.clear();
        lcd.print("Repeat");
        tone(13, 2000);
        delay(300);
        noTone(13);
        attempts++;

        if (attempts >= 3) {
          lcd.clear();
          lcd.print("ALARME ACTIVE");
          alarm = true;
          previousMillis = millis();
        }
      }
      i = 0;
    }
  }
}

bool check_pin(char *code_ref) {
  for (int j = 0; j < 4; j++) {
    if (pin[j] != code_ref[j]) return false;
  }
  return true;
}
