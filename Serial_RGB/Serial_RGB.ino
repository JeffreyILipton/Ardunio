#include <Wire.h>
#include <Servo.h>

#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>

#include <CapacitiveSensor.h>

#define  LED3_RED       2
#define  LED3_GREEN     4
#define  LED3_BLUE      3

#define  LED2_RED       5
#define  LED2_GREEN     7
#define  LED2_BLUE      6

#define  LED1_RED       8
#define  LED1_GREEN     10
#define  LED1_BLUE      9

#define  SERVO1         11
#define  SERVO2         12
#define  SERVO3         13

#define  TOUCH_RECV     14
#define  TOUCH_SEND     15

#define  RELAY1         A0
#define  RELAY2         A1

#define  LIGHT_SENSOR   A2
#define  TEMP_SENSOR    A3

#define  BUTTON1        A6
#define  BUTTON2        A7
#define  BUTTON3        A8

#define  JOY_SWITCH     A9      // pulls line down when pressed
#define  JOY_nINT       A10     // active low interrupt input
#define  JOY_nRESET     A11     // active low reset output

AndroidAccessory acc("Google, Inc.",
		     "DemoKit",
		     "DemoKit Arduino Board",
		     "1.0",
		     "http://www.android.com",
		     "0000000012345678");
Servo servos[3];

// 10M ohm resistor on demo shield
CapacitiveSensor   touch_robot = CapacitiveSensor(TOUCH_SEND, TOUCH_RECV);

void setup();
void loop();

void init_buttons()
{
	pinMode(BUTTON1, INPUT);
	pinMode(BUTTON2, INPUT);
	pinMode(BUTTON3, INPUT);
	pinMode(JOY_SWITCH, INPUT);

	// enable the internal pullups
	digitalWrite(BUTTON1, HIGH);
	digitalWrite(BUTTON2, HIGH);
	digitalWrite(BUTTON3, HIGH);
	digitalWrite(JOY_SWITCH, HIGH);
}


void init_relays()
{
	pinMode(RELAY1, OUTPUT);
	pinMode(RELAY2, OUTPUT);
}


void init_leds()
{
	digitalWrite(LED1_RED, 1);
	digitalWrite(LED1_GREEN, 1);
	digitalWrite(LED1_BLUE, 1);

	pinMode(LED1_RED, OUTPUT);
	pinMode(LED1_GREEN, OUTPUT);
	pinMode(LED1_BLUE, OUTPUT);

	digitalWrite(LED2_RED, 1);
	digitalWrite(LED2_GREEN, 1);
	digitalWrite(LED2_BLUE, 1);

	pinMode(LED2_RED, OUTPUT);
	pinMode(LED2_GREEN, OUTPUT);
	pinMode(LED2_BLUE, OUTPUT);

	digitalWrite(LED3_RED, 1);
	digitalWrite(LED3_GREEN, 1);
	digitalWrite(LED3_BLUE, 1);

	pinMode(LED3_RED, OUTPUT);
	pinMode(LED3_GREEN, OUTPUT);
	pinMode(LED3_BLUE, OUTPUT);
}

void init_joystick(int threshold);



void setLED1(int r,int g, int b){
        analogWrite(LED1_RED, r);
     	analogWrite(LED1_GREEN, g);
        analogWrite(LED1_BLUE, b);
}




int colorRGB[3];
int delayVal = 50;
int blnFade = 0;
int h_int;
float h;
int r=0,g=0,b=0;

void h2rgb(float h, int &R, int &G, int &B);
void colorFade();

byte b1, b2, b3, b4, c;
void setup()
{
	Serial.begin(115200);
	Serial.print("\r\nStart");

	init_leds();
	init_relays();
	init_buttons();
	init_joystick( 5 );

        
	// autocalibrate OFF
	touch_robot.set_CS_AutocaL_Millis(0xFFFFFFFF);

	servos[0].attach(SERVO1);
	servos[0].write(90);
	servos[1].attach(SERVO2);
	servos[1].write(90);
	servos[2].attach(SERVO3);
	servos[2].write(90);


	b1 = digitalRead(BUTTON1);
	b2 = digitalRead(BUTTON2);
	b3 = digitalRead(BUTTON3);
	b4 = digitalRead(JOY_SWITCH);
	c = 0;

	acc.powerOn();


}




// Variables will change:
int buttonPushCounter = 1;
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

int getButton1State(){
      // read the pushbutton input pin:
      buttonState = digitalRead(BUTTON1);
    
      // compare the buttonState to its previous state
      if (buttonState != lastButtonState) {
        // if the state has changed, increment the counter
        if (buttonState == HIGH) {
          // if the current state is HIGH then the button
          // wend from off to on:
          buttonPushCounter++;
        } 
        else {
          // if the current state is LOW then the button
          // wend from on to off:
        }
      }
      // save the current state as the last state, 
      //for next time through the loop
      lastButtonState = buttonState;
    
      
      // turns on the LED every four button pushes by 
      // checking the modulo of the button push counter.
      // the modulo function gives you the remainder of 
      // the division of two numbers:
      
      if (buttonPushCounter % 2 == 0) {
        return HIGH;
        buttonPushCounter=2;
      } else {
        buttonPushCounter=1;
        return LOW;
      }
}


void loop()
{
  if(Serial.available() >= 2){
    
    switch( byte( Serial.read() )) {
      case 'r':
        colorRGB[0] = Serial.read();
        blnFade = 0;
        break;
      case 'g':
        colorRGB[1] = Serial.read();
        blnFade = 0;
        break;   
      case 'b':
        colorRGB[2] = Serial.read();
        blnFade = 0;
        break;
      case 'c':
        Serial.flush();
        blnFade = 0;
        break;
      case 'f':
        delayVal = Serial.read();
        Serial.flush();
        colorFade();
        blnFade = 1;
      }
   }
   setLED1(colorRGB[0],colorRGB[1],colorRGB[2]);
   delay(20);
}


void colorFade() {

 while (blnFade == 1) {
 if(Serial.available() ){
   blnFade = 0;
   break; 
 }   
 for(int fadeValue = 0 ; fadeValue <= 1024; fadeValue +=5) {
    h = ((float)fadeValue)/1024;
    h_int = (int) 360*h;
    h2rgb(h,r,g,b);
    if(Serial.available() ){
      blnFade = 0;
      break; 
    } 
    setLED1(r,g,b);
    delay(delayVal);
  }
 }
}

void h2rgb(float H, int &R, int &G, int &B){
  int var_i;
  float S=1, V=1, var_1, var_2, var_3, var_h, var_r, var_g, var_b;
  if ( S == 0 ) {
    R = V * 255;
    G = V * 255;
    B = V * 255;
  } else {
    var_h = H * 6;
    if ( var_h == 6 ) var_h = 0;
    var_i = int( var_h ) ;
    var_1 = V * ( 1 - S );
    var_2 = V * ( 1 - S * ( var_h - var_i ) );
    var_3 = V * ( 1 - S * ( 1 - ( var_h - var_i ) ) );

    if ( var_i == 0 ) {
      var_r = V     ;
      var_g = var_3 ;
      var_b = var_1 ;
    } else if ( var_i == 1 ) {
      var_r = var_2 ;
      var_g = V     ;
      var_b = var_1 ;
    } else if ( var_i == 2 ) {
      var_r = var_1 ;
      var_g = V     ;
      var_b = var_3 ;
    } else if ( var_i == 3 ) {
      var_r = var_1 ;
      var_g = var_2 ;
      var_b = V     ;
    } else if ( var_i == 4 ) {
      var_r = var_3 ;
      var_g = var_1 ;
      var_b = V     ;
    } else {
      var_r = V     ;
      var_g = var_1 ;
      var_b = var_2 ;
    }
    R = (1-var_r) * 255;
    G = (1-var_g) * 255;
    B = (1-var_b) * 255;
  }
}



// ==============================================================================
// Austria Microsystems i2c Joystick
void init_joystick(int threshold)
{
	byte status = 0;

	pinMode(JOY_SWITCH, INPUT);
	digitalWrite(JOY_SWITCH, HIGH);

	pinMode(JOY_nINT, INPUT);
	digitalWrite(JOY_nINT, HIGH);

	pinMode(JOY_nRESET, OUTPUT);

	digitalWrite(JOY_nRESET, 1);
	delay(1);
	digitalWrite(JOY_nRESET, 0);
	delay(1);
	digitalWrite(JOY_nRESET, 1);

	Wire.begin();

	do {
		status = read_joy_reg(0x0f);
	} while ((status & 0xf0) != 0xf0);

	// invert magnet polarity setting, per datasheet
	write_joy_reg(0x2e, 0x86);

	calibrate_joystick(threshold);
}

int offset_X, offset_Y;

void calibrate_joystick(int dz)
{
	char iii;
	int x_cal = 0;
	int y_cal = 0;

	// Low Power Mode, 20ms auto wakeup
	// INTn output enabled
	// INTn active after each measurement
	// Normal (non-Reset) mode
	write_joy_reg(0x0f, 0x00);
	delay(1);

	// dummy read of Y_reg to reset interrupt
	read_joy_reg(0x11);

	for(iii = 0; iii != 16; iii++) {
		while(!joystick_interrupt()) {}

		x_cal += read_joy_reg(0x10);
		y_cal += read_joy_reg(0x11);
	}

	// divide by 16 to get average
	offset_X = -(x_cal>>4);
	offset_Y = -(y_cal>>4);

	write_joy_reg(0x12, dz - offset_X);  // Xp, LEFT threshold for INTn
	write_joy_reg(0x13, -dz - offset_X);  // Xn, RIGHT threshold for INTn
	write_joy_reg(0x14, dz - offset_Y);  // Yp, UP threshold for INTn
	write_joy_reg(0x15, -dz - offset_Y);  // Yn, DOWN threshold for INTn

	// dead zone threshold detect requested?
	if (dz)
		write_joy_reg(0x0f, 0x04);
}


void read_joystick(int *x, int *y)
{
	*x = read_joy_reg(0x10) + offset_X;
	*y = read_joy_reg(0x11) + offset_Y;  // reading Y clears the interrupt
}

char joystick_interrupt()
{
	return digitalRead(JOY_nINT) == 0;
}


#define  JOY_I2C_ADDR    0x40

char read_joy_reg(char reg_addr)
{
	char c;

	Wire.beginTransmission(JOY_I2C_ADDR);
	Wire.write(reg_addr);
	Wire.endTransmission();

	Wire.requestFrom(JOY_I2C_ADDR, 1);

	while(Wire.available())
		c = Wire.read();

	return c;
}

void write_joy_reg(char reg_addr, char val)
{
	Wire.beginTransmission(JOY_I2C_ADDR);
	Wire.write(reg_addr);
	Wire.write(val);
	Wire.endTransmission();
}
