#ifndef QUADRADO_H
#define QUADRADO_H

#include <QFrame>
#include <QPainter>
#include <QMouseEvent>

class Quadrado : public QFrame
{
    Q_OBJECT
    bool marcado, aberto, travado;
    int pos, i, j;
public:
    Quadrado(QWidget* parent = nullptr) : QFrame(parent) {}
    virtual int getTipo() = 0;
    virtual void abrir() = 0;
    virtual void paintEvent(QPaintEvent* event) = 0;
    virtual void mousePressEvent(QMouseEvent *event) = 0;
    bool getAberto() {return aberto;}
    bool getMarcado() {return marcado;}
    bool getTravado() {return travado;}
    int getPosicao() {return pos;}
    int getI() {return i;}
    int getJ() {return j;}
    void setPosicao(int i, int j);
    void setAberto(bool a) {aberto = a;}
    void setMarcado(bool m) {marcado = m;}
    void setTravado(bool t) {travado = t;}
};

#endif // QUADRADO_H
