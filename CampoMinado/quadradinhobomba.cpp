#include "quadradinhobomba.h"

void quadradinhoBomba::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter p(this);
    QPen pen(Qt::gray);
    p.setPen(pen);

    this->setStyleSheet("background-color:gray;");

    p.drawRect(this->rect().x(), this->rect().y(), this->rect().width()-1, this->rect().height()-1);

    if(this->getAberto() == true) {
        pen.setColor(Qt::red);
        p.setPen(pen);
        this->setStyleSheet("background-color:red;");
        p.drawText(this->rect().x(), this->rect().y(), this->rect().width()-1, this->rect().height()-1,
                   Qt::AlignCenter, tr("B"));
    }

    if(this->getMarcado() == true) {
        pen.setColor(Qt::black);
        p.setPen(pen);
        this->setStyleSheet("background-color:gray;");
        p.drawText(this->rect().x(), this->rect().y(), this->rect().width()-1, this->rect().height()-1,
                   Qt::AlignCenter, tr("M"));
    }
}

void quadradinhoBomba::mousePressEvent(QMouseEvent *event) {
    if(this->getTravado() == false) {
        if(event->button() == Qt::LeftButton and this->getMarcado() == false) {
            this->setAberto(true);
            this->update();
            emit abrirBombas(this->getI(), this->getJ());
            emit Explodiu();
        }
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

void quadradinhoBomba::abrir() {
    if(this->getAberto() == false and this->getMarcado() == false) {
        this->update();
        this->setAberto(true);
    }
}
