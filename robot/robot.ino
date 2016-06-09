int trig1 = 12;
int echo1 = 13;
int trig2 = 11;
int echo2 = 10;

int val = 0;
float prior[] = {0.2, 0.2, 0.2, 0.2, 0.2};

String sensorResult1, sensorResult2;

long duration, distance, sensor1, sensor2;

void setup() {
  // put your setup code here, to run once:
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  Serial.begin(9600);

}

void loop() {

  // Calculate the the sensors
  calculate(trig1, echo1);
  sensor1 = distance;
  calculate(trig2, echo2);
  sensor2 = distance;

  sensorResult1 = translate(sensor1);
  sensorResult2 = translate(sensor2);

  if(sensorResult1.equals("close") && sensorResult2.equals("far")){
    Serial.print("Robot is currently located at ");
    Serial.println("A");
  }
  else if(sensorResult1.equals("midclose") && sensorResult2.equals("midfar")){
    Serial.print("Robot is currently located at ");
    Serial.println("B");  
  }
  else if(sensorResult1.equals("mid") && sensorResult2.equals("mid")){
    Serial.print("Robot is currently located at ");
    Serial.println("C");    
  }
  else if(sensorResult1.equals("midfar") && sensorResult2.equals("midclose")){
    Serial.print("Robot is currently located at ");
    Serial.println("D");    
  }
  else if(sensorResult1.equals("far") && sensorResult2.equals("close")){
    Serial.print("Robot is currently located at ");
    Serial.println("E");    
  }

  delay(2000);
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
