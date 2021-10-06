#include "cliente.h"

Cliente::Cliente() {
    this->id = 0;
    this->nome = "Sem nome";
    this->endereco = QString::fromUtf8("Sem endereço");
    this->telefone = "Sem telefone";
    this->servicos = new QList<Servico*>();
}

Cliente::Cliente(QString nome, QString endereco, QString telefone, QList<Servico *> *servicos) {
    this->id = 0;
    this->nome = nome;
    this->endereco = endereco;
    this->telefone = telefone;
    this->servicos = servicos;
}

QString Cliente::toString() {

    QString format =  QString::fromUtf8("Id: %1, Nome: %2, Endereço: %3, Telefone: %4")
            .arg(QString::number(this->id))
            .arg(this->nome)
            .arg(this->endereco)
            .arg(this->telefone);

    for(int i = 0; i < this->servicos->size(); i++) {
        format += QString::fromUtf8("\n\tServiço[%1]\n").arg(QString::number(i));
        format += this->servicos->at(i)->toString();
    }
    return format;

}

void Cliente::adicionarServico(Servico *s) {
    s->setCliente(this->id);
    this->servicos->insert(0,s);
}

Servico* Cliente::atServico(int indice) {
    return this->servicos->at(indice);
}

double Cliente::totalServicos() {
    double total = 0;
    int size = this->servicos->size();
    for(int i = 0; i < size; i++) {
        total += this->servicos->at(i)->getPreco();
    }
    return total;
}

int Cliente::qtdServicos() {
    return this->servicos->size();
}
