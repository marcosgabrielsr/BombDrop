**Autor**: Marcos Gabriel <br>
**Data da última atualização**: 5/03/2024

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
- Para diminuir a quantidade de parâmetros passados por função e também melhorar a leitura do códigos foram criadas as seguintes structs: `pad` e `fallingItem`.

## Funcionalidades
- 

## Referências
Caso fique interessado em entender mais sobre a classe de pushbuttons acesse o link https://github.com/marcosgabrielsr/ClassePushButton.

Caso fique com dúvidas sobre qual jogo foi utilizado como base para este projeto acesse o link https://pou.fandom.com/wiki/Food_Drop.

O material de apoio para utilização da biblioteca podem ser encontrados no seguinte link https://learn.adafruit.com/adafruit-gfx-graphics-library/rotating-the-display.

## Imagens

<div align="center">
  <img src="https://cdn.discordapp.com/attachments/1153711382336909332/1163666420677234819/IMG-20230909-WA0074.jpg?ex=654067ce&is=652df2ce&hm=534c77987993fd8685b42c0ba37b979d68e9cdb51efe439247b89c3f099c4f49&">
  <p><i>imagem meramente ilustrativa sobre como o jogo funciona(esboço inicial).</i></p>
</div>
