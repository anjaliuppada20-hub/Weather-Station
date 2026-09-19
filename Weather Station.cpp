#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// DHT11 configuration
#define DHT_PIN 2
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

// LCD address: usually 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// LED pins
const int GREEN_LED = 7;
const int RED_LED = 8;


void setup() {

  Serial.begin(9600);

  dht.begin();

  lcd.init();
  lcd.backlight();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Weather Station");

  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  delay(2000);

  lcd.clear();
}


void loop() {

  // Read temperature
  float temperature = dht.readTemperature();

  // Read humidity
  float humidity = dht.readHumidity();


  // Check sensor
  if (isnan(temperature) || isnan(humidity)) {

    Serial.println("Sensor Error");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error");

    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

    delay(2000);

    return;
  }


  // Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");


  // LCD temperature
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");

  lcd.print(temperature, 1);
  lcd.print((char)223);
  lcd.print("C");


  // LCD humidity
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");

  lcd.print(humidity, 1);
  lcd.print("%");


  // Simple temperature indicator
  if (temperature > 30) {

    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

  } else {

    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }


  delay(2000);
}
