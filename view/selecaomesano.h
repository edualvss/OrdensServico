#ifndef SELECAOMESANO_H
#define SELECAOMESANO_H

#include <QDialog>

namespace Ui {
    class SelecaoMesAno;
}

class SelecaoMesAno : public QDialog {
    Q_OBJECT
public:
    SelecaoMesAno(QWidget *parent = 0);
    ~SelecaoMesAno();

signals:
    void mesAno(int,int);

private:
    Ui::SelecaoMesAno *ui;

private slots:
    void ok();
};

#endif // SELECAOMESANO_H
