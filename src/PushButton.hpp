//Classe PushButton

#ifndef PUSHBUTTON
#define PUSHBUTTON

//Incluindo a biblioteca padrão do arduino
#include <Arduino.h>

//Criando Classe PushButton
class PushButton{
    //Definindo atributos e métodos
    public:
        PushButton(const int8_t _pin, const int16_t _time); //Método construtor
        bool pressButton();                                 //Função que verifica se o botão está pressionado
        bool clickButton();                                 //Verifica se clicarão o botão

    protected:
        unsigned long t;                            //instante do último clique do botão
        const int8_t pin;                           //Pino onde o botão está conectado
        const int16_t interval;                     //Intervalo para controle do efeito Bounce 
        bool oldState;                              //Estado anterior do botão
};

#endif