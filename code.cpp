#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

RTC_DS1307 rtc;

// Hardware Pin Definitions
const int BUZZER_PIN = 14; // Piezo Buzzer connected to GPIO14

// Set your target Alarm Time here (24-hour format)
const int ALARM_HOUR = 07;   
const int ALARM_MINUTE = 30; 

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize standard ESP32 I2C pins (SDA=21, SCL=20)
  Wire.begin(21, 20);

  // Initialize OLED Screen
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("OLED allocation failed"));
    for(;;); 
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.println("Clock Initializing...");
  display.display();

  // Initialize DS1307 RTC Module
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC module!");
    display.setCursor(10, 40);
    display.println("RTC Error!");
    display.display();
    for(;;);
  }

  // Automatically sets the RTC to the time this code was compiled (Run once)
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running, setting system time...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  delay(1000);
}

void loop() {
  DateTime now = rtc.now();

  // Format time strings with leading zeros
  char timeBuffer[9];
  sprintf(timeBuffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  
  char dateBuffer[11];
  sprintf(dateBuffer, "%02d/%02d/%04d", now.day(), now.month(), now.year());

  // Clear display buffer
  display.clearDisplay();
  
  // Render Date Layout
  display.setTextSize(1);
  display.setCursor(32, 4);
  display.print(dateBuffer);

  // Render Time Layout (Large Text Font)
  display.setTextSize(2);
  display.setCursor(16, 22);
  display.print(timeBuffer);

  // Display Scheduled Alarm Profile Settings
  display.setTextSize(1);
  display.setCursor(0, 52);
  display.print("Alarm: ");
  char alarmBuf[6];
  sprintf(alarmBuf, "%02d:%02d", ALARM_HOUR, ALARM_MINUTE);
  display.print(alarmBuf);

  // Evaluation Rule Match for Alarm Trigger Condition
  if (now.hour() == ALARM_HOUR && now.minute() == ALARM_MINUTE) {
    display.setCursor(76, 52);
    display.print("[RING!]");
    
    // Create a pulsing beep tone behavior
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    display.setCursor(85, 52);
    display.print("[Active]");
    digitalWrite(BUZZER_PIN, LOW);
  }

  display.display();
  delay(300); // Poll and redraw matrix framework layout
}
