//Gina Gerace, 664765515, ggerac3
//Lab 6: Display Date/Time on LCD
//This code should use the serial monitor to get input of date and time from user.
//  The date and time should then be displayed on the 16x2 display.
//I assumed that the user would input date and time in the correct format.
//I used the arduino serial communication and LCD screen tutorials as reference.


#include <Time.h>
#include <TimeLib.h>
#include <LiquidCrystal.h>
int Month, Day, Year, Hour, Minute, Second = -1;
String input;
bool validDate = false;
bool validTime = false;
String temp;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//returns true if x is in the range (inclusive), false otherwise
bool inRange(int x, int low, int high){
  if(x>=low && x<=high)
    return true;
  return false;
}

void setup() {
  // open the serial port at 9600 bps:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  Serial.println("Please enter the date(mm/dd/yyyy) and time(hh:mm:ss)");
}

void loop() {
  lcd.setCursor(0, 0); // top left

  if(!validDate || !validTime){
    // send data only when you receive data:
    if (Serial.available() > 0) {
      // read in the user input
      Month = Serial.parseInt();
      Day = Serial.parseInt();
      Year = Serial.parseInt();
      Hour = Serial.parseInt();
      Minute = Serial.parseInt();
      Second = Serial.parseInt();
      
      // see if user input a valid date
      validDate = (inRange(Month,1,12) && inRange(Day,1,31) && inRange(Year,1,2019));
      if(!validDate){
        lcd.print("invlaid date!");
        delay(1000);
        lcd.clear();
      }
      validTime = (inRange(Hour,0,23) && inRange(Minute,0,59) && inRange(Second,0,59));
      if(!validTime){
        lcd.print("invlaid time!");
        delay(1000);
        lcd.clear();
      }
      if(validTime && validDate)
        setTime(Hour,Minute,Second,Day,Month,Year);
    }
  }

  else{
    //print time to lcd
    lcd.setCursor(0, 0);                             // top left
    lcd.print(month());  lcd.print('/');
    lcd.print(day());    lcd.print('/');
    lcd.print(year());  
    lcd.setCursor(0, 1);                             // bottom left
    lcd.print(hour());    lcd.print(':');
    lcd.print(minute());  lcd.print(':');
    lcd.print(second()); 
  }
}
