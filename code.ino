#include <Keypad.h> 

#include <Wire.h>

#include <virtuabotixRTC.h>

#include <LiquidCrystal_I2C.h>


#define I2C_ADDR 0x27 

#define BACKLIGHT_PIN 3

#define En_pin 2

#define Rw_pin 1

#define Rs_pin 0

#define D4_pin 4

#define D5_pin 5

#define D6_pin 6

#define D7_pin 7
#define echoPin 36 //
#define trigPin 34 
#define MotorR1 30
#define MotorR2 28
#define MotorRE 32  // 
#define MotorL1 26
#define MotorL2 24


#define MotorLE 22



LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);



virtuabotixRTC myRTC(2, 3, 4); 




const byte numRows= 4; 

const byte numCols= 4; 


long sure, uzaklik; 

char keymap[numRows][numCols]= 

{

{'1', '2', '3', 'A'}, 

{'4', '5', '6', 'B'}, 

{'7', '8', '9', 'C'},

{'*', '0', '#', 'D'}

};



byte rowPins[numRows] = {12,11,10,9}; 

byte colPins[numCols]= {8,7,6,5}; 


int i1,i2,i3,i4;

char c1,c2,c3,c4;

char keypressed,keypressedx;


int A_hour=NULL;

int A_minute=NULL;

int AlarmIsActive=NULL;


int buzzer = 13;



Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);



void setup() {

  Serial.begin(9600);

  lcd.begin (16,2); 

  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);

  lcd.setBacklight(HIGH);

  lcd.home ();
 
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  pinMode(MotorLE, OUTPUT); 
  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(MotorRE, OUTPUT);
                                                  
}


void loop() {

   

  while(keypressed == NO_KEY){ 
digitalWrite(trigPin, LOW); 
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); //

  sure = pulseIn(echoPin, HIGH); //
  uzaklik = sure / 29.1 / 2; //

  Serial.println(uzaklik);

                              

  keypressed = myKeypad.getKey();

  lcd.clear(); 

  myRTC.updateTime();


  if(myRTC.hours==A_hour && myRTC.minutes==A_minute && AlarmIsActive==1 && myRTC.seconds >= 0 && myRTC.seconds <= 2){

    while(keypressedx == NO_KEY){

    tone(buzzer, 1000); 

    delay(100);

    tone(buzzer, 2000);

    delay(100);

  digitalWrite(trigPin, LOW); //
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); //
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); //

  sure = pulseIn(echoPin, HIGH); //
  uzaklik = sure / 29.1 / 2; //

  Serial.println(uzaklik);

  if (uzaklik < 15) // 
  {
    geri();  // 150 ms geri git
    delay(250);
    sag();  // 250 ms sağa dön
    delay(250);
  }
  else {  // değil ise,
    ileri(); // ileri git
  }

    

    lcd.clear();

    lcd.print("     Alarm"); 

    keypressedx = myKeypad.getKey();

    }

  }

  keypressedx = NO_KEY;

  noTone(buzzer);
    
    digitalWrite(MotorR2, LOW); // 
  digitalWrite(MotorL2, LOW); // 
  digitalWrite(MotorR1, LOW); // 
  digitalWrite(MotorL2, LOW); // 
  digitalWrite(MotorR1, LOW); // 
  digitalWrite(MotorL1, LOW); // 

  lcd.setCursor(0,0);

  lcd.print(myRTC.dayofmonth);

  lcd.print("/");

  lcd.print(myRTC.month);

  lcd.print("/");

  lcd.print(myRTC.year);

  lcd.setCursor(0,1);

  lcd.print(myRTC.hours);

  lcd.print(":");

  lcd.print(myRTC.minutes);

  lcd.print(":");

  lcd.print(myRTC.seconds);

  delay(100);

  }

 


         if (keypressed == 'C') //Ayarlar menüsü tuşu. 

             {

              lcd.clear();

              lcd.print("     Ayarlar");

             delay(1000);

              lcd.clear();

              lcd.print("Yil Ayari");






              

             char keypressed2 = myKeypad.waitForKey();  

                    if (keypressed2 != NO_KEY && keypressed2 !='*' && keypressed2 !='#' && keypressed2 !='A' && keypressed2 !='B' && keypressed2 !='C' && keypressed2 !='D' )

                      {

                       c1 = keypressed2;

                       lcd.setCursor(0, 1);

                       lcd.print(c1);

                       }

                 char      keypressed3 = myKeypad.waitForKey();

                    if (keypressed3 != NO_KEY && keypressed3 !='*' && keypressed3 !='#' && keypressed3 !='A' && keypressed3 !='B' && keypressed3 !='C' && keypressed3 !='D' )

                      {

                       c2 = keypressed3;

                       lcd.setCursor(1, 1);

                       lcd.print(c2);

                       }

                   char  keypressed4 = myKeypad.waitForKey();

                   if (keypressed4 != NO_KEY && keypressed4 !='*' && keypressed4 !='#' && keypressed4 !='A' && keypressed4 !='B' && keypressed4 !='C' && keypressed4 !='D' )

                      {

                       c3 = keypressed4;

                       lcd.setCursor(2, 1);

                       lcd.print(c3);

                       }

                   char   keypressed5 = myKeypad.waitForKey();

                   if (keypressed5 != NO_KEY && keypressed5 !='*' && keypressed5 !='#' && keypressed5 !='A' && keypressed5 !='B' && keypressed5 !='C' && keypressed5 !='D' )

                      {

                       c4 = keypressed5;

                       lcd.setCursor(3, 1);

                       lcd.print(c4);

                       }


                     i1=(c1-48)*1000;        

                     i2=(c2-48)*100;

                     i3=(c3-48)*10;

                     i4=c4-48;

                     int N_year=i1+i2+i3+i4;

                   delay(500);

                     lcd.clear();

                     lcd.print("Ay Ayari");


////////////////////////////////////////////////////////////////

                     char keypressed6 = myKeypad.waitForKey();  

                    if (keypressed6 != NO_KEY && keypressed6 !='*' && keypressed6 !='#' && keypressed6 !='A' && keypressed6 !='B' && keypressed6 !='C' && keypressed6 !='D' )

                      {

                       c1 = keypressed6;

                       lcd.setCursor(0, 1);

                       lcd.print(c1);

                       }

                    char   keypressed7 = myKeypad.waitForKey();

                    if (keypressed7 != NO_KEY && keypressed7 !='*' && keypressed7 !='#' && keypressed7 !='A' && keypressed7 !='B' && keypressed7 !='C' && keypressed7 !='D' )

                      {

                       c2 = keypressed7;

                       lcd.setCursor(1, 1);

                       lcd.print(c2);

                       }



                     i1=(c1-48)*10;

                     i2=c2-48;

                    int N_month=i1+i2;

                     delay(500);

                     


                     lcd.clear();

                     lcd.print("Gun Ayari");

                     

 ////////////////////////////////////////////////////////////////                    

                      char keypressed8 = myKeypad.waitForKey();  

                    if (keypressed8 != NO_KEY && keypressed8 !='*' && keypressed8 !='#' && keypressed8 !='A' && keypressed8 !='B' && keypressed8 !='C' && keypressed8 !='D' )

                      {

                        c1 = keypressed8;

                       lcd.setCursor(0, 1);

                       lcd.print(c1);

                       }

                      char keypressed9 = myKeypad.waitForKey();

                    if (keypressed9 != NO_KEY && keypressed9 !='*' && keypressed9 !='#' && keypressed9 !='A' && keypressed9 !='B' && keypressed9 !='C' && keypressed9 !='D' )

                      {

                        c2 = keypressed9;

                       lcd.setCursor(1, 1);

                       lcd.print(c2);

                       }



                     i1=(c1-48)*10;

                     i2=c2-48;

                    int N_day=i1+i2;

                    delay(500);

                     lcd.clear();

                     lcd.print("Saat Ayari");

////////////////////////////////////////////////////////////////////////////////////:                     

                     char keypressed10 = myKeypad.waitForKey();  

                    if (keypressed10 != NO_KEY && keypressed10 !='*' && keypressed10 !='#' && keypressed10 !='A' && keypressed10 !='B' && keypressed10 !='C' && keypressed10 !='D' )

                      {

                       c1 = keypressed10;

                       lcd.setCursor(0, 1);

                       lcd.print(c1);

                       }

                    char   keypressed11 = myKeypad.waitForKey();

                    if (keypressed11 != NO_KEY && keypressed11 !='*' && keypressed11 !='#' && keypressed11 !='A' && keypressed11 !='B' && keypressed11 !='C' && keypressed11 !='D' )

                      {

                        c2 = keypressed11;

                       lcd.setCursor(1, 1);

                       lcd.print(c2);

                       }



                     i1=(c1-48)*10;

                     i2=c2-48;

                    int N_hour=i1+i2;

                    delay(500);

                     lcd.clear();

                     lcd.print("Dakika Ayari");

////////////////////////////////////////////////////////////////////////////////////:

                    char keypressed12 = myKeypad.waitForKey();  

                    if (keypressed12 != NO_KEY && keypressed12 !='*' && keypressed12 !='#' && keypressed12 !='A' && keypressed12 !='B' && keypressed12 !='C' && keypressed12 !='D' )

                      {

                        c1 = keypressed12;

                       lcd.setCursor(0, 1);

                       lcd.print(c1);

                       }

                   char    keypressed13 = myKeypad.waitForKey();

                    if (keypressed13 != NO_KEY && keypressed13 !='*' && keypressed13 !='#' && keypressed13 !='A' && keypressed13 !='B' && keypressed13 !='C' && keypressed13 !='D' )

                      {

                        c2 = keypressed13;

                       lcd.setCursor(1, 1);

                       lcd.print(c2);

                       }



                     i1=(c1-48)*10;

                     i2=c2-48;

                    int N_minutes=i1+i2;

                    delay(500);

                     lcd.clear();


                    myRTC.setDS1302Time(22, N_minutes, N_hour, 1, N_day, N_month, N_year);


                    

                    keypressed=NO_KEY; 

              }

/////////////////////////////////////////Alarm Ayarı/////////////////////////////////

              

             if (keypressed == 'A'){

              lcd.clear();

              lcd.print("  Alarm Ayari  ");

              delay(1000);

              lcd.clear();

              lcd.print("Alarm Saati");

               

               char keypressed14 = myKeypad.waitForKey(); 

                    if (keypressed14 != NO_KEY && keypressed14 !='*' && keypressed14 !='#' && keypressed14 !='A' && keypressed14 !='B' && keypressed14 !='C' && keypressed14 !='D' )

                      {

                       c1 = keypressed14;

                       lcd.setCursor(0, 1);

                       lcd.print(c1);

                       }

                    char   keypressed15 = myKeypad.waitForKey();

                    if (keypressed15 != NO_KEY && keypressed15 !='*' && keypressed15 !='#' && keypressed15 !='A' && keypressed15 !='B' && keypressed15 !='C' && keypressed15 !='D' )

                      {

                        c2 = keypressed15;

                       lcd.setCursor(1, 1);

                       lcd.print(c2);

                       }



                     i1=(c1-48)*10;

                     i2=c2-48;

                     A_hour=i1+i2;

                    delay(500);

                     lcd.clear();

                     lcd.print("Alarm Dakikasi");

                      char keypressed16 = myKeypad.waitForKey(); 

                    if (keypressed16 != NO_KEY && keypressed16 !='*' && keypressed16 !='#' && keypressed16 !='A' && keypressed16 !='B' && keypressed16 !='C' && keypressed16 !='D' )

                      {

                       c1 = keypressed16;

                       lcd.setCursor(0, 1);

                       lcd.print(c1);

                       }

                    char   keypressed17 = myKeypad.waitForKey();

                    if (keypressed17 != NO_KEY && keypressed17 !='*' && keypressed17 !='#' && keypressed17 !='A' && keypressed17 !='B' && keypressed17 !='C' && keypressed17 !='D' )

                      {

                        c2 = keypressed17;

                       lcd.setCursor(1, 1);

                       lcd.print(c2);

                       }



                     i1=(c1-48)*10;

                     i2=c2-48;

                     A_minute=i1+i2;

                    delay(500);

                     lcd.clear();

                      AlarmIsActive=1;

                      keypressed=NO_KEY;

             }

             if (keypressed == 'B')

             {

              lcd.clear();

              lcd.print("Alarm yok");

              AlarmIsActive=0;

              keypressed=NO_KEY;

              delay(500);

             }

             else {

              myRTC.updateTime();

              keypressed=NO_KEY;

             }

             


}



void ileri(){  // Robotun ileri yönde hareketi için fonksiyon tanımlıyoruz.

  digitalWrite(MotorR1, HIGH); // Sağ motorun ileri hareketi aktif
  digitalWrite(MotorR2, LOW); // Sağ motorun geri hareketi pasif
  analogWrite(MotorRE, 150); // Sağ motorun hızı 150

  digitalWrite(MotorL1, HIGH); // Sol motorun ileri hareketi aktif
  digitalWrite(MotorL2, LOW); // Sol motorun geri hareketi pasif
  analogWrite(MotorLE, 150); // Sol motorun hızı 150


}


void sag(){ // Robotun sağa dönme hareketi için fonksiyon tanımlıyoruz.

  digitalWrite(MotorR1, LOW); // Sağ motorun ileri hareketi aktif
  digitalWrite(MotorR2, HIGH); // Sağ motorun geri hareketi pasif
  analogWrite(MotorRE, 0); // Sağ motorun hızı 0 (Motor duruyor)

  digitalWrite(MotorL1, HIGH); // Sol motorun ileri hareketi aktif
  digitalWrite(MotorL2, LOW); // Sol motorun geri hareketi pasif
  analogWrite(MotorLE, 150); // Sol motorun hızı 150
  
  
}


void geri(){ // Robotun geri yönde hareketi için fonksiyon tanımlıyoruz.

  digitalWrite(MotorR1, LOW); // Sağ motorun ileri hareketi pasif
  digitalWrite(MotorR2, HIGH); // Sağ motorun geri hareketi aktif
  analogWrite(MotorRE, 150); // Sağ motorun hızı 150

  digitalWrite(MotorL1, LOW); // Sol motorun ileri hareketi pasif
  digitalWrite(MotorL2, HIGH); // Sol motorun geri hareketi aktif
  analogWrite(MotorLE, 150); // Sol motorun hızı 150
  
}
