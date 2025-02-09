#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "FastLED.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"

// Definições de pinos
#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6
#define LED_RGB_R 11
#define LED_RGB_G 12
#define LED_RGB_B 13
#define LED_MATRIX_PIN 7
#define OUT_PIN 8  // Pino para o controle do WS2812 (ajuste conforme necessário)

// Definições do display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Mapeamento dos LEDs da matriz 5x5
int mapa_leds[25] = {
    24, 23, 22, 21, 20,
    15, 16, 17, 18, 19,
    14, 13, 12, 11, 10,
     5,  6,  7,  8,  9,
     4,  3,  2,  1,  0
};

// Definições do LED RGB
CRGB leds[1]; // LED RGB simples

// Números de 0 a 9
double numeros[10][25] = {
    {0, 1, 1, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 1, 1, 0}, // 0

    {0, 0, 1, 0, 0,
     0, 1, 1, 0, 0,
     0, 0, 1, 0, 0,
     0, 0, 1, 0, 0,
     0, 0, 1, 0, 0}, // 1

    {0, 1, 1, 1, 0,
     0, 0, 0, 1, 0,
     0, 1, 1, 1, 0,
     0, 1, 0, 0, 0,
     0, 1, 1, 1, 0}, // 2

    {0, 1, 1, 1, 0,
     0, 0, 0, 1, 0,
     0, 1, 1, 1, 0,
     0, 0, 0, 1, 0,
     0, 1, 1, 1, 0}, // 3

    {0, 1, 0, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 1, 1, 0,
     0, 0, 0, 1, 0,
     0, 0, 0, 1, 0}, // 4

    {0, 1, 1, 1, 0,
     0, 1, 0, 0, 0,
     0, 1, 1, 1, 0,
     0, 0, 0, 1, 0,
     0, 1, 1, 1, 0}, // 5

    {0, 1, 1, 1, 0,
     0, 1, 0, 0, 0,
     0, 1, 1, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 1, 1, 0}, // 6

    {0, 1, 1, 1, 0,
     0, 0, 0, 1, 0,
     0, 0, 1, 0, 0,
     0, 0, 1, 0, 0,
     0, 0, 1, 0, 0}, // 7

    {0, 1, 1, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 1, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 1, 1, 0}, // 8

    {0, 1, 1, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 1, 1, 0,
     0, 0, 0, 1, 0,
     0, 1, 1, 1, 0}, // 9
};

void set_pixel_color(uint8_t r, uint8_t g, uint8_t b) {
    leds[0] = CRGB(r, g, b); // Usando FastLED para controlar o WS2812
    FastLED.show();
}

// Função para exibir um número na matriz de LEDs
void desenho_pio(double *desenho, double r, double g, double b) {
    float brilho = 0.8;  // Reduz a potência para 80%

    for (int i = 0; i < 25; i++) {
        int posicao_fisica = mapa_leds[i];
        if (desenho[i] == 1) {
            set_pixel_color((uint8_t)(r * 255 * brilho), 
                            (uint8_t)(g * 255 * brilho), 
                            (uint8_t)(b * 255 * brilho));
        } else {
            set_pixel_color(0, 0, 0); // Apaga o LED
        }
    }
}

// Funções de interrupção para os botões
volatile bool buttonAState = false;
volatile bool buttonBState = false;

void buttonAInterrupt() {
  buttonAState = !buttonAState;
}

void buttonBInterrupt() {
  buttonBState = !buttonBState;
}

void setup() {
  // Inicializar comunicação serial
  stdio_init_all();

  // Configuração do display SSD1306
  if (!display.begin(SSD1306_I2C_ADDRESS, 0x3C)) {
    printf("Falha ao inicializar o display SSD1306\n");
    while (true);
  }
  display.clearDisplay();
  
  // Configurar LEDs
  FastLED.addLeds<NEOPIXEL, LED_MATRIX_PIN>(leds, 1);
  
  // Configurar pinos dos botões e interrupções
  gpio_init(BUTTON_A_PIN);
  gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
  gpio_pull_up(BUTTON_A_PIN);
  
  gpio_init(BUTTON_B_PIN);
  gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
  gpio_pull_up(BUTTON_B_PIN);
  
  // Definir interrupções para os botões
  gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, &buttonAInterrupt);
  gpio_set_irq_enabled_with_callback(BUTTON_B_PIN, GPIO_IRQ_EDGE_FALL, true, &buttonBInterrupt);

  // Inicializar LED RGB
  gpio_init(LED_RGB_R);
  gpio_set_dir(LED_RGB_R, GPIO_OUT);
  gpio_init(LED_RGB_G);
  gpio_set_dir(LED_RGB_G, GPIO_OUT);
  gpio_init(LED_RGB_B);
  gpio_set_dir(LED_RGB_B, GPIO_OUT);

  // Mensagem inicial no display
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Projeto iniciado!");
  display.display();
}

void loop() {
  // Verificar o estado do botão A
  if (buttonAState) {
    gpio_put(LED_RGB_G, 1);  // Acende o LED verde
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("LED Verde ligado!");
    display.display();
    printf("LED Verde ligado!\n");
    buttonAState = false;
  } else {
    gpio_put(LED_RGB_G, 0);  // Apaga o LED verde
  }

  // Verificar o estado do botão B
  if (buttonBState) {
    gpio_put(LED_RGB_B, 1);  // Acende o LED azul
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("LED Azul ligado!");
    display.display();
    printf("LED Azul ligado!\n");
    buttonBState = false;
  } else {
    gpio_put(LED_RGB_B, 0);  // Apaga o LED azul
  }

  // Simulação de envio de número para a matriz
  if (stdio_available()) {
    char receivedChar = getchar();
    if (receivedChar >= '0' && receivedChar <= '9') {
      int num = receivedChar - '0'; // Converter caractere para número
      desenho_pio(numeros[num], 1.0, 0.0, 0.0); // Exibir o número na matriz em vermelho
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("Numero: ");
      display.println(receivedChar);
      display.display();
    }
  }
}
