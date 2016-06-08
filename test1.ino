int trig1 = 12;
int echo1 = 13;
int trig2 = 11;
int echo2 = 10;

int val = 0;

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
  calculate(trig1, echo1);
  sensor1 = distance;
  calculate(trig2, echo2);
  sensor2 = distance;

  Serial.print("Sensor 1: ");
  Serial.println(sensor1);
  Serial.print("Sensor 2: ");
  Serial.println(sensor2);
  delay(1000);
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
