//Este arquivo contém todas as bibliotecas utilizadas neste projeto e
//todas as funções utilizadas para o funcionamento do jogo

//Incluindo bibliotecas
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "PushButton.hpp"

// 'sky', 48x25px
const unsigned char bitmap_sky [] PROGMEM = {
	0x00, 0xc0, 0x80, 0x00, 0x01, 0xf8, 0xfb, 0x80, 0xf8, 0x00, 0x1f, 0x0e, 0x0e, 0x00, 0x0c, 0x3f, 
	0xf0, 0x03, 0x00, 0x00, 0x06, 0x66, 0x00, 0x01, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x31, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xcf, 0xf8, 0x00, 0x00, 0x00, 0xf1, 0x86, 0x04, 0x00, 0x00, 
	0x07, 0x80, 0x00, 0x03, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x38, 0x00, 0x00, 0x00, 
	0xb0, 0x00, 0x60, 0x00, 0x00, 0x00, 0x11, 0xb0, 0x40, 0x00, 0x00, 0x00, 0x11, 0xf0, 0x70, 0x00, 
	0x00, 0x00, 0x62, 0x10, 0x70, 0x00, 0x00, 0x00, 0xdc, 0x0c, 0xd8, 0x00, 0xe3, 0xff, 0xb0, 0x07, 
	0x0d, 0x01, 0xbe, 0x00, 0x00, 0x00, 0x07, 0xff, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x6e, 0x00, 0x00, 0x00, 0x80, 0x63, 0xc3, 0xfe, 0x00, 0x01, 0xce, 0xfe, 
	0x00, 0x03, 0xc0, 0x06, 0x7b, 0x80, 0x00, 0x00, 0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x38, 0x70, 
	0x00, 0x00, 0x00, 0x00, 0x0f, 0x80
};

// 'pad', 11x3px
const unsigned char bitmap_pad [] PROGMEM = {
	0xff, 0xe0, 0x7f, 0xc0, 0x3f, 0x80
};

// 'bomb', 6x6px
const unsigned char bitmap_bomb [] PROGMEM = {
	0x30, 0x78, 0x84, 0x84, 0x84, 0x78
};

// 'heart', 7x5px
const unsigned char bitmap_heart [] PROGMEM = {
	0x6c, 0xfe, 0x7c, 0x38, 0x10
};

// 'anchor', 6x6px
const unsigned char bitmap_anchor [] PROGMEM = {
	0x30, 0x78, 0x30, 0x30, 0xb4, 0x48
};

//registro para trabalhar com o pad
struct pad{
	uint8_t life = 1;			//Variável para armazenar os pontos de vida do pad

	int points;					//Variável para armazenar os pontos do player

	uint8_t x = 18;				//Variável para controle da coordenada X do padX

	PushButton *btnL;			//Ponteiro que aponta para o botão da esquerda
	PushButton *btnR;			//Ponteiro que aponta para o botão da esquerda
};

//registro para trabalhar com os itens que caem
struct fallingItem{
	bool isBomb;				//Variável para controle do tipo do item

	uint8_t x;					//Variável para controle da coordenada x do item
	uint8_t y;					//Variável para controle da coordenada y do item

	struct fallingItem * prox;	//Variável que armazena o endereço para o próximo item
};

//Função que imprime na tela a tela inicial e a pontuação máxima
void drawInitScreen(Adafruit_PCD8544 &display, PushButton &button, int16_t record, bool &start);

//Função que pausa o game e seta a váriável para controle de um intervalo de 500 ms
void pause(Adafruit_PCD8544 &display, PushButton &button, bool &intervalPosPause);

//Função que imprime no display o campo de jogo (céu, quantidade de vidas e pontos)
void drawFieldGame(Adafruit_PCD8544 &display, pad &player);

//Função que imprime o pad no campo e altera a posição segundo o comando dos controles
void drawPad(Adafruit_PCD8544 &display, pad &player);

//Função que desenha o item na tela enquanto ele está caindo
void drawFallingItem(Adafruit_PCD8544 &display, fallingItem* &itens, float &interval, pad &player);

//Função que adiciona um novo item para a fila de itens
void addItem(fallingItem* &itens);

//Função que verifica a colisão do item com o pad ou fim do campo
//e gerencia se o player perderá uma vida ou ganhará um ponto
bool itemColision(fallingItem* &itens, pad &player);