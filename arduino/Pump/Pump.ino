/****
*
* Hana Pump
* 
* Author: Mezz / Fivefactorial
*/

// Pins for arduino motor shield
int dir = 12;
int pwm = 3;

// Time remaining in deciseconds (100 milliseconds)
int time = 0;

// Resets the arduino
void(* reset) (void) = 0;

void setTime(int);
void printRemainingTime();

void setup(){
  pinMode(dir, OUTPUT);
  pinMode(pwm, OUTPUT);
  
  Serial.begin(9600);
  while (!Serial);
  
  Serial.println("Welcome to Hana Pump");
  
  digitalWrite(dir, HIGH);
}

void loop(){
   if (time > 0) {
     time -= 1;
     digitalWrite(pwm, HIGH);
   } else {
     digitalWrite(pwm, LOW); 
   }
   delay(100);
}

void serialEvent() {
 char command = (char) Serial.read();
 
 if (command >= '0' && command <= '9') {
  setTime(command - '0');
 } else if (command == 'r' || command == 'R') {
  printRemainingTime();
 } else if (command == 'q') {
    reset();
 } else { // Unknown command
  Serial.println("Illegal command"); 
 }
}

void setTime(int minutes) {
    time = minutes * 10 * 60;
    char text[50];
    sprintf(text,"Set time to %d minutes", minutes);
    Serial.println(text);
}
  
void printRemainingTime() {
  if (time > 0) {
    int minutes = time / 10 / 60;
    int seconds = time / 10 % 60;
    
    char text[50];
    sprintf(text,"Remaining time: %dm %ds", minutes, seconds);
    Serial.println(text);
  } else {
    Serial.println("Stoped");
  }
}
