/*    Patrick Tafoya
 *    2018 Hyperlynx
 *    Solenoid Valve Trigger Switch:
 *      Trigger the solenoid valves with the DROK 200203
 *      MOS trigger switch board. Signal initialized by
 *      serial input.
 */
  //  Arduino pin to Input Signal
const int switchPin = 12;
  //  Boolean value for signal send. Initialize false.
bool switchByte = false;

void setup() {
  Serial.begin(9600);
  pinMode(switchPin, OUTPUT);
  digitalWrite(switchPin, LOW);

}

void loop() {
  while(Serial.available() > 0){
    //  Convert serial input from ASCII value to numerical value
    //  True only when input is greater than zero
    if((Serial.read() - 48) > 0){
    switchByte = true;
    }
    else{  
    switchByte = false;
    } 
  }
    //  Trigger switch when input recieved.
  if(switchByte){
    digitalWrite(switchPin, HIGH);
  }
 else{
    digitalWrite(switchPin, LOW);
  }
  //  Display current trigger status
  Serial.println(switchByte);
}
