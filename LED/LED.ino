int lowIn = A0;
int midianIn = A1;
int highIn = A2;

void setup() {
  Serial.begin(9600);   //Set the baud rate of the comunication
  pinMode(lowIn,INPUT);    //Define the pin as input
  pinMode(midianIn,INPUT);
  pinMode(highIn,INPUT);
}

void loop() {
  //Read the analog value
  float lowVal = analogRead(lowIn);
  float midianVal = analogRead(midianIn);
  float highVal = analogRead(highIn);
  
  //Divide by 205 to obtain a range from 0 to 5V
  float lowVolt = lowVal/205;
  float midianVolt = midianVal/205;
  float highVolt = highVal/205;
  
  //Use serial.print to send the data in a "text" format
  //Serial.println(lowVolt);
  //Serial.println(midianVolt);
  Serial.println(highVolt);
  delay(50);//Small delay between each data send 
}
