#ifndef CONTROLE_H
#define CONTROLE_H

#include <QObject>

#include <QSqlDatabase>

#include <QString>

#include "view/telaprincipal.h"
#include "view/telacriarordemservico.h"
#include "view/telaedicaocliente.h"
#include "view/telaedicaoservico.h"

class Controle : public QObject {
    Q_OBJECT
private:
    TelaPrincipal* tela;
    QSqlDatabase db;

    QStringList TiposServicos;

    void inicializarBancoDados();
    void inicializarArquivos();

    void criarConexoes();

    void carregarListaOS(QList<Cliente*>* lista);
public:
    explicit Controle(TelaPrincipal* tela, QObject *parent = 0);

    void iniciarAplicacao();

private slots:
    void adicionarOS();
    void opcaoDoisCliques(int,int,int);

    void atualizarCliente(Cliente*);
    void atualizarServico(Servico*);

    void buscarPorNome(QString);
    void calcularTotalValores();
    void calcularTotalValoresMes(int mes,int ano);
};

#endif // CONTROLE_H
