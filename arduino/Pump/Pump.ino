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

const int bufferSize = 50;
char buffer[bufferSize];
int pointer = 0;

// Resets the arduino
void(* reset) (void) = 0;

void resetBuffer();
void handleCommand();
int toNumer();

void setTime(int);
void printRemainingTime();

void setup(){
  pinMode(dir, OUTPUT);
  pinMode(pwm, OUTPUT);
  
  resetBuffer();
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
  while (Serial.available()) {
    if (pointer == bufferSize-1) {
      resetBuffer();
      Serial.println("To long command. Buffer overflow!");
    }    
    char next = (char) Serial.read();
    if (next == '\n') {
      handleCommand();
      resetBuffer();
    } else {
     buffer[pointer++] = next;
    }
  }
}

void resetBuffer() {
  pointer = 0;
  for (int x = 0; x < bufferSize; x++) {
    buffer[x] = 0;
  }
}

void handleCommand() {
  int number = toNumber();

  if (number >= 0) {
    setTime(number) ;
  } else {
    String command = buffer;
    if (command.equals("?")) {
      printRemainingTime();
    } else if (command.equalsIgnoreCase("reset")) {
      reset(); 
    } else if (command.equalsIgnoreCase("stop")) {
      setTime(0);
    } else if (pointer != 0) {
      Serial.println("Illegal command!");
    }
  }

}

int toNumber() {
  if (pointer == 0) return -2; // Empty string
  if (pointer > 3) return -3; // String is too long to parse
  
  int number = 0;
  for (int x = 0; x < pointer; x++) {
    if (buffer[x] >= '0' && buffer[x] <= '9') {
      number = number * 10 + buffer[x] - '0';    
    } else {
      return -1; // Contains non numeric character
    }
  }  

  return number; // Parsed number in [0, 999]
}

void setTime(int seconds) {
    time = seconds * 10;
    
    if (seconds == 0) {
      Serial.println("Stopping pump!");
    } else {
      int minutes = seconds / 60;
      int secondsRemaining = seconds % 60;
    
      char text[50];
      sprintf(text,"New time: %dm %ds", minutes, secondsRemaining);
      Serial.println(text);
    }
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
