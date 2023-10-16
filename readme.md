**Autor**: Marcos Gabriel
**Data da última atualização**: 14/10/2023 

## Descrição
Este projeto é uma interpretação e simplificação de jogos similiares ao "Food Drop" do Pou para arduino. A interface foi feita utilizando as bibliotecas `Adafruit_GFX.h` e `Adafruit_PCD8544.h`, além disso também utilizei uma classe com métodos para pushbuttons criada por mim.
Mesmo sendo um projeto simples, acredito que seja interessante para estudo e aprendizado.

Em resumo, neste jogo você controla uma plataforma que se move apenas na direção **x**, seu dever é evitar que as bombas passem da plataforma. Caso a bomba passe da linha da plataforma, você perde um ponto de vida, se o total de pontos de vida forem zero, fim de jogo. Caso caia uma âncora ao invés de uma bomba, deve evitá-la, pois caso você pegue a âncora com a plataforma perderá um ponto de vida.

Bombas e âncoras são geradas de formas aleatórias e em posições aleatórias. Sempre que elas passão da linha da plataforma, são geradas novamente em outras posições.

**OBS**: A IDE utilizada para criação deste projeto é o PlatformIO, mas para trabalhar com o código pode ser utilizado também a Arduino IDE. Além disso, os sprites de jogo podem ser visualizados na pasta *imagens*.

## Estrutuarção do Código
### Estrutura do Código:

1. Inclui bibliotecas necessárias, como `Arduino.h` para funcionalidades do Arduino, `Adafruit_GFX` e `Adafruit_PCD8544` para controlar o display LCD, além de outros arquivos de cabeçalho personalizados.

2. Mapeia os pinos do hardware, definindo constantes para os pinos usados no display, LEDs e botões.

3. Cria objetos necessários, incluindo um objeto `Adafruit_PCD8544` para controlar o display, e objetos `PushButton` para os botões.

4. Declara variáveis para controlar a vida, a posição do "pad" (provavelmente uma plataforma no jogo), pontos e recordes.

5. Declara variáveis booleanas para controlar o início e a pausa do jogo.

6. Define uma variável `interval` para controlar o tempo de queda dos objetos.

7. O `setup()` é a função de inicialização que é executada uma vez no início. Ele configura a comunicação serial, define o pino do LED como saída, inicializa o gerador de números aleatórios e configura o display.

### Função loop():

O loop principal do programa é executado continuamente após o `setup()`. Aqui está o funcionamento da função `loop()`:

- A função `display.clearDisplay()` é chamada para limpar o conteúdo anterior do display.

- Há um condicional que verifica se a variável `start` é **false**. Se for, a função `drawInitScreen()` é chamada para desenhar a tela inicial do jogo, possivelmente com um menu ou uma tela de título.

 - Se `start` for **true**, o jogo está em andamento. O código dentro deste bloco lida com o jogo em execução:

 - - São chamadas diversas funções para desenhar elementos do jogo, como o céu (`drawSky`), o "pad" controlado pelos botões (`drawPad`), os objetos que caem (`drawFallenItens`), e informações de vida e pontos (`drawLifeAndPoints`).

   - Há uma verificação de `intervalPosPause` para pausar o jogo por 2.5 segundos após ser despausado.

   - A função `buttonX.clickBtn()` é usada para verificar se o botão X foi clicado e, se for, a função `pause()` é chamada para pausar o jogo.

- Se a vida for igual ou inferior a 0, o jogo terminou:

   - O recorde é atualizado se os pontos atuais forem maiores que o recorde anterior.

   - A vida é redefinida como 3, os pontos são redefinidos como 0, a variável `start` é definida como **false** e o `interval` é definido como **40**.

   - Há um atraso de 350 milissegundos antes de recomeçar o jogo.

 - Finalmente, o display é girado, atualizado com `display.display()`, e o loop continua. O display é atualizado a cada iteração para mostrar as alterações feitas no loop.

## Circuito Eletrônico

<img src="https://cdn.discordapp.com/attachments/1153711382336909332/1163203943237689404/image.png?ex=653eb917&is=652c4417&hm=aafb61461d30b2c1abee0a6c10e71c59c9cdcf73e34c3c1c1630b3395ad9d880&" />

## Funções Principais
Abaixo estão as principais funções reponsáveis pelo funcionamento do jogo.

1. Função `pause`:
 - Esta função pausa o jogo e exibe a palavra "PAUSE" no display Nokia 5110.
 - Ela aguarda até que um botão (representado pelo objeto button) seja clicado para continuar o jogo.
 - Ao sair da pausa, a variável intervalPosPause é definida como verdadeira.

2. Função `drawSky`:
 - Essa função desenha o céu no campo de jogo no display. Ela utiliza um bitmap para representar o céu.

3. Função `drawLifeAndPoints`:
 - Desenha no display uma linha que separa as informações do jogador do campo de jogo.
 - Exibe corações para representar as vidas do jogador com base no valor de life.
 - Exibe a pontuação do jogador com base no valor de points.

4. Função `drawPad`:
 - Desenha um "pad" (presumivelmente um objeto de controle) no campo de jogo no display.
 - Permite ao jogador mover o pad para a esquerda ou direita usando os botões buttonL e buttonR.

5. Função `drawFallenItems`:
 - Desenha bombas ou âncoras que caem no campo de jogo. A função trata da atualização da posição, colisões, pontos e vidas.
 - A posição da bomba ou âncora é controlada aleatoriamente.
 - A velocidade de queda é ajustada com base em intervalos aleatórios.
 - A colisão com o "pad" é verificada para calcular pontos ou perda de vida.

6. Função `drawInitScreen`:
 - Desenha a tela inicial do jogo no display, incluindo o título, um retângulo e a pontuação máxima (record).
 - A mensagem "(X) to start!" pisca intermitentemente para indicar que o jogador deve pressionar um botão para iniciar o jogo.
 - Quando um botão é clicado, a variável start é definida como verdadeira, indicando o início do jogo.

## Referências
Caso fique interessado em entender mais sobre a classe de pushbuttons acesse o link https://github.com/marcosgabrielsr/ClassePushButton.

Caso fique com dúvidas sobre qual jogo foi utilizado como base para este projeto acesse o link https://pou.fandom.com/wiki/Food_Drop.

O material de apoio para utilização da biblioteca podem ser encontrados no seguinte link https://learn.adafruit.com/adafruit-gfx-graphics-library/rotating-the-display.
