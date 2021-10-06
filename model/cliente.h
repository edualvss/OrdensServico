#ifndef CLIENTE_H
#define CLIENTE_H

#include <QString>
#include <QList>
#include "model/servico.h"

class Cliente {

private:
    int id;
    QString nome;
    QString endereco;
    QString telefone;
    QList<Servico*>* servicos;

public:
    Cliente();
    Cliente(QString nome,QString endereco, QString telefone,QList<Servico*>* servicos=new QList<Servico*>());

    inline void setId(int id) { this->id = id; }
    inline void setNome(QString nome) {this->nome = nome;}
    inline void setEndereco(QString endereco) {this->endereco = endereco;}
    inline void setTelefone(QString telefone) {this->telefone = telefone;}
    inline void setServicos(QList<Servico*>* servicos) {this->servicos = servicos;}

    inline int getId() { return this->id; }
    inline QString getNome() {return this->nome;}
    inline QString getEndereco() {return this->endereco;}
    inline QString getTelefone() {return this->telefone;}
    inline QList<Servico*>* getServicos() {return this->servicos;}

    QString toString();
    void adicionarServico(Servico* s);
    Servico* atServico(int indice);
    double totalServicos();
    int qtdServicos();

};

#endif // CLIENTE_H
