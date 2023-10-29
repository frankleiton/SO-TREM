#include "trem.h"
#include "semaphore.h"
#include <QtCore>
#include <functional>

using namespace std;

//Construtor
Trem::Trem(int ID, int x, int y, int velocidade, function<void (int, int)> verify, function<void (int, int)> liberate) {

    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = 200 - velocidade;
    this->verify = verify; // Verifica se o trilho esta livre, caso contrario, o trem para
    this->liberate = liberate; // Libera o trilho quando o trem ja passaou

}

//Função a ser executada após executar trem->START
void Trem::run() {

    while(true) {

        switch(ID) {
        case 1:     //Trem 1

            if (y == 20 && x < 280) {

                if(x == 250 || x == 260)
                    this->verify(ID, 1);

                x+=10;

            }

            else if (x == 280 && y < 140) {

                if(y == 110 || y == 120)
                    this->verify(ID, 3);

                y+=10;

            }

            else if (x > 10 && y == 140) {

                if(x == 260)
                    this->liberate(ID, 1);
                if(x == 120)
                    this->liberate(ID, 3);

                x-=10;

            }

            else
                y-=10;

            emit updateGUI(ID, x, y);    //Emite um sinal

            break;

        case 2: //Trem 2

            if (y == 20 && x < 550) {

                if(x == 300)
                    this->liberate(ID, 1);

                if(x == 520 || x == 530)
                    this->verify(ID, 2);

                x+=10;

            }

            else if (x == 550 && y < 140) {

                if(y == 110 || y == 120 || y == 130) {
                    this->verify(ID, 1);
                    this->verify(ID, 5);
                    this->verify(ID, 4);
                }

                y+=10;

            }

            else if (x > 280 && y == 140) {

                if(x == 530)
                    this->liberate(ID, 2);
                if(x == 390)
                    this->liberate(ID, 5);

                x-=10;

            }

            else {

                if(y == 120)
                    this->liberate(ID, 4);

                y-=10;

            }

            emit updateGUI(ID, x, y);    //Emite um sinal

            break;

        case 3: //Trem 3

            if (y == 20 && x < 820) {

                if(x == 560)
                    this->liberate(ID, 2);

                x+=10;

            }

            else if (x == 820 && y < 140)
                y+=10;

            else if (x > 550 && y == 140) {

                if(x == 690 || x == 700) {
                    this->verify(ID, 2);
                    this->verify(ID, 6);
                }

                x-=10;

            }

            else {

                if(y == 120)
                    this->liberate(ID, 6);

                y-=10;

            }


            emit updateGUI(ID, x, y);    //Emite um sinal

            break;

        case 4: //Trem 4

            if (y == 140 && x < 410) {

                if(x == 260 || x == 270)
                    this->verify(ID, 4);

                if(x == 300)
                    this->liberate(ID, 3);

                x+=10;

            }

            else if (x == 410 && y < 260) {

                if(y == 160)
                    this->liberate(ID, 4);

                y+=10;

            }

            else if (x > 140 && y == 260) {

                if(x == 390)
                    this->liberate(ID, 7);

                x-=10;

            }

            else {

                if(y == 170 || y == 160) {
                    this->verify(ID, 7);
                    this->verify(ID, 3);
                }

                y-=10;

            }
            emit updateGUI(ID, x, y);    //Emite um sinal

            break;

        case 5: //Trem 5

            if (y == 140 && x < 680) {

                if(x == 430)
                    this->liberate(ID, 7);
                if(x == 570)
                    this->liberate(ID, 5);

                x+=10;

            }

            else if (x == 680 && y < 260) {

                if(y == 160)
                    this->liberate(ID, 6);

                y+=10;

            }

            else if (x > 410 && y == 260) {

                if(x == 440 || x == 430)
                    this->verify(ID, 7);

                x-=10;

            }

            else {

                if(y == 170 || y == 160) {
                    this->verify(ID, 5);
                    this->verify(ID, 6);
                }

                y-=10;

            }

            emit updateGUI(ID, x, y);    //Emite um sinal

            break;

        default:

            break;

        }

        msleep(this->velocidade);

    }

}

void Trem::changeVel(int velocidade) {

    this->velocidade = 200 - velocidade;

}



