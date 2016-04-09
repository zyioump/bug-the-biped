#include <NewPing.h>
#include <VarSpeedServo.h>
#include <SoftwareSerial.h>

#define BUFF_SIZE 256

SoftwareSerial monB(7, 9);

VarSpeedServo MF;
VarSpeedServo MB;

const int ultrasonPin = 6;

NewPing sonar(ultrasonPin, ultrasonPin );

const int hm[2] = {81, 95}; // Home position, you need to set them
const int speed_ = 30; // Slow speed

char c ;

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
    MF.attach(2);  //Front motor
    MB.attach(4);  //Back motor

  // Ouvre la voie série avec le module BT
    monB.begin(9600);


    MF.write(hm[0], speed_, true);
    MB.write(hm[1], speed_, true);
    Serial.begin(115200);
}

void loop() {
    // put your main code here, to run repeatedly:
 bluetooth();
}

void bluetooth() {
  while(monB.available()){
    c = monB.read(); // get Last value pushed
  }
   
  switch(c)
  {
    case 'A':
      robotAvancer();
      break;
    case 'R':
      robotReculer();
      break;
    case 'D':
      robotTournerADroite();
      break;
    case 'G':
      robotTournerAGauche();
      break;
    case 'S':
      robotStop();
      break;
  }
}

unsigned int distance()
{
    unsigned int duration, distance;
    delayMicroseconds(40);

    duration = sonar.ping();

    // Distance proportionnelle à la durée de sortie
    distance = duration/US_ROUNDTRIP_CM;
    Serial.print(duration);
    Serial.print(" ");
    Serial.println(distance);
    if(distance > 40 || distance < 3)
        return 25;  
    return distance;
}

void bouger(const int pos[])
{
    MF.write(hm[0] + pos[0], speed_, true);
    MB.write(hm[1] + pos[1], speed_, true);
}

void robotStop()
{
    bouger(stoper);
}

void robotAvancer()
{
    for(int x=0; x<nbrPos; x++){
        bouger(avancer[x]);
    }
}

void robotReculer()
{
    for(int x=0; x<nbrPos; x++){
        bouger(reculer[x]);
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
