int trig1 = 12;
int echo1 = 13;
int trig2 = 11;
int echo2 = 10;
int resetButton = 9;
int examineButton = 8;

int val = 0;
int reset = 0;
int examine = 0;

float prior[] = {0.2, 0.2, 0.2, 0.2, 0.2};
float normalize = 0;

String sensorResult1, sensorResult2;

long duration, distance, sensor1, sensor2;

void setup() {
  // put your setup code here, to run once:
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  
  pinMode(resetButton, INPUT);
  pinMode(examineButton, INPUT);
  
  Serial.begin(9600);

  Serial.println("Prior Distribution: ");
  for(int i = 0; i < sizeof(prior) / sizeof(float); i++){
    Serial.print(prior[i]);
    Serial.print(" ");
  }
  Serial.print("\n");

  Serial.println("Setup ready. Ready to localize.");

}

void loop() {

  reset = digitalRead(resetButton);
  examine = digitalRead(examineButton);

  if(reset == HIGH){
    Serial.println("Resetting the distribution to first belief...");
    
    prior[0] = 0.2;
    prior[1] = 0.2;
    prior[2] = 0.2;
    prior[3] = 0.2;
    prior[4] = 0.2;

    for(int i = 0; i < sizeof(prior) / sizeof(float); i++){
      Serial.print(prior[i]);
      Serial.print(" ");
    }
    Serial.print("\n");

    delay(2000);
  }

  if(examine == HIGH){

    // Calculate the the sensors
    calculate(trig1, echo1);
    sensor1 = distance;
    calculate(trig2, echo2);
    sensor2 = distance;
  
    sensorResult1 = translate(sensor1);
    sensorResult2 = translate(sensor2);

    Serial.println(sensorResult1);
    Serial.println(sensorResult2);
  
    Serial.println("Calculating posterior distribution...");
  
    if(sensorResult1.equals("close") && sensorResult2.equals("far") || 
       sensorResult1.equals("far") && sensorResult2.equals("close")){
  
      prior[0] *= 0.8;
      prior[1] *= 0.1;
      prior[2] *= 0.1;
      prior[3] *= 0.1;
      prior[4] *= 0.8;
  
      for(int i = 0; i < sizeof(prior) / sizeof(float); i++){
        normalize += prior[i];
      }
  
      prior[0] /= normalize;
      prior[1] /= normalize;
      prior[2] /= normalize;
      prior[3] /= normalize;
      prior[4] /= normalize;
        
    }
    else if(sensorResult1.equals("midclose") && sensorResult2.equals("midfar") || 
            sensorResult1.equals("midfar") && sensorResult2.equals("midclose")){
  
      prior[0] *= 0.1;
      prior[1] *= 0.8;
      prior[2] *= 0.1;
      prior[3] *= 0.8;
      prior[4] *= 0.1;
  
      for(int i = 0; i < sizeof(prior) / sizeof(float); i++){
        normalize += prior[i]; 
      }
  
      prior[0] /= normalize;
      prior[1] /= normalize;
      prior[2] /= normalize;
      prior[3] /= normalize;
      prior[4] /= normalize;
      
    }
    else if(sensorResult1.equals("mid") && sensorResult2.equals("mid")){
      
      prior[0] *= 0.1;
      prior[1] *= 0.1;
      prior[2] *= 0.8;
      prior[3] *= 0.1;
      prior[4] *= 0.1;
  
      for(int i = 0; i < sizeof(prior) / sizeof(float); i++){
        normalize += prior[i];
      }
  
      prior[0] /= normalize;
      prior[1] /= normalize;
      prior[2] /= normalize;
      prior[3] /= normalize;
      prior[4] /= normalize;
    
    }
  
    Serial.println("Done calculating. Printing out posterior distribution:");
  
    for(int i = 0; i < sizeof(prior) / sizeof(float); i++){
      Serial.print(prior[i]);
      Serial.print(" ");
    }
    Serial.print("\n");

    delay(2000);

    normalize = 0;
    
  }

}

void calculate(int trigPin,int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
}

String translate(int val){

  if(val < 20){
    return "close";  
  }
  else if (val < 40){
    return "midclose";
  }
  else if (val < 60){
    return "mid";  
  }
  else if (val < 80){
    return "midfar";  
  }
  else{
    return "far";  
  }
  
}
