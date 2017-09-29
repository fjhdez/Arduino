/*
  Control Arduino Wave
 */
int RST = A3;
int CLK = A4;
int DAT = A5; 
    
    
void setup() {   
    
    
    pinMode(RST, OUTPUT);
    pinMode(CLK, OUTPUT); 
    pinMode(DAT, OUTPUT);
    
    
    digitalWrite(RST, HIGH);
    digitalWrite(CLK, HIGH);
    digitalWrite(DAT, HIGH);
    
    digitalWrite(RST, LOW);
    delay(5);
    digitalWrite(RST, HIGH);
    delay(300);
}

void loop() {
/*
Serial.print(0x7E);
Serial.print(0x07);
Serial.print(0xB0);
Serial.print(0x30);
Serial.print(0x31);
Serial.print(0x30);
Serial.print(0x30);
Serial.print(0x32);
Serial.print(0x7E);  */





  
  
  send(0x0000);
  delay(600000);
  send(0x0001);
  delay(600000);
  send(0x0002);
  delay(600000);
  send(0xFFFE);  
  while(1);
}
void send(int addr)
{
  digitalWrite(CLK, LOW);
  delay(2);
  for (int i=15; i>=0; i--)
  { 
    delayMicroseconds(50);
    if((addr>>i)&0x0001 >0)
      {
        digitalWrite(DAT, HIGH);
        //Serial.print(1);
      }
    else
       {
         digitalWrite(DAT, LOW);
         Serial.print(0);
       }
    delayMicroseconds(50);
    digitalWrite(CLK, HIGH);
    delayMicroseconds(50);
    
    if(i>0)
    digitalWrite(DAT, LOW);
    else
    digitalWrite(DAT, HIGH);
    delayMicroseconds(50);
    
    if(i>0)
    digitalWrite(CLK, LOW);
    else
    digitalWrite(CLK, HIGH);
  }
  
  delay(20); 
}



