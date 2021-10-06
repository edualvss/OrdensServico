#ifndef CLIENTEDAO_H
#define CLIENTEDAO_H

#include <QList>

#include "model/cliente.h"

class ClienteDAO {
private:
    static ClienteDAO* dao;

    ClienteDAO();
public:

    static ClienteDAO* getInstance();

    Cliente* insert(Cliente* c);
    Cliente* update(Cliente* c);
    Cliente* findCliente(int id);
    QList<Cliente*>* findClientes(QString lettersNome);
    QList<Cliente*>* findAll();
    Cliente* erase(int id,bool delServicos=true);
    bool existClient();
};

#endif // CLIENTEDAO_H
