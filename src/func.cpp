#include "bbd_func.h"

//Função que imprime na tela a tela inicial e a pontuação máxima
void drawInitScreen(Adafruit_PCD8544 &display, PushButton &button, int16_t record, bool &start){
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
    if(button.clickButton()){
        start = true;

        //Uma pausa de 350ms para início do jogo
        delay(350);
    }
}

//Função que pausa o game e seta a váriável para controle de um intervalo de 500 ms
void pause(Adafruit_PCD8544 &display, PushButton &button, bool &intervalPosPause){
    while(!button.clickButton()){
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
    display.drawBitmap(0,0, bitmap_sky, 48, 25, BLACK);
}

//Função que imprime no display a linha que separa o campo do jogo, vidas e pontos do jogador
void drawLifeAndPoints(Adafruit_PCD8544 &display, pad &player){
    //Imprimimos a linha que divide as informações do player do campo
    display.drawLine(0, 73, 48, 73, BLACK);

    //imprimimos os corações segundo o número de vidas do player
    if(player.life >= 1)
        display.drawBitmap(0,78, bitmap_heart, 7, 5, BLACK);
    if(player.life >= 2)
        display.drawBitmap(8, 78, bitmap_heart, 7, 5, BLACK);
    if(player.life >= 3)
        display.drawBitmap(16, 78, bitmap_heart, 7, 5, BLACK);

    //Setamos o cursor e condifuramos o texto para imprimirmos os pontos do jogador
    display.setCursor(24, 76);
    display.setTextColor(BLACK);
    display.setTextSize(1);

    //Primeiramnte adicionamos x
    display.print("x");
    
    //Adicionamos zeros que ocuparam as casas das dezenas e centenas caso elas sejam zero
    if(player.points < 10)
        display.print("00");
    else if(player.points < 100)
        display.print("0");
    
    //Por fim, imprimos os pontos do player
    display.print(player.points);
}

//Função que imprime o pad no campo e altera a posição segundo o comando dos controles
void drawPad(Adafruit_PCD8544 &display, pad &player){
    //Variavel para controle de intervalo do pad
    static unsigned long time = 0;

    display.drawBitmap(player.x, 64, bitmap_pad, 11, 3, BLACK);

    if((millis() - time) >= 30){
        //Caso pressionado o buttonL e x > 0, decrementamos x e atualizamos a variável time
        if(player.btnL->pressButton() && player.x > 0){
            player.x -= 1;
            time = millis();
        }
            
        //Caso pressionado o buttonR e x < 37, incrementamos x e atualizamos a variável time
        if(player.btnR->pressButton() && player.x < 37){
            player.x += 1;
            time = millis();
        }
    }
}

//Função que gera os novos itens necessários e reseta a posição y para 0 e gera uma
//nova posição x
/*OBS: NOTE QUE ESTÃO SENDO UTILIZADOS PONTEIROS*/
void genAndRestarItens(falling_item &item){
    //Para deicidir o item que irá cair, será pego um item aleatório, e se ele for par ou divisel por 3 será uma bomba
    //caso contrário será uma âncora
    int8_t a = random(0, 100);

    if(a % 2 == 0 || a % 3 == 0)
        item.isBomb = true;
    else
        item.isBomb = false;

    item.x = random(0, 43);                 //setamos uma nova posição x para o item que vai cair
    item.y = 10;                            //zera-se o eixo y
}

//Função que imprime as bombas que caem sempre em uma posição diferente da última
//Além disso, essa função já faz o tratamento de pontos e perda de vida
void drawFallenItens(Adafruit_PCD8544 &display, pad &player, falling_item &item, float &interval){
    //Variáveis para controle e atualização do tempo de queda da bomba
    const float dValues[4] = {0.1, 0.15, 0.2, 0.34};

    //Variável para controle da atualização do y da bomba
    static unsigned long time = 0;

    //verifica quando a bomba chega na linha final
    if(item.y >= 61 && item.y <= 63){
        //Verificamos se uma das extremidades da bomba toca em pelo menus um pixel do pad ou se elas se encontram no range do pad
        if((item.x >= player.x && item.x <= (player.x + 10)) ||
           ((item.x + 6) >= player.x && (item.x + 6) <= (player.x + 10))){ //Se sim....

            if(item.isBomb)                         //Se for uma bomba...   
                player.points += 1;                   //Incrementamos os pontos
            else                               //Caso seja uma âncora...
                player.life -= 1;                     //É decrementado a vida do player
            
            genAndRestarItens(item);

            interval -= dValues[random(0, 4)]; //diminui-se o tempo de queda da bomba de forma aleatória
        }

    } else if(item.y >= 68){
        //Quando chega ao fim do campo, verifica fica se é uma bomba...
        if(item.isBomb)                            //caso seja...
            player.life -= 1;                  //decrementamos a vida do player

        genAndRestarItens(item);

        interval -= dValues[random(0, 4)]; //diminui-se o tempo de queda da bomba de forma aleatória
    }

    //Desenha a bomba ou a ancora na tela, se isBomb é verdadeiro desenha bomba, caso contrário desenha ancora
    if(item.isBomb)
        display.drawBitmap(item.x, item.y, bitmap_bomb, 6, 6, BLACK);
    else
        display.drawBitmap(item.x, item.y, bitmap_anchor, 6, 6, BLACK);
    
    //verirfica se passou um intervalo de x milissegundos
    if((millis() - time) >= interval){
        time = millis();        //Caso tenha passado, atualizamos a time e incrementamods y
        item.y += 1;
    }
}