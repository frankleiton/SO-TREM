#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "semaphore.h"

#define VAZIO 0
#define MOVENDO 1
#define PARADO -1

#define TRILHO_1 1
#define TRILHO_2 2
#define TRILHO_3 3
#define TRILHO_4 4
#define TRILHO_5 5
#define TRILHO_6 6
#define TRILHO_7 7
#define NENHUM 0

sem_t trens[5]; //Cada trem tem um semaforo
int ocupacoes[7]; // Cada trilho estara vazio ou determinado trem estara passando, o valor id do trem sera armazenado

int status_trem1 = MOVENDO;
int status_trem2 = MOVENDO;
int status_trem3 = MOVENDO;
int status_trem4 = MOVENDO;
int status_trem5 = MOVENDO;

int para_onde_t1_esta_indo = NENHUM;
int para_onde_t2_esta_indo = NENHUM;
int para_onde_t3_esta_indo = NENHUM;
int para_onde_t4_esta_indo = NENHUM;
int para_onde_t5_esta_indo = NENHUM;

void verify(int ID, int n_trilho);
void liberate(int ID, int n_trilho);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i = 0; i < 7; i++) {

        if(i <= 4)
            sem_init(&trens[i], 0, 0);

        ocupacoes[i] = VAZIO;

    }

    //Cria o trem com seu (ID, posição X, posição Y, velocidade inicial)
    trem1 = new Trem(1, 10, 20, 99, verify, liberate);
    trem2 = new Trem(2, 410, 20, 99, verify, liberate);
    trem3 = new Trem(3, 820, 20, 99, verify, liberate);
    trem4 = new Trem(4, 140, 260, 99, verify, liberate);
    trem5 = new Trem(5, 680, 260, 99, verify, liberate);
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


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    if(value <= 0)
        trem1->terminate();
    else if(value > 0) {
        trem1->start();
        trem1->changeVel(value);
    }
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    if(value <= 0)
        trem2->terminate();
    else if(value > 0) {
        trem2->start();
        trem2->changeVel(value);
    }
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    if(value <= 0)
        trem3->terminate();
    else if(value > 0 ) {
        trem3->start();
        trem3->changeVel(value);
    }
}

void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    if(value <= 0)
        trem4->terminate();
    else if(value > 0 ) {
        trem4->start();
        trem4->changeVel(value);
    }
}

void MainWindow::on_horizontalSlider_5_valueChanged(int value)
{
    if(value <= 0)
        trem5->terminate();
    else if(value > 0 ) {
        trem5->start();
        trem5->changeVel(value);
    }
}

/**
 * Verifica se o trem pode passar pelo trilho, caso esteja sem nenhum outro trem passando no momento
 *
 * @brief verify
 * @param ID
 * @param n_trilho
 */
void verify(int ID, int n_trilho) {

    if(ID == 1 || ID == 2) {

        if(n_trilho == 1) {

            if( ocupacoes[n_trilho-1] == VAZIO ) {
                ocupacoes[n_trilho-1] = ID;
            } else if(ocupacoes[n_trilho-1] != ID) {

                if(ID == 1 && status_trem1 != PARADO) {
                    para_onde_t1_esta_indo = TRILHO_1;
                    status_trem1 = PARADO;
                    sem_wait( &trens[ID-1] );
                }
                else if(ID == 2 && status_trem2 != PARADO) {
                    para_onde_t2_esta_indo = TRILHO_1;
                    status_trem2 = PARADO;
                    sem_wait( &trens[ID-1] );
                }

            }

        }



    }

    if(ID == 2 || ID == 3) {

        if(n_trilho == 2) {

            if( ocupacoes[n_trilho-1] == VAZIO ) {
                ocupacoes[n_trilho-1] = ID;
            } else if(ocupacoes[n_trilho-1] != ID) {

                if(ID == 2 && status_trem2 != PARADO) {
                    para_onde_t2_esta_indo = TRILHO_2;
                    status_trem2 = PARADO;
                    sem_wait( &trens[ID-1] );
                }
                else if(ID == 3 && status_trem3 != PARADO) {
                    para_onde_t3_esta_indo = TRILHO_2;
                    status_trem3 = PARADO;
                    sem_wait( &trens[ID-1] );
                }

            }

        }

    }

    if(ID == 1 || ID == 4) {

        if(n_trilho == 3) {

            if( ocupacoes[n_trilho-1] == VAZIO ) {
                ocupacoes[n_trilho-1] = ID;
            } else if(ocupacoes[n_trilho-1] != ID) {

                if(ID == 1 && status_trem1 != PARADO) {
                    para_onde_t1_esta_indo = TRILHO_3;
                    status_trem1 = PARADO;
                    sem_wait( &trens[ID-1] );
                }
                else if(ID == 4 && status_trem4 != PARADO) {
                    para_onde_t4_esta_indo = TRILHO_3;
                    status_trem4 = PARADO;
                    sem_wait( &trens[ID-1] );
                }

            }

        }

    }

    if(ID == 2 || ID == 4) {

        if(n_trilho == 4) {

            if( ocupacoes[n_trilho-1] == VAZIO ) {
                ocupacoes[n_trilho-1] = ID;
            } else if(ocupacoes[n_trilho-1] != ID) {

                if(ID == 2 && status_trem2 != PARADO) {
                    para_onde_t2_esta_indo = TRILHO_4;
                    status_trem2 = PARADO;
                    sem_wait( &trens[ID-1] );
                }
                else if(ID == 4 && status_trem4 != PARADO) {
                    para_onde_t4_esta_indo = TRILHO_4;
                    status_trem4 = PARADO;
                    sem_wait( &trens[ID-1] );
                }

            }

        }

    }

    if(ID == 2 || ID == 5) {

        if(n_trilho == 5) {

            if( ocupacoes[n_trilho-1] == VAZIO ) {
                ocupacoes[n_trilho-1] = ID;
            } else if(ocupacoes[n_trilho-1] != ID) {

                if(ID == 2 && status_trem2 != PARADO) {
                    para_onde_t2_esta_indo = TRILHO_5;
                    status_trem2 = PARADO;
                    sem_wait( &trens[ID-1] );
                }
                else if(ID == 5 && status_trem5 != PARADO) {
                    para_onde_t5_esta_indo = TRILHO_5;
                    status_trem5 = PARADO;
                    sem_wait( &trens[ID-1] );
                }

            }

        }

    }

    if(ID == 3 || ID == 5) {

        if(n_trilho == 6) {

            if( ocupacoes[n_trilho-1] == VAZIO ) {
                ocupacoes[n_trilho-1] = ID;
            } else if(ocupacoes[n_trilho-1] != ID) {

                if(ID == 3 && status_trem3 != PARADO) {
                    para_onde_t3_esta_indo = TRILHO_6;
                    status_trem3 = PARADO;
                    sem_wait( &trens[ID-1] );
                }
                else if(ID == 5 && status_trem5 != PARADO) {
                    para_onde_t5_esta_indo = TRILHO_6;
                    status_trem5 = PARADO;
                    sem_wait( &trens[ID-1] );
                }

            }

        }

    }

    if(ID == 4 || ID == 5) {

        if(n_trilho == 7) {

            if( ocupacoes[n_trilho-1] == VAZIO ) {
                ocupacoes[n_trilho-1] = ID;
            } else if(ocupacoes[n_trilho-1] != ID) {

                if(ID == 4 && status_trem4 != PARADO) {
                    para_onde_t4_esta_indo = TRILHO_7;
                    status_trem4 = PARADO;
                    sem_wait( &trens[ID-1] );
                }
                else if(ID == 5 && status_trem5 != PARADO) {
                    para_onde_t5_esta_indo = TRILHO_7;
                    status_trem5 = PARADO;
                    sem_wait( &trens[ID-1] );
                }

            }

        }

    }

}

/**
 * Assim que um trem passa por um trilho, é liberado o acesso para outro trem que compartilha o trilho
 *
 * @brief free
 * @param ID
 * @param n_trilho
 */
void liberate(int ID, int n_trilho) {
    if( (ID == 1 || ID == 2) ) {

        if(n_trilho == 1) {

            ocupacoes[n_trilho-1] = VAZIO;

            if(ID == 1 && status_trem2 == PARADO && para_onde_t2_esta_indo == TRILHO_1) {
                status_trem2 = MOVENDO;
                sem_post( &trens[1] );
            }
            else if(ID == 2 && status_trem1 == PARADO && para_onde_t1_esta_indo == TRILHO_1) {
                status_trem1 = MOVENDO;
                sem_post( &trens[0] );
            }

        }

    }

    if( (ID == 2 || ID == 3) ) {

        if(n_trilho == 2) {

            ocupacoes[n_trilho-1] = VAZIO;

            if(ID == 2 && status_trem3 == PARADO && para_onde_t3_esta_indo == TRILHO_2) {
                status_trem3 = MOVENDO;
                sem_post( &trens[2] );
            }
            else if(ID == 3 && status_trem2 == PARADO && para_onde_t2_esta_indo == TRILHO_2) {
                status_trem2 = MOVENDO;
                sem_post( &trens[1] );
            }

        }

    }

    if( (ID == 1 || ID == 4) ) {

        if(n_trilho == 3) {

            ocupacoes[n_trilho-1] = VAZIO;

            if(ID == 1 && status_trem4 == PARADO && para_onde_t4_esta_indo == TRILHO_3) {
                status_trem4 = MOVENDO;
                sem_post( &trens[3] );
            }
            else if(ID == 4 && status_trem1 == PARADO && para_onde_t1_esta_indo == TRILHO_3) {
                status_trem1 = MOVENDO;
                sem_post( &trens[0] );
            }

        }

    }

    if( (ID == 2 || ID == 4) ) {

        if(n_trilho == 4) {

            ocupacoes[n_trilho-1] = VAZIO;

            if(ID == 2 && status_trem4 == PARADO && para_onde_t4_esta_indo == TRILHO_4) {
                status_trem4 = MOVENDO;
                sem_post( &trens[3] );
            }
            else if(ID == 4 && status_trem2 == PARADO && para_onde_t2_esta_indo == TRILHO_4) {
                status_trem2 = MOVENDO;
                sem_post( &trens[1] );
            }

        }

    }

    if( (ID == 2 || ID == 5) ) {

        if(n_trilho == 5) {

            ocupacoes[n_trilho-1] = VAZIO;

            if(ID == 2 && status_trem5 == PARADO && para_onde_t5_esta_indo == TRILHO_5) {
                status_trem5 = MOVENDO;
                sem_post( &trens[4] );
            }
            else if(ID == 5 && status_trem2 == PARADO && para_onde_t2_esta_indo == TRILHO_5) {
                status_trem2 = MOVENDO;
                sem_post( &trens[1] );
            }

        }

    }

    if( (ID == 3 || ID == 5) ) {

        if(n_trilho == 6) {

            ocupacoes[n_trilho-1] = VAZIO;

            if(ID == 3 && status_trem5 == PARADO && para_onde_t5_esta_indo == TRILHO_6) {
                status_trem5 = MOVENDO;
                sem_post( &trens[4] );
            }
            else if(ID == 5 && status_trem3 == PARADO && para_onde_t3_esta_indo == TRILHO_6) {
                status_trem3 = MOVENDO;
                sem_post( &trens[2] );
            }

        }

    }

    if( (ID == 4 || ID == 5) ) {

        if(n_trilho == 7) {

            ocupacoes[n_trilho-1] = VAZIO;

            if(ID == 4 && status_trem5 == PARADO && para_onde_t5_esta_indo == TRILHO_7) {
                status_trem5 = MOVENDO;
                sem_post( &trens[4] );
            }
            else if(ID == 5 && status_trem4 == PARADO && para_onde_t4_esta_indo == TRILHO_7) {
                status_trem4 = MOVENDO;
                sem_post( &trens[3] );
            }

        }

    }

}
