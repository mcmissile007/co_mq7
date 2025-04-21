#include <Arduino.h>
#define MQ7_HEAT_PIN 25  // Pin para control del calentador
#define MQ7_READ_PIN 34  // Pin ADC para lectura

void setup() {
  Serial.begin(115200);
  pinMode(MQ7_HEAT_PIN, OUTPUT);
  delay(10000);
  Serial.println("End Setup");
}

void loop() {
  // **Fase alta - 5V en el MQ7 por 60 segundos**
  //**la salida esta conectada al Gate de un MOSFET que no conduce , el MQ7 recibe 5V */
  Serial.println("SET PIN 25 LOW");
  digitalWrite(MQ7_HEAT_PIN, LOW);
  delay(60000);  // Esperar 60 segundos

  // **Fase baja - 1.4V en el MQ7 por 90 segundos**
  //la salida saca 0V lo que cierra el MOSFET y el MQ se alimenta con la salida del LM317T
  Serial.println("SET PIN 25 HIGH");
  digitalWrite(MQ7_HEAT_PIN, HIGH);
  delay(90000);  // Esperar 90 segundos

  // **Lectura del sensor**
  int valor = analogRead(MQ7_READ_PIN);
  float voltaje = (valor / 4095.0) * 3.3;  // Conversión a voltaje (ESP32 es 3.3V)
  Serial.print("Valor MQ-7: ");
  Serial.println(valor);
  Serial.print("Voltaje: ");
  Serial.println(voltaje);
}
