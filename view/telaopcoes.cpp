#include "telaopcoes.h"
#include "ui_telaopcoes.h"

TelaOpcoes::TelaOpcoes(QStringList opcoes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaOpcoes) {

    ui->setupUi(this);

    ui->comboOpcoes->addItems(opcoes);

    connect(ui->btnCancelar,SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->btnOk,SIGNAL(clicked()),this,SLOT(accept()));
}

int TelaOpcoes::getCurrentIndexOpcoes() {
    return this->ui->comboOpcoes->currentIndex();
}

TelaOpcoes::~TelaOpcoes()
{
    delete ui;
}
