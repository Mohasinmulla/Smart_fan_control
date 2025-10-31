#define BLYNK_TEMPLATE_ID "TMPL3ZVsANCjk"
#define BLYNK_TEMPLATE_NAME "Fan control"
#define BLYNK_AUTH_TOKEN "2gHXBdDEeyC4HKwaq4Vk_qcPJ-3g1Y-n"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// WiFi credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Test123";
char pass[] = "00000000";

// DHT11 sensor setup
#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Motor control pins
const int IN1 = 18;
const int IN2 = 19;
const int EN1 = 5;  // PWM pin

// PWM settings
const int pwmFreq = 5000;
const int pwmRes = 12;  // 12-bit resolution (0–4095)

// Fan control state
bool manualMode = false;
int manualSliderValue = 0;

// Manual mode: Fan speed level based on slider value
String getSpeedLevelFromSlider(int sliderValue) {
  if (sliderValue <= 120) return "LOW";
  else if (sliderValue <= 160) return "MEDIUM";
  else return "HIGH";
}

// Auto mode: Fan speed level based on PWM value
String getSpeedLevelFromPWM(int pwmValue) {
  if (pwmValue <= 2800) return "LOW";
  else if (pwmValue <= 3500) return "MEDIUM";
  else return "HIGH";
}

// Set fan speed using mapped PWM
void setFanSpeed(int sliderValue) {
  int pwmValue = map(sliderValue, 0, 255, 2000, 4095);
  ledcWrite(EN1, pwmValue);

  Serial.println("Mode: Manual");
  Serial.printf("Slider Value: %d\n", sliderValue);
  Serial.printf("Fan Speed: %s\n", getSpeedLevelFromSlider(sliderValue).c_str());

  // Optional: Blynk.virtualWrite(V4, getSpeedLevelFromSlider(sliderValue));
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Use new unified PWM attach method
  if (!ledcAttach(EN1, pwmFreq, pwmRes)) {
    Serial.println("PWM attach failed!");
  }

  Blynk.begin(auth, ssid, pass);
}

// Mode switch (manual/auto)
BLYNK_WRITE(V2) {
  manualMode = param.asInt();
  Serial.printf("Mode: %s\n", manualMode ? "Manual" : "Auto");
}

// Slider value
BLYNK_WRITE(V3) {
  manualSliderValue = param.asInt();
  if (manualMode) {
    setFanSpeed(manualSliderValue);
  }
}

void loop() {
  Blynk.run();

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (!isnan(temp)) Blynk.virtualWrite(V0, temp);
  if (!isnan(hum))  Blynk.virtualWrite(V1, hum);

  if (isnan(temp)) {
    Serial.println("Failed to read temperature!");
    return;
  }

  if (!manualMode) {
    int pwmValue;
    if (temp <= 30) {
      pwmValue = 2300;
    } else if (temp < 32) {
      pwmValue = 3200;
    } else {
      pwmValue = 4095;
    }

    ledcWrite(EN1, pwmValue);
    Serial.printf("Auto Mode - Temp: %.1f°C, Fan Speed: %s\n", temp, getSpeedLevelFromPWM(pwmValue).c_str());

    // Optional: Blynk.virtualWrite(V4, getSpeedLevelFromPWM(pwmValue));
  }

  delay(2000);
}
