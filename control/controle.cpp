#include "controle.h"

#include <QSqlQuery>
#include <QSqlError>

#include <QFile>
#include <QTextStream>

#include <QMessageBox>

#include <QDebug>

#include "model/DAO/clientedao.h"
#include "model/DAO/servicodao.h"

Controle::Controle(TelaPrincipal* tela,QObject *parent) :
    QObject(parent) {

    qDebug() << QSqlDatabase::drivers();

    db = QSqlDatabase::addDatabase("QSQLITE");

    this->tela = tela;

    this->criarConexoes();
}

void Controle::criarConexoes() {
    connect(this->tela,SIGNAL(acaoCriarOS()),this,SLOT(adicionarOS()));
    connect(this->tela,SIGNAL(opcaoEscolhida(int,int,int)),this,SLOT(opcaoDoisCliques(int,int,int)));
    connect(this->tela,SIGNAL(calcularTotal()),this,SLOT(calcularTotalValores()));
    connect(this->tela,SIGNAL(calcularTotalMes(int,int)),this,SLOT(calcularTotalValoresMes(int,int)));
    connect(this->tela,SIGNAL(buscarPorNome(QString)),this,SLOT(buscarPorNome(QString)));
}

void Controle::inicializarBancoDados() {
    db.setDatabaseName("OrdensServico.db");

    if(!db.open()) {
        qCritical() << db.lastError();
    } else {
        QSqlQuery query;
        if( db.tables().indexOf("clientes") == -1 ) {
            if(!query.exec("CREATE TABLE IF NOT EXISTS clientes (id integer primary key autoincrement, nome varchar(50) not null,endereco varchar(70) not null,telefone varchar(20) not null)")) {
                qCritical() << db.lastError();
            }
        }
        if( db.tables().indexOf("servicos") == -1 ) {
            if(!query.exec("CREATE TABLE IF NOT EXISTS servicos (id integer primary key autoincrement, tipo char(20) not null, preco real not null, data char(15) not null, cliente integer not null,observacoes varchar(100) not null, foreign key(cliente) references clientes )")) {
                qCritical() << db.lastError();
            }
        }
    }

}

void Controle::inicializarArquivos() {
    QFile arquivo("TiposServicos.txt");

    if(!arquivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->TiposServicos.insert(0,tr("Sky"));
        this->TiposServicos.insert(1,tr("Parabólica"));
        this->TiposServicos.insert(2,tr("Outros"));
        return;
    }

    QTextStream entrada(&arquivo);

    int contador = 0;
    while(!entrada.atEnd()) {
        this->TiposServicos.insert(contador++,entrada.readLine());
    }

    if( contador == 0 ) {
        this->TiposServicos.insert(contador++,tr("Sky"));
        this->TiposServicos.insert(contador++,tr("Parabólica"));
        this->TiposServicos.insert(contador++,tr("Outros"));
    }

}

void Controle::iniciarAplicacao() {

    this->inicializarBancoDados();
    this->inicializarArquivos();

    if(this->tela != NULL) {
        this->carregarListaOS(ClienteDAO::getInstance()->findAll());
        this->tela->show();
    }

}

void Controle::adicionarOS() {

    TelaCriarOrdemServico* tCriarOS = new TelaCriarOrdemServico(this->TiposServicos,this->tela);

    if( tCriarOS->exec() == QDialog::Accepted ) {
        Cliente* c = tCriarOS->getCliente();
        if(c->getId() == 0) {
            // Cria outro cliente no banco
            ClienteDAO::getInstance()->insert(c);
        } else {
            // Utiliza cliente existente
            ClienteDAO::getInstance()->update(c);
        }
    }
    delete tCriarOS;
    this->carregarListaOS(ClienteDAO::getInstance()->findAll());
}

void Controle::opcaoDoisCliques(int id, int indice, int tipo) {


    switch(tipo) {
        case TelaPrincipal::CLIENTE:{
            ClienteDAO* cDao = ClienteDAO::getInstance();
            Cliente* cliente = cDao->findCliente(id);
            switch(indice){
                case TelaPrincipal::TOTAL:{
                    QString msg(tr("Valor total dos serviços prestados ao cliente: "));
                    msg += QString("R$ %1").arg(QString::number(cliente->totalServicos(),'f',2));
                    this->tela->exibirMensagem(tr("Valor Total dos serviços do cliente"),msg);
                    break;
                }
                case TelaPrincipal::EDITAR_CLI:{
                    TelaEdicaoCliente* tec = new TelaEdicaoCliente(cliente,this->tela);
                    connect(tec,SIGNAL(clienteEditado(Cliente*)),this,SLOT(atualizarCliente(Cliente*)));
                    tec->exec();
                    break;
                }
                case TelaPrincipal::EXCLUIR_CLI:{
                    int resultado = this->tela->confirmarMensagem(tr("Confirmar exclusão?"),tr("Você realmente deseja excluir o cliente\n e todos os serviços associados a ele?"),tr("Não será possí­vel recuperar os dados excluí­dos"));
                    if(resultado == QMessageBox::Yes) {
                        cDao->erase(cliente->getId(),true);
                        this->carregarListaOS(cDao->findAll());
                    }
                    break;
                }
            }
            delete cliente;
            break;
        }
        case TelaPrincipal::SERVICO:{
            ServicoDAO* sDao = ServicoDAO::getInstance();
            Servico* servico = sDao->findServico(id);
            switch(indice) {
                case TelaPrincipal::EDITAR_SER:{
                    TelaEdicaoServico* tes = new TelaEdicaoServico(servico,this->TiposServicos,this->tela);
                    connect(tes,SIGNAL(servicoEditado(Servico*)),this,SLOT(atualizarServico(Servico*)));
                    tes->exec();
                    break;
                }
                case TelaPrincipal::EXCLUIR_SER:{
                    int resultado = this->tela->confirmarMensagem(tr("Confirmar exclusão?"),tr("Você realmente deseja excluir o serviço selecionado?"),tr("Não será possí­vel recuperar o dado excluí­do"));
                    if(resultado == QMessageBox::Yes) {
                        sDao->erase(servico->getId());
                        this->carregarListaOS(ClienteDAO::getInstance()->findAll());
                    }
                    break;
                }
            }
            delete servico;
            break;
        }
    }

}

void Controle::atualizarCliente(Cliente *cli) {
    ClienteDAO* cDao = ClienteDAO::getInstance();
    cDao->update(cli);
    this->carregarListaOS(cDao->findAll());
}

void Controle::atualizarServico(Servico *ser) {
    ServicoDAO::getInstance()->update(ser);
    this->carregarListaOS(ClienteDAO::getInstance()->findAll());
}

void Controle::carregarListaOS(QList<Cliente *>* lista) {

    this->tela->limparItemsTreeClientes();

    if(lista == NULL) {
        if(ClienteDAO::getInstance()->existClient()) {
            this->tela->exibirMensagem(tr("Aviso"),tr("Problema ao carregar lista de usuários.\nSe o problema persistir reinicie a aplica?ão"));
        }
    } else {
        int size = lista->size();
        for(int i = 0; i < size; i++) {
            this->tela->adicionarItemTreeClientes(lista->at(i));
        }
        lista->clear();
        delete lista;
    }

}

void Controle::buscarPorNome(QString texto) {

    ClienteDAO* cDao = ClienteDAO::getInstance();
    QList<Cliente*>* clientes = cDao->findClientes(texto);

    if(clientes == NULL) {
        this->carregarListaOS(new QList<Cliente*>());
    } else {
        this->carregarListaOS(clientes);
    }


}

void Controle::calcularTotalValores() {

    this->tela->exibirMensagem(tr("Total"),tr("Valor total: R$ %1").arg(QString::number(ServicoDAO::getInstance()->calcularTotalValoresServicos(),'f',2)));

}

void Controle::calcularTotalValoresMes(int mes, int ano) {

    double total = ServicoDAO::getInstance()->calcularTotalValoresServicos(mes,ano);

    this->tela->exibirMensagem(tr("Total do mês: %1, ano: %2").arg(QString::number(mes)).arg(QString::number(ano)),tr("Valor Total: R$ %1").arg(QString::number(total,'f',2)));

}
