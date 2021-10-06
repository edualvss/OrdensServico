#include <QApplication>

#include "control/controle.h"

int main(int argc, char **argv) {

    QApplication app(argc,argv);

    (new Controle(new TelaPrincipal()))->iniciarAplicacao();

    return app.exec();
}
