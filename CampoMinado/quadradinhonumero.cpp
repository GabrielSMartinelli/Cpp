#include "quadradinhonumero.h"

void quadradinhoNumero::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter p(this);
    QPen pen(Qt::gray);
    p.setPen(pen);

    this->setStyleSheet("background-color:gray;");

    p.drawRect(this->rect().x(), this->rect().y(), this->rect().width()-1, this->rect().height()-1);

    if(this->getAberto() == true and num > 0) {

        switch(num) {

            case(1):
                pen.setColor(Qt::blue);
                p.setPen(pen);
                this->setStyleSheet("background-color:white;");
            break;

            case(2):
                pen.setColor(Qt::green);
                p.setPen(pen);
                this->setStyleSheet("background-color:white;");
            break;

            case(3):
                pen.setColor(Qt::gray);
                p.setPen(pen);
                this->setStyleSheet("background-color:white;");
            break;

            case(4):
                pen.setColor(QColor(165,42,42));
                p.setPen(pen);
                this->setStyleSheet("background-color:white;");
            break;

            case(5):
                pen.setColor(QColor(255,165,0));
                p.setPen(pen);
                this->setStyleSheet("background-color:white;");
            break;

            case(6):
                pen.setColor(Qt::red);
                p.setPen(pen);
                this->setStyleSheet("background-color:white;");
            break;

            case(7):
                pen.setColor(QColor(128,0,128));
                p.setPen(pen);
                this->setStyleSheet("background-color:white;");
            break;

            case(8):
                pen.setColor(Qt::black);
                p.setPen(pen);
                this->setStyleSheet("background-color:white;");
            break;
        }

        p.drawText(this->rect().x(), this->rect().y(), this->rect().width()-1, this->rect().height()-1,
                   Qt::AlignCenter, QString::number(num));
    }

    if(this->getAberto() == true and num == 0) {
        this->setStyleSheet("background-color:white;");
    }

    if(this->getMarcado() == true) {
        pen.setColor(Qt::black);
        p.setPen(pen);
        this->setStyleSheet("background-color:gray;");
        p.drawText(this->rect().x(), this->rect().y(), this->rect().width()-1, this->rect().height()-1,
                   Qt::AlignCenter, tr("M"));
    }
}

void quadradinhoNumero::mousePressEvent(QMouseEvent *event) {
    if(this->getTravado() == false) {
        if(event->button() == Qt::LeftButton and this->getMarcado() == false)
                abrir();

        else if(event->button() == Qt::RightButton and this->getAberto() == false and this->getMarcado() == false) {
            this->setMarcado(true);
            this->update();
        }
        else if(event->button() == Qt::RightButton and this->getAberto() == false and this->getMarcado() == true) {
            this->setMarcado(false);
            this->update();
        }
    }
}

void quadradinhoNumero::setVizinhos() {

    if(this->getI()-1 >= 0) {

        vizinhos.push_back(this->getPosicao()-20);

        if(this->getJ()-1 >= 0)
            vizinhos.push_back(this->getPosicao()-21);

        if(this->getJ()+1 < 20)
            vizinhos.push_back(this->getPosicao()-19);
    }

    if(this->getJ()-1 >= 0)
        vizinhos.push_back(this->getPosicao()-1);

    if(this->getJ()+1 < 20)
        vizinhos.push_back(this->getPosicao()+1);

    if(this->getI()+1 < 20) {

        vizinhos.push_back(this->getPosicao()+20);

        if(this->getJ()-1 >= 0)
            vizinhos.push_back(this->getPosicao()+19);

        if(this->getJ()+1 < 20)
            vizinhos.push_back(this->getPosicao()+21);
    }
}

void quadradinhoNumero::abrir() {
    if(this->getAberto() == false and this->getMarcado() == false) {
        this->setAberto(true);
        emit Confere();
        if(num > 0) {
            this->update();
            return;
        }
        else
            this->update();
            emit abrirVizinhos(this->getI(), this->getJ());
        }
    return;
}

