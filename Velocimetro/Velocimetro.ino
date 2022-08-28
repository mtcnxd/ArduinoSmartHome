const int ledPin =  LED_BUILTIN;
const long interval = 1000;
unsigned long previousMillis = 0;

int rpmCounter = 0;
int rpmSensor  = 2;     // sensor Pin
int diametroRueda = 1;  // meters

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(rpmSensor, INPUT);
}

void loop()
{
  if (digitalRead(rpmSensor)) {
    digitalWrite(ledPin, HIGH);
    rpmCounter++;
  }
  
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    int rpmResult = rpmCounter * 30;
    int distancia = rpmResult * diametroRueda;
    int velocidad = distancia / 2;
    
    Serial.println("R.P.M: " + (String) rpmResult);
    Serial.println("SPEED: " + (String) velocidad);
    rpmCounter = 0;
  }
}
