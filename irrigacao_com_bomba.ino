#include <LiquidCrystal.h>

// Configuração exata do seu display LCD
LiquidCrystal lcd(2,3,4,6,7,8,9,10,11,12,13);

const int PINO_LED_VERDE = A0; 
const int PINO_LED_VERM  = A1; 
const int PINO_RELE      = A2; 
const int PINO_SENSOR_1  = A3; 
const int PINO_SENSOR_2  = A4; 
const int PINO_BOTAO     = A5;

#define RELE_LIGADO    HIGH
#define RELE_DESLIGADO LOW

bool sistemaLigado = false; 
int ultimoEstadoBotao = HIGH;

// Variáveis para guardar o valor suavizado (Filtro)
float umidadeFiltrada1 = -1;
float umidadeFiltrada2 = -1;

void setup() {
  lcd.begin(16,2);
  pinMode(PINO_LED_VERDE, OUTPUT); 
  pinMode(PINO_LED_VERM, OUTPUT);  
  pinMode(PINO_RELE, OUTPUT);
  pinMode(PINO_BOTAO, INPUT_PULLUP);

  digitalWrite(PINO_RELE, RELE_DESLIGADO);
  digitalWrite(PINO_LED_VERDE, LOW);
  digitalWrite(PINO_LED_VERM, HIGH);
  
  lcd.setCursor(0, 0);
  lcd.print("RELE: OFF       ");
  
  const int pinoBacklight = 9; 
  analogWrite(pinoBacklight, 64); 
}

void loop() {
  // 1. Coleta uma média rápida de 10 leituras brutas para matar o ruído elétrico
  long soma1 = 0;
  long soma2 = 0;
  int amostras = 10;

  for (int i = 0; i < amostras; i++) {
    soma1 += analogRead(PINO_SENSOR_1);
    soma2 += analogRead(PINO_SENSOR_2);
    delay(2);
  }
  
  int valorBruto1 = soma1 / amostras;
  int valorBruto2 = soma2 / amostras;
  
  // Converte para porcentagem
  int umidadeInstantanea1 = map(valorBruto1, 650, 300, 0, 100);
  int umidadeInstantanea2 = map(valorBruto2, 650, 300, 0, 100);
  
  umidadeInstantanea1 = constrain(umidadeInstantanea1, 0, 100);
  umidadeInstantanea2 = constrain(umidadeInstantanea2, 0, 100);

  // 2. Aplica o Filtro de Suavização (Exponential Moving Average)
  // O fator 0.1 significa que 90% do valor vem da média anterior e 10% da leitura nova.
  // Isso trava o número e elimina qualquer saltinho brusco na tela.
  if (umidadeFiltrada1 == -1) {
    umidadeFiltrada1 = umidadeInstantanea1; // Inicializa na primeira passada
    umidadeFiltrada2 = umidadeInstantanea2;
  } else {
    umidadeFiltrada1 = (umidadeFiltrada1 * 0.90) + (umidadeInstantanea1 * 0.10);
    umidadeFiltrada2 = (umidadeFiltrada2 * 0.90) + (umidadeInstantanea2 * 0.10);
  }

  // Converte para inteiro para exibir bonitinho no LCD
  int umidadeFinal1 = (int)(umidadeFiltrada1 + 0.5);
  int umidadeFinal2 = (int)(umidadeFiltrada2 + 0.5);

  // 3. Leitura do botão com debounce
  int leituraBotao = digitalRead(PINO_BOTAO);

  if (ultimoEstadoBotao == HIGH && leituraBotao == LOW) {
    sistemaLigado = !sistemaLigado;
    delay(250); 
  }
  ultimoEstadoBotao = leituraBotao;

  const int pinoBacklight = 9; 

  // 4. Controle dos atuadores (LEDs, Relé e LCD Linha 1)
  if (sistemaLigado == true) {
    digitalWrite(PINO_RELE, RELE_LIGADO);
    digitalWrite(PINO_LED_VERDE, HIGH);
    digitalWrite(PINO_LED_VERM, LOW);
    
    lcd.setCursor(0, 0);
    lcd.print("RELE: ON        ");
    analogWrite(pinoBacklight, 255); 
  } else {
    digitalWrite(PINO_RELE, RELE_DESLIGADO);
    digitalWrite(PINO_LED_VERDE, LOW);
    digitalWrite(PINO_LED_VERM, HIGH);
    
    lcd.setCursor(0, 0);
    lcd.print("RELE: OFF       ");
    analogWrite(pinoBacklight, 64); 
  }

  // 5. Exibe os valores estáveis na Linha 2 do LCD
  lcd.setCursor(0, 1);
  lcd.print("S1:"); 
  lcd.print(umidadeFinal1); 
  lcd.print("% ");
  
  lcd.print("S2:"); 
  lcd.print(umidadeFinal2); 
  lcd.print("%   ");

  delay(150);
}