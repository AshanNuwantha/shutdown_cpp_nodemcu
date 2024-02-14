#include <dummy.h>
#define LED 2
#define RELAYPIN 5
#define PUSHBUTTON 4

#define OFF 1
#define ON 2
#define NONE 0

unsigned long buttonPressTime;
unsigned long buttonreleaseTime;


void setup() {
  pinMode(LED, OUTPUT);
  pinMode(RELAYPIN, OUTPUT);
  pinMode(PUSHBUTTON, INPUT_PULLUP);

  Serial.begin(115200); //Set the baudrate to 115200
}
short buttonEventListener(){

  if (digitalRead(PUSHBUTTON) == HIGH) {
    buttonPressTime = millis();
     while(digitalRead(PUSHBUTTON) == HIGH){
        buttonreleaseTime = millis();
     }
    if((buttonreleaseTime - buttonPressTime) > 1000){
      return OFF;
    }else if((buttonreleaseTime - buttonPressTime) > 300 && (buttonreleaseTime - buttonPressTime) < 700){
      return ON;
    }
  }else{
    buttonPressTime = 0;
    buttonreleaseTime = 0;
    return NONE;
  }
  return NONE;
}

void powerBoardEventHandler(short msg){
  if(msg == OFF){
    Serial.write("OFF");
  }else if(msg == ON){
    Serial.write("ON");
  }else if(msg == NONE);
}

void loop() {
  powerBoardEventHandler(buttonEventListener());
}
