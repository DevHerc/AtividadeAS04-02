# Projeto de Controle de LEDs e Display com Raspberry Pi Pico

Este projeto utiliza um Raspberry Pi Pico para controlar um conjunto de LEDs WS2812, um display OLED SSD1306 e dois botões para interações. O projeto foi desenvolvido para exibir números de 0 a 9 na matriz de LEDs e também controlar um LED RGB com os botões. A comunicação com o display e LEDs é feita utilizando a biblioteca `FastLED` para os LEDs WS2812 e `Adafruit_SSD1306` para o display OLED.

## Diagrama de Conexão

- **Botão A**: Pino GPIO 5
- **Botão B**: Pino GPIO 6
- **LED RGB (Vermelho)**: Pino GPIO 11
- **LED RGB (Verde)**: Pino GPIO 12
- **LED RGB (Azul)**: Pino GPIO 13
- **Matriz de LEDs WS2812**: Pino GPIO 7
- **Display OLED SSD1306**: Conexão I2C (Pinos padrão SDA e SCL)

## Bibliotecas Necessárias

O código depende das seguintes bibliotecas:

- **FastLED**: Para controle dos LEDs WS2812.
- **Adafruit SSD1306**: Para controle do display OLED.
- **Adafruit GFX**: Para gráficos do display OLED.
- **Pico SDK**: Para controlar o Raspberry Pi Pico.

## Funcionalidade

### Botões

- **Botão A**: Acende o LED verde e exibe "LED Verde ligado!" no display.
- **Botão B**: Acende o LED azul e exibe "LED Azul ligado!" no display.

### Exibição de Números

O código também exibe números na matriz de LEDs. Ao enviar um número (de 0 a 9) via comunicação serial, ele será exibido na matriz de LEDs em vermelho.

### Controle de LEDs WS2812

Os LEDs WS2812 da matriz 5x5 são controlados para exibir números. A cada número enviado, os LEDs correspondentes são acesos.

## Código

O código realiza as seguintes funções:

- Inicializa o display OLED e o controle da matriz de LEDs WS2812.
- Configura dois botões para alternar o estado de LEDs RGB (verde e azul).
- Recebe números via comunicação serial e exibe esses números na matriz de LEDs.
- Controle de LEDs WS2812 com brilho ajustado.


### Exemplo de Comunicação Serial

- Enviar o número `0` exibe o número 0 na matriz de LEDs.
- Enviar o número `1` exibe o número 1 na matriz de LEDs.
