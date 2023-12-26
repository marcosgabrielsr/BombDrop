//Arquivo .cpp que contém os métodos

//Incluindo arquivo .hpp que contém a classe
#include "PushButton.hpp"

//Função construtora
PushButton::PushButton(const int8_t _pin, const int16_t _interval):
pin(_pin), interval(_interval), t(0), oldState(true){
    //Definindo o pino do botão como pino de entrada com resistor PULLUP
    pinMode(pin, INPUT_PULLUP);
}

//Função que verifica se o botão está pressionado
bool PushButton::pressButton(){
    //Retorna a leitura atual do botão
    return !digitalRead(pin);
}

//Função que verifica se o botão foi clicado
bool PushButton::clickButton(){
    //Armazenando o estado atual do botão
    bool state = digitalRead(pin);
    bool value = false;

    //Verifica se passou um intervalo em milisegundos desde o último clique
    if((millis() - t) >= interval){
        if(oldState && !state){
            value = true;
            t = millis();
        }
    }

    //Atualiza o antigo estado do botão
    oldState = state;

    //Retorna value
    return value;
}