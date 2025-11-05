#include <HCSR04.h>              // Biblioteca para o sensor ultrassônico HC-SR04
#include <Wire.h>                // Biblioteca para comunicação I2C
#include <LiquidCrystal_I2C.h>   // Biblioteca para o display LCD via I2C

// -------------------- Definição de pinos --------------------
const byte TRIGGER_PIN = 6;      // Pino de saída do sensor ultrassônico
const byte ECHO_PIN = 7;         // Pino de entrada do sensor ultrassônico
const int LED_PIN = 8;           // Pino do LED (ou módulo relé)

// -------------------- Objetos do hardware --------------------
UltraSonicDistanceSensor distanceSensor(TRIGGER_PIN, ECHO_PIN); // Sensor ultrassônico
LiquidCrystal_I2C lcd(0x27, 16, 2);                             // Display LCD 16x2 via I2C

// -------------------- Função de configuração --------------------
void setup() {
  pinMode(LED_PIN, OUTPUT);  // Configura o pino do LED como saída

  // Inicializa o LCD
  lcd.init();
  lcd.backlight();

  // Mensagem inicial
  lcd.setCursor(0, 0);
  lcd.print("Sensor iniciado");

  // Pisca o LED para sinalizar inicialização
  digitalWrite(LED_PIN, HIGH);
  delay(1500);
  digitalWrite(LED_PIN, LOW);
  lcd.clear();
}

// -------------------- Função principal --------------------
void loop() {
  // Lê a distância em centímetros
  float distance = distanceSensor.measureDistanceCm();

  // Atualiza o display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distancia:");

  lcd.setCursor(0, 1);

  if (distance <= 0.0) {
    // Caso ocorra erro na leitura do sensor
    lcd.print("Erro de leitura!");
    digitalWrite(LED_PIN, LOW);
  } else {
    // Mostra a distância
    lcd.print(distance, 2);  // duas casas decimais
    lcd.print(" cm");

    // Controla o LED ou relé conforme o nível
    if (distance <= 20.0) {  // Limite de ativação da bomba
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
  }

  delay(500); // Atualiza a cada 500ms
}
