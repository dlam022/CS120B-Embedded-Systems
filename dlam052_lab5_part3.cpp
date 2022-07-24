enum States{INIT, S0, S1} SM1_state;
unsigned long lastRan;
const unsigned long period = 500;

// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
const int xAxis = A0; // Recall that A0 is really a number under the hood.
const int yAxis = A1;
const int light_pattern_size = 2;
const char light_pattern[light_pattern_size] = {0x00, 0x0F};

const char sound_pattern_size = 5;
const double sound_pattern[sound_pattern_size] = {261.63, 293.66, 329.63, 349.23, 392.00}; // C4, D4
const double temp_val[sound_pattern_size] = {261.63, 293.66, 329.63, 349.23, 392.00};

const int buzzer = 3;
int joybutton = 2;
int count = 0;

bool temp = false;
const int xAxis_median = 100; // Adjust this if needed

// Reset the Output Buffer. 
void resetBuffer() {
    delay(150);
    noTone(buzzer);
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

int SM1_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case INIT:
         //State Transition
            state = S0;
        break;
      case S0:
         if(temp){
          state = S1;
         }
          state = S0;
          temp = false;
          count++;
         //State Transition
         break;
      case S1:
        
         
        break;
    }
    switch(state){ // State Action
      case INIT:
         //State Action
        break;
      case S0:
            //State Action
          count = 0;
          while(!temp){
            while(analogRead(yAxis) > 1000) {
                tone(buzzer, sound_pattern[0]);
               // resetBuffer();
                //count++;
              }
              
             while(analogRead(yAxis) < xAxis_median) {
                tone(buzzer, sound_pattern[1]);
                //count++;
             }
             
            while(analogRead(xAxis) < xAxis_median) {
              tone(buzzer, sound_pattern[2]);
              //count++;
            //resetBuffer();
            }
            while(analogRead(xAxis) > 1000) {
              tone(buzzer, sound_pattern[3]);
             // count++;
            //resetBuffer();
           }    
            if(digitalRead(joybutton) == LOW) {
              tone(buzzer, sound_pattern[4]);
              count++;
              if(count == 2){
                temp = true;
              }
              //temp = true;
              //count++;
            //resetBuffer();
            }  
            resetBuffer();
          } 
    
          
         //State Action
        break;

      case S1:
          for(int i = 0; i < 5; i++) {
            tone(buzzer, sound_pattern[i]);
            tempFunction();
            noTone(buzzer);
            resetBuffer();
            tone(buzzer,temp_val[i]);
            tempFunction();
            noTone(buzzer);
            resetBuffer();
          }

    return state;
}
}

void tempFunction(){
  delay(200);
}


void setup() {
    // OUTPUT is a defined macro in Arduino!
    pinMode(joybutton, INPUT_PULLUP);
    for(int i = 0; i < b_size; i++)
        {
            pinMode(b[i], OUTPUT);
        }
    // We will also read from the serial monitor
    Serial.begin(9600);
}

void loop() {
    
    if ((millis() - lastRan) > period) {     
      SM1_state = (States)SM1_Tick(SM1_state);        
      lastRan = millis();   
     }  
}