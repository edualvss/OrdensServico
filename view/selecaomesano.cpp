#include "selecaomesano.h"
#include "ui_selecaomesano.h"

#include <QDate>

SelecaoMesAno::SelecaoMesAno(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelecaoMesAno)
{
    ui->setupUi(this);

    QDate data = QDate::currentDate();

    int mesAtual = data.month();
    int anoAtual = data.year();

    ui->spinMes->setValue(mesAtual);
    ui->spinAno->setValue(anoAtual);

    connect(ui->btnCancelar,SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->btnOk,SIGNAL(clicked()),this,SLOT(ok()));
}

SelecaoMesAno::~SelecaoMesAno()
{
    delete ui;
}

void SelecaoMesAno::ok() {


    emit mesAno(ui->spinMes->value(),ui->spinAno->value());

    this->accept();
}
