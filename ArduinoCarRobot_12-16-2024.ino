#include <Servo.h>

#define Ech 12 
#define Trig 13

// Motor control pins
int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 7;

// Speed control pins
int SpeedA = 5;
int SpeedB = 6;

// Sensor pins (analog)
const int left_sensor = A0;
const int right_sensor = A4;
const int mid_left = A1;
const int mid_right = A3;
const int middle = A2;

float duration, distance;

// Turning functions with speed set to 140
void RR() {
  analogWrite(SpeedA, 125);
  analogWrite(SpeedB, 125);
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  delay(50);
}

void RSR() {
  analogWrite(SpeedA, 120);
  analogWrite(SpeedB, 120);
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  delay(50);
}

void RL() {
  analogWrite(SpeedB, 125);
  analogWrite(SpeedA, 125);
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  delay(50);
}

void RSL() {
  analogWrite(SpeedB, 120);
  analogWrite(SpeedA, 120);
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  delay(50);
}


void setup() {
  
  pinMode(Trig, OUTPUT);
  pinMode(Ech, INPUT);

  Serial.begin(9600);

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  pinMode(left_sensor, INPUT);
  pinMode(right_sensor, INPUT);
  pinMode(mid_left, INPUT);
  pinMode(mid_right, INPUT);
  pinMode(middle, INPUT);

  pinMode(SpeedA, OUTPUT);
  pinMode(SpeedB, OUTPUT);

  analogWrite(SpeedA, 120);  // Forward speed set to 135
  analogWrite(SpeedB, 120);  // Forward speed set to 135
}

void loop() {

  analogWrite(SpeedA, 125);
  analogWrite(SpeedB, 125);

  int L = digitalRead(left_sensor);
  int R = digitalRead(right_sensor);
  int lm = digitalRead(mid_left);
  int rm = digitalRead(mid_right);
  int M = digitalRead(middle);

  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  duration = pulseIn(Ech, HIGH);
  distance = (duration * 0.0343) / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(100);

  if(distance >= 11){
  if ((L == 1) && (R == 1) && (lm == 1) && (rm == 1)) {
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
  } 
  else if ((lm == 0) && (rm == 0) && (L == 0) && (R == 0)) {
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);
  } 
  else if ((lm == 0) && (L == 1) && (rm == 1) && (R == 1)) {
    RSR(); //
  } 
  else if ((lm == 1) && (L == 1) && (rm == 0) && (R == 1)) {
    RSL(); //
  } 
  else if (((lm == 1) || (L == 0)) && (rm == 1) && (R == 1)) {
    RR();
     delay(40);//
  } 
  else if ((lm == 1) && (L == 1) && ((rm == 1) || (R == 0))) {
    RL();
    delay(40); //
  }
  }
}
