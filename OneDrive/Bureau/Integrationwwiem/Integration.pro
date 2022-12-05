QT       += core gui sql quick printsupport texttospeech widgets multimedia serialport charts svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accuse.cpp \
    accuse_stat.cpp \
    affaire.cpp \
    affaire_inter.cpp \
    arduino.cpp \
    authentification.cpp \
    avocat.cpp \
    avocat_inter.cpp \
    citoyen.cpp \
    connexion.cpp \
    main.cpp \
    mainwindow_acuucse.cpp \
    mainwindow_citoyen.cpp \
    menu.cpp \
    qrcode.cpp \
    qrcodegeneratordemo.cpp \
    qrcodegeneratorworker.cpp \
    qrwidget.cpp \
    salle.cpp \
    salle_inter.cpp \
    stat_nb.cpp\
    employer.cpp \
    gestion_des_em.cpp \
    smtp.cpp

HEADERS += \
    accuse.h \
    accuse_stat.h \
    affaire.h \
    affaire_inter.h \
    arduino.h \
    authentification.h \
    avocat.h \
    avocat_inter.h \
    citoyen.h \
    connexion.h \
    mainwindow_acuucse.h \
    mainwindow_citoyen.h \
    menu.h \
    qrcode.h \
    qrwidget.h \
    salle.h \
    salle_inter.h \
    stat_nb.h \
    employer.h \
    gestion_des_em.h \
    smtp.h

FORMS += \
    accuse_stat.ui \
    affaire_inter.ui \
    authentification.ui \
    avocat_inter.ui \
    mainwindow_acuucse.ui \
    mainwindow_citoyen.ui \
    menu.ui \
    salle_inter.ui \
    stat_nb.ui \
    gestion_des_em.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    court.qrc
