int potPin = A7;   //Pot that can vary between 0-5v connected to Analog 7 pin
int pot = 512;     // pot holds the result of the analogRead of the voltage on A7, ranges from 0-1023 i.e. a 10 bit binary number
int mapped = 127;  // holds the result of mapping pot over a smaller range to convert to an 8 bit binary number suitable for a PWM analogWrite
int PWMpin = 3;

void setup() {
  // open the serial port at 9600 bps:
  Serial.begin(9600);

  TCCR2B = TCCR2B & 0b11110000;  // clear lower 4 bits of TCCR2B to zeros
  TCCR2B = TCCR2B | 0b00001011;  // sets lower 4 bits of TCCR2B to 1011
  OCR2A = 0xF8;                  // OCR2A sets the top value for the PWM counter. E8 = 1.08KHz, F8 = 1.01KHz, FF = 977Hz

  Serial.print("\x1b[1;31m");  // Set terminal style to bold, red foreground.  See https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797

  Serial.print("TCCR2A = ");    // Print text
  Serial.println(TCCR2A, BIN);  // Print value of TCCR2A register in binary

  Serial.print("TCCR2B = ");    // Print text
  Serial.println(TCCR2B, BIN);  // Print value of TCCR2B register in binary

  Serial.print("OCR2A = ");     // Print text
  Serial.println(OCR2A, HEX);   // Print value of OCR2A register in hex
  Serial.println("=========");  // Print text

  delay(1000);
  Serial.print("\x1B[1;1H\x1B[2J");  // ANSI VT100 Escape sequences to move terminal cursor to position 1,1 then clear the terminal window
}

void loop() {
  // put your main code here, to run repeatedly:
  pot = analogRead(potPin);            // read the analog voltage on potPin and convert to a value between 0 and 1023
  mapped = map(pot, 0, 1023, 5, 250);  // map a 10-bit number to an 8-bit number as a PWM analogWrite only uses 8-bits.  See: https://www.arduino.cc/reference/en/language/functions/math/map/
  analogWrite(PWMpin, mapped);         // write the value of mapped to digital pin 3 to set PWM
  delay(100);
}
