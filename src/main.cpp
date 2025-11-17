#include <Servo.h>

#include <DHT.h>

#define DHTPIN 7

#define DHTTYPE DHT11

 

DHT dht(DHTPIN,DHTTYPE)

Servo servo1;Servo servo2;

int ledPins[]={2,3,4,5,6,8,9,10};

int buttonPins[]={A0,A1,A2};

int potPins[]={A3,A4};

float tempSensor=A5;  // von Stefan geändert

float lightSensor=A6;// von Ibrahim

int buzzer=11;

int servo1Pin=12;

int servo2Pin=13;

int NumLeds=8;// Ibrahim

<<<<<<< HEAD
int NumButtons=3; // ibbrahim
=======
int buttons=3;  //  hier
>>>>>>> 4c8f0349acb6f81c3aa6977a96df1692568b4be8

int Pots=2;   //  hier und 

int lastButtonState[]={0,0,0};

int ledState[]={0,0,0,0,0,0,0,0};

unsigned long lastDebounceTime[]={0,0,0};

unsigned long debounceDelay=50;

float temp=0;int lightLevel=0;

 

void setup()

{

  Serial.begin(9600);

  dht.begin();servo1.attach(servo1Pin);

  servo2.attach(servo2Pin);

  pinMode(buzzer,OUTPUT);

  for(int i=0;i<numLeds;i++)

  {

    pinMode(ledPins[i],OUTPUT);

  }

  for(int i=0;i<numButtons;i++)

  {

    pinMode(buttonPins[i],INPUT_PULLUP);

  }

  randomSeed(analogRead(0))

}

void loop()

{

  readSensors();

  handleButtons();

  updateLeds();

  controlServos();

  playBuzzer();

  displayStatus();

  delay(100)

}

void readSensors()

{

  temp=dht.readTemperature();

  if(isnan(temp))

  {

    temp=-1

  }

  lightLevel=analogRead(lightSensor)

}

void handleButtons()

{

  for(int i=0;i<numButtons;i++)

  {

    int reading=digitalRead(buttonPins[i]);

    if(reading!=lastButtonState[i])

    {

      lastDebounceTime[i]=millis()

    }

    if((millis()-lastDebounceTime[i])>debounceDelay)

    {

      if(reading!=ledState[i])

      {

        ledState[i]=reading;performButtonAction(i)  

      }

    }

    lastButtonState[i]=reading

  }

}

           

void performButtonAction(int btn)

{

  if(btn==0)

  {

              blinkAll(3,100)

              }

              else if(btn==1){

                chaseForward(100)

                }

                else if(btn==2){chaseBackward(100)

                }

                }void updateLeds()

                {for(int i=0;i<numLeds;i++)

                {if(ledState[i]==LOW)

                {

                digitalWrite(ledPins[i],HIGH)

                }

                else{digitalWrite(ledPins[i],LOW)

                }

                }

                }

void controlServos()

{

  int potVal1=analogRead(potPins[0]);

  int potVal2=analogRead(potPins[1]);

  int angle1=map(potVal1,0,1023,0,180);

  int angle2=map(potVal2,0,1023,0,180);

  servo1.write(angle1);

  servo2.write(angle2)

 

}

 

void playBuzzer()

{

  if(temp>30||lightLevel<200)

  {

    tone(buzzer,1000,200)

  }

  else

  {

    noTone(buzzer)

  }

}

 

void displayStatus()

{

  Serial.print("Temperatur: ");

  Serial.print(temp);

  Serial.print(" °C, Licht: ");

  Serial.print(lightLevel);

  Serial.print(", Servos: ");

  Serial.print(analogRead(potPins[0]));

  Serial.print(",");

  Serial.println(analogRead(potPins[1]))

}

 

                void blinkAll(int times,int delayTime)

 

                {

                  for(int i=0;i<times;i++)

                  {for(int j=0;j<numLeds;j++)

                  {digitalWrite(ledPins[j],HIGH)}

                  delay(delayTime);

                  for(int j=0;j<numLeds;j++)

                  {digitalWrite(ledPins[j],LOW)}delay(delayTime)}

                }

                void chaseForward(int delayTime)

                {for(int i=0;i<numLeds;i++)

 

                  {

                    digitalWrite(ledPins[i],HIGH);

                    delay(delayTime);digitalWrite(ledPins[i],LOW)

                  }

                } void chaseBackward(int delayTime)

                {

                  for(int i=numLeds-1;i>=0;i--)

                  {

                    digitalWrite(ledPins[i],HIGH);

                    delay(delayTime);digitalWrite(ledPins[i],LOW)

                  }

                }

                void complexPattern()

                {

                  for(int i=0;i<5;i++)

                  {

                    chaseForward(50);

                    blinkAll(2,100);

                    chaseBackward(50)

                  }

                  for(int i=0;i<numLeds;i++)

                  {

                    if(i%2==0)

                    {

                      digitalWrite(ledPins[i],HIGH)

                    }

                    else

                    {

                      digitalWrite(ledPins[i],LOW)

                    }

 

                  }

                  delay(200);

                  for(int i=0;i<numLeds;i++)

                  {

                    digitalWrite(ledPins[i],LOW)

 

                  }

                }

                void safetyCheck()

                {

                  if(temp>40)

                  {

                    for(int i=0;i<numLeds;i++)

                    {

                      digitalWrite(ledPins[i],HIGH)

                    }

                    tone(buzzer,2000,500);

                    delay(500);

                    for(int i=0;i<numLeds;i++)

                    {

                      digitalWrite(ledPins[i],LOW)

                    }

                    }

                    if(lightLevel<100)

                    {

                      blinkAll(5,50)

                    }

                    }

                    void combinedActions()

                    {

                      complexPattern();

                      safetyCheck();

                      controlServos();

                      playBuzzer()

                      }

                      void loop2()

                      {

                        combinedActions();

                        displayStatus();

                        delay(100)

                      }