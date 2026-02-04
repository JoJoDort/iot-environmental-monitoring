#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

Adafruit_BME680 bme(BME_CS); // Utilisation du SPI matériel

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(1000); // Attendre que la console série soit prête
    Serial.println("Waiting for serial...");
  }

  Serial.println("Starting sensor initialization...");

  // Initialiser le BME680
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1); // Boucler indéfiniment si le capteur n'est pas trouvé
  }

  // Configuration des paramètres du capteur
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // Configurer le chauffage à 320°C pour 150 ms

  Serial.println("BME680 initialized");
}

void loop() {
  Serial.println("Performing reading...");

  // Effectuer une lecture des données
  if (!bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

  // Afficher les données du capteur
  Serial.print("Temperature = ");
  Serial.print(bme.temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bme.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(bme.humidity);
  Serial.println(" %");

  Serial.print("Gas resistance = ");
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(" kOhms");

  Serial.println();
  delay(2000); // Délai entre les lectures
}