#include <PID_v1.h>
#include <Wire.h>
#include <ZumoShield.h>
double Setpoint, Input, Output;
PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);
int trigPin1 = 9;
int echoPin1 = 10;
int trigPin2 = 6;
int echoPin2 = 5;
int distance1;
int distance2;
int finalDistance = distance2 - distance1;
int duration1;
int duration2;
ZumoMotors motors;
int speed = 100;
int limits = 20;
int distanceToTarget; //distancia a la qe se activa la trampa
int activeTrap; //0-> activada, 1-> desactivada


void setup() {
  pinMode(9, OUTPUT); // Sets the trigPin as an Output
  pinMode(10, INPUT); // Sets the echoPin as an Input
  pinMode(11, OUTPUT); // Sets the trigPin as an Output
  pinMode(12, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication

    //PID
  Input = finalDistance;
  Setpoint = 0;
  
  //enciende el control PID
  myPID.SetOutputLimits(-limits,limits);
  myPID.SetMode(AUTOMATIC);
}
void loop() {
  distance1 = ultrasonido(9, 10);
  Serial.print("Distance 1: ");
  Serial.println(distance1);
  distance2 = ultrasonido(11, 12);
  Serial.print("Distance 2: ");
  Serial.println(distance2);

  
  if (distance1 < $maxdistace){ //definir distancia maxima -> objetivo en la
    Input = finalDistance;
    myPID.Compute();
    motors.setSpeed(Speed + Output, Speed - Output); //Debiera avanzar por default a velocidad Speed
  }
  else{
    motors.setSpeed(limits,-limits); //girar un poco
  }
  if (distance <= distanceToTarget && activeTrap == 1){
    itsATrap();
  }
  else if(distance > distanceToTarget && activeTrap == 0){
    deactivateTrap();
  }


}

long ultrasonido(int trigPin , int echoPin) {
  long duration;
  int distance;
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  return distance;
}

void itsATrap(){
  Serial.println("Subir los brazos");
  activeTrap = 0;
}

void deactivateTrap(){
  Serial.println("Bajar los brazos");
  activeTrap = 1;
}