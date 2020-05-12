#define ir1 48 // in
#define ir2 46 //out


#include <LiquidCrystal.h>
#include <dht.h> 
#define dht_apin A0
 dht DHT;
         
int pirState = LOW;            
int val = 0;  
#include <Keypad.h>

#define Password_Length 4 

int inputPin = 7; 
char Data[Password_Length]; 

char Master[Password_Length] = "123"; 
byte data_count = 0, master_count = 0;
char customKey;
int state = LOW; 
int i=0; 
int a=0,b=0;
int count=0;


const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {31, 33, 35, 37};
byte colPins[COLS] = {39, 41, 43, 45};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

long c,pm=0;
int trigPin = 8;   
int echoPin = 9;   
float duration,cm;
char data = 0;
int j=0;
void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.print("lets go");
  pinMode(13, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
   pinMode(inputPin, INPUT);
   pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
}
void temp()
{
  lcd.print("temp= ");
    lcd.print(DHT.temperature);
    return;
  }
  void humidity()
  {
     DHT.read11(dht_apin);
    
    lcd.print("humidity = ");
    lcd.print(DHT.humidity);
  }
  void ultra()
  {
    digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
 
  
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  
  cm = (duration/2) / 29.1; 
  
  lcd.print(cm);
  lcd.print("cm");
  
  
  }
  void numpad()
  {
    lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Enter Password:");
   delay(1000);
   while(j<3){
   customKey = customKeypad.getKey();
  if (customKey){
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print(Data[data_count]); 
    data_count++;
    j++; 
    }

  if(data_count == Password_Length-1){
    lcd.clear();

    if(!strcmp(Data, Master)){
      lcd.print("Correct");
      delay(1000);
      }
    else{
      lcd.print("Incorrect");
      delay(1000);
      }
    
    lcd.clear();
    clearData();  
  }
  }
 }

 void pir()
 {
   if (val == HIGH)
  {          
   lcd.print("motion detected");
    }
    else {
    lcd.print("Motion ended!");
     } 
 }
void loop()
{j=0;
   if(a==0 && b==0 && digitalRead(ir1))
  {
    a=1;
    b=0;
  }
   if(a==1 && b==0 && digitalRead(ir2))
  {
    count++;
    a=0;
    b=0;
    delay(2000);
  }
  
  if(a==0 && b==0 && digitalRead(ir2))
  {
    a=0;
    b=1;
   // delay(2000);
  }
  if(a==0 && b==1 && digitalRead(ir1))
  {
    count--;
    //delay(5000);
    a=0;
    b=0;
  }
              
  c=millis();
  val = digitalRead(inputPin);  
  if(c-pm>2000)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    i=(i+1)%6;
    switch(i)
    {
      case 5:
      lcd.print("Persons:");
      lcd.setCursor(0,1);
      lcd.print(count);
      break;
      case 1:
       ultra();
      break;


       case 2:
      numpad();
 
       break;

       
       case 0:
       humidity();
       break;
     
       
       case 3:
    temp();
    break;

    
    case 4:
    pir();
 }
    pm=c;
  }
  
}
void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  return;
}
