#include <LiquidCrystal.h>

// Array of Output Pin variables, set to the pins being used
const int rs = 4, en = 5, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const int xAxis = A0; // Recall that A0 is really a number under the hood.
const int yAxis = A1;
const int light_pattern_size = 2;
const char light_pattern[light_pattern_size] = {0x00, 0x0F};

const char sound_pattern_size = 2;
const double sound_pattern[sound_pattern_size] = {261.63, 293.66}; // C4, D4

const int buzzer = 3;
const int joyButton = 2;

const int xAxis_median = 100; // Adjust this if needed
bool temp = false;
bool val = false;
int count = 0;
long startPressed = 0;
long endPressed = 0;
int lastButtonState = 0;
int holdTime = 0;
long idleTime = 0;
int buttonState = 0;
int disCounter = 0;



typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
    
} task;

int delay_gcd;
const unsigned short tasksNum = 2;
task tasks[tasksNum];

enum SM1_States { SM1_INIT, SM1_S0, SM1_S1, SM1_S2};
int SM1_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case SM1_INIT:
         //State Transition
            state = SM1_S0;
        break;
      case SM1_S0:
          buttonState = digitalRead(joyButton);

          if(digitalRead(joyButton) == LOW) {
            state = SM1_S1;
            temp = true;
          }

        
           
                
          
          
         else{
         
           state = SM1_S0;
         }
          
         //State Transition
        break;
      case SM1_S1:
          if(!temp) {
            state = SM1_S0;
          }
          if(digitalRead(joyButton) == LOW) {
            state = SM1_S2;
          }
             //State Transition
        break;
      case SM1_S2:
         if(!val) {
            state = SM1_S0;
            count = 0;
         }
    }
    switch(state){ // State Action
      case SM1_INIT:
         //State Action
        break;
      case SM1_S0:
            //State Action
           if(disCounter > 15) {
              disCounter = 0;
              lcd.setCursor(0,1);
            }
//         if(((analogRead(xAxis) > 500) && (analogRead(xAxis) < 520)) && ((analogRead(yAxis) > 500) && (analogRead(yAxis) < 520))){
//              actionFunction();
            if((analogRead(xAxis) < 50) && ((analogRead(yAxis) > 450) && (analogRead(yAxis) < 550))) {
               lcd.print("c");
               disCounter++;
            }
            else if((analogRead(xAxis) > 1000) && ((analogRead(yAxis) > 450) && (analogRead(yAxis) < 550))) {
               lcd.print("p");
               disCounter++;
              // helper();
            }
            else if((analogRead(yAxis) < 50) && ((analogRead(xAxis) > 450) && (analogRead(xAxis) < 550))) {
               lcd.print("h");
               disCounter++;
              // helper();
            }
            else if((analogRead(yAxis) > 1000) && ((analogRead(xAxis) > 450) && (analogRead(xAxis) < 550))) {
               lcd.print("j");
               disCounter++;
              // helper();
            }
            else if((analogRead(xAxis) < 100) && (analogRead(yAxis) > 1000)) {
              lcd.print("i");
              disCounter++;
             // helper();
            }
            else if((analogRead(xAxis) < 50) && (analogRead(yAxis) < 50)) {
              lcd.print("k");
              disCounter++;
             // helper();
            }
            else if((analogRead(xAxis) > 1000) && (analogRead(yAxis) < 50)){
              lcd.print("r");
              disCounter++;
             // helper();
            }
            else if((analogRead(xAxis) > 1000) && (analogRead(yAxis) > 1000)) {
              lcd.print("y");
              disCounter++;
             // helper();
            }
//         }
           /* lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("EMBEDDED");*/
         //State Action

        break;
      case SM1_S1:
            //State Action
           /* lcd.clear();
            lcd.setCursor(0,1);
            lcd.print("SYSTEMS");*/
           // lcd.print("c");
            if(disCounter > 15) {
              disCounter = 0;
              lcd.setCursor(0,1);
            }
            if((analogRead(xAxis) < 50) && ((analogRead(yAxis) > 450) && (analogRead(yAxis) < 550))) {
               lcd.print("C");
               disCounter++;
               //helper();
               temp = false;
            }
            else if((analogRead(xAxis) > 1000) && ((analogRead(yAxis) > 450) && (analogRead(yAxis) < 550))) {
               lcd.print("P");
               disCounter++;
               temp = false;
              // helper();
            }
            else if((analogRead(yAxis) < 50) && ((analogRead(xAxis) > 450) && (analogRead(xAxis) < 550))) {
               lcd.print("H");
               disCounter++;
               temp = false;
              // helper();
            }
            else if((analogRead(yAxis) > 1000) && ((analogRead(xAxis) > 450) && (analogRead(xAxis) < 550))) {
               lcd.print("J");
               disCounter++;
               temp = false;
              // helper();
            }
            else if((analogRead(xAxis) < 100) && (analogRead(yAxis) > 1000)) {
              lcd.print("I");
              disCounter++;
              temp = false;
             // helper();
            }
            else if((analogRead(xAxis) < 50) && (analogRead(yAxis) < 50)) {
              lcd.print("K");
              disCounter++;
              temp = false;
              //helper();
            }
            else if((analogRead(xAxis) > 1000) && (analogRead(yAxis) < 50)){
              lcd.print("R");
              disCounter++;
              temp = false;
             // helper();
            }
            else if((analogRead(xAxis) > 1000) && (analogRead(yAxis) > 1000)) {
              lcd.print("Y");
              disCounter++;
              temp = false;
              //helper();
            }
         //State Action
        break;
      case SM1_S2:
          lcd.clear();
          disCounter = 0;
          val = false;
    }

    return state;
}

enum SM2_States { SM2_INIT, SM2_S0, SM2_S1};
int SM2_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case SM1_INIT:
         //State Transition
            state = SM1_S0;
        break;
      case SM1_S0:
            state = SM2_S1;
        //State Transition
        break;
      case SM2_S1:
            state = SM1_S0;            
        //State Transition
        break;
    }
    switch(state){ // State Action
      case SM2_INIT:
         //State Action
        break;
      case SM1_S0:
            //State Action
          //  tone(buzzer, sound_pattern[0]);
          
         //State Action
        break;
      case SM2_S1:
            //State Action
   
         //   tone(buzzer, sound_pattern[1]);
         //State Action
        break;
    }

    return state;
}


void helper() {
  delay(500);
}


void updateButton() {
   if(digitalRead(joyButton) == LOW) {
      startPressed = millis();
      idleTime = startPressed - endPressed;
      if(idleTime >= 500 && idleTime < 1000) {
        Serial.print("Button ws idle for half a second");
      }
      if(idleTime >= 1000) {
        Serial.print("Button was idle for one second or more");
      }
   }

   else{
      endPressed = millis();
      holdTime = endPressed - startPressed;

      if(holdTime >= 500 && holdTime < 1000) {
        Serial.print("button was held for half a second");
      }

      if(holdTime >= 1000) {
        Serial.print("button was held for one second or more");
        val = true;
        
      }
   }
  
}



void setup() {
    //some set up (Default Arduino Function)
    pinMode(joyButton, INPUT_PULLUP);
    

    // LEDs
   
    Serial.begin(9600);


  unsigned char i = 0;
  tasks[i].state = SM1_INIT;
  tasks[i].period = 500;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  i++;
  tasks[i].state = SM2_INIT;
  tasks[i].period = 1000;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;

  delay_gcd = 500; // GCD
  lcd.begin(16,2);

 // lcd.print("WE LOVE");
}


void loop() {
  // put your main code here, to run repeatedly:
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
      
     }
   }
}