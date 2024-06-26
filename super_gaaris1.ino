//initializing the rgb strip pins
#define b 6 //blue
#define g 5 //green
#define r 3 //red

//initializing the ultrasonic sensor pins

#define echoPin 8
#define trigPin 12

//initializing the trigger distances of colour alerts
#define trigDist1 30
#define trigDist2 10

long duration;
int distance; 
bool fade=true;

void setup() {
  Serial.begin(9600);
  pinMode(g,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(r,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}


void loop() {
  calDistance(); //calling the function that will calculate the distance
  if(distance<=trigDist1 && distance>trigDist2){ //stage 1 trigger distance
    fadedOrange(3);
    fade=true;
  }
  else if(distance<=trigDist2){ //stage 2 trigger distance
    fadedRed(3);
    fade=true;
  }
  else{
    fadeInBlue(); //idle
  }
}

void calDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; //calculating distance using the distance = speed of sound * time taken/2
  Serial.println(distance);
}

void fadedRed(int val){ //function to get a faded red blink
    for(int i=255; i>0; i-=val){
      analogWrite(r, i);      
      analogWrite(g, 255);
      analogWrite(b, 255);
      delay(5);
    }
    for(int i=0; i<255; i+=val){
      analogWrite(r, i);      
      analogWrite(g, 255);
      analogWrite(b, 255);
      delay(5);
    }
}

void fadedOrange(int val){ //function to get a faded orange blink
    for(int i=255; i>0; i-=val){
      analogWrite(r, i);      
      analogWrite(b, 255);
      analogWrite(g, i>230?i:230);
      delay(5);
    }
    for(int i=0; i<255; i+=val){
      analogWrite(r, i);      
      analogWrite(b, 255);
      analogWrite(g,i<230?240:i);
      delay(5);
    }
}

void fadeInBlue(){ //Blue fade in 
  if(fade==true){
    for(int i=255; i>0; i-=1){
        analogWrite(g, 255);
        analogWrite(r, 255);
        analogWrite(b, i); 
        delay(5); 
     }
  }
  fade=false;
  analogWrite(g, 255);
  analogWrite(r, 255);
  analogWrite(b, 0);
}