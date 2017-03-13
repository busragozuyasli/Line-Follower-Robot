#include <QTRSensors.h>

#define NUM_SENSORS 8
#define NUM_SAMPLES_PER_SENSOR 4
#define EMITTER_PIN 2
const int sag_i = 7;
const int sag_g = 6;
const int sol_i = 5;
const int sol_g = 4;
const int sag_e = 9;
const int sol_e = 3;
int maxspeed=200;
int minspeed=0;

int s_durum1, s_durum2, s_durum3, s_durum4, s_durum5, s_durum6, s_durum7, s_durum8;
QTRSensorsAnalog qtra((unsigned char[]) {12, 13, 14, 15, 16, 17,18 ,19},
NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

void setup() {
  
  Serial.begin(9600);
  delay(500);

  pinMode(sag_i, OUTPUT);
  pinMode(sag_g, OUTPUT);
  pinMode(sol_i, OUTPUT);
  pinMode(sol_g, OUTPUT);
  pinMode(sol_e,OUTPUT);
  pinMode(sag_e,OUTPUT);

Serial.begin(9600);
delay(500);
int i;
pinMode(13, OUTPUT);
digitalWrite(13, HIGH);
for (i = 0; i < 400; i++)
{
qtra.calibrate();
}
digitalWrite(13, LOW);
for (i = 0; i < NUM_SENSORS; i++)
{
Serial.print(qtra.calibratedMinimumOn[i]);
Serial.print(' ');
}
Serial.println();
for (i = 0; i < NUM_SENSORS; i++)
{
Serial.print(qtra.calibratedMaximumOn[i]);
Serial.print(' ');
}
Serial.println();
Serial.println();
delay(1000);
}

void loop() {
  Serial.print("gitti");
  
 unsigned int position = qtra.readLine(sensorValues);
 
 int line_position = position - 3500;
 
    if(line_position>0){
    analogWrite(sag_e,minspeed);
    analogWrite(sol_e,maxspeed);
    digitalWrite(sag_i, LOW);
    digitalWrite(sag_g, HIGH);
    digitalWrite(sol_i, HIGH);
    digitalWrite(sol_g, LOW);
    
  }
  if(line_position<0)
  {
    analogWrite(sag_e,maxspeed);
    analogWrite(sol_e,minspeed);
    digitalWrite(sag_i, HIGH);
    digitalWrite(sag_g, LOW);
    digitalWrite(sol_i, LOW);
    digitalWrite(sol_g, HIGH);
  }
}
