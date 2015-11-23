

// Declare variables for input/output pins
int measurePin = 0; // Analog pin 0 used as output voltage from sensor to Arduini
int ledPower = 12; // Digital pin 12 used as ON/OFF for sensor LED
int fanpowerPin= 8; // Digital pin 8 used as ON/OFF for sensor fan

// Declare variables for pulselength, pulse width, and when to read the output signal
int samplingTime = 280; // Sample  0.28ms into the pulse width
int deltaTime = 40; // time left of pulse width after read value
int sleepTime = 9680; //Pulse period 10ms. 10000ms-320ms=9680ms to wait before next led pulse

// Declare variables used to store data
float voMeasured = 0; // Stores measured output (0-1023) from sensor
float calcVoltage = 0; // Calculate actual voltage output from sensor
float dustDensity = 0; // Calculate dust density [ug/m3]
float vS = 0; // Vs reference value (no  fan running for a 100 readings minutes

// Declare variables used to store reference voltage when sensor fan is not running
int countReading = 600; // Stores number of sensor readings when fan is not running
int vSrawvalue =0; // variable to store raw value from sensor when fan is not runnigng
float vSvoltage =0; // Variable  to store output voltge from sensor when fan is not running
float vStotal =0; // variable to keep track of all readings to define Vs Reference voltage

void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT); // set pin 12 as OUTPUT
  pinMode(fanpowerPin, OUTPUT); // set pin 12 as OUTPUT
  
  // Function to store a Vs referennce value when sensor fan is not running.
  // Reference value will be recalculated every time the system reboots.
  // The reference value will be calculated by reading the sensor output
  // voltage and averaged for "countReading" seconds.


  digitalWrite(fanpowerPin,LOW); // power off sensorFan
  delay(2000); //Wait 2seconds

  Serial.println("Preparing Vs Reference voltage");
  Serial.print("Set time for Vs ref value: ");
  Serial.print(countReading);
  Serial.println(" seconds");
  
  for (int i=0; i<=countReading; i++) {
  delay(200); // Wait 1 second between each reading
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime); //Wait samplingTime before reading V0output
  vSrawvalue = analogRead(measurePin); // read the dust value
  delayMicroseconds(deltaTime); //Wait deltaTime before shuttign  of LED
  digitalWrite(ledPower,HIGH); // turn the LED off
  vSvoltage=  vSrawvalue*5.0/1024; // Calculate actual voltage [V]
  vStotal = vStotal+vSvoltage; //Adding up all read voltages

  Serial.print(" Vs Output [mV]: "); // Print Vs Output to see progress
  Serial.print(vSvoltage*1000); // print mV
  Serial.print(" VsTotal [mV]: "); // Print Vs Total to see progress
  Serial.println(vStotal*1000);
  }
// Calculate Vs reference value

  vS=vStotal /(countReading) * 1000; //Calculate average output voltage when fan is not running. REFERENCE VALUE

 
  digitalWrite(fanpowerPin,HIGH); // power on sensorFan
  delay(5000); // Wait 5 seconds before starting void loop
  
}
 
void loop(){

// Read the sensor and print outputs...

  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime); //Wait samplingTime before reading V0output
 
  voMeasured = analogRead(measurePin); // read the dust value
 
  delayMicroseconds(deltaTime); //Wait deltaTime before shuttign  of LED
  digitalWrite(ledPower,HIGH); // turn the LED off
  
  delayMicroseconds(sleepTime); // No use in this example
 
  calcVoltage = voMeasured * (5.0 / 1024)*1000; // Calculate output voltage from Raw analog signal to mV
 
  dustDensity = 0.6 * (calcVoltage-vS); //calculate dust voltage according to sensor datasheet formula, BETA=1
 
  Serial.print("Vs [mV]: ");
  Serial.print(vS);
  
  Serial.print(" Raw Signal (0-1023): ");
  Serial.print(voMeasured);
 
  Serial.print(" V0 [mV]: ");
  Serial.print(calcVoltage);

  Serial.print(" (V0-Vs) [mV]: ");
  Serial.print(calcVoltage - vS);
 
  Serial.print(" Dust density [ug/m3]:");
  Serial.println(dustDensity);
 
  delay(2000); // Wait 2 seconds between each reading/printing
}


