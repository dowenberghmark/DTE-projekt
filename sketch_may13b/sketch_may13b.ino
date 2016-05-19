

int digit1 = 12;    //PWM Display pin 1
int digit2 = 9;    //PWM Display pin 2
int digit3 = 8;     //PWM Display pin 6
int digit4 = 6;    //PWM Display pin 8

int Uin = A5;       //PWM Uin pin A0

int segA = 11;    //Display pin 14
int segB = 7;     //Display pin 16
int segC = 4;     //Display pin 13
int segD = 2;     //Display pin 3
int segDP = 3;  //Decimal point
int segE = A1;    //Display pin 5
int segF = 10;     //Display pin 11
int segG = 5;     //Display pin 15


void setup() {
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);


  analogReference(DEFAULT);
  Serial.begin(9600);

  pinMode(13, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly: NO
  int temp = tempReader();
  displayNumber(temp*10, 2); 
  //digitalWrite(digit3, HIGH);
  //lightNumber(2);
  
  //displayNumber(millis() / 1000);
}




