#ifndef TELAOPCOES_H
#define TELAOPCOES_H

#include <QDialog>

namespace Ui {
    class TelaOpcoes;
}

class TelaOpcoes : public QDialog {
    Q_OBJECT
public:
    TelaOpcoes(QStringList opcoes,QWidget *parent = 0);
    ~TelaOpcoes();

    int getCurrentIndexOpcoes();

private:
    Ui::TelaOpcoes *ui;
};

#endif // TELAOPCOES_H
