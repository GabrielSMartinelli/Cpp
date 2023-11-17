#ifndef QUADRADINHONUMERO_H
#define QUADRADINHONUMERO_H

#include "quadrado.h"


class quadradinhoNumero : public Quadrado
{
    Q_OBJECT
    int num;
    std::vector<int> vizinhos;
public:
    quadradinhoNumero(QWidget* parent = nullptr) : Quadrado(parent) {}
    int getTipo() {return 0;}
    int getNum() {return num;}
    std::vector<int> getVizinhos() {return vizinhos;}
    void setNumero(int n) {num = n;}
    void setVizinhos();
    void abrir(); //abre o quadradinho de numero
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent *event);
signals:
    void abrirVizinhos(int i, int j); //manda o campo abrir os vizinhos desse quadrado
    void Confere(); //sinal pro campo verificar se o jogador ganhou
};

#endif // QUADRADINHONUMERO_H
