#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

#define NUM_LEDS    144 // Número de leds de la tira
#define LED_PIN     6   // Pin digital Arduino Uno

CRGB g_LEDs[NUM_LEDS] = {0}; //Buffer

void setup() {
  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(g_LEDs, NUM_LEDS);  // FastLed
}

void loop() {
  DrawComet(); // Efecto Cometa
}

void DrawComet() {
    const byte fadeAmt = 128;
    const int cometSize = 5; // Tamaño del cometa (5 LEDs consecutivos)
    const int deltaHue  = 4; // Velocidad cambio de color

    static byte hue = HUE_RED; // Color rojo
    static int iDirection = 1; // 1: se mueve a la derecha | -1: se mueve a la izquierda
    static int iPos = 0; // Posición inicial

    hue += deltaHue; // Cambio color

    iPos += iDirection; // Cambio posicion

    // Compruba si llego al final 
    if (iPos == (NUM_LEDS - cometSize) || iPos == 0)
        iDirection *= -1;
    
    for (int i = 0; i < cometSize; i++)
        g_LEDs[iPos + i].setHue(hue);
    
    // Desvanece los leds aleatoriamente
    for (int j = 0; j < NUM_LEDS; j++)
        if (random(10) > 5)
            g_LEDs[j] = g_LEDs[j].fadeToBlackBy(fadeAmt);  

    FastLED.show();
    delay(50);
}


