// This sketch will send out a canon D50 trigger signal (probably works with most canons)
// See the full tutorial at http://www.ladyada.net/learn/sensors/ir.html
// this code is public domain, please enjoy!

int IRledPin =  12;    // LED connected to digital pin 12
int buttonPin = 3;     // footswitch connected to digital #3

// The setup() method runs once, when the sketch starts

void setup()   {                
  // initialize the IR digital pin as an output:
  pinMode(IRledPin, OUTPUT);      
  
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH); // pullup on
  
  Serial.begin(9600);
}

void loop()                     
{
  if (true) {
    // footswitch pressed
    Serial.println("Sending IR signal");
  
    SendTVOnCode();
    //SendCanonCode();
     
    delay(3*1000);  // wait 3 seconds (* 1000 milliseconds)
  }
}

// This procedure sends a 38KHz pulse to the IRledPin 
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
  
  cli();  // this turns off any background interrupts
  
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(10);         // hang out for 10 microseconds
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(10);         // hang out for 10 microseconds

   // so 26 microseconds altogether
   microsecs -= 26;
  }
  
  sei();  // this turns them back on
}

void SendTVOnCode(){
pulseIR(8840);
delayMicroseconds(4380);
pulseIR(580);
delayMicroseconds(560);
pulseIR(540);
delayMicroseconds(540);
pulseIR(560);
delayMicroseconds(1620);
pulseIR(600);
delayMicroseconds(540);
pulseIR(560);
delayMicroseconds(540);
pulseIR(560);
delayMicroseconds(540);
pulseIR(560);
delayMicroseconds(560);
pulseIR(540);
delayMicroseconds(560);
pulseIR(540);
delayMicroseconds(1640);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(600);
delayMicroseconds(540);
pulseIR(560);
delayMicroseconds(1620);
pulseIR(580);
delayMicroseconds(1620);
pulseIR(580);
delayMicroseconds(1620);
pulseIR(580);
delayMicroseconds(1620);
pulseIR(580);
delayMicroseconds(1620);
pulseIR(580);
delayMicroseconds(560);
pulseIR(560);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(560);
pulseIR(540);
delayMicroseconds(560);
pulseIR(560);
delayMicroseconds(540);
pulseIR(560);
delayMicroseconds(560);
pulseIR(540);
delayMicroseconds(560);
pulseIR(560);
delayMicroseconds(540);
pulseIR(560);
delayMicroseconds(1620);
pulseIR(580);
delayMicroseconds(540);
pulseIR(560);
delayMicroseconds(1620);
pulseIR(580);
delayMicroseconds(1620);
pulseIR(580);
delayMicroseconds(1620);
pulseIR(580);
delayMicroseconds(1620);
pulseIR(580);
delayMicroseconds(1620);
pulseIR(580);
delayMicroseconds(1620);
pulseIR(580);
delayMicroseconds(39060);
pulseIR(8860);
delayMicroseconds(2180);
pulseIR(580);

}


void SendCanonCode() {
  // This is the code for my particular Canon, for others use the tutorial
  // to 'grab' the proper code from the remote
  
pulseIR(220);
delayMicroseconds(860);
pulseIR(220);
delayMicroseconds(1660);
pulseIR(220);
delayMicroseconds(760);
pulseIR(200);
delayMicroseconds(2740);
pulseIR(220);
delayMicroseconds(1260);
pulseIR(220);
delayMicroseconds(1260);
pulseIR(220);
delayMicroseconds(1120);
pulseIR(220);
delayMicroseconds(2620);
pulseIR(220);
delayMicroseconds(12700);
pulseIR(220);
delayMicroseconds(860);
pulseIR(200);
delayMicroseconds(1000);
pulseIR(220);
delayMicroseconds(740);
pulseIR(220);
delayMicroseconds(720);
pulseIR(220);
delayMicroseconds(720);
pulseIR(220);
delayMicroseconds(2460);
pulseIR(220);
delayMicroseconds(720);
pulseIR(220);
delayMicroseconds(720);
pulseIR(200);
delayMicroseconds(14584);
pulseIR(220);
    
    delay(65);
    
pulseIR(220);
delayMicroseconds(860);
pulseIR(220);
delayMicroseconds(1660);
pulseIR(220);
delayMicroseconds(760);
pulseIR(200);
delayMicroseconds(2740);
pulseIR(220);
delayMicroseconds(1260);
pulseIR(220);
delayMicroseconds(1260);
pulseIR(220);
delayMicroseconds(1120);
pulseIR(220);
delayMicroseconds(2620);
pulseIR(220);
delayMicroseconds(12700);
pulseIR(220);
delayMicroseconds(860);
pulseIR(200);
delayMicroseconds(1000);
pulseIR(220);
delayMicroseconds(740);
pulseIR(220);
delayMicroseconds(720);
pulseIR(220);
delayMicroseconds(720);
pulseIR(220);
delayMicroseconds(2460);
pulseIR(220);
delayMicroseconds(720);
pulseIR(220);
delayMicroseconds(720);
pulseIR(200);
delayMicroseconds(14584);
pulseIR(220);
}

