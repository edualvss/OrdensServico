#ifndef SERVICO_H
#define SERVICO_H

#include <QString>
#include <QDate>

class Servico {

private:
    int id;
    QString tipo;
    double preco;
    QDate data;
    QString observacoes;
    int cliente;

public:
    Servico();
    Servico(QString tipo,double preco,QDate data = QDate::currentDate(),int idCliente = 0, QString obs=QString());

    inline void setId(int id) {this->id = id;}
    inline void setTipo(QString tipo) {this->tipo = tipo;}
    inline void setPreco(double preco) {this->preco = preco;}
    inline void setData(QDate data) {this->data = data;}
    inline void setCliente(int idCliente) {this->cliente = idCliente;}
    inline void setObservacoes(QString obs) {this->observacoes = obs;}

    inline int getId() {return this->id;}
    inline QString getTipo() {return this->tipo;}
    inline double getPreco() {return this->preco;}
    inline QDate getData() {return this->data;}
    inline int getCliente() {return this->cliente;}
    inline QString getObservacoes() {return this->observacoes;}

    QString toString();
    bool equals(Servico* s);

};

#endif // SERVICO_H
