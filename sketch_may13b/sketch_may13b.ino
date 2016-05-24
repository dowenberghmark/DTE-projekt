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
int segDP = 13;  //Decimal point
int segE = A1;    //Display pin 5
int segF = 10;     //Display pin 11
int segG = 5;     //Display pin 15

int buttonPin = 3;
int switchPin = A4; 

int ff_ClockSR = 1;
int ff_ClockRC = A2;
int ff_out = A0;
//int flipflopRes = A0;

int temp = 25;

volatile int iter = 1;
volatile int displayFlag = 1; 

volatile long timeOffset = 0;
volatile long currentTime;
volatile long ff_flag = 0;

boolean currentState = LOW;//stroage for current button state
boolean lastState = LOW;//storage for last button state
  
void setup() {
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);  
  pinMode(segDP, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  
  pinMode(buttonPin, INPUT);
  
  pinMode(ff_ClockSR, OUTPUT);
  pinMode(ff_ClockRC, OUTPUT);
  pinMode(ff_out, INPUT);
  
  attachInterrupt( digitalPinToInterrupt( buttonPin ), f, CHANGE);
  
  analogReference(DEFAULT);
  Serial.begin(9600);
  }


void loop() {
 
  currentTime = millis();
  
 // Serial.print("Offset: "); Serial.println(timeOffset);
  // put your main code here, to run repeatedly: NO
  int loopOnSecond = (millis() - timeOffset) / 1000;
  int HHMM = 0;

  if(loopOnSecond/60 > 90){
    digitalWrite(switchPin, LOW);
  } 
  switchTrigger();
 

  //read temperature every (TIME_TO_READ)th second
  if (loopOnSecond % TIME_TO_READ == 0){
    temp = tempReader();
    flipflop_handler(loopOnSecond); 
  }
  
  //Deciding between displaying temperature and time
  if ( loopOnSecond > (SWITCH_TIME_SEC * iter ) && displayFlag == 1 ){
    displayFlag = 0;
    iter++;
    //Serial.print("Displaying time: ");Serial.println(HHMM);
    
  } else if (loopOnSecond > (SWITCH_TIME_SEC * iter ) && displayFlag == 0 ){
    displayFlag = 1;
    iter++;
    //Serial.print("displaying temp ");Serial.println(temp);
    
  }

  //Display TEMP or TIME
  if (displayFlag == 1 ){
    displayNumber(temp*10, 2); 
  } else if(displayFlag == 0 ){
      HHMM = formatSecondsToHHMM( loopOnSecond );
      displayNumber(HHMM, 1);
  }

  
       
}



//Convert milliseconds from program startrunning to the format Hours:Minutes
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

// Write 1 or 0 to switchPin
void switchTrigger(){
    int flipflop = digitalRead(ff_out);
    if(ff_flag == 0){
      digitalWrite(switchPin, HIGH);
    }
    if(ff_flag == 1){
       digitalWrite(switchPin, LOW);
    }
    
  }


//ISR
void f() {
  Serial.print("Offset: "); Serial.println(timeOffset);
  
  currentState = digitalRead(buttonPin);
  if (currentState == HIGH && lastState == LOW){//if button has just been pressed
    //Serial.println("pressed");
    //delay(1);//crude form of button debouncing
    displayFlag = 1;
    iter = 1; 
    timeOffset = currentTime;
    ff_flag = 0;
  } 
  lastState = currentState;
  
}

void flipflop_handler(int bornTime){
  
    int readValue = 0;
    int minFive = 15;
    digitalWrite(ff_ClockSR, HIGH);
    delay(4);
    digitalWrite(ff_ClockSR, LOW);
    delay(4);
    digitalWrite(ff_ClockRC, HIGH);
    delay(4);
    digitalWrite(ff_ClockRC, LOW);

    readValue = digitalRead(ff_out);

    if (readValue == 1 && ff_flag == 0){

      ff_flag = 1;
    }
    else if(readValue == 0 && ff_flag == 0 &&  bornTime > minFive){
      ff_flag = 1;    
    }
}

