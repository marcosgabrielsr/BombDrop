#include "func.h"

//Função que imprime na tela a tela inicial e a pontuação máxima
void drawInitScreen(Adafruit_PCD8544 &display, PushButton button, int16_t record, bool &start){
    //Variáveis para controle da alternância do aviso de clique do botão
    static bool blink = true;
    static unsigned long time = 0;

    //Desenha um retângulo que cerca toda a tela
    display.drawRect(0, 0, 48, 84, BLACK);

    //Desenha um retângulo sobre o título do jogo
    display.drawRect(2, 6, 44, 21, BLACK);

    //Configurando display para escrita do título
    display.setCursor(4, 8);
    display.setTextColor(BLACK);
    display.setTextSize(1);

    //Escrevendo título
    display.println("BOMB");
    display.setCursor(21, 18);
    display.print("DROP");

    //Configurando e escrevendo o record
    display.setCursor(4, 40);
    display.print("RECORD: ");
    display.setCursor(20, 50);
    display.print(record);

    //Verifica se passou um intervalo de 700 ms
    if((millis() - time) >= 700){
        blink = !blink;
        time = millis();
    }

    //Configura e escreve a mensagem caso blink seja verdadeiro
    display.setCursor(8, 64);
    blink ? display.print("(X) to start!") : display.print("");

    //Altera star para true caso botão seja clicado
    if(button.clickBtn()){
        start = true;

        //Uma pausa de 350ms para início do jogo
        delay(350);
    }
}

//Função que pausa o game e seta a váriável para controle de um intervalo de 500 ms
void pause(Adafruit_PCD8544 &display, PushButton button, bool &intervalPosPause){
    while(!button.clickBtn()){
        display.clearDisplay();

        display.setCursor(10, 40);
        display.setTextColor(BLACK);
        display.setTextSize(1);

        display.print("PAUSE");

        display.display();
    }

    intervalPosPause = true;
}

//Função que imprime o céu no campo do jogo
void drawSky(Adafruit_PCD8544 &display){
    display.drawBitmap(0,0, epd_bitmap_sky, 48, 25, BLACK);
}

//Função que imprime no display a linha que separa o campo do jogo, vidas e pontos do jogador
void drawLifeAndPoints(Adafruit_PCD8544 &display, uint8_t &life, uint16_t &points){
    //Imprimimos a linha que divide as informações do player do campo
    display.drawLine(0, 73, 48, 73, BLACK);

    //imprimimos os corações segundo o número de vidas do player
    if(life >= 1)
        display.drawBitmap(0,78,epd_bitmap_heart, 7, 5, BLACK);
    if(life >= 2)
        display.drawBitmap(8, 78,epd_bitmap_heart, 7, 5, BLACK);
    if(life >= 3)
        display.drawBitmap(16, 78, epd_bitmap_heart, 7, 5, BLACK);

    //Setamos o cursor e condifuramos o texto para imprimirmos os pontos do jogador
    display.setCursor(24, 76);
    display.setTextColor(BLACK);
    display.setTextSize(1);

    //Primeiramnte adicionamos x
    display.print("x");
    
    //Adicionamos zeros que ocuparam as casas das dezenas e centenas caso elas sejam zero
    if(points < 10)
        display.print("00");
    else if(points < 100)
        display.print("0");
    
    //Por fim, imprimos os pontos do player
    display.print(points);
}

//Função que imprime o pad no campo e altera a posição segundo o comando dos controles
void drawPad(Adafruit_PCD8544 &display, PushButton &buttonL, PushButton &buttonR, uint8_t &padX){
    //Variavel para controle de intervalo do pad
    static unsigned long time = 0;

    display.drawBitmap(padX, 64, epd_bitmap_pad, 11, 3, BLACK);

    if((millis() - time) >= 30){
        //Caso pressionado o buttonL e x > 0, decrementamos x e atualizamos a variável time
        if(buttonL.pressBtn() && padX > 0){
            padX -= 1;
            time = millis();
        }
            
        //Caso pressionado o buttonR e x < 37, incrementamos x e atualizamos a variável time
        if(buttonR.pressBtn() && padX < 37){
            padX += 1;
            time = millis();
        }
    }
    
}

//Função que gera os novos itens necessários e reseta a posição y para 0 e gera uma nova posição x
/*OBS: NOTE QUE ESTÃO SENDO UTILIZADOS PONTEIROS*/
void genAndRestarItens(int8_t *x, int8_t *y, bool *isBomb){
    //Para deicidir o item que irá cair, será pego um item aleatório, e se ele for par ou divisel por 3 será uma bomba
    //caso contrário será uma âncora
    int8_t a = random(0, 100);
    if(a % 2 == 0 || a % 3 == 0)
        *isBomb = true;
    else
        *isBomb = false;

    *x = random(0, 43);              //setamos uma nova posição x para o item que vai cair
    *y = 10;                          //zera-se o eixo y
}

//Função que imprime as bombas que caem sempre em uma posição diferente da última
//Além disso, essa função já faz o tratamento de pontos e perda de vida
void drawFallenItens(Adafruit_PCD8544 &display, uint8_t &life,uint16_t &points, uint8_t padX, float &interval){
    //coorenadas da bomba
    static int8_t x = random(0, 43), y = 10;
    static bool isBomb = true;

    //Variáveis para controle e atualização do tempo de queda da bomba
    const float dValues[4] = {0.1, 0.15, 0.2, 0.34};

    //Variável para controle da atualização do y da bomba
    static unsigned long time = 0;

    //verifica quando a bomba chega na linha final
    if(y >= 61 && y <= 63){
        //Verificamos se uma das extremidades da bomba toca em pelo menus um pixel do pad ou se elas se encontram no range do pad
        if((x >= padX && x <= (padX + 10)) || ((x + 6) >= padX && (x + 6) <= (padX + 10))){ //Se sim....
            if(isBomb)                         //Se for uma bomba...   
                points += 1;                   //Incrementamos os pontos
            else                               //Caso seja uma âncora...
                life -= 1;                     //É decrementado a vida do player
            
            //Resentando as coordenadas e gerando novo item
            genAndRestarItens(&x, &y, &isBomb);

            interval -= dValues[random(0, 4)]; //diminui-se o tempo de queda da bomba de forma aleatória
        }                                   
    } else if(y >= 68){
            //Quando chega ao fim do campo, verifica fica se é uma bomba...
            if(isBomb)                            //caso seja...
                life -= 1;                  //decrementamos a vida do player

            interval -= dValues[random(0, 4)]; //diminui-se o tempo de queda da bomba de forma aleatória

            //Por fim, gera um novo item 
            genAndRestarItens(&x, &y, &isBomb);
        }

    //Desenha a bomba ou a ancora na tela, se isBomb é verdadeiro desenha bomba, caso contrário desenha ancora
    if(isBomb)
        display.drawBitmap(x, y, epd_bitmap_bomb, 6, 6, BLACK);
    else
        display.drawBitmap(x, y, epd_bitmap_anchor, 6, 6, BLACK);
    
    //verirfica se passou um intervalo de x milissegundos
    if((millis() - time) >= interval){
        time = millis();        //Caso tenha passado, atualizamos a time e incrementamods y
        y += 1;
    }
}