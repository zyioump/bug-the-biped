#include <VarSpeedServo.h>

VarSpeedServo MF;
VarSpeedServo MB;

const int hm[2] = {95, 97}; // Home position, you need to set them
const int speed_ = 30; // Slow speed

const int nbrPos = 2;
const int amplitudeBackDeg = 25;
const int amplitudeFrontDeg = 8;
const int stoper [2] = {0,0};
const int avancer [nbrPos][2] = {
  {-amplitudeFrontDeg, amplitudeBackDeg},
  {amplitudeFrontDeg, -amplitudeBackDeg}
};
const int reculer [nbrPos][2] = {
  {-amplitudeFrontDeg, -amplitudeBackDeg},
  {amplitudeFrontDeg, amplitudeBackDeg}
};
const int droite [nbrPos][2] = {
  {-amplitudeFrontDeg + 20 , amplitudeBackDeg - 20},
  {amplitudeFrontDeg, -amplitudeBackDeg}
};
const int gauche [3][2] = {
  {-amplitudeFrontDeg - 20  , amplitudeBackDeg + 80},
  {-amplitudeFrontDeg - 10  , amplitudeBackDeg },
  {amplitudeFrontDeg, -amplitudeBackDeg}
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
  robotTournerAGauche();
}

void bouger(const int pos[])
{
    MF.slowmove(hm[0] + pos[0], speed_);
    MB.slowmove(hm[1] + pos[1], speed_);
}

void robotStop()
{
    bouger(stoper);
    delay(450);
}

void robotAvancer()
{
  for(int x=0; x<nbrPos; x++){
    bouger(avancer[x]);
    delay(450);
  }
}

void robotReculer()
{
  for(int x=0; x<nbrPos; x++){
    bouger(reculer[x]);
    delay(450);
  }
}

void robotTournerAGauche()
{
    MB.slowmove(180 , 100);
    MF.slowmove(hm[0] - amplitudeFrontDeg, 50);
    delay(400);
    MF.slowmove(hm[0] + amplitudeFrontDeg, 100);
    MB.slowmove(80, 150);
    delay(250);
  
}

void robotTournerADroite()
{
    MB.slowmove(0, 100);
    MF.slowmove(hm[0] + amplitudeFrontDeg, 50);
    delay(400);
    MF.slowmove(hm[0] - amplitudeFrontDeg, 100);
    MB.slowmove(100, 150);
    delay(250);
}
