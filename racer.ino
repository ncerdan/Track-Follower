//define pins
int rLED = 4; //D4
int gLED = 3; //D3
int bLED = 2; //D2
int LEDs[] = {rLED, gLED, bLED};

int rMOTOR = 10; //D10
int lMOTOR = 9;  //D9

int lSENSOR = A2; //A2
int mSENSOR = A1; //A1
int rSENSOR = A0; //A0

//define pin types
void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(LEDs[i], OUTPUT);
  }

  pinMode(rMOTOR, OUTPUT);
  pinMode(lMOTOR, OUTPUT);
}


//define vars to be used in loop
int inputL, inputM, inputR;

//define routine
void loop() {
  /* Read IR Sensor Input */
  inputL = analogRead(lSENSOR);
  inputM = analogRead(mSENSOR);
  inputR = analogRead(rSENSOR);

  /* Normalize Base Values to ~1*/
  inputL = inputL - 45;
  inputM = inputM - 42;
  inputR = inputR - 190;

  /* Normalize Scaling */ 
  inputL = inputL * 1;
  inputM = inputM * 2;
  inputR = inputR * 1; 

  /* Define constants */
  int L_THRESHOLD = 125;
  int M_THRESHOLD = 200;
  int R_THRESHOLD = 200;
  int GO = 100;
  int TURN = 100;
  int STOP = 0;
 
  if (inputL > L_THRESHOLD && inputM > M_THRESHOLD && inputR > R_THRESHOLD) {
    //stop
    digitalWrite(bLED, HIGH);
    digitalWrite(rLED, HIGH);
    digitalWrite(gLED, LOW);
    
    analogWrite(rMOTOR, STOP);
    analogWrite(lMOTOR, STOP);
    while(1){} //endless loop
  } else if (inputL > L_THRESHOLD) {
    //left turn       
    digitalWrite(bLED, HIGH);
    digitalWrite(rLED, LOW);
    digitalWrite(gLED, LOW);

    analogWrite(lMOTOR, STOP);
    analogWrite(rMOTOR, TURN);
  } else if (inputR > R_THRESHOLD) {
    //right turn    
    digitalWrite(rLED, HIGH);
    digitalWrite(bLED, LOW);
    digitalWrite(gLED, LOW);

    analogWrite(rMOTOR, STOP);
    analogWrite(lMOTOR, TURN);
  } else {
    //straight
    digitalWrite(gLED, HIGH);
    digitalWrite(rLED, LOW);
    digitalWrite(bLED, LOW);

    analogWrite(rMOTOR, GO);
    analogWrite(lMOTOR, GO);
  } 
  
  delay(50);
}
