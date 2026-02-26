const int btn = 7; //btn pin
const int buzz = 8; //buzz pin
const int pot = A1; // potentiometer pin
const int motorIn1 = 5; // motor pin
const int motorIn2 = 6; // motor pin
const int led = 4; //led pin
int input_pot_servo; //values for pot according to set range for servo
int input_pot_motor; //values for pot according to set range for motor
int input_pot_led; //how frequent led blinks (ms);
const int EnA = 3; // Enable pin for motor

// below for btn debounce
bool last_btn_state = LOW; // previous btn state
bool btn_state = LOW; // current btn state
unsigned long btn_deb = 100; // delay for debounce
unsigned long last_btn_deb = 0; // last debounce time
bool btn_toggle = false; // controls the on and off components

#include <Servo.h>
Servo myservo;

void setup() {
  pinMode(btn, INPUT);
  pinMode(buzz, OUTPUT);
  pinMode(pot, INPUT);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(EnA, OUTPUT);
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, HIGH);
  myservo.attach(9); // servo motor pin
  Serial.begin(9600);
}

void btn_press() {
  if (millis() - last_btn_deb >= btn_deb) // wait for debounce time
  {
    btn_state = digitalRead(btn); // read btn state
    
    if (btn_state != last_btn_state) // check btn state
    {
      last_btn_deb = millis(); // reset timer
      last_btn_state = btn_state; // update for both states to be the same
      
      if (btn_state == HIGH) // if button pressed
      {
        btn_toggle = !btn_toggle; // toggle on/off
      }
    }
  }
}

void pot_func(){
  Serial.println(input_pot_motor);
  if (btn_toggle)
  {
    int pot_val = analogRead(pot);
    input_pot_motor = map(pot_val, 0, 1023, 0, 255);
    input_pot_servo = map(pot_val, 0, 1023, 0, 90);
    input_pot_led = map(pot_val, 0, 1023, 0, 1000);
  } 
  else{
    input_pot_motor = 0;
    input_pot_servo = 0;
  }
}

void btn_buzz_servo() { // action upon btn click
  if (btn_toggle) 
  {
    tone(buzz, 1000);
    myservo.write(input_pot_servo);
  } 
  else 
  {
    noTone(buzz);
    myservo.write(0);
  }
}

void motor_control(){
  if (btn_toggle) {
    analogWrite(EnA, input_pot_motor);
  }
  else{
    analogWrite(EnA, 0);
  }
  
}

void led_control() {
  if (btn_toggle) {
    digitalWrite(led, HIGH);
  } else{
  	digitalWrite(led, LOW);
  }
}
void loop() {
  btn_press();
  pot_func();
  btn_buzz_servo();
  motor_control();
  led_control();
}
