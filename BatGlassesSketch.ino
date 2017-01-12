//BatGlasses Sketch
//ENGSCI 1050
//Purpose: To provide vibratory feedback at varying intensity when within vicinity of an obstacle
//Written by: Max Edell
//Date: February 12, 2014


//Initialize pins for ping sensors and vibratory motors as arrays
int pingPins[] = {7,8};
int feedbackPins[] = {5,6};

//Initialize names for differentiation of sensors in serial monitor and testing
char *pingString[] = {"Right", "Left"};

//Setup function, runs once at initialization of sketch
void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
}

//Loop (main) function
void loop()
{
  unsigned long cmDistance;
  for(int i=0; i < 2; i++)
  {
    
    //Call ping function and return distance in cm to cmDistance
    cmDistance = ping(i);
    
    
    //Option 1: Using PWM on pins 5,6 vary the vibratory force based on 5 cases:
    //1) object not detected within ability of the sensor -> 0% duty cycle (no vibration felt)
    //2) object detected at a distance between 150cm and 250cm -> 10% duty cycle
    //3) object detected at distance between 90cm and 150cm -> 30% duty cycle
    //4) object detected at distance between 90cm and 30cm -> 70% duty cycle
    //5) object detected at distance closer than 30cm -> 100% duty cycle (full vibration felt)
  if(cmDistance >= 150)
  {
    analogWrite(feedbackPins[i],25);
  }
  else if(cmDistance < 150 && cmDistance >= 90)
  {
    analogWrite(feedbackPins[i],76);
  }
   else if(cmDistance < 90 && cmDistance >= 30)
  {
    analogWrite(feedbackPins[i],178);
  }
  else if(cmDistance < 30)
  {
    analogWrite(feedbackPins[i],255);
  }

  
  
  
  //Option 2: Using PWM based on linearly decreasing function
  //y = duty cycle (0-255)
  //x = distance (cm) (1-250)
  
 /* if(cmDistance<=250&&cmDistance>=1)
  {
    int pwm = 195-cmDistance;
    analogWrite(feedbackPins[i],pwm);
  }*/
  
  
  //Option 3: Using PWM based on exponential decay
  //
  
    //Serial print the distance for analyzing accuracy and performing testing
    Serial.print(pingString[i]);
    Serial.print(cmDistance);
    Serial.print("cm, ");    
    delay(50);
  }
  Serial.println();
  delay(50);
} 

//Ping function
unsigned long ping(int i)
{
  unsigned long echoDuration;

  pinMode(pingPins[i], OUTPUT); // Switch pingPin to output
  digitalWrite(pingPins[i], LOW); // Send low pulse to clear interference
  delayMicroseconds(2); // Wait for 2 microseconds
  digitalWrite(pingPins[i], HIGH); // Send high pulse to be detected
  delayMicroseconds(5); // Wait for 5 microseconds
  digitalWrite(pingPins[i], LOW); // Stop pulse
  pinMode(pingPins[i], INPUT); // Switch pingPin to input
  digitalWrite(pingPins[i], HIGH); // Turn on pullup resistor
  echoDuration = pulseIn(pingPins[i], HIGH); //Listen for echo

  //Convert echo duration (time in microseconds) into distance in cm and return value to main function
  //Speed of sound is 340.29m/s or 29.387 microseconds/cm
  //so divide echo duration by twice this value to get half 
  //the distance for the pulse to get to the object and return
  return (echoDuration / 58.77);
}
