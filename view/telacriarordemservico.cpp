#include "telacriarordemservico.h"
#include "ui_telacriarordemservico.h"

#include "model/DAO/clientedao.h"

#include <QCompleter>
#include <QStringList>

TelaCriarOrdemServico::TelaCriarOrdemServico(QStringList listaTipos,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaCriarOrdemServico) {
    ui->setupUi(this);

    this->cliente = NULL;

    ui->dateIn->setDate(QDate::currentDate());

    this->adicionarListaTiposServicos(listaTipos);

    QList<Cliente*>* clientes = ClienteDAO::getInstance()->findAll();
    if(clientes != NULL) {
        QStringList listaNomes;

        int size = clientes->size();
        if(size != 0) {
            for(int i = 0; i < size; i++) {
                Cliente* c = clientes->at(i);
                listaNomes.insert(i,c->getNome());
            }
            QCompleter* completer = new QCompleter(listaNomes);
            completer->setCaseSensitivity(Qt::CaseInsensitive);
            connect(completer,SIGNAL(activated(QString)),this,SLOT(preencherCamposDadosExistentes(QString)));
            ui->lineInNomeCliente->setCompleter(completer);
        }
    }

    connect(ui->btnCriar,SIGNAL(clicked()),this,SLOT(criarOS()));
    connect(ui->btnCancelar,SIGNAL(clicked()),this,SLOT(cancelar()));
}

void TelaCriarOrdemServico::preencherCamposDadosExistentes(QString nome) {

    QList<Cliente*>* clientes = ClienteDAO::getInstance()->findClientes(nome);
    int size = clientes->size();
    if(size == 1) {
        Cliente* c = clientes->at(0);
        this->ui->lineInEnderecoCliente->setText(c->getEndereco());
        this->ui->lineInTelefoneCliente->setText(c->getTelefone());
        this->cliente = c;
    }

}

TelaCriarOrdemServico::~TelaCriarOrdemServico()
{
    delete ui;
}

void TelaCriarOrdemServico::adicionarListaTiposServicos(QStringList lista) {

    for(int i = 0; i < lista.size(); i++) {
        ui->comboInTipoServico->addItem(lista.at(i));
    }
}

void TelaCriarOrdemServico::criarOS() {

    QString nomeCli = ui->lineInNomeCliente->text().toUtf8();
    QString enderecoCli = ui->lineInEnderecoCliente->text().toUtf8();
    QString telefone = ui->lineInTelefoneCliente->text();
    QString tipoServico = ui->comboInTipoServico->itemText(ui->comboInTipoServico->currentIndex());
    QDate data = ui->dateIn->date();
    QString obs = ui->lineInObs->text().toUtf8();
    double precoServico = ui->spinInPreco->value();

    Servico* s = new Servico(tipoServico,precoServico,data,0,obs);

    if(this->cliente == NULL) {
        this->cliente = new Cliente(nomeCli,enderecoCli,telefone);
    }

    this->cliente->adicionarServico(s);

    this->accept();
}

void TelaCriarOrdemServico::cancelar() {

    this->reject();
}
