#include <LiquidCrystal.h>

// Inicializa o objeto do display LCD com os pinos conectados ao Arduino
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Definição dos pinos conectados aos atuadores e sensores
const int ledVerde = 4;
const int ledAmarelo = 5;
const int ledVermelho = 6;
const int buzzer = 3;
const int tmp36 = A0;    // TMP36: sensor de temperatura
const int potUmid = A1;  // Potenciômetro simulando umidade
const int ldr = A2;      // LDR: sensor de luminosidade

// Variáveis que armazenarão as médias dos sensores
float temperatura;
int umidade;
int luminosidade;

// Definição para cálculo da média de leituras
const int numLeituras = 5;
float tempLeituras[numLeituras];
int umidLeituras[numLeituras];
int luzLeituras[numLeituras];
int leituraAtual = 0;  // Índice atual do vetor circular

// Controle da alternância de mensagens no display
unsigned long tempoAnterior = 0;
const long intervaloDisplay = 3000;  // Tempo de troca de mensagem no LCD (3 segundos)
int mensagemAtual = 0;  // 0 = Luminosidade, 1 = Umidade, 2 = Temperatura

// Limites para categorizar os níveis de luminosidade
const int ESCURO_MAX = 500;
const int MEIA_LUZ_MAX = 800;

// Variáveis de estado para determinar alertas
bool alertaLuminosidade = false;
bool alertaTemperatura = false;
bool alertaUmidade = false;

void setup() {
  // Inicializa o display LCD com 16 colunas e 2 linhas
  lcd.begin(16, 2);

  // Define os pinos de saída
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Inicializa os vetores de leitura com zeros
  for (int i = 0; i < numLeituras; i++) {
    tempLeituras[i] = 0;
    umidLeituras[i] = 0;
    luzLeituras[i] = 0;
  }

  // Mensagem inicial no display
  lcd.print("Vinheria");
  lcd.setCursor(0, 1);
  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Leitura bruta dos sensores
  float tempRaw = analogRead(tmp36);
  int umidRaw = analogRead(potUmid);
  int luzRaw = analogRead(ldr);

  // Conversão da leitura do TMP36 para graus Celsius
  float tempAtual = (tempRaw * 5.0 / 1024.0 - 0.5) * 100;

  // Conversão da leitura do potenciômetro para faixa de umidade (0 a 100%)
  int umidAtual = map(umidRaw, 0, 1023, 0, 100);

  // Armazena as leituras atuais nos vetores circulares
  tempLeituras[leituraAtual] = tempAtual;
  umidLeituras[leituraAtual] = umidAtual;
  luzLeituras[leituraAtual] = luzRaw;

  // Atualiza o índice do vetor (modo circular)
  leituraAtual = (leituraAtual + 1) % numLeituras;

  // Calcula a média das últimas 5 leituras
  temperatura = calcularMediaTemp();
  umidade = calcularMediaUmid();
  luminosidade = calcularMediaLuz();

  // Avalia as condições de alerta com base nas médias
  verificarAlertas();

  // Controla LEDs e Buzzer com base nos alertas
  controlarSinais();

  // Atualiza a mensagem do display a cada 3 segundos
  unsigned long tempoAtual = millis();
  if (tempoAtual - tempoAnterior >= intervaloDisplay) {
    tempoAnterior = tempoAtual;
    mensagemAtual = (mensagemAtual + 1) % 3;  // Alterna entre 0, 1 e 2
    mostrarMensagemAtual();  // Exibe a mensagem atual no LCD
  }
}

// Função para calcular a média da temperatura
float calcularMediaTemp() {
  float soma = 0;
  for (int i = 0; i < numLeituras; i++) {
    soma += tempLeituras[i];
  }
  return soma / numLeituras;
}

// Função para calcular a média da umidade
int calcularMediaUmid() {
  int soma = 0;
  for (int i = 0; i < numLeituras; i++) {
    soma += umidLeituras[i];
  }
  return soma / numLeituras;
}

// Função para calcular a média da luminosidade
int calcularMediaLuz() {
  int soma = 0;
  for (int i = 0; i < numLeituras; i++) {
    soma += luzLeituras[i];
  }
  return soma / numLeituras;
}

// Avalia se há necessidade de alerta em cada sensor
void verificarAlertas() {
  // Alerta de luminosidade: muito clara
  alertaLuminosidade = (luminosidade >= MEIA_LUZ_MAX);

  // Alerta de temperatura: fora da faixa de 10°C a 15°C
  alertaTemperatura = (temperatura < 10 || temperatura > 15);

  // Alerta de umidade: fora da faixa de 50% a 70%
  alertaUmidade = (umidade < 50 || umidade > 70);
}

// Controla os LEDs e o buzzer conforme os alertas ativos
void controlarSinais() {
  // Desliga todos os LEDs antes de aplicar a lógica
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);

  // LED e buzzer de acordo com a luminosidade
  if (alertaLuminosidade) {
    digitalWrite(ledVermelho, HIGH);
  } else if (luminosidade >= ESCURO_MAX && luminosidade < MEIA_LUZ_MAX) {
    digitalWrite(ledAmarelo, HIGH);
  } else {
    digitalWrite(ledVerde, HIGH);
  }

  // LED e buzzer de acordo com a temperatura (LED Amarelo)
  if (alertaTemperatura) {
    digitalWrite(ledAmarelo, HIGH);
  }

  // LED e buzzer de acordo com a umidade (LED Vermelho)
  if (alertaUmidade) {
    digitalWrite(ledVermelho, HIGH);
  }

  // Ativa o buzzer se houver qualquer tipo de alerta
  if (alertaLuminosidade || alertaTemperatura || alertaUmidade) {
    tone(buzzer, 1000);  // Liga o buzzer em 1kHz
  } else {
    noTone(buzzer);  // Desliga o buzzer
  }
}

// Exibe no LCD as informações em sequência: Luminosidade → Umidade → Temperatura
void mostrarMensagemAtual() {
  lcd.clear();

  switch (mensagemAtual) {
    case 0: // Luminosidade
      lcd.setCursor(0, 0);
      lcd.print("Luminosidade:");
      lcd.setCursor(0, 1);
      if (luminosidade < ESCURO_MAX) {
        lcd.print("Escuro");
      } else if (luminosidade < MEIA_LUZ_MAX) {
        lcd.print("Meia luz");
      } else {
        lcd.print("Claro");
      }
      break;

    case 1: // Umidade
      lcd.setCursor(0, 0);
      lcd.print("Umidade:");
      lcd.setCursor(0, 1);
      if (umidade < 50) {
        lcd.print("Baixa = ");
      } else if (umidade <= 70) {
        lcd.print("OK = ");
      } else {
        lcd.print("Alta = ");
      }
      lcd.print(umidade);
      lcd.print("%");
      break;

    case 2: // Temperatura
      lcd.setCursor(0, 0);
      lcd.print("Temperatura:");
      lcd.setCursor(0, 1);
      if (temperatura < 10) {
        lcd.print("Baixa = ");
      } else if (temperatura <= 15) {
        lcd.print("OK = ");
      } else {
        lcd.print("Alta = ");
      }
      lcd.print(temperatura, 1);
      lcd.print("C");
      break;
  }
}
