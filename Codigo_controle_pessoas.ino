#include <Streaming.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define SENSOR_ENTRADA 2    // Botão de entrada
#define SENSOR_SAIDA 3      // Botão de saída
#define BOTAO_LAMPADA1 4    // Botão para controlar o LED
#define BOTAO_LAMPADA2 5    // ==
#define BOTAO_LAMPADA3 6    // ==
#define LED_LAMPADA1 7      // LED que representa a lâmpada
#define LED_LAMPADA2 8      // ==
#define LED_LAMPADA3 9      // ==
#define LED_MAX_PESSOAS 10  // LED para avisar quando bater o máximo de pessoas
#define DEBOUNCE 200
#define LIMITE_TEMPO_ENTRE_BOTOES 800
#define TEMPO_LED_PISCANDO 500

// Declaração das globais

unsigned long tempo_sensor_entrada = 0;
unsigned long tempo_sensor_saida = 0;
unsigned long ultimoDebounce1 = 0;
unsigned long ultimoDebounce2 = 0;
unsigned long ultimoDebounceLampadas[3] = { 0 };
unsigned long tempoUltimoPiscaLed = 0;
uint8_t estado_sensor_entrada = 0;
uint8_t estado_sensor_saida = 0;
uint8_t numeroPessoas = 0;
uint8_t lampadas[3] = { 0 };
uint8_t estadoLampadas[3] = { 0 };
uint8_t estadoAnteriorBotao[3] = { 1 };

uint8_t escanear_endereco(void) ;


//LiquidCrystal_I2C lcd(escanear_endereco(), 16, 2);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  i2c_detectar(); // detecta endereço do LCD automaticamente
  escanear_endereco();
  delay(50000);
  lcd.begin(16, 2); // inicializa o LCD
  lcd.backlight();
  pinMode(SENSOR_ENTRADA, INPUT_PULLUP);
  pinMode(SENSOR_SAIDA, INPUT_PULLUP);
  pinMode(BOTAO_LAMPADA1, INPUT_PULLUP);
  pinMode(BOTAO_LAMPADA2, INPUT_PULLUP);
  pinMode(BOTAO_LAMPADA3, INPUT_PULLUP);
  pinMode(LED_LAMPADA1, OUTPUT);
  pinMode(LED_LAMPADA2, OUTPUT);
  pinMode(LED_LAMPADA3, OUTPUT);
  pinMode(LED_MAX_PESSOAS, OUTPUT);
}


void loop() {
  verificar_sensor_entrada();
  verificar_sensor_saida();
  verificar_botoes_lampadas();
  looping_Geral();
  MAX_PESSOAS();
}

void looping_Geral() {  // verifica o tempo de acionamento dos sensores de entrada e saída
  if (estado_sensor_entrada == 1 && estado_sensor_saida == 1) {
    if (tempo_sensor_entrada < tempo_sensor_saida && (tempo_sensor_saida - tempo_sensor_entrada) <= LIMITE_TEMPO_ENTRE_BOTOES) {
      Verificar_entrada();
      verificar_saida();
    } else if (tempo_sensor_saida < tempo_sensor_entrada && (tempo_sensor_entrada - tempo_sensor_saida) <= LIMITE_TEMPO_ENTRE_BOTOES) {
      verificar_saida();
      Verificar_entrada();
    }
    estado_sensor_entrada = 0;
    estado_sensor_saida = 0;
  } else if (estado_sensor_entrada == 1 && (millis() - tempo_sensor_entrada) > LIMITE_TEMPO_ENTRE_BOTOES) {
    Serial.println("TEMPO EXCEDIDO - TENTE NOVAMENTE");
    lcd.clear();
    lcd.print(F("TEMPO EXCEDIDO"));
    estado_sensor_entrada = 0;
  } else if (estado_sensor_saida == 1 && (millis() - tempo_sensor_saida) > LIMITE_TEMPO_ENTRE_BOTOES) {
    Serial.println("TEMPO EXCEDIDO - TENTE NOVAMENTE");
    lcd.clear();
    lcd.print(F(" TEMPO EXCEDIDO "));
    estado_sensor_saida = 0;
  }
}

void verificar_sensor_entrada() {  // verifica o sensor de entrada
  uint8_t leitura_entrada = digitalRead(SENSOR_ENTRADA);
  if (leitura_entrada == 0 && millis() - ultimoDebounce1 > DEBOUNCE) {
    ultimoDebounce1 = millis();
    if (estado_sensor_entrada == 0) {
      estado_sensor_entrada = 1;
      tempo_sensor_entrada = millis();
      Serial.println("ENTRADA ATIVA");
      lcd.clear();
      lcd.print(F("ENTRADA ATIVA"));
    }
  }
}

void verificar_sensor_saida() {  // verifica o sensor de saída
  uint8_t leitura_saida = digitalRead(SENSOR_SAIDA);
  if (leitura_saida == LOW && millis() - ultimoDebounce2 > DEBOUNCE) {
    ultimoDebounce2 = millis();
    if (estado_sensor_saida == 0) {
      estado_sensor_saida = 1;
      tempo_sensor_saida = millis();
      Serial.println("SAIDA ATIVA");
      lcd.clear();
      lcd.print(F("SAIDA ATIVA"));
    }
  }
}

void verificar_botoes_lampadas() {  // verifica o acionamento dos botões dos LEDs e o estado deles
  uint8_t estadoAtualBotao[3];
  for (int i = 0; i < 3; i++) {
    estadoAtualBotao[i] = digitalRead(BOTAO_LAMPADA1 + i);
    if (estadoAtualBotao[i] != estadoAnteriorBotao[i] && millis() - ultimoDebounceLampadas[i] > DEBOUNCE) {
      ultimoDebounceLampadas[i] = millis();
      if (estadoAtualBotao[i] == LOW) {
        lampadas[i] = !lampadas[i];
        digitalWrite(LED_LAMPADA1 + i, lampadas[i]);
        Serial.print("LAMPADA ");
        Serial.print(i + 1);
        Serial.println(lampadas[i] ? F("ligada") : F("desligada"));
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Lamp            "));
        lcd.print(i + 1);
        lcd.print(F(" "));

        lcd.print(lampadas[i] ? F("ON ") : F("OFF"));
      }
      estadoAnteriorBotao[i] = estadoAtualBotao[i];
    }
  }
}

void Verificar_entrada() {  // informa a quantidade de pessoas que entraram na casa
  if (tempo_sensor_entrada < tempo_sensor_saida) {
    if (numeroPessoas < 5) {
      numeroPessoas++;
      restaurar_estado_lampadas();
      lcd.clear();
      lcd.print(F("Entrou na casa!"));
      lcd.setCursor(0, 1);
      lcd.print(F("Pessoas: "));
      lcd.print(numeroPessoas);
    } else {
      lcd.clear();
      lcd.print(F("Limite atingido."));
    }
  }
  estado_sensor_entrada = 0;
}

void verificar_saida() {
  if (tempo_sensor_saida < tempo_sensor_entrada) {  // informa a quantidade de pessoas que saíram
    if (numeroPessoas > 0) {
      numeroPessoas--;
      lcd.clear();
      lcd.print(F("Saiu da casa!"));
      lcd.setCursor(0, 1);
      lcd.print(F("Pessoas: "));
      lcd.print(numeroPessoas);
      if (numeroPessoas == 0) {
        salvar_estado_lampadas();
        desligar_lampadas();
      }
    } else {
      lcd.clear();
      lcd.print(F("Sem pessoas."));
    }
  }
  estado_sensor_saida = 0;
}

void restaurar_estado_lampadas() {  // restaura o estado das lâmpadas quando uma pessoa retorna
  for (uint8_t i = 0; i < 3; i++) {
    digitalWrite(i + LED_LAMPADA1, estadoLampadas[i]);
  }
}

void salvar_estado_lampadas(void) {  // salva o estado das lâmpadas
  for (uint8_t i = 0; i < 3; i++) {
    estadoLampadas[i] = lampadas[i];
  }
}

void desligar_lampadas(void) {  // desliga as lâmpadas
  for (uint8_t i = 0; i < 3; i++) {
    lampadas[i] = 0;
    digitalWrite(i + LED_LAMPADA1, LOW);
  }
}

void MAX_PESSOAS() {  // aciona o LED que informa que a casa está cheia
  if (numeroPessoas == 5) {
    if (millis() - tempoUltimoPiscaLed > TEMPO_LED_PISCANDO) {
      tempoUltimoPiscaLed = millis();
      digitalWrite(LED_MAX_PESSOAS, digitalRead(LED_MAX_PESSOAS) == LOW ? HIGH : LOW);
    }
  } else {
    digitalWrite(LED_MAX_PESSOAS, LOW);
  }
}

/*void i2c_detectar(void) {
  uint8_t contagem = 0;
  Wire.begin();
  Serial.println(F("DETECTAR I2C INICIADA..."));
  for (uint8_t i = 8; i < 120; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print(F("ENDEREÇO ENCONTRADO: 0x"));
      Serial.println(i, HEX);
      contagem++;
    }
  }
  Serial.println(F("DETECTADO COM SUCESSO!"));
  Serial.print(contagem, DEC);
  if (!contagem) {
    Serial.println(F(" NENHUM DISPOSITIVO ENCONTRADO"));
  }
}

uint8_t escanear_endereco(void) {
  for (uint8_t endereco = 8; endereco < 120; endereco++) {
    Wire.beginTransmission(endereco);
    if (!Wire.endTransmission()) {
      Serial.print("endereco encontrado: ");
      Serial.println(endereco);
      return endereco;
    } 
  }
  Serial.println("nenhum endereco encontrado.");
  return 0;
}*/