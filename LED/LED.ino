int lowIn = A0;
int midianIn = A1;
int highIn = A2;
int level = 0;  // 0 -> Low, 1 -> Median, 2 -> High
int currentLevel = 0;
int resetHighPin = 3;
int resetMedianPin = 2;
int resetValue = 4;
int lowLEDPin = 9;
int medianLEDPin = 10;
int highLEDPin = 11; 

boolean isChanged = false;
boolean isRest = false;

void setup() {
  Serial.begin(9600);   //Set the baud rate of the comunication
  pinMode(lowIn,INPUT);    //Define the pin as input
  pinMode(midianIn,INPUT);
  pinMode(highIn,INPUT);
  
  pinMode(resetMedianPin, INPUT_PULLUP);
  pinMode(resetHighPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(resetMedianPin), resetMedian, RISING);
  attachInterrupt(digitalPinToInterrupt(resetHighPin), resetHigh, RISING);

  pinMode(lowLEDPin, OUTPUT); 
  pinMode(medianLEDPin, OUTPUT);
  pinMode(highLEDPin, OUTPUT);
  
  Serial.print(resetValue);  //default notification
}

void loop() {
  delay(1000);//Small delay between each data send 
  //Read the analog value
  float lowVal = analogRead(lowIn);
  float midianVal = analogRead(midianIn);
  float highVal = analogRead(highIn);
  
  //Divide by 205 to obtain a range from 0 to 5V
  float lowVolt = lowVal/205;
  float midianVolt = midianVal/205;
  float highVolt = highVal/205;
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
  
  
  if(isChanged && !isRest){
    Serial.print(level);
    isChanged = false;
  }

  if(isRest){
    Serial.print(resetValue);
    isRest = false;
  }

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
