#include<SD.h>
#include<SPI.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
int val=A0, br, sw=2, sw2=3, button=0, cs=4;
float res=10.0;
File myFile;
void setup() {
  Serial.begin(9600);
  pinMode(val, INPUT);
  pinMode(sw, INPUT_PULLUP);
  pinMode(cs, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  again:
  lcd.clear();
  Serial.print("Inicijalizacija SD kartice...\n");
  lcd.print("Inicijalizacija");
  lcd.setCursor(0,1);
  lcd.print("SD kartice...");
  delay(1500);
  if(!SD.begin(cs)){
    lcd.clear();
    Serial.println("Inicijalizacija neuspješna.");
    lcd.print("Inicijalizacija");
    lcd.setCursor(0,1);
    lcd.print("neuspjesna.");
    delay(1500);
    goto again;
  }
  lcd.clear();
  Serial.println("Inicijalizacija gotova.");
  lcd.setCursor(0,0);
  lcd.print("Inicijalizacija");
  lcd.setCursor(0,1);
  lcd.print("gotova.");
  delay(1500);
}
void loop() {
  lcd.clear();
  br=analogRead(val);
  float nap=br*0.0048828125;
  int lux=500/(res*((5-nap)/nap));
  button=digitalRead(sw);
  if(button==0){
    Serial.println("Spremanje na SD karticu...");
    lcd.setCursor(0,0);
    lcd.print("Spremanje na SD");
    delay(1500);
    myFile=SD.open("lux.txt", FILE_WRITE);
    if(!SD.begin(cs)){
      lcd.clear();
      Serial.println("Neuspjesno spremanje.");
      lcd.print("Neuspjesno");
      lcd.setCursor(0,1);
      lcd.print("spremanje.");
      delay(2000);
    }
    else{
      myFile.print(lux);
      myFile.println(" luksa");
      myFile.close();
      Serial.println("Spremljeno.");
      lcd.setCursor(0,1);
      lcd.print("Spremljeno");
      delay(1000);
    }
  }
  Serial.print("Vrijednost: ");
  Serial.print(lux);
  Serial.print(" lux \t");
  Serial.print("Napon: ");
  Serial.print(nap);
  Serial.println(" volti \t");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Izmjereno:");
  lcd.setCursor(11,0);
  lcd.print(lux);
  delay(1000);
}
