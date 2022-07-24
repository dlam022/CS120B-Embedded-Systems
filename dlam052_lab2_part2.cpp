// C++ code
//
// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {2, 3, 4, 5};
// Output Buffer
int b_buf = 0x00;
// Input Variables

// Serial Monitor Buffer
int s_buf = 0x00; 

/* 's' is an array of integers of size 8. Note that arrays start at 1
 We will use this to be able to see the individual bit values of the s_buf

 */
const int s_size = 8;
int s[s_size];

// We can also define our own helper functions. It is a good idea to use helper functions whenever they make sense.
// Normally we also define the return type (void for none)
const int a_size = 2;
const int a[a_size] = {8,9};
const int a_type[a_size] = {0,1}; //0 for pulldown, 1 for pullup

const int X = 8;
const int Y = 9;

int xStatus = 0;
int yStatus = 0;

int counter = 0;

bool ledOn = false;
bool buttonState = LOW;
bool currentButton = LOW;


// Read from the serial monitor into s_buf and the s[] array for individual bits
void readData()
{
    if(Serial.available())
        s_buf = Serial.parseInt();

    for(int i = (s_size - 1); i>=0; i--)  { 
        s[i] = (s_buf >> i) & 0x01; // What's going on here?
        // ">>" bit shifting 
        // "&" bit masking
    }

}
// Reset the Output Buffer. 
void resetBuffer() {
    for(int i = 0; i < b_size; i++) {
        // Note this is an arduino function call to the pins
        digitalWrite(b[i], LOW);
    }
}
// Writes to the buffer. Note this function ORs the current value with the new value
// Note that size is an optional argument with default size the same as the buffer
void writeBuffer(unsigned char b_temp, int size = b_size)
{
  if(s_buf != 0){
    s_buf = s_buf >> 1;
    for (int i = (size - 1); i >= 0; i--) {
        if ((b_temp >> i) & 0x01) {
        digitalWrite(b[i], HIGH);
        }
    }
  }

}

void turnLedOff(int num) {
 for(int i = 0; i < b_size; i++){
   if(i == num) {
      digitalWrite(b[i], LOW);
    }
  }
}



void turnLedOn(int count) {
  
  for(int i = 0; i  < b_size; i++){
    if(i == count) {
      digitalWrite(b[i], HIGH);
    }
  }

}

void turnEverythingOff() {
   digitalWrite(b[0], LOW);
   digitalWrite(b[1], LOW);
   digitalWrite(b[2], LOW);
   digitalWrite(b[3], LOW);
}

void turnEverythingOn(){
  digitalWrite(b[0], HIGH);
  digitalWrite(b[1], HIGH);
  digitalWrite(b[2], HIGH);
  digitalWrite(b[3], HIGH);
}
      
  



void setup() {
    pinMode(X, INPUT);
    pinMode(Y, INPUT_PULLUP);
    // OUTPUT is a defined macro in Arduino!
    for(int i = 0; i < b_size; i++)
    {
        pinMode(b[i], OUTPUT);
    }
    // We will also read from the serial monitor
    Serial.begin(9600);
}

void loop() {
    if(digitalRead(X)== HIGH && counter >= b_size) {
      delay(1000);
      turnEverythingOff();
      counter = 0;
  /*    if(counter >= b_size) {
        turnEverythingOff();
        counter = 0;
      }
      */
    }
    else if(digitalRead(X) == HIGH) {
      delay(1000);
      turnLedOn(counter);
      counter++;
    }

    if(digitalRead(Y) == LOW && counter < 0) {
      delay(1000);
      turnEverythingOn();
      counter = 3;
      
     /* if(counter <= 0) {
        counter = 0;
      }
      */
    }
    else if(digitalRead(Y) == LOW) {
      delay(1000);
      turnLedOff(counter);
      counter--;
    }
}