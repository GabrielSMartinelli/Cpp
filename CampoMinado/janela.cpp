#include "janela.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <ctime>

janela::janela(QWidget *parent)
    : QMainWindow{parent}
{
    this->setGeometry(400, 100, 550, 570);
    this->setWindowTitle("Campo Minado");

    QMenuBar* menu = new QMenuBar(this);
    QMenu* opcoes = new QMenu("Menu", menu);
    menu->addMenu(opcoes);
    this->setMenuBar(menu);

    QAction* NovoJogo = new QAction("Novo jogo", opcoes);
    QAction* SalvarJogo = new QAction("Salvar", opcoes);
    QAction* AbrirJogo = new QAction("Abrir", opcoes);

    opcoes->addAction(NovoJogo);
    opcoes->addAction(SalvarJogo);
    opcoes->addAction(AbrirJogo);

    connect(NovoJogo, SIGNAL(triggered(bool)), this, SLOT(NovoJogo()));
    connect(SalvarJogo, SIGNAL(triggered(bool)), this, SLOT(Salvar()));
    connect(AbrirJogo, SIGNAL(triggered(bool)), this, SLOT(Abrir()));

    CampoMinado = criaCampo();
}

Campo* janela::criaCampo() {

    srand(time(NULL));

    Campo* campo = Campo::getInstancia();
    campo->setParent(this);
    campo->setAbertos(0);
    campo->setGeometry(25, 45, 500, 500);
    int b = 0;
    while((b < 10) or b > 200)
        b = QInputDialog::getInt(this, "Bombas", "Digite um número de bombas entre 10 e 200:");
    campo->setBombas(b);
    for(int a = b; a>0; a--)
        campo->criaBombas();
    connect(campo, SIGNAL(Vitoria()), this, SLOT(MsgVitoria()));
    connect(campo, SIGNAL(Derrota()), this, SLOT(MsgDerrota()));

    for(int i=0; i<20; i++) {
        for(int j=0; j<20; j++) {
            campo->criaQuadradinhos(i, j);
        }
    }
    campo->setNumero();
    return campo;
}

Campo* janela::criaCampoParaAbrir() {

    srand(time(NULL));

    Campo* campo = Campo::getInstancia();
    campo->setParent(this);
    campo->setAbertos(0);
    campo->setGeometry(25, 45, 500, 500);
    connect(campo, SIGNAL(Vitoria()), this, SLOT(MsgVitoria()));
    connect(campo, SIGNAL(Derrota()), this, SLOT(MsgDerrota()));
    return campo;
}

void janela::NovoJogo() {
    CampoMinado->deleteInstancia();
    CampoMinado = criaCampo();
    CampoMinado->update();
    CampoMinado->show();
}

void janela::MsgVitoria() {
    QMessageBox Msg;
    Msg.setWindowTitle("Vitória");
    Msg.setText("Parabéns, você venceu!");
    Msg.exec();
}

void janela::MsgDerrota() {
    QMessageBox Msg;
    Msg.setWindowTitle("Derrota");
    Msg.setText("Você perdeu!");
    Msg.exec();
}

void janela::Salvar() {
    QString NomeDoArquivo = QFileDialog::getSaveFileName(this);
    QFile Arquivo(NomeDoArquivo);
    if(!NomeDoArquivo.isEmpty()) {
        Arquivo.open(QIODevice::WriteOnly);
        QTextStream out(&Arquivo);
        for(int i=0; i<20; i++) {
            for(int j=0; j<20; j++) {
                if(this->CampoMinado->getQuadradinho(i, j)->getTipo() == 0) {
                    quadradinhoNumero* q = static_cast<quadradinhoNumero*>(this->CampoMinado->getQuadradinho(i, j));
                    out << q->getTipo() << " " <<
                           q->getMarcado() << " " <<
                           q->getAberto() << " " <<
                           q->getTravado() << " " <<
                           q->getNum() << "\n";
                }
                else {
                    out << this->CampoMinado->getQuadradinho(i, j)->getTipo() << " " <<
                           this->CampoMinado->getQuadradinho(i, j)->getMarcado() << " " <<
                           this->CampoMinado->getQuadradinho(i, j)->getAberto() << " " <<
                           this->CampoMinado->getQuadradinho(i, j)->getTravado() << "\n";
                }
            }
        }
        out << this->CampoMinado->getBombas() << "\n";
    }
    Arquivo.close();
}

void janela::Abrir() {
    QString NomeDoArquivo = QFileDialog::getOpenFileName(this);
    QFile Arquivo(NomeDoArquivo);
    if(!NomeDoArquivo.isEmpty()) {
        Arquivo.open(QIODevice::ReadOnly);
        QTextStream in(&Arquivo);
        int i, j, abertos;
        i = j = abertos = 0;
        CampoMinado->deleteInstancia();
        CampoMinado = criaCampoParaAbrir();
        while(!in.atEnd()) {
            int l = 20*i + j;
            QString info = in.readLine();
            std::string linha = info.toStdString();
            bool m, a, t;
            int tipo, n;

            if(l < 400) {
                if(linha[0] == '0') {
                    tipo = 0;
                    try {
                        n = linha[8] - '0';
                        if((n < 0) or n > 8)
                            throw 4;
                    }
                    catch(int erro) {
                        QMessageBox::warning(this, "Erro", "Não foi possível ler o arquivo");
                        return;
                    }
                }

                else if(linha[0] == '1')
                    tipo = 1;

                else {
                    try{throw 0;}
                    catch(int erro) {
                        QMessageBox::warning(this, "Erro", "Não foi possível ler o arquivo");
                        return;
                    }
                }

                if(linha[2] == '0')
                    m = false;
                else if(linha[2] == '1')
                    m = true;
                else {
                    try{throw 1;}
                    catch(int erro) {
                        QMessageBox::warning(this, "Erro", "Não foi possível ler o arquivo");
                        return;
                    }
                }

                if(linha[4] == '0')
                    a = false;
                else if(linha[4] == '1') {
                    a = true;
                }
                else{
                    try{throw 2;}
                    catch(int erro) {
                        QMessageBox::warning(this, "Erro", "Não foi possível ler o arquivo");
                        return;
                    }
                }

                if(linha[6] == '0')
                    t = false;
                else if(linha[6] == '1')
                    t = true;
                else {
                    try{throw 3;}
                    catch(int erro) {
                        QMessageBox::warning(this, "Erro", "Não foi possível ler o arquivo");
                        return;
                    }
                }

                if(tipo == 0) {
                    this->CampoMinado->criaQuadradinhos(i, j);
                }

                else if(tipo == 1)
                    this->CampoMinado->criaBombas(i, j);

                this->CampoMinado->getQuadradinho(i, j)->setMarcado(m);
                this->CampoMinado->getQuadradinho(i, j)->setAberto(a);
                this->CampoMinado->getQuadradinho(i, j)->setTravado(t);

                if(a == true)
                    this->CampoMinado->setAbertos(++abertos);

                j++;
                if(j == 20) {
                    j = 0;
                    i++;
                }
            }
            else {
                int b = std::stoi(linha);
                this->CampoMinado->setBombas(b);
                this->CampoMinado->setNumero();
            }
        }
        CampoMinado->update();
        CampoMinado->show();
    }
    Arquivo.close();
}

