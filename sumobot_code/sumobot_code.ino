#include <Servo.h>

Servo wheelL;
Servo wheelR;

int fL = 10; int fR = 11;
int bL = 12; int bR = 13; 

//ultrasonic PIN DECLARATION

const int trigPin=6;    //setting the trigger and echo pins
const int echoPin=7;

/////////////////////////////////////

void setup() {
  Serial.begin(9600); 
  wheelL.attach(2);
  wheelR.attach(3);

  //IR SENSOR INPUT SETUP
  
  pinMode(fL, INPUT); //front left
  pinMode(fR, INPUT); //front right
  pinMode(bL, INPUT); //back left
  pinMode(bR, INPUT); //back right

  //ULTRASONIC PIN SETUP

  pinMode(trigPin,OUTPUT);  //this sets our i/o
  pinMode(echoPin, INPUT);  
 
}

void loop() {//
  
  //searching...

    if(ultraSoundAVG()<30.0){
      
      Serial.println("ATTACK!! ");
      
      forward(1000);  //forward for 1s
      
    }
  
    else{ 
      
      Serial.println("KEEP SPINNING");
      deg30CW();
  
      
    }

  
  //ultraSoundAVG();

  //Serial.println("TURNING 90 DEG"); 
  //deg90CW();  //a close approximation to a hairpin turn CLOCKWISE
  /*wheelL.write(130); //we will write the approximate stopping values for L/R motors, then delay for "t" ms
  wheelR.write(94);
  */
  stop(1);
  
    
  
  /*if(digitalRead(fL) == HIGH && digitalRead(fR) == HIGH) {
    //reverse(1500); 
    return; //goes back to top of loop and begins searching
  }

  if(digitalRead(bL) == HIGH && digitalRead(bR) == HIGH) {
    forward(1500); 
    return; //goes back to top of loop and begins searching again
  }
  */
  

 

  
  
 
}
void forward(int t) {
  wheelL.write(180);
  wheelR.write(50);
  delay(t); 
  
}

void reverse(int t) {
  wheelL.write(80);
  wheelR.write(150);
  delay(t); 
}

void stop(int t) {
  wheelL.write(130); //we will write the approximate stopping values for L/R motors, then delay for "t" ms
  wheelR.write(94);
  delay(t); 
  return; 
}

void deg90CW() {
  wheelL.write(180);
  wheelR.write(150);
  delay(1300); 
  return;
}

void deg30CW(){
  wheelL.write(180);
  wheelR.write(150);
  delay(440); 
  return;
}

void search() {
  
 
    
  
  
}

//////////////////////////////////////////////////////

double ultraSound(){    //our ultrasonic method!!
  int duration;
  double distance;
  //needs to loop CONSTANTLY 
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);    //this bit of code sends a 10us pulse to be reflected back
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration= pulseIn(echoPin, HIGH);
  distance=duration*0.034/2; //this is a result of a derivation! Look it up if needed

  //Serial.print("Current distance to nearest object: ");
  //Serial.println(distance); //prints the distance to the terminal

  return distance;

}  

//////////////////////////////////////////////////////

double ultraSoundAVG(){ //this method is for more precision
  
  double avgDistance=0;
  
  for(int i=0;i<5;i++){
    avgDistance+=ultraSound();  //totals and then will avg. 
  }

  avgDistance=avgDistance/5;
  
  //Serial.print("AVG over 5 tries: ");
  //Serial.println(avgDistance);
  
  return avgDistance;
}

//////////////////////////////////////////////////////
