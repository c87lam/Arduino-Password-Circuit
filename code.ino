//Include keypad and LCD library
#include <Keypad.h>
#include <LiquidCrystal.h>

//Initialize pins for LCD and keypad
LiquidCrystal lcd(8,9,10,11,12,13);
const byte ROWS = 4;
const byte COLS = 4;

//Initialize pins for the LEDs
int greenLED = A2;
int redLED = A1;
int yellowLED = A0;

//Define password
String password = "14A3B";
String code;

//Attempts
int attempts = 0;
int maxAttempts = 3;

//Custom character for lock
byte lock[] = {
  B00000,
  B01110,
  B10001,
  B10001,
  B11111,
  B11011,
  B11011,
  B11111
};

//Custom character for unlock
byte unlock[] = {
  B00000,
  B01110,
  B00001,
  B00001,
  B11111,
  B11011,
  B11011,
  B11111
};

//Define the symbols for the keypad
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

//Assign pins for rows and columns for keypad
byte rowPins[ROWS] = {A5,A4,2,3}; 
byte colPins[COLS] = {4,5,6,7}; 

//Initialize keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup(){
  
  //Set the LCD display
  lcd.begin(16,2);
  lcd.print("Enter Password");
  lcd.createChar(0,lock);
  lcd.createChar(1,unlock);
  lcd.home();
  lcd.setCursor(0,1);
  
  //Assign the LED pins as outputs
  pinMode(greenLED,OUTPUT);
  pinMode(redLED,OUTPUT);
  pinMode(yellowLED,OUTPUT);
  
  digitalWrite(yellowLED,LOW);
 
}
  
void loop(){
  
  //Initialize key
  char key = keypad.getKey();
  
  //Displays '*' on LCD if keypad is pressed
  if (key != NO_KEY){
    lcd.print("*");
  }
  
  //Adds the respective key to code
  if (key == '1'||key == '2'||key == '3'||key == '4'||key == '5'||key == '6'||
      key == '7'||key == '8'||key == '9'||key == '0'||key == 'A'||key == 'B'
      ||key == 'C'||key == 'D'){
    
    code = code + key;
    
  }
  
  //Resets screen if '*' is pressed
  if(key == '*'){
    setup();
    
  }
  
  //If # is pressed, verifies if password is entered correctly
  if(key == '#'){
     if (password == code){
       correct();
     } else {
       incorrect();
     }
  }
}

void correct(){
  lcd.clear();  
  lcd.print("Valid Password");
  lcd.setCursor(7,1);
  lcd.write((byte)1);
  digitalWrite(greenLED,HIGH);     
  delay(3000);
  digitalWrite(greenLED,LOW);
  code = "";
  lcd.clear();
  setup();
}

void incorrect(){
  
  attempts++;
  
  if (attempts > maxAttempts){
    lcd.clear();
    lcd.print("Locked");
    lcd.setCursor(7,0);
    lcd.write((byte)0);
    digitalWrite(redLED,LOW);
    digitalWrite(yellowLED,HIGH);
  } else {
    lcd.clear();
    lcd.print("Invalid Password");
    lcd.setCursor(0,1);
    lcd.print("Max Attempt:3");
    digitalWrite(redLED,HIGH);
    delay(3000);
    digitalWrite(redLED,LOW);
    digitalWrite(yellowLED,LOW);
    code = "";
    lcd.clear();
    setup();
  }
}
