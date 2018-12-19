/* Hyperlynx small scale wheel test motor code
 *  Author: Eric Stepan
 *  Date: 12/18/18
 *  Tested on 
 *    Arduino Version 1.8.7
 *    Operating System: Windows 10
 *  Description: Recieves power percentage from arduino to run a motor at variable speeds while sensing the rpm and displaying on an LCD.
 */

 //Import libraries
 #include <LiquidCrystal_I2C.h>
 #include <Wire.h>
 #include <stdio.h>

 //Initialize library
 LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


//Declare ints
const int magSensor = 2;        // the magnetic sensor pin
const int ledPin =  13;         // the number of the LED pin
int magSensorState = 0;         // variable for reading the magnetic sensor status
unsigned int rpm;               // rpm reading
int processingInput = 0;        // store motor power from processing
volatile byte pulses;           // number of pulses
unsigned long timeold;          // timer storage variable
unsigned int pulsesperturn = 1; // The number of pulses per revolution
                                // depends on the number of tape strips on motor.


//For takeRading function
void counter()
{
 pulses++; //Update count
}


//Setup
void setup()
{
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  
  // initialize the magnetic sensor pin as an input:
  pinMode(magSensor, INPUT);
  attachInterrupt(0, counter, FALLING);
  pulses = 0;
  rpm = 0;
  timeold = 0;

  Serial.begin(9600);

  // set up the LCD's visual initialization:
  lcd.begin(16, 2);
  
  // Print a message to the LCD.
  lcd.clear();
  lcd.print("Setup Complete");
  delay (2500);
  lcd.clear();
  lcd.print("HyperLynx 2019");
  delay (2500);
}


//Loop
void loop()
{
  takeReading(); //happens once per second      
  magLED();      //turn led on when magnet is in range
  readInput();   //read input from processing if available
}


//takeReading
void takeReading()
{
  if (millis() - timeold >= 1000)
  {
    /*Uptade every one second, this will be equal to reading frecuency (Hz).*/
    //Don't process interrupts during calculations
    detachInterrupt(0);
    
    //Note that this would be 60*1000/(millis() - timeold)*pulses if the interrupt
    //happened once per revolution
    rpm = (60 * 1000 / pulsesperturn )/ (millis() - timeold)* pulses;
    timeold = millis();
    pulses = 0;
    
    //Write it out to serial port
    Serial.print("RPM = ");
    Serial.println(rpm,DEC);

    //Fancy Footwork
    lcd.clear();
    lcd.print("HyperLynx");
    lcd.setCursor(0,1);
    lcd.print("RPM = ");
    lcd.setCursor(6, 1);
    lcd.print(rpm,DEC);
    //Restart the interrupt processing
    attachInterrupt(0, counter, FALLING);
  }
}

//magLED
void magLED()
{
  // read the state of the magnetic Sensor value:
  magSensorState = digitalRead(magSensor);

  // Check if the sensor voltage is pulled low (in range of magnet).
  // If it is, the magSensorState is LOW:
  if (magSensorState == HIGH)
  {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  } 
  else 
  {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  }
  //Serial.println(magSensorState);
}

//readInput
void readInput()
{
  // will be true if 1 or more characters are available to read.
    if( Serial.available()> 0 )
    {
      processingInput = Serial.read();
    }
}
