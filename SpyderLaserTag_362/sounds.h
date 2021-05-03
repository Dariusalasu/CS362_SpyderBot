int sadTrumpet[] = {
  NOTE_B3, NOTE_C4, NOTE_AS3, NOTE_B3, NOTE_A3, NOTE_AS3
};

double sadTrumpet_D[] = {
  32, 2, 32, 2, 32, 1
};

int surprised[] = {
  NOTE_B3, NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, 
  NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, 
  NOTE_B4, NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, 
  NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, 
  NOTE_B5
};

double surprised_D[] = {
  16, 32, 64, 64, 64, 64, 
  64, 64, 64, 64, 64, 64, 
  64, 64, 64, 64, 64, 64, 
  64, 64, 64, 64, 32, 16, 
  6
};

int curious[] = {
  NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3, NOTE_B3, NOTE_C4, 
  NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_E4, 
  NOTE_DS4, NOTE_D4, NOTE_CS4, NOTE_C4, NOTE_B3, NOTE_AS3, 
  NOTE_A3, NOTE_GS3, NOTE_G3
};

double curious_D[] = {
  4, 100, 200, 200, 200, 200, 
  200, 200, 200, 100, 8, 100, 
  200, 200, 200, 200, 200, 200, 
  200, 100, 4
};

//haha song was taken from the following website with slight modifications to work with the code:
//https://create.arduino.cc/projecthub/GeneralSpud/passive-buzzer-song-take-on-me-by-a-ha-0f04a8
int haha[] = {
  NOTE_DS4, NOTE_C4, NOTE_F4, NOTE_DS4, NOTE_C4
};

double haha_D[] = {
  2.2, 2.2, 6.8, 2.2, 2.2
};

int takeMeOn[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5, 
  NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, 
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5, 
  NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};

double takeMeOn_D[] = {
  8, 8, 8, 4, 4, 4, 
  4, 7, 8, 8, 8, 8, 
  8, 8, 8, 4, 4, 4, 
  4, 7, 8, 8, 8, 8
};

int Annie_Melody[] = {
  NOTE_A4, 
  //its       the     most       beau      ti       ful       time       of       the
  NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_CS5, NOTE_CS5, NOTE_D5, 
  //year
  NOTE_B4, 
  //lights   fill     the    streets  spread     ing     so       much
  NOTE_B4, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_CS5, 
  //cheer
  NOTE_A4, 
  //I       should    be       play      ing       in       the      win      ter
  NOTE_A4, NOTE_FS4, NOTE_A4, NOTE_A4, NOTE_FS4, NOTE_A4, NOTE_FS4, NOTE_A4, NOTE_B4, 
  //snow
  NOTE_A4, 
  //but       im      ma       be       un        der    the        mi     stle
  NOTE_FS4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_E4, 
  //toe
  NOTE_E4, 
  //I        don't      wan        na       miss       out       on       the       ho        li
  NOTE_CS5, NOTE_CS5, NOTE_CS5, NOTE_CS5, NOTE_CS5, NOTE_CS5, NOTE_CS5, NOTE_CS5, NOTE_CS5, NOTE_D5, 
  //day
  NOTE_B4, 
  //But       I      can't    stop      star     ing       at      your
  NOTE_B4, NOTE_A4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_CS5, 
  //face
  NOTE_A4, 
  //I       should    be       play      ing       in       the      win      ter
  NOTE_A4, NOTE_FS4, NOTE_A4, NOTE_A4, NOTE_FS4, NOTE_A4, NOTE_FS4, NOTE_A4, NOTE_B4, 
  //snow
  NOTE_A4, 
  //but       im      ma       be       un        der    the        mi     stle
  NOTE_FS4, NOTE_A4, NOTE_FS4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_E4, 
  //toe
  NOTE_E4, 
  //With     you       oo
  NOTE_E4, NOTE_E5, NOTE_CS5, 
  //shaw      ty       with      you
  NOTE_B4, NOTE_CS5, NOTE_CS5, NOTE_B4, 
  //with     you       oo
  NOTE_E4, NOTE_E5, NOTE_CS5, 
  //shaw      ty     with      you
  NOTE_B4, NOTE_B4, NOTE_B4, NOTE_A4, 
  //With     you       oo
  NOTE_E4, NOTE_E5, NOTE_CS5, 
  //Un       der      the      mi      stle      toe
  NOTE_A4, NOTE_B4, NOTE_A4, NOTE_D5, NOTE_CS5, NOTE_A4
  //Finish song
};

double Annie_Melody_D[] = {
  1.83, 
  5.49, 10.98, 3.66, 5.49, 10.98, 3.66, 5.49, 10.98, 5.49, 
  1.568, 
  3.66, 5.49, 10.98, 3.66, 5.49, 10.98, 5.49, 3.66, 
  1.568, 
  5.49, 10.98, 3.66, 5.49, 10.98, 5.49, 10.98, 5.49, 3.66, 
  1.83, 
  10.98, 5.49, 10.98, 3.66, 5.49, 10.98, 5.49, 3.66, 3.66, 
  1.568, 
  5.49, 10.98, 5.49, 10.98, 5.49, 10.98, 5.49, 10.98, 3.66, 5.49, 
  1.568, 
  5.49, 10.98, 3.66, 3.66, 5.49, 10.98, 5.49, 3.66, 
  1.568, 
  5.49, 10.98, 3.66, 5.49, 10.98, 5.49, 10.98, 5.49, 3.66, 
  1.83, 
  10.98, 5.49, 10.98, 3.66, 5.49, 10.98, 5.49, 3.66, 3.66, 
  2.745, 
  3.66, 3.66, 1.22, 
  5.49, 10.98, 5.49, 2.745, 
  3.66, 3.66, 1.22, 
  5.49, 10.98, 5.49, 2.745, 
  3.66, 3.66, 1.22, 
  5.49, 5.49, 5.49, 1.83, 3.66, 0.665
  //Finish Song
};

int highToLow[] = {
  NOTE_F4, NOTE_E4, NOTE_DS4, NOTE_D4, NOTE_C4, NOTE_B3, 
  NOTE_AS3, NOTE_A3, NOTE_GS3, NOTE_G3, NOTE_FS3, NOTE_F3, 
  NOTE_E3
};

double highToLow_D[] = {
  16, 32, 64, 64, 64, 64, 
  64, 64, 64, 64, 32, 16, 
  6
};

int startup[] = {
  NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, 
  0, NOTE_C6, NOTE_G6, NOTE_C7
};

double startup_D[] = {
  29, 64, 64, 64, 48, 1, 
  2, 29, 32, 1.75
};
