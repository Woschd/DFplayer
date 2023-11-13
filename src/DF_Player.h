class DFplayer {
	
// it expects the sd card to contain this file structure:
//
// sd:/mp3/0001.mp3
// sd:/mp3/0002.mp3
// sd:/mp3/0003.mp3	
	
// Satzaufbau
// 7E FF 06 0F 00 01 01 xx xx EF
// 0	->	7E is start code
// 1	->	FF is version
// 2	->	06 is length
// 3	->	0F is command
// 4	->	00 is no receive
// 5 	->	01 01 is parameter 1 / high byte
// 6	->	01 01 is parameter 2 / low byte
// 7~8	->	checksum high byte = 0 - ( FF+06+0F+00+01+01 )
// 7~8	->	checksum low byte  = 0 - ( FF+06+0F+00+01+01 )
// 9	->	EF is end code	

	
  private: // alles was folgt, ist nur für den internen Gebrauch durch die Klasse selbst:

  
  // Array der zu sendenden Daten
  //                        0     1     2     3     4     5     6     7     8     9     
  uint8_t DF_Buffer[10] =    {0x7E, 0xFF, 0x06, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEF}; // send Data to DF Player
  uint8_t   _volume;
  uint16_t  _track;
  unsigned long time_to_send_volume;
  bool volume_sent;
  unsigned long time_to_send_play;
  bool play_sent;
 
  void _DF_calc_crc(){
	uint16_t DF_crc = 1 + (0xFFFF-(DF_Buffer[1] + DF_Buffer[2] + DF_Buffer[3] +  DF_Buffer[4] + DF_Buffer[5] + DF_Buffer[6]));		
	DF_Buffer[7] =  DF_crc >> 8;
	DF_Buffer[8] = 	DF_crc;	  
  }
  
  void _DF_send(){
    //Serial.begin(9600);
    for (int i = 0; i <= 9 ; i++){ 
      Serial.write(DF_Buffer[i]);
    }	
    //Serial.begin(115200);  
  }	  
  
//.....................................................................................................
  public: //alles was folgt, ist auch nach außen sichtbar

  void play(uint16_t track = 0){
    DF_Buffer[3] = 0x12;          // Befehl zum Abspielen
	  DF_Buffer[5] = track >> 8;
	  DF_Buffer[6] = track;
    _DF_calc_crc();
	  _DF_send();
  }	 

  void play_vol(uint16_t track = 0, uint8_t vol = 15){
    _volume = vol;
    _track = track;
    time_to_send_volume = millis() + 100;   // min. 100ms Verzögerung zwischen zwei Befehlen
    time_to_send_play = millis() + 200;     // min. 100ms Verzögerung zwischen zwei Befehlen
    Serial.begin(9600);
    volume_sent = false;
    play_sent = false;
  }	

  void run(){
    if(!volume_sent && millis() > time_to_send_volume){     
      volume(_volume);
      volume_sent = true;  
    }  

    if(!play_sent && millis() > time_to_send_play){     
      play(_track);
      play_sent = true;  
      Serial.begin(115200);
    }  

  }

  void volume(uint8_t volume = 15){
    if(volume > 30){
		  volume = 30;
	  }
	  DF_Buffer[3] = 0x06;  // Befehl für Lautstärke
    DF_Buffer[5] = 0x00;
	  DF_Buffer[6] = volume;
    _DF_calc_crc();
	  _DF_send();
  }  
 
  void stop(){
    DF_Buffer[3] = 0x16;  // Befehl zum Anhalten
    DF_Buffer[5] = 0x00;
	  DF_Buffer[6] = 0x00;
    _DF_calc_crc();
	  _DF_send();		
  }	  
    
};  // Class DFplayer