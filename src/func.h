//Este arquivo contém todas as bibliotecas utilizadas neste projeto e
//todas as funções utilizadas para o funcionamento do jogo

//Incluindo bibliotecas
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "PushButton.hpp"
#include "sptrites.h"

//Função que imprime na tela a tela inicial e a pontuação máxima
void drawInitScreen(Adafruit_PCD8544 &display, PushButton button, int16_t record, bool &start);

//Função que pausa o game e seta a váriável para controle de um intervalo de 500 ms
void pause(Adafruit_PCD8544 &display, PushButton button, bool &intervalPosPause);

//Função que imprime o céu no campo do jogo
void drawSky(Adafruit_PCD8544 &display);

//Função que imprime no display a linha que separa o campo do jogo, vidas e pontos do jogador
void drawLifeAndPoints(Adafruit_PCD8544 &display, uint8_t &life, uint16_t &points);

//Função que imprime o pad no campo e altera a posição segundo o comando dos controles
void drawPad(Adafruit_PCD8544 &display, PushButton &buttonL, PushButton &buttonR, uint8_t &padX);

//Função que imprime as bombas que caem sempre em uma posição diferente da última
//Além disso, essa função já faz o tratamento de pontos e perda de vida
void drawFallenItens(Adafruit_PCD8544 &display, uint8_t &life,uint16_t &points, uint8_t padX, float &interval);