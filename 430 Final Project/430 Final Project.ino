/*
 * 430 Final Project
 * 
 * This program uses the CC3200 wireless microcontroller along with a servo and an ultrasonic sensor. The servo will
 * sweep a cone repeatedly until the ultrsonic sensor detects an object within 50 cm. Once it detects an object it 
 * will sweep in a smaller cone to pseudo track the object it detected. When the object moves away from 50 cm from 
 * the ultrasonic sensor, the servo will continue it's initial sweeping motion. If the ultrasonic sensor detects an
 * object closer than 25 cm it will turn on a red LED. If it detects an object between 25 and 50 cm it will turn on a 
 * yellow LED. Lastly if there are no objects closer than 50 cm a green LED will be turned on.
 * 
 * By: Andrew Gates, Brandon Watt, and Vladislav Psarev
 */
 
#include <Servo.h> 

Servo myservo;  // create servo object to control a servo a maximum of eight servo objects can be created 
int pos = 0;    // variable to store the servo position 

// Pin 5 on CC3200
const int buzzerPin = 3;
const int pingPin = 7;
const int servoPin = 31;

void setup() 
{
  myservo.attach(servoPin);
  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;
  int itemTrackFlag = 0;
  int lowValue = 0, highValue = 0;
  
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
    
    if(pos%15 == 0)
    {
      // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
      // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
      pinMode(pingPin, OUTPUT);
      digitalWrite(pingPin, LOW);
      delayMicroseconds(2);
      digitalWrite(pingPin, HIGH);
      delayMicroseconds(5);
      digitalWrite(pingPin, LOW);

      // The same pin is used to read the signal from the PING))): a HIGH
      // pulse whose duration is the time (in microseconds) from the sending
      // of the ping to the reception of its echo off of an object.
      pinMode(pingPin, INPUT);
      duration = pulseIn(pingPin, HIGH);

      // convert the time into a distance
      inches = microsecondsToInches(duration);
      cm = microsecondsToCentimeters(duration);
  
      if(cm < 25)
      {
        itemTrackFlag = 0;
      
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(buzzerPin, HIGH);  
        digitalWrite(RED_LED, HIGH);  
      
        if(pos + 30 > 180)
        {
          highValue = 180; 
          lowValue = pos - 30;
        }  
      
        else if(pos - 30 < 0)
        {
          lowValue = 0; 
          highValue = pos + 30;
        } 
      
        else
        {
          lowValue = pos - 30;
          highValue = pos + 30; 
        }  
      
        for(int i = lowValue; i <= highValue; i++)
        {
          myservo.write(i); 
          delay(15);
        
          pinMode(pingPin, OUTPUT);
          digitalWrite(pingPin, LOW);
          delayMicroseconds(2);
          digitalWrite(pingPin, HIGH);
          delayMicroseconds(5);
          digitalWrite(pingPin, LOW);
        
          pinMode(pingPin, INPUT);
          duration = pulseIn(pingPin, HIGH);
        
          cm = microsecondsToCentimeters(duration);
      
          if(cm < 25)
          {
            itemTrackFlag = 1;
          }
        
          if(itemTrackFlag == 1 && i == highValue)
          {
            i = lowValue - 1;
            itemTrackFlag = 0;
          }
        }  
        pos = highValue;
      }  
      else if(cm > 25 && cm < 50)
      {
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(buzzerPin, LOW);  
        digitalWrite(YELLOW_LED, HIGH);  
      }  
      else
      {
        digitalWrite(RED_LED, LOW);
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(buzzerPin, LOW);  
        digitalWrite(GREEN_LED, HIGH);  
      }  
  
      Serial.print(inches);
      Serial.print(" in, ");
      Serial.print(cm);
      Serial.print(" cm, ");
      Serial.print(pos);
      Serial.print(" degrees");
      Serial.println();
      }  
   } 
  
   for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
   {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
    
    if(pos%15 == 0)
    {
      // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
      // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
      pinMode(pingPin, OUTPUT);
      digitalWrite(pingPin, LOW);
      delayMicroseconds(2);
      digitalWrite(pingPin, HIGH);
      delayMicroseconds(5);
      digitalWrite(pingPin, LOW);

      // The same pin is used to read the signal from the PING))): a HIGH
      // pulse whose duration is the time (in microseconds) from the sending
      // of the ping to the reception of its echo off of an object.
      pinMode(pingPin, INPUT);
      duration = pulseIn(pingPin, HIGH);

      // convert the time into a distance
      inches = microsecondsToInches(duration);
      cm = microsecondsToCentimeters(duration);
  
      if(cm < 25)
      {
        itemTrackFlag = 0;
      
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(buzzerPin, HIGH);  
        digitalWrite(RED_LED, HIGH);  
      
        if(pos + 30 > 180)
        {
          highValue = 180; 
          lowValue = pos - 30;
        }  
      
        else if(pos - 30 < 0)
        {
          lowValue = 0; 
          highValue = pos + 30;
        } 
      
        else
        {
          lowValue = pos - 30;
          highValue = pos + 30; 
        }  
      
        for(int i = highValue; i >= lowValue; i--)
        {
          myservo.write(i); 
          delay(15);
        
          pinMode(pingPin, OUTPUT);
          digitalWrite(pingPin, LOW);
          delayMicroseconds(2);
          digitalWrite(pingPin, HIGH);
          delayMicroseconds(5);
          digitalWrite(pingPin, LOW);
        
          pinMode(pingPin, INPUT);
          duration = pulseIn(pingPin, HIGH);
        
          cm = microsecondsToCentimeters(duration);
      
          if(cm < 25)
          {
            itemTrackFlag = 1;
          }
        
          if(itemTrackFlag == 1 && i == lowValue)
          {
            i = highValue + 1;
            itemTrackFlag = 0;
          }  
        }  
        pos = lowValue;
      }  
      else if(cm > 25 && cm < 50)
      {
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(buzzerPin, LOW);  
        digitalWrite(YELLOW_LED, HIGH);  
      }  
      else
      {
        digitalWrite(RED_LED, LOW);
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(buzzerPin, LOW);  
        digitalWrite(GREEN_LED, HIGH);  
      }  
  
      Serial.print(inches);
      Serial.print(" in, ");
      Serial.print(cm);
      Serial.print(" cm, ");
      Serial.print(pos);
      Serial.print(" degrees");
      Serial.println();
      }  
   } 
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
