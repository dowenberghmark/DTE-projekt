//for display
#define SWITCH_TIME_SEC 10
//for reading temp
#define TIME_TO_READ 10
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

int temp = 25;
int iter = 1;
int displayFlag = 1; 
  
  
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
  int loopOnSecond = millis()/1000;
  int HHMM = 0;
  
  if (loopOnSecond % TIME_TO_READ == 0){
    temp = tempReader();  
  }
  
  
  if ( loopOnSecond > (SWITCH_TIME_SEC * iter ) && displayFlag == 1 ){
    displayFlag = 0;
    iter++;
    //displayNumber(temp*10, 2); 
    //Serial.print(our modulevalue: ");Serial.println(x);
    Serial.print("Displaying time: ");Serial.println(HHMM);
    
  } else if (loopOnSecond > (SWITCH_TIME_SEC * iter ) && displayFlag == 0 ){
    displayFlag = 1;
    iter++;
    //HHMM = formatSecondsToHHMM( loopOnSecond );
    Serial.print("displaying temp ");Serial.println(temp);
    //displayNumber(HHMM, 1); 
    
  }

  if (displayFlag == 1 ){
    displayNumber(temp*10, 2); 
    //Serial.println("Displaying tempeture");
    
  } else if(displayFlag == 0 ){
    HHMM = formatSecondsToHHMM( loopOnSecond );
    //Serial.print("My time: ");Serial.println(HHMM);
    displayNumber(HHMM, 1);  
  }
  
  Serial.println(displayFlag);
  //digitalWrite(digit3, HIGH);
  //lightNumber(2);
  
  //displayNumber(millis() / 1000);
}

//convert milliseconds from program startrunning to the format Hours:Minutes
int formatSecondsToHHMM(int currentMillis){
  //currentMillis /= 1000;
  
  if (currentMillis < 60){
    return currentMillis;
  }else if(currentMillis < 3600) {
    float minutes = floor( currentMillis / 60);
    currentMillis -= minutes* 60; 
    int HHMM =  (int)minutes * 100 + currentMillis;
    return HHMM;
  }
  else {
    int hours = floor(currentMillis / 3600);
    float minutes = floor(( currentMillis - hours * 3600) / 60);
    int HHMM = hours * 100 + (int)minutes;
    return HHMM;
  }
}


