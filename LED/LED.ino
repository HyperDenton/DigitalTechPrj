//Variables
int lowIn = A0, midianIn = A1,highIn = A2; //Analog read pins
int level = 0, currentLevel = 0;  // 0 -> Low, 1 -> Median, 2 -> High
int resetHighPin = 3, resetMedianPin = 2, resetValue = 4; //Reset pins
int lowLEDPin = 9, medianLEDPin = 10, highLEDPin = 11; //Output pins
boolean isChanged = false,isRest = false; //status mark

void setup() {
  Serial.begin(9600);   
  
  //Set analog input pins
  pinMode(lowIn,INPUT);    
  pinMode(midianIn,INPUT);
  pinMode(highIn,INPUT);
  
  //Set reset pins and attach interrupt
  pinMode(resetMedianPin, INPUT_PULLUP);
  pinMode(resetHighPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(resetMedianPin), resetMedian, RISING);
  attachInterrupt(digitalPinToInterrupt(resetHighPin), resetHigh, RISING);
  
  //Set output pins
  pinMode(lowLEDPin, OUTPUT); 
  pinMode(medianLEDPin, OUTPUT);
  pinMode(highLEDPin, OUTPUT);
  
  //Initial output
  Serial.print(resetValue);
}

void loop() {
  //Small delay between each data send 
  delay(1000);
  
  //Read the analog value
  float lowVal = analogRead(lowIn);
  float midianVal = analogRead(midianIn);
  float highVal = analogRead(highIn);
  
  //Divide by 205 to obtain a range from 0 to 5V
  float lowVolt = lowVal/205;
  float midianVolt = midianVal/205;
  float highVolt = highVal/205;

  //When the sensor feels the megnet, the voltage drops form 5 to around 0.12V
  if(lowVolt < 0.5) {
    currentLevel = 0;
    if(currentLevel != level){
      isChanged = true;
      level = currentLevel;
    }
  }
  
  if(midianVolt < 0.5) {
    currentLevel = 1;
    if(currentLevel != level){
      isChanged = true;
      level = currentLevel;
    }
  }
  
  if(highVolt < 0.5) {
   currentLevel = 2;
    if(currentLevel != level){
      isChanged = true;
      level = currentLevel;
    }
  }
  
  //Only send message via bluetooth when value is changed by itself
  if(isChanged && !isRest){
    Serial.print(level);
    isChanged = false;
  }

  //Send message when value is reset
  if(isRest){
    Serial.print(resetValue);
    isRest = false;
  }

  //show the level on level indicate LEDs
  if(level == 0){
    digitalWrite(lowLEDPin, HIGH);
    digitalWrite(medianLEDPin, LOW);
    digitalWrite(highLEDPin, LOW);
  }
  
  if(level == 1){
    digitalWrite(lowLEDPin, HIGH);
    digitalWrite(medianLEDPin, HIGH);
    digitalWrite(highLEDPin, LOW);
  }
  
  if(level == 2){
    digitalWrite(lowLEDPin, HIGH);
    digitalWrite(medianLEDPin, HIGH);
    digitalWrite(highLEDPin, HIGH);
  }

}

//Reset functions
void resetMedian(){
  level = 1;
  resetValue = 5;
  isRest = true;
}

void resetHigh(){
  level = 2;
  resetValue = 6;
  isRest = true;
}
