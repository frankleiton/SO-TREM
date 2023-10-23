#include "trem.h"
#include <functional>
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y, int velocidade, std::function<void (int, int)> verify, std::function<void (int, int)> free){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = velocidade;
    this->verify = verify;
    this->free = free;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 60 && x <450){

                if(x ==420 || x == 430)
                {
                    this->verify(ID, 1);
                }

                x+=10;
            }
            else if (x == 450 && y < 180){
                if(y == 150 || y == 160)
                {
                    this->verify(ID, 3);
                }
                y+=10;
            }

            else if (x > 180 && y == 180){

                if(x == 430)
                    this->free(ID, 1);
                if(x == 180)
                   this->free(ID, 3);

                x-=10;
            }

            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 60 && x <720)
                x+=10;
            else if (x == 720 && y < 180)
                y+=10;
            else if (x > 450 && y == 180)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 180 && x <320)
                x+=10;
            else if (x == 320 && y < 300)
                y+=10;
            else if (x > 50 && y == 300)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (y == 180 && x <590)
                x+=10;
            else if (x == 590 && y < 300)
                y+=10;
            else if (x > 320 && y == 300)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 180 && x <860)
                x+=10;
            else if (x == 860 && y < 300)
                y+=10;
            else if (x > 590 && y == 300)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:
            break;
        }
        msleep(velocidade);
    }
}


void Trem::changeVel(int velocidade) {

    this->velocidade = 200 - velocidade;

}





