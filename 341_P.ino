#include <Servo.h>
#include <LiquidCrystal_I2C.h>

Servo servoSet1;
Servo servoSet2;

LiquidCrystal_I2C lcd_1(0x27,20,4); // set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd_2(0x25,20,4);

#define buzzer 7

const int trigPin1 = 8;     // defines sonar pins numbers
const int echoPin1 = 9;

const int trigPin2 = 10;  
const int echoPin2 = 11;

const int trigPin3 = 12; 
const int echoPin3 = 13;


long duration1;           // defines sonar variables
double distanceCm1;
long duration2;        
double distanceCm2;
long duration3;        
double distanceCm3;

int t = 13;

void setup()
{
  servoSet1.attach(5);
  servoSet1.write(0);
  servoSet2.attach(6);
  servoSet2.write(0);
  
  lcd_1.init(); // initialize the lcd 
  lcd_2.init();   

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);

  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(trigPin2, OUTPUT);
  
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  pinMode(echoPin2, INPUT);
  
}


void loop(){

    barUp();
    
    //Sonar1
    digitalWrite(trigPin1, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);
    duration1 = pulseIn(echoPin1, HIGH);
    distanceCm1= duration1*0.034/2;
    Serial.println(distanceCm1);
    delay(50);
  
    //Sonar2
    digitalWrite(trigPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
    duration2 = pulseIn(echoPin2, HIGH);
    distanceCm2= duration2*0.034/2;
    Serial.println(distanceCm2);
    delay(50);

    //Sonar3
    digitalWrite(trigPin3, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin3, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin3, LOW);
    duration3 = pulseIn(echoPin3, HIGH);
    distanceCm3= duration3*0.034/2;
    Serial.println(distanceCm3);
    delay(300);

  lcdSaver();

  if(distanceCm1 <= 30){
      
      getTime1(); 
  }

  
   if(distanceCm2 <= 30){
      
      getTime2();
  }  

//   if(distanceCm3 > 5){
//
//        barUp();
//    }
}  

void getTime1(){
  if(distanceCm1<=30 || distanceCm2<=30){
    
      for(int i =0; i<=13; i++){

          digitalWrite(buzzer, LOW);
        
          lcdPrint1();

          digitalWrite(buzzer, HIGH);

          if(t>0){
            t--;
            }
            
          if(t<11){
          barDown();
          }
          
          delay(1000);
          }
          lcdSaver();
          barUp();
          lcd_1.clear();
          lcd_2.clear();
          t = 13;
        }
}

void getTime2(){
  if(distanceCm1<=30 || distanceCm2<=30){
    
      for(int i =0; i<=13; i++){

          digitalWrite(buzzer, LOW);

          lcdPrint2();
          
          digitalWrite(buzzer, HIGH);

          if(t>0){
            t--;
            }

          if(t<11){
          barDown();
          }
          
          delay(1000);
          }
          lcdSaver();
          barUp();
          lcd_1.clear();
          lcd_2.clear();
          t = 13;
        }
}



void lcdPrint1(){

  lcd_1.clear();
  lcd_2.clear();
          
  lcd_1.backlight();
  lcd_2.backlight();
          
  lcd_1.setCursor(3,0);
  lcd_2.setCursor(3,0);
          
  lcd_1.print("DHA-RAJ UP");
  lcd_2.print("DHA-RAJ UP");
          
  lcd_1.setCursor(1,1);
  lcd_2.setCursor(1,1);
          
  lcd_1.print(t);
  lcd_2.print(t);
          
  lcd_1.setCursor(4,1);
  lcd_2.setCursor(4,1);
          
  lcd_1.print("Sec to Come");
  lcd_2.print("Sec to Come");
}



void lcdPrint2(){
  
   lcd_1.clear();
   lcd_2.clear();
              
   lcd_1.backlight();
   lcd_2.backlight();
              
   lcd_1.setCursor(2,0);
   lcd_2.setCursor(2,0);
              
   lcd_1.print("RAJ-DHA DOWN");
   lcd_2.print("RAJ-DHA DOWN");
              
   lcd_1.setCursor(1,1);
   lcd_2.setCursor(1,1);
              
   lcd_1.print(t);
   lcd_2.print(t);
              
   lcd_1.setCursor(4,1);
   lcd_2.setCursor(4,1);
              
   lcd_1.print("Sec to Come");
   lcd_2.print("Sec to Come");
}

void lcdSaver(){
  lcd_1.clear();
  lcd_2.clear();
          
  lcd_1.backlight();
  lcd_2.backlight();
          
  lcd_1.setCursor(3,0);
  lcd_2.setCursor(3,0);
          
  lcd_1.print("AUTOMATED");
  lcd_2.print("AUTOMATED");
          
  lcd_1.setCursor(1,1);
  lcd_2.setCursor(1,1);

  lcd_1.print("RAIL CROSSING");
  lcd_2.print("RAIL CROSSING");
}


void barDown() {
    servoSet1.write(95);
    servoSet2.write(105);
}

void barUp(){
    servoSet1.write(0);
    servoSet2.write(0);
}
