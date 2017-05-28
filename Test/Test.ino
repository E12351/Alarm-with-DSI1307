#include <LowPower.h>
#include <EEPROM.h>
//Include the library code:
#include <LiquidCrystal.h>
#include <Wire.h>

#include "RTClib.h"

#define SERIAL_DEBUG

//Initialize the LCD library with the numbers of the interface pins
LiquidCrystal lcd(13,12,11,10,9,8);

volatile byte state = LOW;

int mainmenu = 1;

int currentV = 22 ;

int Year;
int Month;
int Date;
int Hour;
int Min;
int Sec;

RTC_DS1307 RTC;
//############################################################################
void setup (){
  //Initialize the RTC
  Wire.begin();
  RTC.begin();
  Serial.begin(9600);

  //Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  // Print a message to the LCD.
//  lcd.print("RTC TEST");

//  Add interupt pin
  attachInterrupt(digitalPinToInterrupt(2),  Aj_main, FALLING  );
  attachInterrupt(digitalPinToInterrupt(18), Aj_l,    FALLING  );
  attachInterrupt(digitalPinToInterrupt(19), Aj_r,    FALLING  );
  attachInterrupt(digitalPinToInterrupt(3),  cancel,    LOW  );

  //One second delay
  delay(1000);

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }else{
    Serial.println("RTC is running!");
  }
  
  int state = EEPROM.read(3);
  Serial.print("Alarm State :");
  Serial.println(state);

  if(state == 1){
    
  }else{
    EEPROM.write(0, 99);
    EEPROM.write(1, 99);
  }
  

//  EEPROM.write(0, 23);
//  EEPROM.write(1,27);
//  state = HIGH;
//  Serial.println(state);
  Serial.println(EEPROM.read(0));
  Serial.println(EEPROM.read(1));
//  RTC.adjust(DateTime(2016,5,26,9,20,12));
  //Add a command for setting the RTC values
//  cmdAdd("SetRTC", SetDateTime);  
}
//############################################################################
void loop (){
  DateTime now = RTC.now();
  Serial.print("Time Now : ");
  Serial.print(now.hour());
  Serial.print(" : ");
  Serial.println(now.minute());
  
  int A = EEPROM.read(0);
  int B = EEPROM.read(1);

  Serial.print("Alarm Time read ");
  Serial.print(A);
  Serial.print(" : ");
  Serial.println(B);

  Serial.print("A<=hours : ");
  Serial.print(A<=now.hour());
  Serial.print("  B<=Min : ");
  Serial.println(B<now.minute());
  
  if (A<=now.hour() && B<=now.minute() ){
    Serial.println( ":)" );
  }else{
    lcd.clear();
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
  //#############################################
  if(mainmenu == 1 ){
//    Serial.println("Time");
    time();
  }
  if(mainmenu == 2 ){
    Serial.println("Hours");
    lcd.clear();
    lcd.print("Time Settings");
    lcd.setCursor(0, 2); 
    lcd.print("Hour : ");
    Hour = currentV;
    if(currentV > 23 ){
      Hour = currentV % 24;
    }
//    EEPROM.write(0, Hour);
    lcd.print(Hour);
  }
  if(mainmenu == 3 ){
    Serial.println("Minuts");
    lcd.clear();
    lcd.print("Time Settings");
    lcd.setCursor(0, 2); 
    lcd.print("Min : ");
    lcd.print(currentV);
    Min = currentV;
//    EEPROM.write(1, Min);
  }
  if(mainmenu == 4 ){
    lcd.clear();
    lcd.print("Sure .. ?");
    lcd.setCursor(0, 2); 
    lcd.print("ok        cancel");
  }
  if(mainmenu == 5 ){
    Serial.println("Set");
    for(int i=0;i<3;i++){
      lcd.clear();
      lcd.print("-- Time Set --");
      lcd.setCursor(0, 2); 
      lcd.print("Time Iniziated ");
      lcd.print(i);
      delay(1000);
    }
//    mainmenu = 1;
    RTC.adjust(DateTime(2016,5,26,Hour,Min,00));
  }
  if(mainmenu == 6 ){
      Serial.println("Hours");
      lcd.clear();
      lcd.print("Alarm Settings");
      lcd.setCursor(0, 2); 
      lcd.print("Hour : ");
      Hour = currentV;
      if(currentV > 23 ){
        Hour = currentV % 24;
      }
      lcd.print(Hour);
  }
  if(mainmenu == 7 ){
    Serial.println("Minuts");
    lcd.clear();
    lcd.print("Alarm Settings");
    lcd.setCursor(0, 2); 
    lcd.print("Min : ");
    lcd.print(currentV);
    Min = currentV;
  }
  if(mainmenu == 8 ){
    lcd.clear();
    lcd.print("Sure .. ?");
    lcd.setCursor(0, 2); 
    lcd.print("ok        cancel");
  }
  if(mainmenu == 9 ){
    Serial.println("Set");
    for(int i=0;i<3;i++){
      lcd.clear();
      lcd.print("-- Time Set --");
      lcd.setCursor(0, 2); 
      lcd.print("Alarm Iniziated ");
      lcd.print(i);
      delay(1000);
      mainmenu = 1;
      state != state;
   }
   Serial.print("Alarm set ");
   Serial.print(Hour);
   Serial.print(" : ");
   Serial.println(Min);
   
   EEPROM.write(0, Hour);
   EEPROM.write(1, Min);
   EEPROM.write(3, 1 );
  }
  delay(500);
}
//############################################################################
void Aj_main(){
  mainmenu++;
  Serial.print("Interupt 1 : ");
  Serial.println(mainmenu);
  if(mainmenu == 10){
    mainmenu = 1;
  }
  delay(200);
}
//############################################################################
void Aj_l() {
  currentV++;
  if(currentV == 60){
    currentV = 0;
  }
  Serial.println(currentV);
  delay(200);
}
//############################################################################
void Aj_r() {
  currentV--;
  if(currentV == -1){
    currentV = 59;
  }
  Serial.println(currentV);
  delay(200);
}
//############################################################################
void cancel() {
  if(mainmenu == 4) mainmenu = 6;
  if(mainmenu == 8) mainmenu = 1;
//  delay(200);
}
//############################################################################
void time(){
    DateTime now = RTC.now();

    //Clear screen. Set the cursor to line 1
    //Print the date
    lcd.clear();
    
//    lcd.print(now.year(), DEC);
//    lcd.print('/');
//    lcd.print(now.month(), DEC);
//    lcd.print('/');
//    lcd.print(now.day(), DEC);
//    lcd.print(' ');
    
    lcd.print(" +#*-- Time --*#+");
    //Set the cursor to line 2
    //Print the time
    lcd.setCursor(0, 2);     

    lcd.print("    ");
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);    

//    #ifdef SERIAL_DEBUG
//      Serial.print(now.year());
//      Serial.print(now.year(), DEC);
//      Serial.print('/');
//      Serial.print(now.month(), DEC);
//      Serial.print('/');
//      Serial.print(now.day(), DEC);
//      Serial.print(' ');
//      Serial.print(now.hour(), DEC);
//      Serial.print(':');
//      Serial.print(now.minute(), DEC);
//      Serial.print(':');
//      Serial.print(now.second(), DEC);
//      Serial.println();
//    #endif
    
    //Delay one second
    delay(1000);
}
//############################################################################
// SetDate
// Example to show how to split the command and set the RTC
// Usage: At the command line, type
// SetRTC 2016 08 10 14 56 12
//
// The output should look like this:
// Arg 0: SetRTC
// Arg 1: 2016
// Arg 2: 08
// Arg 3: 10
// Arg 4: 14
// Arg 5: 56
// Arg 6: 12

void SetDateTime(int arg_cnt, char **args)
{
  int Year;
  int Month;
  int Date;
  int Hour;
  int Min;
  int Sec;
  
  String x = args[1];
  Year = x.toInt();
 
  x = args[2];
  Month = x.toInt(); 
  
  x = args[3];
  Date = x.toInt();
  
  x = args[4];
  Hour = x.toInt();
  x = args[5];
  Min = x.toInt();
  x = args[6];
  Sec = x.toInt();
  
//  #ifdef SERIAL_DEBUG
//    Serial.print("Year is ");
//    Serial.println(Year);
//    Serial.print("Month is ");
//    Serial.println(Month);
//    Serial.print("Date is ");
//    Serial.println(Date);
//    Serial.print("Hour is ");
//    Serial.println(Hour);
//    Serial.print("Min is ");
//    Serial.println(Min);
//    Serial.print("Sec is ");
//    Serial.println(Sec);
//  #endif
  
  // The below line sets the RTC with date & time
  RTC.adjust(DateTime(Year, Month, Date, Hour, Min, Sec));
}
//############################################################################
