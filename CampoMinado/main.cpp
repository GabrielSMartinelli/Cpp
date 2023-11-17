#include <QApplication>
#include "janela.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    janela j;
    j.show();

    return app.exec();
}
