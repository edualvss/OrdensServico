#include "telaprincipal.h"
#include "ui_telaprincipal.h"

#include <QScreen>
#include <QMessageBox>

#include "view/telaopcoes.h"
#include "view/selecaomesano.h"

TelaPrincipal::TelaPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TelaPrincipal) {

    ui->setupUi(this);

    QHeaderView* headerView = ui->treeClientes->header();
    headerView->resizeSection(0,60);
    headerView->resizeSection(1,150);
    headerView->resizeSection(2,100);
    headerView->resizeSection(3,210);


    this->centralizarTela();

    connect(ui->actionCriarOS,SIGNAL(triggered()),this,SLOT(criarOS()));
    connect(ui->treeClientes,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(doubleClickItemTreeClientes(QTreeWidgetItem*,int)));
    connect(ui->btnTotal,SIGNAL(clicked()),this,SLOT(total()));
    connect(ui->btnTotalMes,SIGNAL(clicked()),this,SLOT(totalMes()));

    connect(ui->lineInBuscaNome,SIGNAL(textEdited(QString)),this,SLOT(buscar(QString)));

}

TelaPrincipal::~TelaPrincipal()
{
    delete ui;
}

void TelaPrincipal::centralizarTela() {
    int x, y;
    int screenWidth;
    int screenHeight;

    QScreen *desktop = QWidget::screen();

    screenWidth = desktop->size().width();
    screenHeight = desktop->size().height();

    x = (screenWidth - this->width()) / 2;
    y = (screenHeight - this->height()) / 2;

    this->move( x, y );

}

void TelaPrincipal::criarOS() {
    emit acaoCriarOS();
}

void TelaPrincipal::adicionarItemTreeClientes(Cliente *cliente) {

    QTreeWidgetItem* cli = new QTreeWidgetItem(ui->treeClientes);
    cli->setData(0,Qt::DisplayRole,cliente->getId());
    cli->setData(0,Qt::UserRole,CLIENTE);
    cli->setData(1,Qt::DisplayRole,cliente->getNome());
    cli->setData(2,Qt::DisplayRole,cliente->getTelefone());
    cli->setData(3,Qt::DisplayRole,cliente->getEndereco());

    QList<Servico*>* servicos = cliente->getServicos();
    int size = servicos->size();
    for(int i = 0; i < size; i++) {
        Servico* s = servicos->at(i);
        QTreeWidgetItem* ser = new QTreeWidgetItem(cli);
        ser->setData(0,Qt::DisplayRole,s->getId());
        ser->setData(0,Qt::UserRole,SERVICO);
        ser->setData(1,Qt::DisplayRole,s->getTipo());
        ser->setData(2,Qt::DisplayRole,s->getData().toString("dd/MM/yyyy"));
        ser->setData(3,Qt::DisplayRole,QString("R$ %1").arg(QString::number(s->getPreco(),'f',2)));
        ser->setData(4,Qt::DisplayRole,s->getObservacoes());
    }

}

void TelaPrincipal::limparItemsTreeClientes() {
    this->ui->treeClientes->clear();
}

void TelaPrincipal::exibirMensagem(QString titulo, QString msg) {
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setModal(true);
    msgBox->setWindowTitle(titulo);
    msgBox->setText(msg);
    msgBox->setIcon(QMessageBox::Information);
    msgBox->exec();
    delete msgBox;
}

int TelaPrincipal::confirmarMensagem(QString titulo, QString questao, QString msg) {
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setModal(true);
    msgBox->setWindowTitle(titulo);
    msgBox->setInformativeText(questao);
    msgBox->setText(msg);
    msgBox->setIcon(QMessageBox::Question);
    msgBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox->setDefaultButton(QMessageBox::Yes);
    int result = msgBox->exec();
    delete msgBox;
    return result;
}

void TelaPrincipal::doubleClickItemTreeClientes(QTreeWidgetItem *item, int /*coluna*/) {
// Não é necessário utilizar o dado coluna, nesta versão do soft.
//    coluna = 0;
    QStringList lista;

    int tipo = item->data(0,Qt::UserRole).toInt();
    switch(tipo) {
        case CLIENTE:
            // Tratar dois cliques para clientes
            // Opções: Editar, Excluir, Ver somatório de preço dos serviços do cliente específicos
            lista.insert(TOTAL,tr("Total, dos serviços deste cliente"));
            lista.insert(EDITAR_CLI,"Editar info. do cliente");
            lista.insert(EXCLUIR_CLI,tr("Excluir cliente e seus serviçoes"));
            break;
        case SERVICO:
            // Tratar dois cliques para serviços
            // Opções: Editar, Excluir
            lista.insert(EDITAR_SER,tr("Editar serviço"));
            lista.insert(EXCLUIR_SER,tr("Excluir serviço"));
            break;
    }
    TelaOpcoes* to = new TelaOpcoes(lista,this);
    if( to->exec() == QDialog::Accepted ) {
        int result = to->getCurrentIndexOpcoes();
        emit opcaoEscolhida(item->data(0,Qt::DisplayRole).toInt(),result,tipo);
    }
    delete to;

}

void TelaPrincipal::total() {
    emit calcularTotal();
}

void TelaPrincipal::totalMes() {

    SelecaoMesAno* sma = new SelecaoMesAno(this);

    connect(sma,SIGNAL(mesAno(int,int)),this,SLOT(enviarMesAno(int,int)));

    sma->exec();

    delete sma;
}

void TelaPrincipal::buscar(QString texto) {
    emit buscarPorNome(texto);
}

void TelaPrincipal::enviarMesAno(int mes, int ano) {
    emit calcularTotalMes(mes,ano);
}
