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

const int xAxis_median = 100; // Adjust this if needed
const int word_bank_size = 10;
//const String wordBank[word_bank_size] = {snake, ocean, timer, jazzy, broke, drain, refer, cadet, charm, aside};
const int joyButton = 2;
bool temp = true;
unsigned int count = 0;
bool val = false;
bool temper = true;
int ycounter = 1;

unsigned int joycount = 0;
int disCounter = 0;
const char alpha[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};





typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
    
} task;

int delay_gcd;
const unsigned short tasksNum = 2;
task tasks[tasksNum];

enum SM1_States { SM1_INIT, SM1_S0, SM1_S1, SM1_S2, SM1_S3};
int SM1_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case SM1_INIT:
         //State Transition
            state = SM1_S0;
        break;
      case SM1_S0:
          if(digitalRead(joyButton) == LOW) {
            state = SM1_S1;
          }
          else{
            state = SM1_S0;
          }
         //State Transition
        break;
      case SM1_S1:
            if(val) {
              state = SM1_S2;
            }
            state = SM1_S1;
             //State Transition
        break;
            
      case SM1_S2:
           if(digitalRead(joyButton) == LOW) {
              state = SM1_S3;
           }
           break;
      case SM1_S3:
          state = SM1_S3;
          break;
    }
    switch(state){ // State Action
      case SM1_INIT:
         //State Action
        break;
      case SM1_S0:
            //State Action
           if(temp){
              lcd.print("_____#");
              temp = false;
           }
           
           
         //State Action
        break;
      case SM1_S1:
            //State Action
           if(!val) {
             lcd.print("abcdefghijklm");
             lcd.setCursor(0,1);
             lcd.print("nopqrstuvwxyz");
             val = true;
           }
         //State Action
        break;
    

    case SM1_S2:
        //lcd.setCursor(0,0);
        break;
          
    

    case SM1_S3:
            if((joycount == 0) && (ycounter == 0)) {
                lcd.clear();
                lcd.print("a____#");
            }
            else if((joycount == 1) && (ycounter == 0)) {
                lcd.clear();
                lcd.print("b____#");
            }
            else if((joycount == 2) && (ycounter == 0)) {
                lcd.clear();
                lcd.print("c____#");
            }
            else if((joycount == 3) && (ycounter == 0)) {
                lcd.clear();
                lcd.print("d____#");
            }
            else if((joycount == 4) && (ycounter == 0)) {
                lcd.clear();
                lcd.print("e____#");
            }
            else if((joycount == 5) && (ycounter == 0)) {
                lcd.clear();
                lcd.print("f____#");
            }
        break;
    }
    return state;
    
}

enum SM2_States { SM2_INIT, SM2_S0, SM2_S1};
int SM2_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case SM2_INIT:
         //State Transition
            state = SM2_S0;
        break;
      case SM2_S0:
            if((digitalRead(joyButton) == HIGH) && val) {
                state = SM2_S1;
            }
            state = SM2_S0;
        //State Transition
        break;
      case SM2_S1:
            state = SM2_S1;            
        //State Transition
        break;
    }
    switch(state){ // State Action
      case SM2_INIT:
         //State Action
         
        break;
      case SM2_S0:
            //State Action
            if(temper) {
              lcd.setCursor(0,0);
              lcd.blink();
              temper = false;
            }
            if(analogRead(xAxis) < 100) {
              joycount--;
              count--;
              lcd.setCursor(count,ycounter);
              lcd.blink();
            }
            else if(analogRead(xAxis) > 1000) {
               joycount++;
               Serial.print(joycount);
               count++;
               lcd.setCursor(count,ycounter);
               lcd.blink();
            }
            else if(analogRead(yAxis) < 100) {
               ycounter = 1;
               lcd.setCursor(count, ycounter);
               lcd.blink();
            }
            else if(analogRead(yAxis) > 1000) {
               ycounter = 0;
               lcd.setCursor(count, ycounter);
               lcd.blink();
            }
            
           /* if(analogRead(xAxis) > 100) {
               count++;
               lcd.cursor();
            }*/
       //     tone(buzzer, sound_pattern[0]);
          
         //State Action
        break;
      case SM2_S1:
            //State Action
            if((joycount == 0) && (ycounter == 0)) {
                lcd.clear();
                lcd.print("a____#");
            }
            else if((joycount == 1) && (ycounter == 0)) {
                lcd.clear();
                lcd.print("b____#");
            }
            else if((joycount == 2) && (ycounter == 0)) {
                lcd.clear();
                lcd.print("c____#");
            }
            else if((joycount == 3) && (ycounter == 0)) {
                lcd.clear();
                lcd.print("d____#");
            }
            else if((joycount == 4) && (ycounter == 0)) {
                lcd.clear();
                lcd.print("e____#");
            }
            else if((joycount == 5) && (ycounter == 0)) {
                lcd.clear();
                lcd.print("f____#");
            }
   
   
          //  tone(buzzer, sound_pattern[1]);
         //State Action
        break;
    }

    return state;
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

   // GCD
  lcd.begin(16,2);

  
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