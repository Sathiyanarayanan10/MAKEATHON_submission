// built in arduino library<br>
#include <LiquidCrystal.h>
#include <HCSR04.h>
LiquidCrystal lcd(12,11,5,4,3,2);
const int BuzzerPin=1;
const int trigPin = 7;
const int echoPin = 6;
int pwmPin = 10; // assigns pin 12 to variable pwm
int pot = A0; // assigns analog input A0 to variable pot
int c1 = 8;   // declares variable c1
int c2 = 9;   // declares variable c2

const int sw = 13;   // switch variable

int speed1;
UltraSonicDistanceSensor distanceSensor(trigPin, echoPin);
void setup() {
  pinMode(pwmPin, OUTPUT); 
  pinMode(pot, INPUT); 
  pinMode(BuzzerPin,OUTPUT);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Start");
  Serial.begin(9600);
  Serial.println("Started");
}
void TurnMotorA(){ //We create a function which control the direction and speed
//digitalWrite(in1, LOW); //Switch between this HIGH and LOW to change direction
//digitalWrite(in2, HIGH);
speed1 = analogRead(A0);
speed1 = speed1*0.2492668622; //We read thea analog value from the potentiometer calibrate it
// Then inject it to our motor
if((255-speed1)>130){
  if((distanceSensor.measureDistanceCm()+1)<10)
  {
    speed1=0;
    digitalWrite(BuzzerPin,HIGH);
  }
  else if((distanceSensor.measureDistanceCm()+1)<50)
  {
    speed1=speed1/1.5;
  }
  else if((distanceSensor.measureDistanceCm()+1)<70)
  {
    speed1=speed1/1.25;
  }  
 analogWrite(pwmPin,speed1);  
 //delay(100);
}
}
void loop() {
  TurnMotorA();
  lcd.begin(16, 2);
  // clear old screen data
  lcd.clear();
  
  lcd.setCursor(0,1);
  lcd.print ("Speed is:");
  c2= analogRead(pot); 
  int speed = c2*0.2492668622;
  analogWrite (pwmPin, speed);  
  
  
 int value = digitalRead(sw);
 if(value==1)
 {
  lcd.print(255-speed);
 }
 else{
  if((255-speed)<=200){
    lcd.print(255-speed);
  }
  else{
    lcd.print("200");
  }
 }
  lcd.setCursor (13,1);
  lcd.print ("RPM");
  
  delay(100);
}