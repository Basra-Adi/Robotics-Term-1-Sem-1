const int btn = 7;
const int buzz = 8;
const int pot = A1;

#include <Servo.h>
Servo myservo;

//btn debounce
const int btn_deb_time = 100;
unsigned long last_btn_deb;
byte last_btn_state = LOW;
byte btn_state = LOW;
bool btn_toggle = false;

// pot input
int input_pot = 0;



void setup() {
  pinMode(btn, INPUT);
  pinMode(buzz, OUTPUT);
  pinMode(pot, INPUT);
  myservo.attach(9);
  Serial.begin(9600);
}

void btn_press() {
  if (millis() - last_btn_deb >= btn_deb_time){
    btn_state = digitalRead(btn);

    if (btn_state != last_btn_state) {
      last_btn_deb = millis();
      last_btn_state = btn_state;
      
      if (btn_state == HIGH){
        btn_toggle = !btn_toggle;
      }
    }
  }
}

void pot_func() {
  if (btn_toggle) {
    int pot_val = analogRead(pot);
    input_pot = map(pot_val, 0, 1023, 0, 90);
    Serial.println(input_pot);
  }
}

void servo_buzz() {
  if (btn_toggle) {
    tone(buzz, 1000);
  }
  else{
    noTone(buzz);
  }
  if (btn_toggle){
    myservo.write(input_pot);
  }
  else{
    myservo.write(0);
  }
}

void motor_control() {
  
}

void loop() {
  btn_press();
  servo_buzz();
  pot_func();
}
