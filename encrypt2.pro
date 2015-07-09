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
QMAKE_CXXFLAGS += -D_FILE_OFFSET_BITS=64 -DLARGEFILE_SOURCE=1a
macx: LIBS+= -I/usr/local/include -L/usr/local/lib -lgpgme -lassuan -lgpg-error
unix:!macx {
LIBS+= `gpgme-config  --cflags --libs`
}
win32: LIBS += -lWS2_32 -L$$PWD/ -llibgpgme-11
win32: INCLUDEPATH += $$PWD/
win32: DEPENDPATH += $$PWD/

target.path = ~/encrypt2
INSTALLS += target

