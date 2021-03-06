CONFIG += c++11
QT += sql xml widgets network

FORMS += src/mainwindow.ui src/settingsdialog.ui
SOURCES += \
    src/application.cc \
    src/xmlrpc.cc \
    src/mainwindow.cc \
    src/main.cc \
    src/oshandling.cc \
    src/utils.cc \
    src/subdownloader.cc \
    src/settings.cc \
    src/settingsdialog.cc \
    src/subdata.cc \
    src/subtitlemodel.cc
HEADERS += \
    src/config.h \
    src/application.hh \
    src/xmlrpc.hh \
    src/mainwindow.hh \
    src/oshandling.hh \
    src/utils.hh \
    src/subdownloader.hh \
    src/settings.hh \
    src/settingsdialog.hh \
    src/subdata.hh \
    src/subtitlemodel.hh

DESTDIR = build
OBJECTS_DIR = build/.obj
MOC_DIR = build/.moc
RCC_DIR = build/.rcc
UI_DIR = build/.ui

TARGET = qsubber
