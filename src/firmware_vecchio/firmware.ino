#include "ares_joint.h"
#include "ares_drive.h"         //includo le librerie interne create
#include "ares_globals.h"
#include "ares_pins.h"    

void setup() {
  Serial.begin(9600);  
  joint[0].init(dati[0].pins);
  joint[1].init(dati[1].pins);
  joint[2].init(dati[2].pins);
 
}

void loop() {
  Serial.println("Caricato");
  delay(1000);
  
}
