

#define BLYNK_TEMPLATE_ID "TMPL6-_CFpAvt"
#define BLYNK_TEMPLATE_NAME "Project1Arduino"
#define BLYNK_AUTH_TOKEN "zt_Umwk_o_fu4ZodIb3s6glQIKCLRqpx"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
// #include <BlynkSimpleStream.h>
// #include <SoftwareSerial.h>
// SoftwareSerial DebugSerial(2, 3); // RX, TX

// int SensorPin = A0;

char auth[] = "zt_Umwk_o_fu4ZodIb3s6glQIKCLRqpx";
char ssid[] = "Thanh"; // Your WiFi credentials.
char pass[] = "30122003";
LiquidCrystal_I2C lcd(0x27, 20, 4);
int soilMoisture = 35;
int rainSensor = 34;
int vibrationSensor = 32;
void setup()
{
  // put your setup code here, to run once:
  // DebugSerial.begin(9600);
  Serial.begin(9600);
  lcd.init(); // initialize the lcd
              // Print a message to the LCD.
  lcd.backlight();
  Blynk.begin(auth, ssid, pass);
  pinMode(soilMoisture, INPUT);
  pinMode(rainSensor, INPUT);
  pinMode(vibrationSensor, INPUT);
  // pinMode(3, INPUT);
  

  // Blynk.begin(Serial, auth);
}

void loop()
{
  // put your main code here, to run repeatedly:
  
  int vibrate = digitalRead(vibrationSensor);
  double moistureAnalog = analogRead(soilMoisture);
  double rainAnalog = analogRead(rainSensor);
  double moisturePercentage = 100 - (moistureAnalog / 4095.00 * 100);
  double rainMeasure = 100 - (rainAnalog / 4095.00 * 100);
  // int vibration = digitalRead(3);
  // Serial.print("\nCambien:");
  // Serial.print(giatriAnalog);
  // Serial.print(" - ");
  // Serial.print(doAm);
  // Serial.println("  ");
  // Blynk.virtualWrite(V0, doAm);
  // Serial.print("\nVibrate:");
  // Serial.print(vibration);
  // double SensorVolts = (analogRead(SensorPin) * 0.0048828125) / 5.0 * 100;

  lcd.setCursor(0, 0);
  lcd.print("Moisture:");
  lcd.print(moisturePercentage);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Rainfall:");
  lcd.print(rainMeasure);
  lcd.print("mm");
  
  Blynk.run();
  Blynk.virtualWrite(V0, moisturePercentage);
  Blynk.virtualWrite(V1, rainMeasure);
  Blynk.virtualWrite(V3, vibrate);
  if (vibrate == 1)
  {
    if (moisturePercentage > 40 && rainMeasure > 55)
    {
      Blynk.virtualWrite(V2, "Canh Bao M3");
    }
    else if (moisturePercentage > 40 && rainMeasure <= 55)
    {
      Blynk.virtualWrite(V2, "Canh bao M2");
    }
    else if (moisturePercentage <= 40 && rainMeasure > 55)
    {
      Blynk.virtualWrite(V2, "Canh bao M1");
    }
    else
    {
      Blynk.virtualWrite(V2, "An toan");
    }
  }
  else
  {
    if ((moisturePercentage > 40 && rainMeasure > 55))
    {
      Blynk.virtualWrite(V2, "Canh bao M1");
    }
    else
    {
      Blynk.virtualWrite(V2, "An toan");
    }
  }

  delay(1000);
  // Blynk.run();
  // Blynk.virtualWrite(V0, SensorVolts);
  // Blynk.virtualWrite(V1, "WARNING");
}
