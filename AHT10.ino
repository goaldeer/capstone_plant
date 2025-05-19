#include <BH1750.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;
BH1750 lightMeter;

void setup() {
  Serial.begin(115200);

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();

  if (! aht.begin()) {
    Serial.println("NO AHT");
    while (1) delay(10);
  }
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);
  // For Wemos / Lolin D1 Mini Pro and the Ambient Light shield use
  // Wire.begin(D2, D1);
  lightMeter.begin();

  Serial.println(F("BH1750 Test begin"));
}

void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.print("조도 : ");
  Serial.print(lux);
  Serial.println(" lx");

  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  Serial.print("온도 : "); Serial.println(temp.temperature);
  Serial.print("습도 : "); Serial.println(humidity.relative_humidity);;
  delay(1000);
}