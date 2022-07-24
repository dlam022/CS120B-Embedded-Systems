// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {2, 3, 4, 5};
// Output Buffer
int b_buf = 0x00;
// Input Variables

// Serial Monitor Buffer
int s_buf = 0x00; 

/* 's' is an array of integers of size 8. Note that arrays start at 0
 We will use this to be able to see the individual bit values of the s_buf

 */
const int s_size = 8;
int s[s_size];

const int X = 8;
const int Y = 9;

int lightVal = 0;
int buttonValue = 0;
//bool buttonHeld = false;


// We can also define our own helper functions. It is a good idea to use helper functions whenever they make sense.
// Normally we also define the return type (void for none)

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
    for (int i = (size - 1); i >= 0; i--) {
        if ((b_temp >> i) & 0x01) {
        digitalWrite(b[i], HIGH);
        }
    }

}

void modeZero() {

  if(digitalRead(Y) == LOW) {
    buttonValue = 1;
  }
  if(buttonValue == 1){
    modeOne();
  }
  else{
    lightVal = analogRead(A1);

    if(lightVal > 500) {
      digitalWrite(b[0], HIGH);
      digitalWrite(b[1], HIGH);
      digitalWrite(b[2], HIGH);
      digitalWrite(b[3], HIGH);
    }
    if(lightVal > 400 && lightVal < 500) {
      digitalWrite(b[0], HIGH);
      digitalWrite(b[1], HIGH);
      digitalWrite(b[2], HIGH);
      digitalWrite(b[3], LOW);
    }
    if(lightVal > 300 && lightVal < 400){
      digitalWrite(b[0], HIGH);
      digitalWrite(b[1], HIGH);
      digitalWrite(b[2], LOW);
      digitalWrite(b[3], LOW);
    }
    if(lightVal > 200 && lightVal < 300) {
      digitalWrite(b[0], HIGH);
      digitalWrite(b[1], LOW);
      digitalWrite(b[2], LOW);
      digitalWrite(b[3], LOW);
    }
    if(lightVal < 200) {
      digitalWrite(b[0], LOW);
      digitalWrite(b[1], LOW);
      digitalWrite(b[2], LOW);
      digitalWrite(b[3], LOW);
    }
  }

  /*if(digitalRead(Y) == LOW) {
    buttonValue = 1;
  }
  if(buttonValue == 1){
    modeOne();
  }

   /* for(int i = 0; i < 4; i++){
      digitalWrite(b[i], HIGH);
      Serial.print("LDR is dark, LED is on");
    } */
  
}

void modeOne() {

  if(digitalRead(X) == HIGH) {
    buttonValue = 0;
  }
  if(buttonValue == 0) {
    modeZero();
  }

  else{
  
    lightVal = analogRead(A1);

    if(lightVal > 500) {
      digitalWrite(b[0], LOW);
      digitalWrite(b[1], LOW);
      digitalWrite(b[2], LOW);
      digitalWrite(b[3], LOW);
    }
    if(lightVal > 400 && lightVal < 500) {
      digitalWrite(b[0], HIGH);
      digitalWrite(b[1], LOW);
      digitalWrite(b[2], LOW);
      digitalWrite(b[3], LOW);
    }
    if(lightVal > 300 && lightVal < 400){
      digitalWrite(b[0], HIGH);
      digitalWrite(b[1], HIGH);
      digitalWrite(b[2], LOW);
      digitalWrite(b[3], LOW);
    }
    if(lightVal > 200 && lightVal < 300) {
      digitalWrite(b[0], HIGH);
      digitalWrite(b[1], HIGH);
      digitalWrite(b[2], HIGH);
      digitalWrite(b[3], LOW);
    }
    if(lightVal < 200) {
      digitalWrite(b[0], HIGH);
      digitalWrite(b[1], HIGH);
      digitalWrite(b[2], HIGH);
      digitalWrite(b[3], HIGH);
    }

  }
  
}


void setup() {
    pinMode(X, INPUT);
    pinMode(Y, INPUT_PULLUP);
    pinMode(A1, INPUT);
    // OUTPUT is a defined macro in Arduino!
    for(int i = 0; i < b_size; i++)
    {
        pinMode(b[i], OUTPUT);
    }
    // We will also read from the serial monitor
    Serial.begin(9600);
}

void loop() {
  modeZero();
   
}