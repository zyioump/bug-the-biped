#include <VarSpeedServo.h>

VarSpeedServo MF;
VarSpeedServo MB;

const int hm[2] = {95, 97}; // Home position, you need to set them
const int speed_ = 40; // Slow speed

const int nbPos = 2;
const int amplitudeBackDeg = 25;
const int amplitudeFrontDeg = 8;
const int pos[nbPos][2] = {
  {amplitudeFrontDeg, -amplitudeBackDeg},
  {-amplitudeFrontDeg, amplitudeBackDeg}
};


void setup() {
  // put your setup code here, to run once:
  MF.attach(10);  //Front motor
  MB.attach(11);  //Back motor

  MF.slowmove(hm[0], speed_);
  MB.slowmove(hm[1], speed_);
}

void loop() {
  // put your main code here, to run repeatedly:
  int foreward = 1;
  int noMvt = 0;
  int nbMvt = 20;

  for(int x=0; x<nbPos; x++){
    MF.slowmove(hm[0] + pos[x][0], speed_);
    MB.slowmove(hm[1] + pos[x][1], speed_);
    
    x = x % nbPos ;
    /*if( (noMvt %  nbMvt) == 0 ){
      foreward = -1 * foreward;
      noMvt = 0;
      delay(3000);
    }*/

    noMvt++;
    delay(450);
  }
  
}
