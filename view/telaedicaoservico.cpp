#include "telaedicaoservico.h"
#include "ui_telaedicaoservico.h"

TelaEdicaoServico::TelaEdicaoServico(Servico* servico, QStringList tipos,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaEdicaoServico)
{
    ui->setupUi(this);

    this->servico = servico;

    ui->comboTipos->addItems(tipos);
    ui->comboTipos->setCurrentIndex(tipos.indexOf(servico->getTipo()));
    ui->spinPreco->setValue(servico->getPreco());
    ui->dateIn->setDate(servico->getData());
    ui->lineInObs->setText(servico->getObservacoes());

    connect(ui->btnCancelar,SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->btnOk,SIGNAL(clicked()),this,SLOT(ok()));
}

TelaEdicaoServico::~TelaEdicaoServico()
{
    delete ui;
}

void TelaEdicaoServico::ok() {

    QString tipo = ui->comboTipos->currentText();
    QDate data = ui->dateIn->date();
    double preco = ui->spinPreco->value();
    QString obs = ui->lineInObs->text().toUtf8();

    this->servico->setTipo(tipo);
    this->servico->setData(data);
    this->servico->setPreco(preco);
    this->servico->setObservacoes(obs);

    emit servicoEditado(this->servico);

    this->accept();

}
