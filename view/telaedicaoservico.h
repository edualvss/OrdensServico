#ifndef TELAEDICAOSERVICO_H
#define TELAEDICAOSERVICO_H

#include <QDialog>

#include "model/servico.h"

namespace Ui {
    class TelaEdicaoServico;
}

class TelaEdicaoServico : public QDialog {
    Q_OBJECT
public:
    TelaEdicaoServico(Servico* servico,QStringList tipos,QWidget *parent = 0);
    ~TelaEdicaoServico();

signals:
    void servicoEditado(Servico*);

private slots:
    void ok();
private:
    Servico* servico;
    Ui::TelaEdicaoServico *ui;
};

#endif // TELAEDICAOSERVICO_H
