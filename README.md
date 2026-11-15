# Sistema de Monitoramento e Controle de Umidade com Arduino

Este repositório contém o código-fonte de um sistema desenvolvido em **Arduino** para monitoramento de umidade em dois pontos distintos, equipado com filtro digital contra ruídos, controle de atuadores via relé, botões com tratamento de *debounce* e interface visual em display LCD 16x2.

---

## 🚀 Funcionalidades

* **Leitura Dupla de Sensores:** Monitoramento simultâneo de dois sensores analógicos de umidade.
* **Filtro Digital (Exponential Moving Average - EMA):** Aplicação de um filtro de suavização matemática nas leituras para eliminar ruídos elétricos e evitar variações bruscas (saltos) na exibição do display.
* **Média de Amostragem:** Coleta rápida de 10 amostras brutas por ciclo para estabilização prévia do sinal.
* **Controle de Relé e Atuadores:** Acionamento de um relé e LEDs indicadores (Verde para sistema ligado, Vermelho para desligado).
* **Interface LCD 16x2:** Exibição em tempo real do estado do relé e das porcentagens de umidade de ambos os sensores, incluindo controle dinâmico do *backlight* (brilho do visor).
* **Controle por Botão com *Debounce*:** Alternância segura do estado do sistema através de um botão físico com resistor *pull-up* interno.

---

## 📌 Pinout e Conexões

| Componente | Pino no Arduino | Descrição |
| :--- | :--- | :--- |
| **Display LCD 16x2** | 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13 | Conexões de dados e controle do display |
| **Backlight LCD** | Pino 9 (PWM) | Controle de intensidade da luz de fundo |
| **LED Verde** | A0 | Indicador visual de sistema ligado (Relé ON) |
| **LED Vermelho** | A1 | Indicador visual de sistema desligado (Relé OFF) |
| **Módulo Relé** | A2 | Acionamento de carga externa |
| **Sensor de Umidade 1** | A3 | Entrada analógica para leitura do Sensor 1 |
| **Sensor de Umidade 2** | A4 | Entrada analógica para leitura do Sensor 2 |
| **Botão (Push Button)** | A5 | Alternância de estado do sistema (com INPUT_PULLUP) |

---

## 🛠️ Requisitos e Dependências

* **Hardware:**
  * Placa Arduino (Uno, Nano, Mega, etc.)
  * Display LCD 16x2
  * 2x Sensores de umidade analógicos
  * Módulo Relé
  * LEDs Verde e Vermelho (com resistores adequados)
  * Botão Push Button
* **Software:**
  * [Arduino IDE](https://www.arduino.cc/en/software)
  * Biblioteca padrão `LiquidCrystal` (já inclusa nativamente na IDE do Arduino)

---

## ⚙️ Como Usar

1. Clone este repositório ou faça o download dos arquivos.
2. Abra a **Arduino IDE**.
3. Conecte sua placa Arduino ao computador.
4. Abra o arquivo `.ino` contendo o código fornecido.
5. Verifique se as conexões físicas da sua protoboard/circuito correspondem à tabela de pinagem descrita acima.
6. Compile e faça o *upload* do código para a sua placa.

---

## 📝 Licencia / Contribuição
Sinta-se à vontade para abrir *issues* ou enviar *pull requests* caso queira sugerir melhorias ou novas funcionalidades para o projeto!