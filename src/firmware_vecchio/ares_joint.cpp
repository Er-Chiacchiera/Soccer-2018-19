#include "ares_joint.h"   //includo la libreria

Joint::Joint() {}  

void Joint::init(uint8_t*pins) {    //funzione di inizializzazione dei pin
                                    
    uint8_t* pin_pwm = &pins[0];    
    uint8_t* pin_dira = &pins[1];   
    uint8_t* pin_dirb = &pins[2];   

    pinMode(*pin_pwm, OUTPUT);      //vado ad impostare i puntatori creati come OUTPUT e gli do come valore                               
    analogWrite(*pin_pwm, 0);      //iniziale a 0

    pinMode(*pin_dira, OUTPUT);     // <------------
    digitalWrite(*pin_dira, 0);    

    pinMode(*pin_dirb, OUTPUT);     // <------------
    digitalWrite(*pin_dirb, 0);

    this-> pin_pwm = pin_pwm;      //vado a dire che le variabili create sulla libreria devono essere uguali 
    this-> pin_dira = pin_dira;    //a le variabili puntatori create nella funzione per non andare a rischiare 
    this-> pin_dirb = pin_dirb;    //di scrivere su un'altra variabile
    this-> pwm=0;
    this-> dir=0;

}
//Controllo velocità 
void Joint::setSpeed(int16_t speed) {  //creo una funzione di nome "setSpeed" passandogli la variabile "speed"
        uint16_t pwm = 0;              //creo 2 variabili 
        uint8_t dir = 0;
 
        if(speed>= 0){                 //gli dico che se la variabile che gli sto passando è >= 0
            pwm = speed;               //la variabile pwm diventa la variabile che gli sto passando 
            dir = 0;                   //e dir è = 0
        }
        else {                         //altrimenti il pwm diventa la variabile che gli sto passando negativa
            pwm = - speed;             // e la variabile dir la setto = 1
            dir = 1;
        }
        if(pwm > 255){                //e se la variabile pwm è maggiore di 255 la fisso a 255 
            pwm = 255;                // (per evitare di andare a scrivere un dato più grande di quello 
        }                             //che la variabile nella libreria può contenere, ossia 2 byte)
        
        this-> pwm = pwm;             //riscrivo questo per non andare a rischiare di scrivere su 
        this-> dir = dir;             //altre variabili
}

void Joint::handle() {              //creo una funzione di nome handle
    digitalWrite(pin_dira, dir);    //scrivo in digitale che la variabile del pin della direzione A nella 
    digitalWrite(pin_dirb, !dir);   //libreria è la variabile "dir" nella funzione di setSpeed però dico che 
    analogWrite(pin_pwm, pwm);      //la variabile del pin dell direzione B non deve essere la variabile "dir", 
                                    //e scrivo in analogico che il pin del pwm creato nella libreria deve 
                                    //essere il valore della variabile pwm creata nella funzione di setSpeed
}
