#include "bbd_func.h"

//Função que imprime na tela a tela inicial e a pontuação máxima
void drawInitScreen(Adafruit_PCD8544 &display, PushButton &button, int16_t record, bool &start) {
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
void pause(Adafruit_PCD8544 &display, PushButton &button, bool &intervalPosPause) {
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

//Função que imprime no display o campo de jogo (céu, quantidade de vidas e pontos)
void drawFieldGame(Adafruit_PCD8544 &display, pad &player) {
    //Desenhando o céu do campo
    display.drawBitmap(0,0, bitmap_sky, 48, 25, BLACK);

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
    
    //Adicionamos zeros que ocuparam as casas das dezenas e centenas caso elas sejam zero
    if(player.points < 10)
        display.print("x00");

    else if(player.points < 100)
        display.print("x0");

    else
        display.print("x");
    
    //Por fim, imprimos os pontos do player
    display.print(player.points);
}

//Função que imprime o pad no campo e altera a posição segundo o comando dos controles
void drawPad(Adafruit_PCD8544 &display, pad &player) {
    //Variavel para controle de intervalo do pad
    static unsigned long time = 0;

    display.drawBitmap(player.x, 64, bitmap_pad, 11, 3, BLACK);

    if((millis() - time) >= 30){
        //Caso pressionado o buttonL e x > 0, decrementamos x e atualizamos a variável time
        if (player.btnL->pressButton() && player.x > 0) {
            player.x -= 1;
            time = millis();
        }
            
        //Caso pressionado o buttonR e x < 37, incrementamos x e atualizamos a variável time
        if (player.btnR->pressButton() && player.x < 37){
            player.x += 1;
            time = millis();
        }
    }
}

//Função que adiciona um novo item para a fila de itens
void addItem(fallingItem* &itens) {
    fallingItem *p = itens, *newItem = NULL;

    newItem = (fallingItem*) calloc (1, sizeof(fallingItem));

    if (newItem == NULL) {                            //Erro na alocação de memória
        return;
    }

    newItem->isBomb = random(0, 2);
    newItem->x = random(0, 43);
    newItem->y = 10;
    newItem->prox = NULL;

    if(itens == NULL)
        itens = newItem;
    
    else{
        while(p->prox != NULL) p = p->prox;
        p->prox = newItem;
    }
}

//Função que remove os items da fila
void removeItem(fallingItem* &itens) {
    fallingItem *p = itens;

    if(itens != NULL) {
        itens = itens->prox;
        free(p);
    }
}

//Função que verifica a colisão do item com o pad ou fim do campo
//e gerencia se o player perderá uma vida ou ganhará um ponto
bool itemColision(fallingItem* &itens, pad &player) {
    fallingItem *item = itens;
    
    //Verifica se o item chega em um intervalo onde o pad pode pegálo
    if(item->y >= 61 && item->y <= 63) {
        //Verifica se algum pixel do item está sobre algum pixel do pad
        if((item->x >= player.x && item->x <= (player.x + 10))  ||
            ((item->x + 6) >= player.x && (item->x + 6) <= (player.x + 10))){

                //Verifica se é uma bomba (ponto++) ou âncora (life--)
                if(item->isBomb)
                    player.points++;
                else
                    player.life--;
                
                removeItem(itens);
                return true;
        }
    
    //Verifica se o item chegou ao fim do campo
    } else if(item->y >= 68) {
        //Verifica se é uma bomba (life--)
        if (item->isBomb)
            player.life--;
        
        removeItem(itens);
        return true;
    }

    return false;
}

//Função que desenha o item na tela enquanto ele está caindo
void drawFallingItem(Adafruit_PCD8544 &display, fallingItem* &itens, float &interval, pad &player) {
    fallingItem *p = itens;
    static unsigned long t = 0;
    uint8_t aux = 0;

    //Verifica se passou interval ms
    if((millis() - t) >= interval)
        aux = 1;

    //Percorre e desenha todos os itens da lista e os desenha
    while(p != NULL) {
        if(p->isBomb)
            display.drawBitmap(p->x, p->y, bitmap_bomb, 6, 6, BLACK);
        else
            display.drawBitmap(p->x, p->y, bitmap_anchor, 6, 6, BLACK);

        p->y += aux;
        p = p->prox;
    }

    //Caso aux == 1, resetamos a variável t
    if(aux == 1)
        t = millis();
}