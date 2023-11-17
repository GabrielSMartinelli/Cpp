#include "campo.h"
#include <iostream>
#include <fstream>

Campo::Campo(QWidget *parent) : QFrame(parent) {
    for(int i=0; i<20; i++)
        for(int j=0; j<20;j++)
            this->quadradinhos[i][j] = nullptr;
}

Campo* Campo::instancia = nullptr;

void Campo::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter p(this);

    p.drawRect(this->rect().x(), this->rect().y(), this->rect().width()-1, this->rect().height()-1);
}

Campo* Campo::getInstancia() {
    if(instancia == nullptr)
       instancia = new Campo();
    return instancia;
}

Campo* Campo::deleteInstancia() {
    delete instancia;
    instancia = nullptr;
    return instancia;
}

void Campo::criaQuadradinhos(int i, int j) {
    if(this->quadradinhos[i][j] == nullptr) {
        quadradinhoNumero* q = new quadradinhoNumero(this);
        q->setPosicao(i, j);
        q->setMarcado(false);
        q->setAberto(false);
        q->setTravado(false);
        q->setGeometry(25*j, 25*i, 25, 25);
        q->setVizinhos();
        connect(q, SIGNAL(abrirVizinhos(int,int)), this, SLOT(abreQuadradinhos(int,int)));
        connect(q, SIGNAL(Confere()), this, SLOT(Verifica()));
        this->quadradinhos[i][j] = q;
    }
}

void Campo::criaBombas() {
    int x = rand()%20;
    int y = rand()%20;
    if(this->quadradinhos[x][y] == nullptr) {
        this->quadradinhos[x][y] = new quadradinhoBomba(this);
        this->quadradinhos[x][y]->setPosicao(x, y);
        this->quadradinhos[x][y]->setMarcado(false);
        this->quadradinhos[x][y]->setAberto(false);
        this->quadradinhos[x][y]->setTravado(false);
        this->quadradinhos[x][y]->setGeometry(25*y, 25*x, 25, 25);
        connect(this->quadradinhos[x][y], SIGNAL(abrirBombas(int,int)), this, SLOT(abreBombas(int,int)));
        connect(this->quadradinhos[x][y], SIGNAL(Explodiu()), this, SLOT(Perdeu()));
    }
    else
        criaBombas();
}

void Campo::criaBombas(int i, int j) {
    if(this->quadradinhos[i][j] == nullptr) {
        this->quadradinhos[i][j] = new quadradinhoBomba(this);
        this->quadradinhos[i][j]->setPosicao(i, j);
        this->quadradinhos[i][j]->setMarcado(false);
        this->quadradinhos[i][j]->setAberto(false);
        this->quadradinhos[i][j]->setTravado(false);
        this->quadradinhos[i][j]->setGeometry(25*j, 25*i, 25, 25);
        connect(this->quadradinhos[i][j], SIGNAL(abrirBombas(int,int)), this, SLOT(abreBombas(int,int)));
        connect(this->quadradinhos[i][j], SIGNAL(Explodiu()), this, SLOT(Perdeu()));
    }
}

void Campo::abreQuadradinhos(int i, int j) {
    std::vector<int>::iterator it;
    quadradinhoNumero* q = static_cast<quadradinhoNumero*>(this->quadradinhos[i][j]);
    std::vector<int> v = q->getVizinhos();
    for(it = v.begin(); it < v.end(); it++) {
        int x = (*it) / 20;
        int y = (*it) % 20;
        if(this->quadradinhos[x][y]->getTipo() == 0)
            this->quadradinhos[x][y]->abrir();
    }
}

void Campo::abreBombas(int i, int j) {
    for(int x=0; x<20; x++) {
        for(int y=0; y<20; y++) {
            if(this->quadradinhos[x][y]->getTipo() == 1 and (x != i or y != j))
                this->quadradinhos[x][y]->abrir();
        }
    }
}

void Campo::Verifica() {
    abertos++;
    if(400-bombas == abertos) {
        for(int i=0; i<20; i++)
            for(int j=0; j<20; j++)
                quadradinhos[i][j]->setTravado(true);
        emit Vitoria();
    }
}

void Campo::Perdeu() {
    for(int i=0; i<20; i++)
        for(int j=0; j<20; j++)
            quadradinhos[i][j]->setTravado(true);
    emit Derrota();
}

void Campo::setNumero() {
    for(int i=0; i<20; i++) {
        for(int j=0; j<20; j++) {
            int n = 0;
            if(this->quadradinhos[i][j]->getTipo() == 0) {
                quadradinhoNumero* q = static_cast<quadradinhoNumero*>(this->quadradinhos[i][j]);
                std::vector<int> v = q->getVizinhos();
                for(std::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
                    int x = (*it)/20;
                    int y = (*it)%20;
                    if(quadradinhos[x][y]->getTipo() == 1)
                        n++;
                }
                q->setNumero(n);
            }
        }
    }
}


