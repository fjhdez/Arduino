

int RST = A3;
int CLK = A4;
int DAT = A5; 



void setup() {
  pinMode(RST, OUTPUT);
  
  digitalWrite(RST, HIGH);    
  digitalWrite(RST, LOW);
  delay(5);
  digitalWrite(RST, HIGH);
  
  Serial.begin(9600);
  
Serial.write(0x01);
Serial.write(0x01);
Serial.write(0x01);
Serial.write(0x01);
Serial.write(0x01);
Serial.write(0x01);
Serial.write(0x01);
Serial.write(0xFE);  
Serial.write(0xFF);  
}

void loop() {
Serial.write(0xFE);  
Serial.write(0xFF);
delay(1000);

}
