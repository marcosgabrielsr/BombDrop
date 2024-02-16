//Incluindo biblioteca principal do jogo
#include "bbd_func.h"

//Mapeando Hardware:
//pinos do display
#define pinCLK 3
#define pinDIN 4
#define pinDC 5
#define pinCE 6
#define pinRST 7
#define led 2

//pinos dos botões
#define pinBtnL 8
#define pinBtnX 9
#define pinBtnR 10

//Criando obejtos
Adafruit_PCD8544 display = Adafruit_PCD8544(pinCLK, pinDIN, pinDC, pinCE, pinRST);

PushButton buttonL(pinBtnL, 170);
PushButton buttonX(pinBtnX, 170);
PushButton buttonR(pinBtnR, 170);

//Variáveis pra controle dde vida, coordenada x do pad e pontos
uint16_t record = 0;

//Variáveis para de iniciar o jogo e pause do jogo
bool start = false;

//Variável para controle de tempo de queda da bomba
float interval = 200;

//Criando structs para controle dos itens e do pad
fallingItem *itens = NULL;
pad player;

void setup(){
  Serial.begin(9600);

  //Define led como pino de saída e deixa o led de fundo ligado
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  //configurando a função randomica de acordo com a porta A0 usando o randomSeed()
  randomSeed(analogRead(A0));

  player.btnL = &buttonL;
  player.btnR = &buttonR;

  //Inicializando o display
  display.begin();
  display.setContrast(57);
  display.clearDisplay();
  display.display();
}

void loop(){
  display.clearDisplay();

  drawFieldGame(display, player);

  if(buttonX.clickButton())
    addItem(itens);

  drawFallingItem(display, itens, interval, player);
  drawPad(display, player);

  itemColision(itens, player);

  display.setRotation(1);
  display.display();
}