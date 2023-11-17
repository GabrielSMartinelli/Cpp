#ifndef CAMPO_H
#define CAMPO_H

#include <QFrame>
#include <QMouseEvent>
#include "quadrado.h"
#include "quadradinhobomba.h"
#include "quadradinhonumero.h"

class Campo : public QFrame
{
    Q_OBJECT
    static Campo* instancia;
    Quadrado *quadradinhos[20][20];
    int bombas;
    int abertos;
    Campo(QWidget* parent = nullptr);
public:
    Campo(const Campo& campo) = delete;
    Campo operator=(Campo campo) = delete;
    static Campo* getInstancia();
    static Campo* deleteInstancia();
    void setBombas(int b) {bombas = b;}
    void setNumero();
    void setAbertos(int a) {abertos = a;}
    int getBombas() {return bombas;}
    Quadrado* getQuadradinho(int i, int j) {return quadradinhos[i][j];}
    void criaQuadradinhos(int i, int j); //cria um quadrado sem bomba
    void criaBombas(int i, int j); //cria bomba num quadrado especifico
    void criaBombas();//cria bomba numa posicao aleatoria
    void paintEvent(QPaintEvent *event);
signals:
    void Vitoria();
    void Derrota();
public slots:
    void abreQuadradinhos(int i, int j); //vai abrindo quadradinhos ate onde der (onde numero > 0)
    void abreBombas(int i, int j); //abre todas as bombas do campo
    void Verifica(); //checa se o jogador venceu
    void Perdeu(); //checa se o jogador perdeu
};

#endif // CAMPO_H
