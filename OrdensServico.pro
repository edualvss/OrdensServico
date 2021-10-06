TEMPLATE = app

QT = core \
    gui \
    sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets # Qt 5



HEADERS += model/servico.h \
    model/cliente.h \
    model/DAO/servicodao.h \
    model/DAO/clientedao.h \
    control/controle.h \
    view/telaprincipal.h \
    view/telacriarordemservico.h \
    view/telaopcoes.h \
    view/selecaomesano.h \
    view/telaedicaocliente.h \
    view/telaedicaoservico.h
SOURCES += model/servico.cpp \
    model/cliente.cpp \
    model/DAO/servicodao.cpp \
    model/DAO/clientedao.cpp \
    main.cpp \
    control/controle.cpp \
    view/telaprincipal.cpp \
    view/telacriarordemservico.cpp \
    view/telaopcoes.cpp \
    view/selecaomesano.cpp \
    view/telaedicaocliente.cpp \
    view/telaedicaoservico.cpp
FORMS += view/telaprincipal.ui \
    view/telacriarordemservico.ui \
    view/telaopcoes.ui \
    view/selecaomesano.ui \
    view/telaedicaocliente.ui \
    view/telaedicaoservico.ui
RESOURCES += images.qrc
