/* UNIVERSIDAD ADOLFO IBAÑEZ
    Robótica TICS 251
    Miguel Carrasco miguel.carrasco@uai.cl
    version 1.0  02-04-2018
*/

#include <Wire.h>
#include <ZumoShield.h>
#include <PID_v1.h>
#include <Pixy.h>

#define SPEED           130
#define TURN_BASE_SPEED 100
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);


//camera parameters
int width = 320;
int height = 240;

Pixy pixy;


//PID variables
double SetpointPan, InputPan, OutputPan;
PID myPID_Pan(&InputPan, &OutputPan, &SetpointPan, 0.45, 0.5, 0.001, DIRECT);

int index, x, y;
int posX = 1500;


void setup() {

  Serial.begin(9600);
  Serial.println("starting Pixy Cam --->");
  pixy.init();
  InputPan = pixy.blocks[0].x;//Input es el x del bloque
  SetpointPan = 318 / 2; //Establece el setPoint en la mitad
  myPID_Pan.SetMode(AUTOMATIC);
  x = pixy.blocks[0].x;//se establece x;
  myPID_Pan.SetOutputLimits(-100, 100);//limites de los motores

  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);

}

void loop() {

  uint16_t blocks;
  char buf[32];
  blocks = pixy.getBlocks();

  if (blocks) {//Si detecta el color , hace el calculo con PID y lo gira
    x = pixy.blocks[0].x;
    y = pixy.blocks[0].y;
    InputPan = x;
    myPID_Pan.Compute();
    Serial.print("Output:");
    Serial.println(OutputPan);
    motors.setSpeeds(-OutputPan,OutputPan);
    //Update Servo Position
   
    Serial.print(x);

    Serial.print(" ");
    Serial.print(y);
    Serial.println();

  }
 if(!blocks){//Si no detecta el color gira
  motors.setSpeeds(50,-50);
 }
   


}

