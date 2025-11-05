#include <HCSR04.h>              // Biblioteca para o sensor ultrassônico HC-SR04
#include <Wire.h>                // Biblioteca para comunicação I2C
#include <LiquidCrystal_I2C.h>   // Biblioteca para o display LCD I2C

// -------------------- Definição de pinos --------------------
const byte TRIGGER_PIN = 6;      // Pino de saída (trigger) do sensor ultrassônico
const byte ECHO_PIN = 7;         // Pino de entrada (echo) do sensor ultrassônico
const int LED_PIN = 8;           // Pino do LED (representa a bomba d’água)

// -------------------- Criação dos objetos --------------------
UltraSonicDistanceSensor distanceSensor(TRIGGER_PIN, ECHO_PIN); // Objeto do sensor
LiquidCrystal_I2C lcd(0x27, 16, 2);                             // Endereço e tamanho do LCD (16 colunas, 2 linhas)

// -------------------------------------------------------------
// Função de configuração - executa apenas uma vez ao iniciar
// -------------------------------------------------------------
void setup() {
  pinMode(LED_PIN, OUTPUT);  // Define o pino do LED como saída

  // Inicializa o display LCD
  lcd.init();
  lcd.backlight();           // Liga a luz de fundo do display

  // Mensagem de inicialização
  lcd.setCursor(0, 0);
  lcd.print("Sensor iniciado");
  
  // Pisca o LED para indicar que o sistema está pronto
  digitalWrite(LED_PIN, HIGH);
  delay(1500);
  digitalWrite(LED_PIN, LOW);
  
  lcd.clear(); // Limpa o display
}

// -------------------------------------------------------------
// Função principal - executa continuamente
// -------------------------------------------------------------
void loop() {
  bool bombaLigada = false;   // Variável para controlar o estado da bomba
  
  // Mede a distância em centímetros
  float distancia = distanceSensor.measureDistanceCm();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distancia:");

  lcd.setCursor(0, 1);

  // Verifica se houve erro de leitura
  if (distancia <= 0.0) {
    lcd.print("Erro de leitura!");
  } else {
    // Enquanto o nível estiver acima de 10 cm, mantém a bomba ligada
    while (distancia > 10.0) {
      if (!bombaLigada) {
        digitalWrite(LED_PIN, HIGH);  // Liga o LED (bomba ligada)
        bombaLigada = true;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Bomba ligada!");
        delay(2000);
        lcd.clear();
      }

      // Mostra a distância atual no LCD
      lcd.setCursor(0, 0);
      lcd.print("Distancia:");
      lcd.setCursor(0, 1);
      lcd.print(distancia, 2);  // Mostra duas casas decimais
      lcd.print(" cm");

      // Atualiza a medição a cada 200 ms
      distancia = distanceSensor.measureDistanceCm();
      delay(200);
    }

    // Quando a distância for menor ou igual a 10 cm, desliga a bomba
    if (bombaLigada) {
      digitalWrite(LED_PIN, LOW);
      bombaLigada = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Bomba desligada");
      delay(2000);
      lcd.clear();
    }

    // Exibe a distância final
    lcd.setCursor(0, 0);
    lcd.print("Distancia:");
    lcd.setCursor(0, 1);
    lcd.print(distancia, 2);
    lcd.print(" cm");
  }

  delay(500); // Espera antes da próxima leitura
}
