////test for esp water leak sensor 
///@TAKEABYTE 2024 


#include <Arduino.h>
#include <Wire.h>

#define WATER_SENSOR_PIN 13
#define WATER_POWER_PIN 16
int WaterState;            // the current reading from the input pin
int lastWaterState = HIGH;  // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    //
unsigned long startTime = 0;
unsigned long currentTime = 0;

int count;

void waterdetect(void)
{
  int reading = digitalRead(WATER_SENSOR_PIN);

  // If the switch changed, due to noise or pressing:
  if (reading != lastWaterState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    // if the button state has changed:
    if (reading != WaterState) {
      WaterState = reading;

      // only toggle the LED if the new button state is HIGH
      if (WaterState == LOW) {
            Serial.println("==============WATER=======================");
            count++;
            Serial.print("Watercount: ");
            Serial.println(count);

      }
      else {
              Serial.println("==============Calm Down=======================");
      }
    }
  }
  lastWaterState = reading;
}

 void loop()
{  
  digitalWrite(WATER_POWER_PIN, HIGH);
  waterdetect();
  digitalWrite(WATER_POWER_PIN, LOW);
  Serial.println("Going to sleep for a bit.");
  delay(500);
}

void setup()
{
  pinMode(WATER_SENSOR_PIN, INPUT_PULLUP);
  pinMode(WATER_POWER_PIN, OUTPUT);
   time_t timeout = millis();
  Serial.begin(115200);
  Serial.println("====================================="); 
  Serial.println("=====================================");
}