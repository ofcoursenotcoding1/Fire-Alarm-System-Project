// Fire Alarm System with Two-Level Warning (Motor + Buzzer)

const int tempPin = A0;    // TMP36/LM35 sensor
const int ledPin  = 13;    // LED
const int buzzer  = 7;     // Piezo buzzer
const int motor   = 6;     // Vibration motor

// Temperature thresholds
const float warnThreshold = 30.0;  // Warning level (motor)
const float alarmThreshold = 60.0; // Final alarm (buzzer)

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(motor, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(tempPin);
  float voltage = sensorValue * (5.0 / 1023.0);

  // TMP36: Temp in °C = (voltage - 0.5) * 100
  float temperatureC = (voltage - 0.5) * 100.0;

  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  if (temperatureC >= alarmThreshold) {
    // Final alarm condition (>= 60°C)
    digitalWrite(ledPin, HIGH);
    digitalWrite(motor, HIGH);   // Motor ON
    tone(buzzer, 1000);          // Buzzer ON
  }
  else if (temperatureC >= warnThreshold) {
    // Warning condition (30–59°C)
    digitalWrite(ledPin, HIGH);
    digitalWrite(motor, HIGH);   // Motor ON
    noTone(buzzer);              // Buzzer OFF
  }
  else {
    // Safe condition (< 30°C)
    digitalWrite(ledPin, LOW);
    digitalWrite(motor, LOW);
    noTone(buzzer);
  }

  delay(500);
}
