QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    model/model.cc \
    model/model_credit.cc \
    model/model_deposit.cc \
    view/credit.cc \
    view/deposit.cc \
    main.cc \
    view/mainwindow.cc \
    view/qcustomplot.cc \
    controller/controller.cc

HEADERS += \
    model/model.h \
    model/model_credit.h \
    model/model_deposit.h \
    view/credit.h \
    view/deposit.h \
    view/mainwindow.h \
    view/qcustomplot.h \
    controller/controller.h

FORMS += \
    view/credit.ui \
    view/deposit.ui \
    view/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
