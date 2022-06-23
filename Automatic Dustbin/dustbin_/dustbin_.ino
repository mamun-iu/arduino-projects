#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define trigPin 11
#define echoPin 10
float dustBinHeight = 100.0;

void setup() {
  Serial.begin (9600);
  lcd.begin();
  lcd.backlight();
  //lcd.print("Hello, world!");
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(8, OUTPUT);
}

void loop() {
//  float duration, distance;
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//
//  duration = pulseIn(echoPin, HIGH);
//  distance = (duration / 2) * 0.0344;
//
//  if //(distance >= 400 || distance <= 2) 
//    (distance <=10)
//  {
//    //Serial.print("Distance = ");
//    //Serial.println("Out of range");
//    digitalWrite(8,HIGH);
//  }
//  else {
//    Serial.print("Distance = ");
//    Serial.print(distance);
//    Serial.println(" cm");
//    delay(500);
//    digitalWrite(8,LOW);
//  }
Serial.println("Percent");
measureDustbinHeightPercent();
  delay(500);
}
void measureDustbinHeightPercent(){
  float duration, distance ;
  lcd.clear();
  lcd.setCursor(0,0);
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2.0;

  if(distance > dustBinHeight){
    Serial.print(distance);
    Serial.println(" TOO MUCH DISTANCE");
    return ;
  }
  Serial.print("Distance Now");
  Serial.println(distance);

  float fillUpPercentage = ((dustBinHeight - distance) * 100 ) / dustBinHeight ;
  Serial.print("Percent Filled Up ");
  Serial.println(fillUpPercentage);
  lcd.clear();
  lcd.println("Dustbin ");
  lcd.setCursor(0,1);
  lcd.print(fillUpPercentage);
  lcd.println(" % Fi ");
  
}
