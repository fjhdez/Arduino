
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "2d24872151984d489cef8e43c62f43f2";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AMPUYENTA";
char pass[] = "";
int ledPin = 12;
long startsecondswd;            // weekday start time in seconds
long stopsecondswd;             // weekday stop  time in seconds
long nowseconds;                // time now in seconds
BlynkTimer timer;
WidgetRTC rtc;
String displaycurrenttimepluswifi;
int ledState = LOW;
int butState;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin , OUTPUT); 
  setSyncInterval(1);
  rtc.begin();
  //Blynk.begin(auth, ssid, pass, IPAddress(213, 32, 90, 71));
  Blynk.begin(auth, ssid, pass);
   int mytimeout = millis() / 1000;
  while (Blynk.connect() == false) { // try to connect to server for 10 seconds
      delay(1000);
      setSyncInterval(900000);  //every 15min
    }


  timer.setInterval(10000L, activeSalida);  
  timer.setInterval(5000L, clockvalue);  // check value for time
  clockvalue();
}

void activeSalida() {
   Blynk.syncVirtual(V0); // sync timeinput widget
   //Serial.println("activeSalida");
}


void clockvalue() // Digital clock display of the time
{

 int gmthour = hour();
  if (gmthour == 24){
     gmthour = 0;
  }
  String displayhour =   String(gmthour, DEC);
  int hourdigits = displayhour.length();
  if(hourdigits == 1){
    displayhour = "0" + displayhour;
  }
  String displayminute = String(minute(), DEC);
  int minutedigits = displayminute.length();  
  if(minutedigits == 1){
    displayminute = "0" + displayminute;
  }  

  displaycurrenttimepluswifi = "Clock:  " + displayhour + ":" + displayminute;
  Blynk.setProperty(V3, "label", displaycurrenttimepluswifi);

  
}

BLYNK_WRITE(V0)
{
TimeInputParam t(param);

  // Process start time
  if (butState) {
    ledState = HIGH;
    updateLed();  
  } 
  else if (t.hasStartTime() && t.hasStopTime())
  {
    nowseconds = ((hour() * 3600) + (minute() * 60) + second());
    startsecondswd = (t.getStartHour() * 3600) + (t.getStartMinute() * 60);
    stopsecondswd = (t.getStopHour() * 3600) + (t.getStopMinute() * 60);
    
    if(nowseconds >= startsecondswd && nowseconds <= stopsecondswd + 60){    
         ledState = HIGH;
     } else {
         ledState = LOW;
     }
     updateLed();
  }
}

BLYNK_WRITE(V1) {
  butState = param.asInt();
  Blynk.syncVirtual(V0);
}

void updateLed() {
  digitalWrite(ledPin, ledState);
  Blynk.virtualWrite(V2, ledState);
}

void loop() {
  // put your main code here, to run repeatedly:

  Blynk.run();
  timer.run();

}
