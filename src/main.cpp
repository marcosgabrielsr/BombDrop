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
float interval = INIT_INTERVAL;
uint16_t time = INIT_TIME;
unsigned long i = 0;

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

  if(!start)
    drawInitScreen(display, buttonX, record, start);
  
  else {
    i = millis();

    //Equanto o player ainda tiver pontos de vida
    while(player.life > 0) {
      display.clearDisplay();

      drawFieldGame(display, player);

      newItem(time, i, itens);
      drawFallingItem(display, itens, interval, player);

      drawPad(display, player);
      itemColision(itens, player, interval);

      if(buttonX.clickButton()){
        unsigned long d = millis() - i;

        pause(display, buttonX);

        display.clearDisplay();

        drawFieldGame(display, player);
        drawFallingItem(display, itens, interval, player);
        drawPad(display, player);

        display.display();

        delay(3000);

        i = millis() - d;
      }

      display.display();
    }
    
    //start volta a ser false para impressão da tela inicial
    start = false;
    record = player.points;
    player.points = 0;
    player.life = 3;
    interval = INIT_INTERVAL;
    time = INIT_TIME;

    while(itens != NULL) removeItem(itens);         //Código que esvazia toda a fila
  }

  display.setRotation(1);
  display.display();
}