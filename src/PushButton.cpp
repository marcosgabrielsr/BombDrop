//
// Classe PushButton
//  arquivo cpp

#include "PushButton.hpp"
    //Criando a função construtora da classe
    PushButton::PushButton(const uint8_t pin, const uint16_t time):
    _pin(pin), _time(time), delay1(0)
    {
        //define o pino do botão como entrada com resistor pullup
        pinMode(_pin, INPUT_PULLUP);
        old_state = true;
    }

    //Método pressBtn(): Verifica se o botão está pressioando, ou seja se for empurrado retornará true
    //se não retornará false
    bool PushButton::pressBtn(){
      return !digitalRead(_pin);
    }

    //Método clickBtn(): Verifica se o botão foi pressionado, e retorna true apenas no instante em que ele foi pressionado(clicado)
    bool PushButton::clickBtn(){
      //pegando a leitura digital do pino do botão 
      bool state_btn = digitalRead(_pin);
      bool value = false;

      //Verifica se já se passou um intervalo de 170 milissegundos
      if((millis() - delay1) >= _time){
        //Se o botão é pressinado
        if(old_state && !state_btn){
          //value se torna verdadeiro, e o intervalo é resetado
          value = true;
          delay1 = millis();
        }
      }
      //atualiza o estado anterior do botão
      old_state = state_btn;

      //retorna value
      return value;
    }