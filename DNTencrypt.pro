######################################################################
# Automatically generated by qmake (2.01a) Fri Oct 30 16:27:20 2015
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . \
              form_gui \
              include \
              src \
              src_gui
INCLUDEPATH += . include build/src

# Input
HEADERS += include/gpg-error.h \
           include/gpgme.h \
           include/mainwindow.h \
           include/mytextedit.h \
           include/objects.h \
           include/passphrase.h \
           include/settings.h \
           include/sha1.h \
           include/t-support.h \
    include/chatinit.h \
    form_gui/chatinit.h
FORMS += form_gui/mainwindow.ui \
         form_gui/passphrase.ui \
         form_gui/settings.ui \
    form_gui/passphraseform.ui \
    form_gui/chatinit.ui
SOURCES += src_gui/mainwindow.cpp \
           src_gui/passphrase.cpp \
           src_gui/passphraseform.cpp \
           src_gui/settings.cpp \
    form_gui/chatinit.cpp