//left motor
#define IN1 6
#define IN2 9
//right motor
#define IN3 10
#define IN4 11
//IR sensor
#define IRsensor 2
int val = 0;
//ultrasonic sensor
#define trig 8
#define echo 7
float duration = 0.0;
float distance = 0.0;

void setup() {
  //left motor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  //right motor
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  //IR sensor
  pinMode(IRsensor, INPUT);
  //ultra sonic sensor
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  //just need in setup
  Serial.begin(9600);
}

void forwardAnalog(int speed){
  //left motor
  analogWrite(IN1, speed);
  analogWrite(IN2, 0);
  //right motor
  analogWrite(IN3, speed);
  analogWrite(IN4, 0);
}

void backwardAnalog(int speed){
  //left motor
  analogWrite(IN1, 0);
  analogWrite(IN2, speed);
  //right motor
  analogWrite(IN3, 0);
  analogWrite(IN4, speed);
}

void turnLeft(int speed){
  //left motor
  analogWrite(IN1, 0);
  analogWrite(IN2, speed);
  //right motor
  analogWrite(IN3, speed);
  analogWrite(IN4, 0);
}

void turnRight(int speed){
  //left motor
  analogWrite(IN1, speed);
  analogWrite(IN2, 0);
  //right motor
  analogWrite(IN3, 0);
  analogWrite(IN4, speed);
}

void stopMotor(){
  //left motor
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  //right motor
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}

void calc(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH); //sending out frequency for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH); //equals to the input of the echo while it is on (it turns it on and measures) (amount of time the sent out frequency took to come back to the ultra sonic sensor)
  distance = (duration / 2) * 0.0343; //duration is going and coming back so we only want distane of one travel so we divide by two to get time it takes to reach and then multiply by speed factor of the waves.

  val = digitalRead(IRsensor);

  Serial.println(distance); //don't need (just to show us what is happening in serial monitor) 
}

/*void avoidBlackLine(){
  long startTime = millis();
  long durationIR = (1000);
  while (millis() < startTime + durationIR) {
    backwardAnalog(200);
  }
  turnLeft(255);//can be right or left
  delay(1500); //might have to adjust to see it do a 180 degree turn but not exact
}*/

void movement(){
  if (distance < 15 && distance > 1){ //distance is in cm
    //forward movement to attack the bots head on
    forwardAnalog(255);
    delay(100);
  }
  else if (val == 1) { //if crossing the border
  //this one should e higher priority (make it the if)
    stopMotor();
    delay(100);
    backwardAnalog(255);
    delay(1000);
    stopMotor();
    delay(200);
    turnLeft(255); //can be right or left
    delay(1500); //might have to adjust to see it do a 180 degree turn or close to it
  }
  else {
    //make it so it is just spinning to detect other robots
    forwardAnalog(200); //our standard movement of choice
    delay(100);
  }
}

void loop() {
  calc();
  movement();
}