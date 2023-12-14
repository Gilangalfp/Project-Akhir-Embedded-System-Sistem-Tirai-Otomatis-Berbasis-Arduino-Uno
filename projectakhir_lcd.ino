#include <Wire.h>
#include <BH1750.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);
Servo myservo;
BH1750 lightMeter (0x23);

void setup() {
  Serial.begin(9600);

  Wire.begin();
  lightMeter.begin();
  myservo.attach(9);
  
  lcd.begin(16,2);
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(6,0);
  lcd.print("TIRAI");
  lcd.setCursor(5,1);
  lcd.print("OTOMATIS");
  delay(3000);
  lcd.clear();
}

void loop(){
  uint16_t lux = lightMeter.readLightLevel();

  lcd.setCursor(0,0);
  lcd.print("Inten: ");
  lcd.setCursor(7,0);
  lcd.print(lux);
  lcd.print("lux");

  if(lux>=0 && lux<=10){
    myservo.write(0);
    delay(2000);
    lcd.setCursor(0,1);
    lcd.print("DI LUAR GELAP");
    delay(5000);
    lcd.clear();
  }
  else if(lux>=10){
    myservo.write(90);
    delay(2000);
    lcd.setCursor(0,1);
    lcd.print("DI LUAR TERANG");
    delay(5000);
    lcd.clear();
  }
}

