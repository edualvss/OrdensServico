#include "servico.h"

Servico::Servico() {

    this->id = 0;
    this->tipo = "Sem tipo";
    this->preco = 0;
    this->data = QDate::currentDate();
    this->observacoes = QString();
    this->cliente = 0;

}

Servico::Servico(QString tipo, double preco, QDate data,int idCliente, QString obs) {
    this->id = 0;
    this->tipo = tipo;
    this->preco = preco;
    this->data = data;
    this->cliente = idCliente;
    this->observacoes = obs;
}

QString Servico::toString() {
    return QString::fromUtf8("IdServico: %1, TipoServico: %2, PrecoServico: %3, DataServico: %4, IdClienteServico: %5, OBS: %6")
            .arg(QString::number(this->id))
            .arg(this->tipo)
            .arg(QString::number(this->preco))
            .arg(this->data.toString("dd/MM/yyyy"))
            .arg(QString::number(this->cliente)
            .arg(this->observacoes));
}

bool Servico::equals(Servico *s) {

    if( this->id == s->id ) {
        if(this->cliente == s->cliente && this->preco == s->preco) {
            if(this->tipo == s->tipo && this->data == s->data && this->observacoes == s->observacoes) {
                return true;
            }
        }
    }
    return false;
}
