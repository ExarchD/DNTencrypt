TEMPLATE = app
TARGET = encrypt2
INCLUDEPATH += . include /usr/local/include
# Input
HEADERS += include/objects.h include/t-support.h \
    mainwindow.h \ 
    passphrase.h \
    include/sha1.h \
    settings.h
SOURCES += src/main.cxx src/sender.cxx \
    mainwindow.cpp \
    passphrase.cpp \
    src/encrypter.cpp \
    src/retriever.cpp \
    src/sha1.cpp \
    settings.cpp

QT       += core gui
QT += widgets concurrent
FORMS += \
    mainwindow.ui \
    passphrase.ui \
    settings.ui
QMAKE_CXXFLAGS += -D_FILE_OFFSET_BITS=64 -std=c++11 -DLARGEFILE_SOURCE=1
#LIBS+= `gpgme-config  --cflags --libs`
#LIBS+= `C:/Program%20Files%20(x86)/GnuPG/bin/gpgconf.exe  --cflags --libs`
#LIBS+=-I/usr/local/include -L/usr/local/lib -lgpgme -lassuan -lgpg-error
LIBS      += -lWS2_32

target.path = ~/encrypt2
INSTALLS += target


unix|win32: LIBS += -L$$PWD/ -llibgpgme-11

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
