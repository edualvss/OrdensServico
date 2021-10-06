#ifndef TELAEDICAOCLIENTE_H
#define TELAEDICAOCLIENTE_H

#include <QDialog>

#include "model/cliente.h"

namespace Ui {
    class TelaEdicaoCliente;
}

class TelaEdicaoCliente : public QDialog {
    Q_OBJECT
public:
    TelaEdicaoCliente(Cliente* cliente, QWidget *parent = 0);
    ~TelaEdicaoCliente();

signals:
    void clienteEditado(Cliente*);

private slots:
    void ok();

private:
    Ui::TelaEdicaoCliente *ui;
    Cliente* cliente;
};

#endif // TELAEDICAOCLIENTE_H
