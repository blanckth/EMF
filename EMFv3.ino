#define NUMREADINGS 30
int senseLimit = 1111;
int val = 0;
int probePin = A0;
int LED1 = 3;
int LED2 = 5;
int LED3 = 6;
int LED4 = 9;
int buzzer = 12;
int buzzerTone = 0;
int readings[NUMREADINGS];
int index = 0;
int total = 0;
int average = 0;
void compTest()
{
  analogWrite(LED1, 255);
  delay(666);
  analogWrite(LED2, 255);
  delay(666);
  analogWrite(LED3, 255);
  delay(666);
  analogWrite(LED4, 255);
  delay(666);
  analogWrite(LED4, 0);
  delay(333);
  analogWrite(LED3, 0);
  delay(333);
  analogWrite(LED2, 0);
  delay(333);
  analogWrite(LED1, 0);
  delay(333);
  analogWrite(LED4, 255);
  tone(buzzer, 666);
  delay(666);
  noTone(buzzer);
  analogWrite(LED4, 0);
  delay(333);
}
void setup()
{
  pinMode(LED1, OUTPUT);
  delay(66);
  pinMode(LED2, OUTPUT);
  delay(66);
  pinMode(LED3, OUTPUT);
  delay(66);
  pinMode(LED4, OUTPUT);
  delay(66);
  pinMode(buzzer, OUTPUT);
  delay(66);
  compTest();
  Serial.begin(9600);
  for (int i = 0; i < NUMREADINGS; i++)
    readings[i] = 0;
}

void loop()
{
  val = analogRead(probePin);
  val = constrain(val, 0, senseLimit);
  int sLim = senseLimit;
  if ( senseLimit > 255 ){
    sLim = 255;
  }
  val = map(val, 0, sLim, 0, 1023);
  total -= readings[index];
  readings[index] = val;
  total += readings[index];
  index = (index + 1);
  if (index >= NUMREADINGS) index = 0;
  average = total / NUMREADINGS;
  if (average < 128) {
    analogWrite(LED1, map(average, 0, 1023,0,255));
    buzzerTone = map(average, 0, 1023, 111, 666);
    tone(buzzer, buzzerTone);
    analogWrite(LED2, 0);
    analogWrite(LED3, 0);
    analogWrite(LED4, 0);
  }
  else 
  {
    analogWrite(LED1, map(average, 0, 1023,1,255));
    buzzerTone = map(average, 0, 1023, 111, 666);
    tone(buzzer, buzzerTone);
    if (average < 256)
    {
      analogWrite(LED2, 0);
      analogWrite(LED3, 0);
      analogWrite(LED4, 0);
    }
    else
    {
      analogWrite(LED1, map(average, 0, 1023,1,255));
      analogWrite(LED2, map(average, 0, 1023,1,255));
      buzzerTone = map(average, 0, 1023, 222, 666);
      tone(buzzer, buzzerTone);
      if (average < 512)
      {
        analogWrite(LED3, 0);
        analogWrite(LED4, 0);
      }
      else
      {    
        analogWrite(LED1, map(average, 0, 1023,1,255));
        analogWrite(LED2, map(average, 0, 1023,1,255));
        analogWrite(LED3, map(average, 0, 1023,1,255));
        buzzerTone = map(average, 0, 1023, 222, 666);
        tone(buzzer, buzzerTone);
        if (average < 768)
        {
          analogWrite(LED4, 0);
        }
        else
        {    
          analogWrite(LED1, map(average, 0, 1023,1,255));
          analogWrite(LED2, map(average, 0, 1023,1,255));
          analogWrite(LED3, map(average, 0, 1023,1,255));
          analogWrite(LED4, map(average, 0, 1023,1,255));
          buzzerTone = map(average, 0, 1023, 222, 666);
          tone(buzzer, buzzerTone);
        }
      }
    }
  }
  Serial.println(average);
}
