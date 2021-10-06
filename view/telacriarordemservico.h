#ifndef TELACRIARORDEMSERVICO_H
#define TELACRIARORDEMSERVICO_H

#include <QDialog>

#include "model/cliente.h"

namespace Ui {
    class TelaCriarOrdemServico;
}

class TelaCriarOrdemServico : public QDialog {
    Q_OBJECT
public:
    TelaCriarOrdemServico(QStringList listaTipos,QWidget *parent = 0);
    ~TelaCriarOrdemServico();

    inline Cliente* getCliente() { return this->cliente; }

private slots:
    void criarOS();
    void cancelar();

    void preencherCamposDadosExistentes(QString nome);

private:

    void adicionarListaTiposServicos(QStringList lista);

    Ui::TelaCriarOrdemServico *ui;
    Cliente* cliente;
};

#endif // TELACRIARORDEMSERVICO_H
