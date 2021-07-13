

int dir = 12;
int pwm = 3;

int time = 0;

void(* reset) (void) = 0;

void setup(){
  pinMode(dir, OUTPUT);
  pinMode(pwm, OUTPUT);
  
  Serial.begin(9600);
  while (!Serial);
  
  Serial.println("Welcome to Pump master 5000!");
  
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
 
 if (command >= '0' && command <= '9') { // Set pump time.
  time = (command - '0') * 10 * 60;

 } else if (command == 'r' || command == 'R') { // Check remaining time
  if (time > 0) {
    char text[50];
    sprintf(text,"Remaining time: %ds", time / 10);
    Serial.println(text);
  } else {
    Serial.println("Stoped");
  }

 } else if (command == 'q') {
    reset();
 } else { // Unknown command
  Serial.println("Illegal command"); 
 }

}
