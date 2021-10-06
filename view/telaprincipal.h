#ifndef TELAPRINCIPAL_H
#define TELAPRINCIPAL_H

#include <QMainWindow>

#include "model/cliente.h"

class QTreeWidgetItem;

namespace Ui {
    class TelaPrincipal;
}

class TelaPrincipal : public QMainWindow {
    Q_OBJECT
public:
    TelaPrincipal(QWidget *parent = 0);
    ~TelaPrincipal();

    void adicionarItemTreeClientes(Cliente* cliente);
    void limparItemsTreeClientes();

    void exibirMensagem(QString titulo, QString msg);
    int confirmarMensagem(QString titulo,QString questao,QString msg);

    enum { CLIENTE,SERVICO };
    enum {TOTAL=0,EDITAR_CLI,EXCLUIR_CLI};
    enum {EDITAR_SER=0,EXCLUIR_SER};

private:

    Ui::TelaPrincipal *ui;

    void centralizarTela();

private slots:
    void criarOS();
    void doubleClickItemTreeClientes(QTreeWidgetItem*,int);

    void buscar(QString);
    void total();
    void totalMes();

    void enviarMesAno(int,int);

signals:
    void acaoCriarOS();
    void calcularTotal();
    void calcularTotalMes(int,int);
    void buscarPorNome(QString);
    void opcaoEscolhida(int id,int opcao,int tipo);
};

#endif // TELAPRINCIPAL_H
