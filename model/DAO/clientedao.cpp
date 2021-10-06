#include "clientedao.h"

#include "model/DAO/servicodao.h"

#include <QSqlQuery>
#include <QVariant>

ClienteDAO* ClienteDAO::dao = 0;

ClienteDAO::ClienteDAO() {

}

ClienteDAO* ClienteDAO::getInstance() {
    if(!dao) {
        dao = new ClienteDAO();
    }
    return dao;
}

Cliente* ClienteDAO::insert(Cliente *c) {

    QSqlQuery query;
    QString nome = c->getNome();
    QString endereco = c->getEndereco();
    QString telefone = c->getTelefone();
    query.prepare(QString("INSERT INTO clientes (nome,endereco,telefone) values ('%1','%2','%3')")
                  .arg(nome)
                  .arg(endereco)
                  .arg(telefone)
                  );
    if(!query.exec()) {
        return NULL;
    } else {

       c->setId(query.lastInsertId().toInt());

        QList<Servico*>* servicos = c->getServicos();
        int size = servicos->size();
        ServicoDAO* sDao = ServicoDAO::getInstance();
        int idCliente = c->getId();
        for( int i = 0; i < size; i++ ) {
            Servico* s = servicos->at(i);
            s->setCliente(idCliente);
            sDao->insert(s);
        }
        return c;
    }

//        query.prepare(QString("SELECT id FROM clientes WHERE nome='%1' and endereco='%2' and telefone='%3'")
//                      .arg(nome)
//                      .arg(endereco)
//                      .arg(telefone)
//                      );
//        if(!query.exec()) {
//            return NULL;
//        } else {
//            while(query.next()) {
//                c->setId(query.value(0).toInt());
//            }

//            QList<Servico*>* servicos = c->getServicos();
//            int size = servicos->size();
//            ServicoDAO* sDao = ServicoDAO::getInstance();
//            int idCliente = c->getId();
//            for( int i = 0; i < size; i++ ) {
//                Servico* s = servicos->at(i);
//                s->setCliente(idCliente);
//                sDao->insert(s);
//            }
//            return c;
//        }
//    }
}

Cliente* ClienteDAO::update(Cliente *c) {

    QSqlQuery query;
    query.prepare(QString("UPDATE clientes SET nome='%1',endereco='%2',telefone='%3' WHERE id=%4")
                  .arg(c->getNome())
                  .arg(c->getEndereco())
                  .arg(c->getTelefone())
                  .arg(QString::number(c->getId()))
                  );
    if(!query.exec()) {
        return NULL;
    } else {
        QList<Servico*>* servicos = c->getServicos();
        int size = servicos->size();
        ServicoDAO* sDao = ServicoDAO::getInstance();
        int idCliente = c->getId();
        for(int i = 0; i < size; i++) {
            Servico* s = servicos->at(i);
            s->setCliente(idCliente);
            Servico* find = sDao->findServico(s->getId());
            if(find == NULL || s->getId() == 0) {
                sDao->insert(s);
            } else {
                if(!s->equals(find)) {
                    sDao->update(s);
                }
            }
        }
        return c;
    }

}

Cliente* ClienteDAO::findCliente(int id) {

    QSqlQuery query;

    query.prepare(QString("SELECT * FROM clientes WHERE id=%1 ORDER BY nome").arg(QString::number(id)));
    if(!query.exec()) {
        return NULL;
    } else {
        Cliente* cli = NULL;
        while(query.next()) {
            cli = new Cliente();
            cli->setId(query.value(0).toInt());
            cli->setNome(query.value(1).toString());
            cli->setEndereco(query.value(2).toString());
            cli->setTelefone(query.value(3).toString());
            break;
        }
        if(cli != NULL) {
            cli->setServicos(ServicoDAO::getInstance()->findServicos(id));
        }
        return cli;
    }

}

QList<Cliente*>* ClienteDAO::findClientes(QString lettersNome) {

    QSqlQuery query;
    query.prepare(QString("SELECT * FROM clientes WHERE nome LIKE ('%%1%') ORDER BY nome").arg(lettersNome));
    if(!query.exec()) {
        return NULL;
    } else {
        QList<Cliente*>* clientes = new QList<Cliente*>();
        int contador = 0;
        while(query.next()) {
            Cliente* cli = new Cliente();
            cli->setId(query.value(0).toInt());
            cli->setNome(query.value(1).toString());
            cli->setEndereco(query.value(2).toString());
            cli->setTelefone(query.value(3).toString());
            clientes->insert(contador++,cli);
        }
        int size = clientes->size();
        if(size == 0) {
            delete clientes;
            return NULL;
        } else {
            ServicoDAO* sDao = ServicoDAO::getInstance();
            for(int i = 0; i < size; i++) {
                Cliente* c = clientes->at(i);
                c->setServicos(sDao->findServicos(c->getId()));
            }
            return clientes;
        }
    }

}

QList<Cliente*>* ClienteDAO::findAll() {
    QSqlQuery query;
    query.prepare(QString("SELECT * FROM clientes ORDER BY nome"));
    if(!query.exec()) {
        return NULL;
    } else {
        QList<Cliente*>* clientes = new QList<Cliente*>();
        int contador = 0;
        while(query.next()) {
            Cliente* cli = new Cliente();
            cli->setId(query.value(0).toInt());
            cli->setNome(query.value(1).toString());
            cli->setEndereco(query.value(2).toString());
            cli->setTelefone(query.value(3).toString());
            clientes->insert(contador++,cli);

        }
        int size = clientes->size();
        if(size == 0) {
            delete clientes;
            return NULL;
        } else {
            ServicoDAO* sDao = ServicoDAO::getInstance();
            for(int i = 0; i < size; i++) {
                Cliente* c = clientes->at(i);
                c->setServicos(sDao->findServicos(c->getId()));
            }
            return clientes;
        }
    }
}

Cliente* ClienteDAO::erase(int id,bool delServicos) {

    Cliente* cli = this->findCliente(id);

    if(cli == NULL) {
        return NULL;
    }

    QSqlQuery query;

    query.prepare(QString("DELETE FROM clientes WHERE id=%1").arg(QString::number(id)));
    if(!query.exec()) {
        return NULL;
    } else {
        if(delServicos) {
            ServicoDAO* sDao = ServicoDAO::getInstance();
            QList<Servico*>* servicos = cli->getServicos();
            int size = servicos->size();
            for(int i = 0; i < size; i ++) {
                Servico* s = servicos->at(i);
                sDao->erase(s->getId());
                delete s;
            }
        }
        return cli;
    }
}

bool ClienteDAO::existClient() {

    QSqlQuery query;
    query.prepare("SELECT * FROM servicos");
    if(!query.exec()) {
        return false;
    } else {
        bool existe = false;
        while(query.next()) {
            existe = true;
            break;
        }
        return existe;
    }

}
