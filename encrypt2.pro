TEMPLATE = app
TARGET = encrypt2
INCLUDEPATH += . include /usr/local/include
# Input
HEADERS += include/objects.h include/t-support.h \
    mainwindow.h 
SOURCES += src/main.cxx src/retriever.cxx src/sender.cxx \
    mainwindow.cpp

QT       += core gui
QT += widgets
FORMS += \
    mainwindow.ui
CONFIG -=x86_64
#unix|win32: LIBS += -D_FILE_OFFSET_BITS=64
LIBS+= -L/usr/local/lib -lgpgme

