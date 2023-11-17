#ifndef QUADRADINHOBOMBA_H
#define QUADRADINHOBOMBA_H

#include "quadrado.h"

class quadradinhoBomba : public Quadrado
{
    Q_OBJECT
public:
    quadradinhoBomba(QWidget* parent = nullptr) : Quadrado(parent) {}
    int getTipo() {return 1;}
    void abrir(); //abre o quadradinho de bomba
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent *event);
signals:
    void abrirBombas(int i, int j); //avisa pro campo abrir todas as bombas
    void Explodiu(); //avisa que explodiu bomba, logo o jogador perdeu
};

#endif // QUADRADINHOBOMBA_H
