//Incluindo biblioteca principal do jogo
#include "func.h"

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
uint8_t life = 3;
uint8_t padX = 0;
uint16_t points = 0, record = 0;

//Variáveis para de iniciar o jogo e pause do jogo
bool start = false;
bool intervalPosPause = false;

//Variável para controle de tempo de queda da bomba
float interval = 40;

void setup(){
  //Define led como pino de saída e deixa o led de fundo ligado
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  //configuramos a função randomica de acordo com a porta A0 usando o randomSeed()
  randomSeed(analogRead(A0));

  //Inicializando o display
  display.begin();
  display.setContrast(57);
  display.clearDisplay();
  display.display();
}

void loop(){
  display.clearDisplay();

  //Verifica se start é falso
  if(start == false){
    //Chama a função que desenha a tela inicial dos jogos
    drawInitScreen(display, buttonX, record, start);

  }else{
    if(life >= 1){

      //Chama as funções que definem o jogo
      drawSky(display);

      drawPad(display, buttonL, buttonR, padX);

      drawFallenItens(display, life, points, padX, interval);

      drawLifeAndPoints(display, life, points);

      //Para o jogo por 500 ms depois de ser despausado
      if(intervalPosPause){
          display.display();
          intervalPosPause = false;
          delay(2500);
      }

      //Chama a função pause quando buttonX for clicado durante o jogo  
      if(buttonX.clickButton())
        pause(display, buttonX, intervalPosPause);

    } else {
      //Atualiza o record e reiniciliza os pontos, as quantidade de vidas e o tempo de queda dos objetos
      if(points > record)
      record = points;

      life = 3;
      points = 0;
      start = false;
      interval = 40;
      delay(350);
    }
  }

  display.setRotation(3);
  display.display();
}