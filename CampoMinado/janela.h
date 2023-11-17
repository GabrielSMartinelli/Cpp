#ifndef JANELA_H
#define JANELA_H

#include "campo.h"
#include <QMainWindow>
#include <QPushButton>

class janela : public QMainWindow
{
    Q_OBJECT
    Campo *CampoMinado;

public:
    explicit janela(QWidget *parent = nullptr);
    Campo* criaCampo();
    Campo* criaCampoParaAbrir();

public slots:
    void MsgVitoria();
    void MsgDerrota();
    void NovoJogo();
    void Salvar();
    void Abrir();
};

#endif // JANELA_H
