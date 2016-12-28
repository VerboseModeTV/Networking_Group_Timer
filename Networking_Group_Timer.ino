/*

  Networking Group Timer
  
  Created by: Chad Lawson <chad@verbosemode.tv>
  Version: 1.0

*/

// Assign the LEDs to pins
#define RED 6
#define GREEN 5
#define BLUE 3
#define TILT 8

// Assign times to the colors
#define gTime 60
#define yTime 90
#define rTime 120
#define BOUNCE 60

// Since we are using a CA LED we need to work backwards
#define COMMON_ANODE

// Define our variables
long start;
boolean running = true;
boolean tiltState;
int bounceCheck = 0;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(TILT, INPUT);
    
  // Initialize our timer
  setColor(0,0,0);
  start = millis();
  
  // Let's try it
  Serial.begin(9600);
  Serial.println("Let's go!");
  
} // setup

void loop() {
  
  tiltState = digitalRead(TILT);
  if(tiltState == LOW)
  {
    Serial.print("Tilt!: ");
    if(bounceCheck > BOUNCE) {    
        running = false;
    } else {
        bounceCheck++;
    }
    Serial.println(bounceCheck);
  } else {
    if(bounceCheck > 0) {
      bounceCheck--;
    }
  }
  
  if(running == true) {
    
    int secs = getTime();
    
    switch(secs) {
      
      case 0:
        setColor(4,4,4);
        break;
      
      case gTime:
        setColor(0,32,0);
        break;
  
      case yTime:
        setColor(16,32,0);
        break;

      case rTime:
        setColor(32,0,0);
        break;
        
    } // switch
        
  } // if(running)
  
  else {

    setColor(16,0,16);
    start = millis();
    running = true;
    
  } // else 
  
} // loop

int getTime() {
  long delta = millis() - start;
  int secs = delta / 1000;
  return secs;
}

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(RED, red);
  analogWrite(GREEN, green);
  analogWrite(BLUE, blue);  
}

/*
  Version History
  
  1.0 - Initial Version (141220)
  
*/
