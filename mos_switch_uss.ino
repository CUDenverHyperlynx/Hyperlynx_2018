/*     Patrick Tafoya
 *     2018 Hyperlynx
 *     Solenoid Valve Trigger Switch:
 *      Trigger the solenoid valves with the DROK 20203
 *      MOS trigger switch board. Signal initialized by
 *      ultrasonic sensor reading. US sensor is not integral
 *      to code, only used to show successful trigger through
 *      sensor reading. Sensor distance NOT filtered.
 *    */

const int switchPin = 12;
const int triggerPin = 11;
const int echoPin = 10;
bool switchByte = false;

void setup() {
  Serial.begin(9600);
  pinMode(switchPin, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(switchPin, LOW);

}

void loop() {
  static unsigned int distanceCM;
  distanceCM = (unsigned int)(getUltrasonicMeasurement() / 58UL);
  //  If uss reads closer than 10 cm, switchByte to true
  if(distanceCM < 10){
    switchByte = true;
  }
  else{
    switchByte = false;
  }
  //  If true, trigger switch
  if(switchByte){
    digitalWrite(switchPin, HIGH);
  }
  else{
    digitalWrite(switchPin, LOW);
  }
  //  Display current trigger status and distance reading
  Serial.print(switchByte);
  Serial.print("\t\t");
  Serial.println(distanceCM);
}

//  Function for Ultrasonic sensor reading
unsigned long getUltrasonicMeasurement(){
  unsigned long duration;
  unsigned long echoStartTime;
  unsigned long echoStopTime;

  //Trigger line low 2ms
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  //Trigger line high 10ms
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  //Trigger line low
  digitalWrite(triggerPin, LOW);
  //wait for echo
  while(digitalRead(echoPin) != HIGH);
  //Start timer
  echoStartTime = micros();
  //Stop timer when ech revieved
  while(digitalRead(echoPin) != LOW);
  echoStopTime = micros();
  //Measure elapsed time
  duration = echoStopTime - echoStartTime;

  return duration;
  
}
