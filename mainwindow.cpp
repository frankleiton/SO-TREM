#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "semaphore.h"

//Um semáforo para cada trem criado
sem_t trens[5];
int occupations[7];

//vazio 0
//andando 1
//parado -1

int statusT1 = 1;
int statusT2 = 1;
int statusT3 = 1;
int statusT4 = 1;
int statusT5 = 1;

//trilhos
//1,2,3,4,5,6,7 e nenhum 0

int whereGoTrain1 = 0;
int whereGoTrain2 = 0;
int whereGoTrain3 = 0;
int whereGoTrain4 = 0;
int whereGoTrain5 = 0;

void CheckRailBlocked(int id_trem, int id_trilho);
void CheckRailFree(int id_trem, int id_trilho);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i = 0; i < 7; i++) {

        if(i <= 4)
        {
            sem_init(&trens[i], 0, 0);
        }

        occupations[i] = 0;

    }

    //Cria o trem com seu (ID, posição X, posição Y)
    trem1 = new Trem(1,180,60, 99, CheckRailBlocked, CheckRailFree);
    trem2 = new Trem(2,450,60, 99, CheckRailBlocked, CheckRailFree);
    trem3 = new Trem(3,50,180, 99, CheckRailBlocked, CheckRailFree);
    trem4 = new Trem(4,320,180, 99, CheckRailBlocked, CheckRailFree);
    trem5 = new Trem(5,590,180, 99, CheckRailBlocked, CheckRailFree);

    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();

}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
    case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
        ui->label_trem1->setGeometry(x,y,21,17);
        break;
    case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem2->setGeometry(x,y,21,17);
        break;
    case 3: //Atualiza a posição do objeto da tela (quadrado) que representa o trem3
        ui->label_trem3->setGeometry(x,y,21,17);
        break;
    case 4: //Atualiza a posição do objeto da tela (quadrado) que representa o trem4
        ui->label_trem4->setGeometry(x,y,21,17);
        break;
    case 5: //Atualiza a posição do objeto da tela (quadrado) que representa o trem5
        ui->label_trem5->setGeometry(x,y,21,17);
        break;

    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_trem_1_valueChanged(int value)
{
    if(value <= 0)
           trem1->terminate();
       else if(value > 0 ) {
           trem1->start();
           trem1->changeVel(value);
    }
}

void MainWindow::on_horizontalSlider_trem_2_valueChanged(int value)
{
    if(value <= 0)
           trem2->terminate();
       else if(value > 0 ) {
           trem2->start();
           trem2->changeVel(value);
    }
}


void MainWindow::on_horizontalSlider_trem_3_valueChanged(int value)
{
    if(value <= 0)
           trem3->terminate();
       else if(value > 0 ) {
           trem3->start();
           trem3->changeVel(value);
    }
}


void MainWindow::on_horizontalSlider_trem_4_valueChanged(int value)
{
    if(value <= 0)
           trem4->terminate();
       else if(value > 0 ) {
           trem4->start();
           trem4->changeVel(value);
    }
}


void MainWindow::on_horizontalSlider_trem_5_valueChanged(int value)
{
    if(value <= 0)
           trem5->terminate();
       else if(value > 0 ) {
           trem5->start();
           trem5->changeVel(value);
    }
}

void CheckRailBlocked(int id_trem, int id_trilho)
{
    if((id_trem ==1 || id_trem == 2) && id_trilho == 1){
        if( occupations[id_trilho-1] == 0 ) {
            occupations[id_trilho-1] = id_trem;
        } else if(occupations[id_trilho-1] != id_trem) {

            if(id_trem == 1 && statusT1 != -1) {
                whereGoTrain1 = 1;
                statusT1 = -1;
                sem_wait( &trens[id_trem-1] );
            }
            else if(id_trem == 2 && statusT2 != -1) {
                whereGoTrain2 = 1;
                statusT2 = -1;
                sem_wait( &trens[id_trem-1] );
            }

        }
    }

    if((id_trem == 2 || id_trem == 3) && id_trilho == 2) {

        if( occupations[id_trilho-1] == 0 ) {
            occupations[id_trilho-1] = id_trem;
        } else if(occupations[id_trilho-1] != id_trem) {

            if(id_trem == 2 && statusT2 != -1) {
                whereGoTrain2 = 2;
                statusT2 = -1;
                sem_wait( &trens[id_trem-1] );
            }
            else if(id_trem == 3 && statusT3 != -1) {
                whereGoTrain3 = 2;
                statusT3 = -1;
                sem_wait( &trens[id_trem-1] );
            }

        }

    }

    if((id_trem == 1 || id_trem == 4) && id_trilho == 3) {

        if( occupations[id_trilho-1] == 0 ) {
            occupations[id_trilho-1] = id_trem;
        } else if(occupations[id_trilho-1] != id_trem) {

            if(id_trem == 1 && statusT1 != -1) {
                whereGoTrain1 = 3;
                statusT1 = -1;
                sem_wait( &trens[id_trem-1] );
            }
            else if(id_trem == 4 && statusT4 != -1) {
                whereGoTrain4 = 3;
                statusT4 = -1;
                sem_wait( &trens[id_trem-1] );
            }

        }
    }

    if((id_trem == 2 || id_trem == 4) && id_trilho == 4) {

        if( occupations[id_trilho-1] == 0 ) {
            occupations[id_trilho-1] = id_trem;
        } else if(occupations[id_trilho-1] != id_trem) {

            if(id_trem == 2 && statusT2 != -1) {
                whereGoTrain2 = 4;
                statusT2 = -1;
                sem_wait( &trens[id_trem-1] );
            }
            else if(id_trem == 4 && statusT4 != -1) {
                whereGoTrain4 = 4;
                statusT4 = -1;
                sem_wait( &trens[id_trem-1] );
            }

        }

    }

    if((id_trem == 2 || id_trem == 5) && id_trilho == 5) {

        if( occupations[id_trilho-1] == 0 ) {
            occupations[id_trilho-1] = id_trem;
        } else if(occupations[id_trilho-1] != id_trem) {

            if(id_trem == 2 && statusT2 != -1) {
                whereGoTrain2 = 5;
                statusT2 = -1;
                sem_wait( &trens[id_trem-1] );
            }
            else if(id_trem == 5 && statusT5 != -1) {
                whereGoTrain5 = 5;
                statusT5 = -1;
                sem_wait( &trens[id_trem-1] );
            }

        }

    }

    if((id_trem == 3 || id_trem == 5) && id_trilho == 6) {



        if( occupations[id_trilho-1] == 0 ) {
            occupations[id_trilho-1] = id_trem;
        } else if(occupations[id_trilho-1] != id_trem) {

            if(id_trem == 3 && statusT3 != -1) {
                whereGoTrain3 = 6;
                statusT3 = -1;
                sem_wait( &trens[id_trem-1] );
            }
            else if(id_trem == 5 && statusT5 != -1) {
                whereGoTrain5 = 6;
                statusT5 = -1;
                sem_wait( &trens[id_trem-1] );
            }

        }



    }

    if((id_trem == 4 || id_trem == 5) && id_trilho == 7) {

        if( occupations[id_trilho-1] == 0 ) {
            occupations[id_trilho-1] = id_trem;
        } else if(occupations[id_trilho-1] != id_trem) {

            if(id_trem == 4 && statusT4 != -1) {
                whereGoTrain4 = 7;
                statusT4 = -1;
                sem_wait( &trens[id_trem-1] );
            }
            else if(id_trem == 5 && statusT5 != -1) {
                whereGoTrain5 = 7;
                statusT5 = -1;
                sem_wait( &trens[id_trem-1] );
            }

        }

    }
}

void CheckRailFree(int id_trem, int id_trilho) {
    if( (id_trem == 1 || id_trem == 2) && id_trilho == 1 ) {

        occupations[id_trilho-1] = 0;

        if(id_trem == 1 && statusT2 == -1 && whereGoTrain2 == 1) {
            statusT2 = 1;
            sem_post( &trens[1] );
        }
        else if(id_trem == 2 && statusT1 == -1 && whereGoTrain1 == 1) {
            statusT1 = 1;
            sem_post( &trens[0] );
        }

    }

    if( (id_trem == 2 || id_trem == 3) ) {

            if(id_trilho == 2) {

                occupations[id_trilho-1] = 0;

                if(id_trem == 2 && statusT3 == -1 && whereGoTrain3 == 2) {
                    statusT3 = 1;
                    sem_post( &trens[2] );
                }
                else if(id_trem == 3 && statusT2 == -1 && whereGoTrain2 == 2) {
                    statusT2 = 1;
                    sem_post( &trens[1] );
                }

            }

        }

        if( (id_trem == 1 || id_trem == 4) ) {

            if(id_trilho == 3) {

                occupations[id_trilho-1] = 0;

                if(id_trem == 1 && statusT4 == -1 && whereGoTrain4 == 3) {
                    statusT4 = 1;
                    sem_post( &trens[3] );
                }
                else if(id_trem == 4 && statusT1 == -1 && whereGoTrain1 == 3) {
                    statusT1 = 1;
                    sem_post( &trens[0] );
                }

            }

        }

        if( (id_trem == 2 || id_trem == 4) ) {

            if(id_trilho == 4) {

                occupations[id_trilho-1] = 0;

                if(id_trem == 2 && statusT4 == -1 && whereGoTrain4 == 4) {
                    statusT4 = 1;
                    sem_post( &trens[3] );
                }
                else if(id_trem == 4 && statusT2 == -1 && whereGoTrain2 == 4) {
                    statusT2 = 1;
                    sem_post( &trens[1] );
                }

            }

        }

        if( (id_trem == 2 || id_trem == 5) ) {

            if(id_trilho == 5) {

                occupations[id_trilho-1] = 0;

                if(id_trem == 2 && statusT5 == -1 && whereGoTrain5 == 5) {
                    statusT5 = 1;
                    sem_post( &trens[4] );
                }
                else if(id_trem == 5 && statusT2 == -1 && whereGoTrain2 == 5) {
                    statusT2 = 1;
                    sem_post( &trens[1] );
                }

            }

        }

        if( (id_trem == 3 || id_trem == 5) ) {

            if(id_trilho == 6) {

                occupations[id_trilho-1] = 0;

                if(id_trem == 3 && statusT5 == -1 && whereGoTrain5 == 6) {
                    statusT5 = 1;
                    sem_post( &trens[4] );
                }
                else if(id_trem == 5 && statusT3 == -1 && whereGoTrain3 == 6) {
                    statusT3 = 1;
                    sem_post( &trens[2] );
                }

            }

        }

        if( (id_trem == 4 || id_trem == 5) ) {

            if(id_trilho == 7) {

                occupations[id_trilho-1] = 0;

                if(id_trem == 4 && statusT5 == -1 && whereGoTrain5 == 7) {
                    statusT5 = 1;
                    sem_post( &trens[4] );
                }
                else if(id_trem == 5 && statusT4 == -1 && whereGoTrain4 == 7) {
                    statusT4 = 1;
                    sem_post( &trens[3] );
                }

            }

        }
}
