#include "telaedicaocliente.h"
#include "ui_telaedicaocliente.h"

TelaEdicaoCliente::TelaEdicaoCliente(Cliente* cliente,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaEdicaoCliente)
{
    ui->setupUi(this);

    this->cliente = cliente;

    ui->lineInNome->setText(cliente->getNome());
    ui->lineInEndereco->setText(cliente->getEndereco());
    ui->lineInTelefone->setText(cliente->getTelefone());

    connect(ui->btnCancelar,SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->btnOk,SIGNAL(clicked()),this,SLOT(ok()));
}

TelaEdicaoCliente::~TelaEdicaoCliente()
{
    delete ui;
}

void TelaEdicaoCliente::ok() {

    QString nome = ui->lineInNome->text();
    QString endereco = ui->lineInEndereco->text();
    QString telefone = ui->lineInTelefone->text();

    this->cliente->setNome(nome);
    this->cliente->setEndereco(endereco);
    this->cliente->setTelefone(telefone);

    emit clienteEditado(this->cliente);

    this->accept();
}
