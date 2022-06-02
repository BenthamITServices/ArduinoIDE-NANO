int potPin = A7; //Pot that can vary between 0-5v connected to Analog 7 pin
int pot = 512; // pot holds the result of the analogRead of the voltage on A7, ranges from 0-1023 i.e. a 10 bit binary number
int mapped = 127; // holds the result of mapping pot over a smaller range to convert to an 8 bit binary number suitable for a PWM analogWrite

void setup() {

// open the serial port at 9600 bps:
Serial.begin(9600);

TCCR2B = TCCR2B & 0b11110000; // clear lower 4 bits of TCCR2B to zeros
TCCR2B = TCCR2B | 0b00001011; // sets lower 4 bits of TCCR2B to 1011
OCR2A = 0xF8; // OCR2A sets the top value for the PWM counter. E8 = 1.08KHz, F8 = 1.01KHz, FF = 977Hz

Serial.print("TCCR2A = ");
Serial.println(TCCR2A, BIN);

Serial.print("TCCR2B = ");
Serial.println(TCCR2B, BIN);

Serial.print("OCR2A = ");
Serial.println(OCR2A, HEX);
Serial.println("=========");
}


void loop() {
  // put your main code here, to run repeatedly:
pot = analogRead(potPin);
mapped = map(pot, 0, 1023, 5, 250);
analogWrite (3,mapped);
delay(100);
}
