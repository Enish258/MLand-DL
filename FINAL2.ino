#include <Servo.h>
#include<LiquidCrystal.h>
#include "dht.h"
//#include <IRremote.h>      //including infrared remote header file
#include "Wire.h"
#include <Password.h>
#include <Keypad.h>
//#include "Wire.h"
//#include "I2Cdev.h"
//#include "MPU6050.h"
//#include "math.h"
#define IR_out A5
#define IR_in A9

//MPU6050 mpu;

int16_t accY, accZ; float accAngle;
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns

#define dht_pin A1 // Analog Pin sensor is connected to
# define bulb 42
# define fan 44

void person_out();
void person_in();


char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'}, 
  {'*', '0', '#', 'D'}
};
//int pirpin = A0;
int gate_state = 0;
int personNo = 0;
int fan_state = 0, bulb_state = 0;
int sensor1;
int sensor2;
int servoPin = 8;
int RECV_PIN = 9;        // the pin where you connect the output pin of IR sensor
int a[4];
int k = 0, j = 0, count = 0, s = 0;
int g = 0;
int h = 0;
int value1 = 0;
int preirval2 = 0;
int fire = 0;
char pass[] = {'6', '7', '8', '9'};
char data;

String date = "9-03-2019";
String Time = "9:45";
byte rowPins[ROWS] = { 30, 31, 32, 33 };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.

byte colPins[COLS] = { 34, 35, 36, 37 };

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//IRrecv irrecv(RECV_PIN);
LiquidCrystal lcd(12, 11, 6, 4, 3, 2);
Servo Servo1;
//decode_results results;
dht DHT;

int occurtime = 0, currtime = 0, preirval = 0;
int i = 0;
int urgentdrip = 0;

void print_lcd(void);
int drippage1(void);
int drippage2(void);
int drippage3(void);
int drippage10(void);
int drippage11(void);
void password(void);
void check(void);
void thief(void);
void closedoor();
void openDoor();
void remote();
void earthquake(void);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(115200);
  //irrecv.enableIRIn();
  Servo1.attach(servoPin);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
  keypad.setDebounceTime(250);
  pinMode(IR_out, INPUT);
  pinMode(IR_in, INPUT);
  pinMode(bulb, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(dht_pin, INPUT);
  //mpu.initialize();
  lcd.begin(16, 2);
  delay(1000);
}

int z = 0;


void loop()
{
  keypad.getKey();
  print_lcd();
  //thief();
  aag_lagi();
  serial_read();
  control();
  password();
  //earthquake();
 person_in();
  
  
  person_out();
}

void control()
{
  digitalWrite(bulb, bulb_state);
  digitalWrite(fan, fan_state);
  if (gate_state)
    openDoor();
  else
    closeDoor();
}

void serial_read()
{
  if (Serial.available() || Serial1.available() || Serial2.available())
  {
    String data = ""; 
    if (Serial.available())
      data = Serial.readStringUntil('\n');
    else if (Serial1.available())
      data = Serial1.readStringUntil('\n');
    else if (Serial2.available())
      data = Serial2.readStringUntil('\n');

    if (data.substring(0, 1) == "t")
    {
      date = data.substring(1, 10);
      Time = data.substring(11, 14);
      return;
    }
    Serial.println(data);
    lcd.clear();
    occurtime = millis();
    if (data.charAt(0)== 'l' && data.charAt(7)== 'n')
    {
      Serial.println('B');
      Serial1.println('B');
      Serial2.println('B');
      bulb_state = 1;
      lcd.print("Bulb is turned");
      lcd.setCursor(0, 1);
      lcd.print("on");
    }
    else if (data.charAt(0)== 'l' && data.charAt(7)== 'f')
    {
      Serial.println('b');
      Serial1.println('b');
      Serial2.println('b');
      bulb_state = 0;
      lcd.print("Bulb is turned");
      lcd.setCursor(0, 1);
      lcd.print("off");
    }
    else if (data.charAt(0)== 'f' && data.charAt(5)== 'n')
    {
      Serial.println('F');
      Serial1.println('F');
      Serial2.println('F');
      fan_state = 1;
      lcd.print("bulb2 is turned on");
    }
    else if (data.charAt(0)== 'f' && data.charAt(5)== 'f')
    {
      Serial.println('f');
      Serial1.println('f');
      Serial2.println('f');
      fan_state = 0;
      lcd.print("bulb2 is turn off");
    }
    else if (data.charAt(0)== 'o')
    {
      Serial.println('d');
      Serial1.println('d');
      Serial2.println('d');
      gate_state = 1;
      lcd.print("Door is opened");
    }
    else if (data.charAt(0)== 'c')
    {
      Serial.println('D');
      Serial1.println('D');
      Serial2.println('D');
      gate_state = 0;
      lcd.print("Door is closed");
    }
  }
}

void print_lcd()
{
  currtime = millis();
  if ((currtime - occurtime) > 2000)
  {
    occurtime = millis();
    switch (i) {
      case 0: drippage1(); break;
      case 1: drippage2(); break;
      case 2: drippage3(); break;
      case 3: drippage4(); break;
      case 4: drippage5();break;
    }
  }
}

int drippage1() {
  lcd.clear();
  lcd.print("date:");
  lcd.print(date);
  lcd.setCursor(0, 1);
  lcd.print("time:");
  lcd.print(Time);
  i = (i + 1) % 5;
}

int drippage2() {
  DHT.read11(dht_pin);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TEMP:");
  lcd.print(DHT.temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity=");
  lcd.print(DHT.humidity);
  lcd.print("%  ");
  i = (i + 1) % 5;
}

int drippage3()
{
  lcd.clear();
  lcd.print("bulb:");
  lcd.print(bulb_state);
  lcd.setCursor(8, 0);
  lcd.print("bulb2:");
  lcd.print(fan_state);
  lcd.setCursor(0, 1);
  lcd.print("door:");
  lcd.print(gate_state);
  i = (i + 1) % 5;
}

int drippage4()
{
  int v = analogRead(A8);
  v = map(v, 1023, 0, 0, 100);
  lcd.clear();
  lcd.print("MOISTURE: ");
  lcd.setCursor(0, 1);
  if (v < 0)
    lcd.print("0%");
  else
  {
    lcd.print(v);
    lcd.print("%");
  }
  i = (i + 1) % 5;
}
int drippage5()
  {
  lcd.clear();
  lcd.print("no. of persons:");
  lcd.setCursor(0, 1);
  lcd.print(personNo);
  i = (i + 1) % 5;
  }



void aag_lagi()
{
  DHT.read11(dht_pin);
  if (DHT.temperature > 50)
  {
    fire++;
  }
  else
    fire = 0;
  if (fire >  20)
  {
    lcd.clear();
    lcd.print("AAG LAGI");
    gate_state = 1;
    openDoor();
    occurtime = millis();
    Serial.println('A');
    Serial1.println('A');
    Serial2.println('A');
  }
}

void keypadEvent(KeypadEvent ekey)
{
  switch (keypad.getState())
  {
    case PRESSED:
      Serial.println(ekey);
      if (ekey == 'A')
      {
        fan_state = !fan_state;
        lcd.clear();
        occurtime = millis();
        if (fan_state)
        {
          lcd.print("bulb 2 is on");
          Serial.println('F');
          Serial1.println('F');
          Serial2.println('F');
        }
        else
        {
          lcd.print("bulb 2 is off");
          Serial.println('f');
          Serial1.println('f');
          Serial2.println('f');
        }
        return;
      }
      else if (ekey == 'B')
      {
        bulb_state = !bulb_state;
        lcd.clear();
        occurtime = millis();
        if (bulb_state)
        {
          lcd.print("bulb is turn on");
          Serial.println('B');
          Serial1.println('B');
          Serial2.println('B');
        }
        else
        {
          lcd.print("bulb is turn off");
          Serial.println('b');
          Serial1.println('b');
          Serial2.println('b');
        }
        return;
      }
    
      a[k] = ekey;
      k++;
      lcd.clear();
      for (int h = 0; h < k; h++)
        lcd.print('*');
      occurtime = millis();
  }
}

void password()
{
  if (k == 4)
  {
    check();
  }
}

void check()
{
  k = 0;
  count = 0;
  for (j = 0; j <= 3; j++)
  {
    if (a[j] == pass[j]) {
      count++;
      Serial.println(count);}
  }

 
  if (count == 4)
  {
    lcd.clear();
    lcd.print("Access approved");
    Serial.println('d');
    Serial1.println('d');
    Serial2.println('d');
    openDoor();
    occurtime = millis();
    i = (i + 1) % 4;
  }
  else if (count < 4)
  {
    lcd.clear();
    lcd.print("Access denied");
    preirval = 0;
    closeDoor();
    occurtime = millis();
    i = (i + 1) % 4;
  }
}



void openDoor()
{
  Servo1.write(80);
  delay(100);
  gate_state=1;
}
void closeDoor()
{
  // Make servo go to 90 degrees
  Servo1.write(170);
  //preirval = 0;
  //preirval2 = 0;
  gate_state=0;
  delay(100);
}

int drippage11() {
  lcd.clear();
  person_out();
}


/*void thief()
{
  if (personNo <= 0 && digitalRead(pirpin))
  {
    lcd.clear();
    lcd.print("ALERT");
    occurtime = millis();
    Serial.println('T');
    Serial1.println('T');
     Serial2.println('T');
  }
}*/


/*void earthquake()
  {
  accZ = mpu.getAccelerationZ();
  accY = mpu.getAccelerationY();
  accAngle = atan2(accY, accZ)*RAD_TO_DEG;
  if(isnan(accAngle));
  else
  {
  if(accAngle>20 || accAngle<-20)
  lcd.print("ALERT Earthquake");
  Serial.println("Earthquake");
  }
  occurtime=millis();
  }*/



void person_out()
{
  sensor1 = analogRead(IR_out);
  sensor2 = analogRead(IR_in);

  if (sensor2 >= 500)
  {

    Serial.println("Gate is open");
    lcd.clear();  
    lcd.print("Gate is open");
    openDoor(); 
    int j = 0;
    while (j < 5000)
    {
      sensor1 = analogRead(IR_out);
      if (sensor1 >=500)
      {
        personNo--;
       
        lcd.clear();
        lcd.print("Total person in");
        lcd.setCursor(0, 1); 
        lcd.print("home :");  
        lcd.print(personNo);
        closeDoor();                                                             
        Serial.print("Total person in home");
        Serial.println(personNo);
        delay(1000);
        break;
      }
      else if (j > 4998)
      {
        Serial.println("Gate is closed");
        lcd.clear();
        lcd.print("Gate is closed");
        closeDoor();       
      }
      delay(1);
      j++;
    }
  }
}


void person_in()
{
  sensor1 = analogRead(IR_out);
  sensor2 = analogRead(IR_in);

  if (sensor1>=500)
  {   
    int j = 0;
    while (j < 5000)
    {
      sensor2 = analogRead(IR_in);

      if (sensor2 >= 500)
      {
        personNo++;
        closeDoor();
        Serial.print("Total person in home =");
        Serial.println(personNo);
        lcd.clear();  lcd.print("Total person in");  
        lcd.setCursor(0, 1);  
        lcd.print("home :"); 
        lcd.print(personNo);
        delay(2000);
        break;
      }
      else if (j > 4998)
      {
        Serial.println("Gate is closed");
        closeDoor();
        lcd.clear();   
        lcd.print("Gate is closed");
        break;
      }
      delay(1);
      j++;
    }
  }
}
