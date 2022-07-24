// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
const int xAxis = A0; // Recall that A0 is really a number under the hood.
const int yAxis = A1;
const int light_pattern_size = 2;
const char light_pattern[light_pattern_size] = {0x00, 0x0F};

const char sound_pattern_size = 2;
const double sound_pattern[sound_pattern_size] = {261.63, 293.66}; // C4, D4

const int buzzer = 3;
int new_array[b_size];
int game_array[b_size];
int counter = 1;
const int xAxis_median = 100; // Adjust this if needed

int ran;
const int joyButton = 2;
int count = 1;
bool something = true;
bool temper = false;
// Reset the Output Buffer. 
void resetBuffer() {
    delay(500);
    for(int i = 0; i < b_size; i++) {
        // Note this is an arduino function call to the pins
        digitalWrite(b[i], LOW);
    }
}
// Writes to the buffer. Note this function ORs the current value with the new value
// Note that size is an optional argument with default size the same as the buffer
void writeBuffer(unsigned char b_temp, int size = b_size)
{
    for (int i = (size - 1); i >= 0; i--) {
        if ((b_temp >> i) & 0x01) {
        digitalWrite(b[i], HIGH);
        }
    }

}


typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
    
} task;

int delay_gcd;
const unsigned short tasksNum = 2;
task tasks[tasksNum];

enum SM1_States { SM1_INIT, SM1_S0};
int SM1_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case SM1_INIT:
         //State Transition
            if(digitalRead(joyButton) == LOW){
              state = SM1_S0;
            }
        break;
      case SM1_S0:
              state = SM1_S0;
            
         //State Transition
        break;
    }

    switch(state){ // State Action
      case SM1_INIT:
         //State Action
        break;
      case SM1_S0:
            //State Action
      ran = random(0,5);
      if(digitalRead(joyButton) == LOW) {
        count = 1;
        memset(new_array, 0, sizeof new_array);  
      }
      if(count < 4){
        if(ran == 1) {
          digitalWrite(b[0], HIGH);
          delay(500);
          digitalWrite(b[0], LOW);
          new_array[count] = 8;
          Serial.print(count);
          count++;
        }
        else if(ran == 2) {
          digitalWrite(b[1], HIGH);
          delay(500);
          digitalWrite(b[1], LOW);
          new_array[count] = 9;
          Serial.print(count);
          count++;
        }
        else if(ran == 3) {
          digitalWrite(b[2], HIGH);
          delay(500);
          digitalWrite(b[2], LOW);
          new_array[count] = 10;
          Serial.print(count);
          count++;
        }
        else if(ran == 4) {
          digitalWrite(b[3], HIGH);
          delay(500);
          digitalWrite(b[3], LOW);
          new_array[count] = 11;
          Serial.print(count);
          count++;
        }
      }
//  if(count == 4) {
//    helper();
//    count++;
//  }
     
      
      
          
         //State Action
        break;


    return state;
  }
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
            if(counter >= 4) {
              state = SM2_S1;
            }
        //State Transition
        break;
      case SM2_S1:
            if(digitalRead(joyButton) == LOW) {
              state = SM2_S0;
              memset(new_array, 0, sizeof new_array); 
              memset(game_array, 0, sizeof game_array);
              counter = 1;         
            }
        //State Transition
        break;
    }
    switch(state){ // State Action
      case SM2_INIT:
         //State Action
        break;
      case SM2_S0:
            //State Action
        if(counter < 4) {
           if(analogRead(yAxis) > 1000) {
              digitalWrite(b[1], HIGH);
              resetBuffer();
              game_array[counter] = 9;
              counter++;
           }
           if(analogRead(yAxis) < xAxis_median) {
              digitalWrite(b[2], HIGH);
              resetBuffer();
              game_array[counter] = 10;
              counter++;
           }
           if(analogRead(xAxis) < xAxis_median) {
              digitalWrite(b[0], HIGH);
              resetBuffer();
              game_array[counter] = 8;
              counter++;
           }
           if(analogRead(xAxis) > 1000) {
              digitalWrite(b[3], HIGH);
              resetBuffer();
              game_array[counter] = 11;
              counter++;
           }
        }
          
         //State Action
        break;
      case SM2_S1:
            //State Action
           
         something = areEqual(new_array, game_array);
         if(something){
              digitalWrite(b[0], HIGH);
              digitalWrite(b[1], HIGH);
              digitalWrite(b[2], HIGH);
              digitalWrite(b[3], HIGH);
              resetBuffer();
         }
         something = temper;
            
         //State Action
        break;
    }

    return state;
}



void helper() {
  for(int i = 1; i < 5; i++) {
    digitalWrite(new_array[i], HIGH);
    resetBuffer();
  }
}

bool areEqual(int new_array[], int game_array[]) {
  for(int j = 1; j < 5; j++) {
    if(new_array[j] != game_array[j]) {
     // Serial.print(new_array[j]);
    //  Serial.print("  ");
     // Serial.print(game_array[j]);
      return false;
    }
    Serial.print(new_array[j]);
    Serial.print("   ");
    Serial.print(game_array[j]);
  }
  return true;
}


void setup() {
    //some set up (Default Arduino Function)
    pinMode(joyButton, INPUT_PULLUP);
    // LEDs
    for(int i = 0; i < b_size; i++)
    {
        pinMode(b[i], OUTPUT);
    }
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
  delay(delay_gcd); // GCD.
}