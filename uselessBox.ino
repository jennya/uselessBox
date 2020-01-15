
#include "globals.h"
#include "box.h"

Box uselessBox;

void setup() 
{
  Serial.begin(9600);
  
  uselessBox.Initialize(
    SWITCH_PIN,
    POT_PIN,
    DIMMER_PIN,
    SERVO_PIN,
    SAMPLES);
}

void loop() {
  uselessBox.UpdateState();
}
