#include "DF_Player.h"
DFplayer mp3; 

uint16_t  track;
unsigned long time_for_track;

void setup() {
  Serial.begin(9600);
  time_for_track = millis() + 3000;  
}

void loop() {
  if(millis() > time_for_track){
    if(track <= 10){
      Serial.println(track);
      mp3.play_vol(track, 20);
      ++ track; 
    } 
    else{
      track = 0;
    } 
    time_for_track = millis() + 3000;
  }
   
  mp3.run();
}
