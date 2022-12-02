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
    admin.cpp \
    affaire.cpp \
    affaire_inter.cpp \
    arduino.cpp \
    authentification.cpp \
    avocat.cpp \
    avocat_inter.cpp \
    connexion.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    qrcode.cpp \
    qrcodegeneratordemo.cpp \
    qrcodegeneratorworker.cpp \
    qrwidget.cpp \
    stat_nb.cpp

HEADERS += \
    accuse.h \
    accuse_stat.h \
    admin.h \
    affaire.h \
    affaire_inter.h \
    arduino.h \
    authentification.h \
    avocat.h \
    avocat_inter.h \
    connexion.h \
    mainwindow.h \
    menu.h \
    qrcode.h \
    qrwidget.h \
    stat_nb.h

FORMS += \
    accuse_stat.ui \
    affaire_inter.ui \
    authentification.ui \
    avocat_inter.ui \
    mainwindow.ui \
    mainwindow_acuucse.ui \
    menu.ui \
    stat_nb.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    court.qrc
