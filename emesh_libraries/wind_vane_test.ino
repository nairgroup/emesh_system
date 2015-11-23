//This arduino code is for use with the sparkfun SEN-08942 Wind Vane/Anemometer

//Initialization of variables
float wind_count; //For determining wind speed; need float for math later in the code


void setup() {
  Serial.begin(9600); //Opening serial port to the computer monitor

  //Creation of functions to count anemomometer revolutions
  //go to wind_increment function on Rising edge of pin 2, the pin where the anemometer is attached
  attachInterrupt(digitalPinToInterrupt(2), wind_increment, RISING);

  
}

void loop() {
  //Setting the Arduino to print observations every 10 seconds
  delay(10000); //units of delay are milleseconds
  
  //Creation of header for data points
  Serial.print("Wspd m/s");
  Serial.print("\t");
  Serial.println("Wdir V"); //Must be converted from volts in post-processing

  //Reading and printing observations
  Serial.print(24.0/36.0*(wind_count/10.0)); //Change denominator to number of seconds of measurement time
                                               //(24.0/36.0) is derived from the wind system's data sheet
  wind_count = 0; //Reseting wind_count for next cycle
  Serial.print("\t");
  Serial.print(analogRead(0)*0.0049); //0.0049 converts analogRead value to a voltage, for 5V arduinos
  
}


//helper function that increments the anemometer revolution count
void wind_increment() {
  wind_count++;
}
