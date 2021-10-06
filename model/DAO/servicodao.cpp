#include "servicodao.h"

#include <QSqlQuery>
#include <QVariant>
#include <QStringList>

ServicoDAO* ServicoDAO::dao = 0;

ServicoDAO::ServicoDAO() {}

ServicoDAO* ServicoDAO::getInstance() {
    if(!dao) {
        dao = new ServicoDAO();
    }
    return dao;
}

Servico* ServicoDAO::insert(Servico *s) {

    QSqlQuery query;
    QString tipo = s->getTipo();
    QString preco = QString::number(s->getPreco());
    QString data = s->getData().toString("dd/MM/yyyy");
    QString cliente = QString::number( s->getCliente() );
    QString obs = s->getObservacoes();
    query.prepare(QString("INSERT INTO servicos (tipo,preco,data,cliente,observacoes) values ('%1',%2,'%3',%4,'%5')")
                  .arg(tipo)
                  .arg(preco)
                  .arg(data)
                  .arg(cliente)
                  .arg(obs)
                  );
    if(!query.exec()) {
        return NULL;
    } else {
        s->setId(query.lastInsertId().toInt());
        return s;
//        query.prepare(QString("SELECT id FROM servicos WHERE tipo='%1' and preco=%2 and data='%3' and cliente=%4 and observacoes='%5'")
//                      .arg(tipo)
//                      .arg(preco)
//                      .arg(data)
//                      .arg(cliente)
//                      .arg(obs)
//                      );
//        if(!query.exec()) {
//            return NULL;
//        } else {
//            while(query.next()) {
//                int id = query.value(0).toInt();
//                s->setId(id);
//                return s;
//            }
//            return NULL;
//        }
    }
}

Servico* ServicoDAO::update(Servico *s) {

    QSqlQuery query;
    query.prepare(QString("UPDATE servicos SET tipo='%1',preco=%2,data='%3',cliente=%4, observacoes='%5' WHERE id=%6")
                  .arg(s->getTipo())
                  .arg( QString::number(s->getPreco()) )
                  .arg(s->getData().toString("dd/MM/yyyy"))
                  .arg( QString::number(s->getCliente()) )
                  .arg(s->getObservacoes())
                  .arg( QString::number(s->getId()) )
                  );
    if(!query.exec()) {
        return NULL;
    } else {
        return s;
    }

}

Servico* ServicoDAO::findServico(int id) {

    QSqlQuery query;
    query.prepare(QString("SELECT * FROM servicos WHERE id=%1").arg(QString::number(id)));
    if(!query.exec()) {
        return NULL;
    } else {
        while(query.next()) {
            Servico* s = new Servico();
            s->setId(query.value(0).toInt());
            s->setTipo(query.value(1).toString());
            s->setPreco(query.value(2).toDouble());
            QString d = query.value(3).toString();
            QStringList dSep = d.split("/");
            QDate data;
            data.setDate(dSep.value(2).toInt(),dSep.value(1).toInt(),dSep.value(0).toInt());
            s->setData(data);
            s->setCliente(query.value(4).toInt());
            s->setObservacoes(query.value(5).toString());
            return s;
        }
        return NULL;
    }

}

QList<Servico*>* ServicoDAO::findServicos(int idCliente) {

    QSqlQuery query;
    query.prepare(QString("SELECT * FROM servicos WHERE cliente=%1 ORDER BY tipo").arg(QString::number(idCliente)));
    if(!query.exec()) {
        return NULL;
    } else {
        QList<Servico*>* lista = new QList<Servico*>();
        int contador = 0;
        while(query.next()) {
            Servico* s = new Servico();
            s->setId(query.value(0).toInt());
            s->setTipo(query.value(1).toString());
            s->setPreco(query.value(2).toDouble());
            QString d = query.value(3).toString();
            QStringList dSep = d.split("/");
            QDate data;
            data.setDate(dSep.value(2).toInt(),dSep.value(1).toInt(),dSep.value(0).toInt());
            s->setData(data);
            s->setCliente(query.value(4).toInt());
            s->setObservacoes(query.value(5).toString());
            lista->insert(contador++,s);
        }
        return lista;
    }

}

QList<Servico*>* ServicoDAO::findServicos(QString lettersTipo) {

    QSqlQuery query;
    query.prepare(QString("SELECT * FROM servicos WHERE tipo LIKE ('%%1%') ORDER BY tipo").arg(lettersTipo));
    if(!query.exec()) {
        return NULL;
    } else {
        QList<Servico*>* lista = new QList<Servico*>();
        int contador = 0;
        while(query.next()) {
            Servico* s = new Servico();
            s->setId(query.value(0).toInt());
            s->setTipo(query.value(1).toString());
            s->setPreco(query.value(2).toDouble());
            QString d = query.value(3).toString();
            QStringList dSep = d.split("/");
            QDate data;
            data.setDate(dSep.value(2).toInt(),dSep.value(1).toInt(),dSep.value(0).toInt());
            s->setData(data);
            s->setCliente(query.value(4).toInt());
            s->setObservacoes(query.value(5).toString());
            lista->insert(contador++,s);
        }
        return lista;
    }

}

QList<Servico*>* ServicoDAO::findAll() {
    QSqlQuery query;
    query.prepare(QString("SELECT * FROM servicos ORDER BY tipo"));
    if(!query.exec()) {
        return NULL;
    } else {
        QList<Servico*>* lista = new QList<Servico*>();
        int contador = 0;
        while(query.next()) {
            Servico* s = new Servico();
            s->setId(query.value(0).toInt());
            s->setTipo(query.value(1).toString());
            s->setPreco(query.value(2).toDouble());
            QString d = query.value(3).toString();
            QStringList dSep = d.split("/");
            QDate data;
            data.setDate(dSep.value(2).toInt(),dSep.value(1).toInt(),dSep.value(0).toInt());
            s->setData(data);
            s->setCliente(query.value(4).toInt());
            s->setObservacoes(query.value(5).toString());
            lista->insert(contador++,s);
        }
        return lista;
    }

}

Servico* ServicoDAO::erase(int id) {

    Servico* s = this->findServico(id);

    if(s != NULL) {
        QSqlQuery query;
        query.prepare(QString("DELETE FROM servicos WHERE id=%1").arg(QString::number(id)));
        if(!query.exec()) {
            return NULL;
        }
    }

    return s;
}

double ServicoDAO::calcularTotalValoresServicos() {

    QSqlQuery query;
    query.prepare(QString("SELECT sum(preco) FROM servicos"));
    if(!query.exec()) {
        return -1;
    } else {
        while(query.next()) {
            return query.value(0).toDouble();
        }
        return 0;
    }

}

double ServicoDAO::calcularTotalValoresServicos(int mes, int ano) {

    QList<Servico*>* servicos = this->findAll();

    double total = -1;
    if(servicos != NULL) {
        total = 0;
        int size = servicos->size();
        for(int i = 0; i < size; i++) {
            Servico* s = servicos->at(i);
            QDate data = s->getData();
            if(data.month() == mes && data.year() == ano) {
                total += s->getPreco();
            }
        }
    }

    return total;
}
