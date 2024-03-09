**Autor**: Marcos Gabriel <br>
**Data da última atualização**: 08/03/2024

# BombDrop

## Descrição
Este projeto consiste em um jogo desenvolvido para plataforma arduino e similares, que utiliza um display Nokia 5110 para exibir gráficos e interagir com o jogador. O jogo foi desenvolvido na PlatformIO IDE utilizando as bibliotecas Adafruit_GFX e Adafruit_PCD8544.

## Componentes Necessários
- Placa Arduino (ou outras compatíveis)
- Display Nokia 5110 84x48
- 3 Botões (PushButtons)
- Alguns fios (jumpers)

## Instalação
1. Faça o download ou clone o repositório para o seu computador.
2. Conecte o display e os botões no arduino seguindo o esquema apresentado abaixo.

<div align="center">
  <img src="https://media.discordapp.net/attachments/1153711382336909332/1163203943237689404/image.png?ex=65f74b17&is=65e4d617&hm=5c02390f2ac1a11a2768e774a023b7da476040c9b086204829755aabd5413b30&=&format=webp&quality=lossless">
</div>

3. Abra a pasta do projeto no PlatformIO IDE.
4. Carregue o código para o seu Arduino.
5. Pronto! Agora é só jogar e se divertir!

## Modo de Uso
1. Ligue o Arduino.
2. Aperte o botão X (botão central) para inicar o jogo.
3. Use os botões das laterias (L e R) para controlar a plataforma.

## Controles
- Botão X: Este botão é usado para começar o jogo na tela inicial e para pausá-lo enquanto o jogo está em execução.

- Botão L: Este botão é utilizado para mover a plataforma (pad) para esquerda na execução do jogo.

- Botão R: Este botão é utilizado para mover a plataforma (pad) para direita na execução do jogo.

## Estruturas de Dados Personalizadas:
Para diminuir a quantidade de parâmetros passados por função e também melhorar a leitura do códigos foram criadas as seguintes structs: `pad` e `fallingItem`.

- ### Struct pad:
  - **Descrição**: Struct utilizada para representar a plataforma controlada pelo jogador, armazenando suas coordenadas x, pontos ganhos, pontos de vida e botões de ação (L e R).

  - **Campos**:
    - `uint8_t life`: Campo responsável por armazenar os pontos de vida do jogador;
    - `int points`: Campo responsável por armazenar os pontos ganhos pelo jogador ao recolher as bombas;
    - `uint8_t x`: Campo responsável por armazenar à coorenada x da plataforma;
    - `PushButton *btnL`: Campo resonável por armazenar o ponteiro de um objeto PushButton utilizado para mover a plataforma para esquerda;
    - `PushButton *btnR`: Campo resonável por armazenar o ponteiro de um objeto PushButton utilizado para mover a plataforma para Direita;

- ### Struct fallingItem:
  - **Descrição**: Struct utilizada para representar um elemento de uma fila simplesmente encadeada, responsável por armazenar os itens que estão aparentes na tela.

  - **Campos**:
    - `bool isBomb`: Campo responsável por informar se o novo item é uma bomba(true) ou uma âncora(false);
    - `uint8_t x`: Campo responsável por armazenar a coordenada x do item;
    - `uint8_t y`: Campo responsável por armazenar a coordenada y do item;
    - `struct fallingItem * prox`: Campo responsável por apontar para o próximo item da fila;

## Funcionalidades
- 

## Contribuição:
Se deseja contribuir para o projeto, sinta-se à vontade para abrir problemas ou enviar solicitações de pull requests.

## Referências
Caso fique interessado em entender mais sobre a classe de pushbuttons acesse o link https://github.com/marcosgabrielsr/ClassePushButton.

Caso fique com dúvidas sobre qual jogo foi utilizado como base para este projeto acesse o link https://pou.fandom.com/wiki/Food_Drop.

O material de apoio para utilização da biblioteca podem ser encontrados no seguinte link https://learn.adafruit.com/adafruit-gfx-graphics-library/rotating-the-display.

## Demonstração
<div align="center">
  <img src="https://cdn.discordapp.com/attachments/1153711382336909332/1215818224487370885/20240308_202548.jpg?ex=65fe21f5&is=65ebacf5&hm=d73c848568b15c3690bcae5b0d9b3bbcae9f2573ed149926c85cc349f46fe4e1&">
  <p><i>Imagem do projeto em execução.</i></p>
</div>
