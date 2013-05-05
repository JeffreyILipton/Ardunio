


void setup()
{
	Serial.begin(9600);
	Serial.print("\r\nStart");
}


void loop()
{
  if(Serial.available() >= 2){
    
    switch( byte( Serial.read() )) {
      case 'r':
        colorRGB[0] = Serial.read();
        break;
      case 'g':
        colorRGB[1] = Serial.read();
        break;   
      case 'b':
        colorRGB[2] = Serial.read();
        break;
      }
   }
   delay(20);
}


