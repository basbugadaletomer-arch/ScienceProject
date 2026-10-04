#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo teleskop;

const int merkur  = 12;
const int venus   = 8;
const int mars    = 7;
const int jupiter = 4;
const int saturn  = 2;

const int servoPin = 3;

int mevcutAci = 90;

void setup() {
  pinMode(merkur, INPUT_PULLUP);
  pinMode(venus, INPUT_PULLUP);
  pinMode(mars, INPUT_PULLUP);
  pinMode(jupiter, INPUT_PULLUP);
  pinMode(saturn, INPUT_PULLUP);

  teleskop.attach(servoPin);
  teleskop.write(mevcutAci);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("UZAY TELESKOBU");
  lcd.setCursor(0, 1);
  lcd.print("Gezegen sec");
}

void loop() {
  if (digitalRead(merkur) == LOW) {
    hedefSec("MERKUR", "En kucuk", 20);
    butonBekle(merkur);
  }

  if (digitalRead(venus) == LOW) {
    hedefSec("VENUS", "Cok sicak", 50);
    butonBekle(venus);
  }

  if (digitalRead(mars) == LOW) {
    hedefSec("MARS", "Kizil gezegen", 85);
    butonBekle(mars);
  }

  if (digitalRead(jupiter) == LOW) {
    hedefSec("JUPITER", "En buyuk", 125);
    butonBekle(jupiter);
  }

  if (digitalRead(saturn) == LOW) {
    hedefSec("SATURN", "Halkali", 160);
    butonBekle(saturn);
  }
}

void hedefSec(String isim, String bilgi, int hedefAci) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(isim);

  lcd.setCursor(0, 1);
  lcd.print("Yoneliyor...");

  servoYavasGit(hedefAci);

  delay(300);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(isim);

  lcd.setCursor(0, 1);
  lcd.print(bilgi);
}

void servoYavasGit(int hedefAci) {
  if (hedefAci > mevcutAci) {
    for (int aci = mevcutAci; aci <= hedefAci; aci++) {
      teleskop.write(aci);
      delay(15);
    }
  } else {
    for (int aci = mevcutAci; aci >= hedefAci; aci--) {
      teleskop.write(aci);
      delay(15);
    }
  }

  mevcutAci = hedefAci;
}

void butonBekle(int pin) {
  delay(30);

  while (digitalRead(pin) == LOW) {
    delay(10);
  }

  delay(30);
}