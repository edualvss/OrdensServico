#ifndef SERVICODAO_H
#define SERVICODAO_H

#include <QList>

#include "model/servico.h"

class ServicoDAO {
private:
    static ServicoDAO* dao;

    ServicoDAO();
public:
    static ServicoDAO* getInstance();

    Servico* insert(Servico* s);
    Servico* update(Servico* s);
    Servico* findServico(int id);
    QList<Servico*>* findServicos(QString lettersTipo);
    QList<Servico*>* findServicos(int idCliente);
    QList<Servico*>* findAll();
    Servico* erase(int id);
    double calcularTotalValoresServicos();
    double calcularTotalValoresServicos(int mes,int ano);

};

#endif // SERVICODAO_H
