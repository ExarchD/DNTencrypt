#############################################################################
# Makefile for building: encrypt2
# Generated by qmake (3.0) (Qt 5.4.1)
# Project:  encrypt2.pro
# Template: app
# Command: /usr/lib/qt/bin/qmake -o Makefile encrypt2.pro
#############################################################################

MAKEFILE      = Makefile

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CONCURRENT_LIB -DQT_CORE_LIB
CFLAGS        = -pipe -O2 -march=x86-64 -mtune=generic -O2 -pipe -fstack-protector-strong --param=ssp-buffer-size=4 -Wall -W -D_REENTRANT -fPIC $(DEFINES)
CXXFLAGS      = -pipe -D_FILE_OFFSET_BITS=64 -std=c++11 -O2 -march=x86-64 -mtune=generic -O2 -pipe -fstack-protector-strong --param=ssp-buffer-size=4 -Wall -W -D_REENTRANT -fPIC $(DEFINES)
INCPATH       = -I. -I. -Iinclude -isystem /usr/local/include -isystem /usr/include/qt -isystem /usr/include/qt/QtWidgets -isystem /usr/include/qt/QtGui -isystem /usr/include/qt/QtConcurrent -isystem /usr/include/qt/QtCore -I. -I. -I/usr/lib/qt/mkspecs/linux-g++
QMAKE         = /usr/lib/qt/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = encrypt21.0.0
DISTDIR = /home/dpluth/Source/encrypt2/.tmp/encrypt21.0.0
LINK          = g++
LFLAGS        = -Wl,-O1 -Wl,-O1,--sort-common,--as-needed,-z,relro
LIBS          = $(SUBLIBS) `gpgme-config --cflags --libs` -lQt5Widgets -lQt5Gui -lQt5Concurrent -lQt5Core -lGL -lpthread 
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = src/main.cxx \
		src/sender.cxx \
		mainwindow.cpp \
		passphrase.cpp \
		src/retriever.cpp moc_mainwindow.cpp \
		moc_passphrase.cpp
OBJECTS       = main.o \
		sender.o \
		mainwindow.o \
		passphrase.o \
		retriever.o \
		moc_mainwindow.o \
		moc_passphrase.o
DIST          = /usr/lib/qt/mkspecs/features/spec_pre.prf \
		/usr/lib/qt/mkspecs/common/shell-unix.conf \
		/usr/lib/qt/mkspecs/common/unix.conf \
		/usr/lib/qt/mkspecs/common/linux.conf \
		/usr/lib/qt/mkspecs/common/gcc-base.conf \
		/usr/lib/qt/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/qt/mkspecs/common/g++-base.conf \
		/usr/lib/qt/mkspecs/common/g++-unix.conf \
		/usr/lib/qt/mkspecs/qconfig.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_clucene_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_declarative.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_declarative_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_designer.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_designer_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_designercomponents_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_help.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_help_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_location.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_location_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_positioning.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_positioning_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_qml.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_qml_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_qmltest.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_qmltest_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_quick.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_quick_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_quickparticles_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_quickwidgets.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_quickwidgets_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_script.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_script_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_scripttools.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_scripttools_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_sensors.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_sensors_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_uitools.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_uitools_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_webchannel.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_webchannel_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_webkit.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_webkit_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_webkitwidgets.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_webkitwidgets_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_xmlpatterns.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_xmlpatterns_private.pri \
		/usr/lib/qt/mkspecs/features/qt_functions.prf \
		/usr/lib/qt/mkspecs/features/qt_config.prf \
		/usr/lib/qt/mkspecs/linux-g++/qmake.conf \
		/usr/lib/qt/mkspecs/features/spec_post.prf \
		/usr/lib/qt/mkspecs/features/exclusive_builds.prf \
		/usr/lib/qt/mkspecs/features/default_pre.prf \
		/usr/lib/qt/mkspecs/features/resolve_config.prf \
		/usr/lib/qt/mkspecs/features/default_post.prf \
		/usr/lib/qt/mkspecs/features/warn_on.prf \
		/usr/lib/qt/mkspecs/features/qt.prf \
		/usr/lib/qt/mkspecs/features/resources.prf \
		/usr/lib/qt/mkspecs/features/moc.prf \
		/usr/lib/qt/mkspecs/features/unix/opengl.prf \
		/usr/lib/qt/mkspecs/features/uic.prf \
		/usr/lib/qt/mkspecs/features/unix/thread.prf \
		/usr/lib/qt/mkspecs/features/testcase_targets.prf \
		/usr/lib/qt/mkspecs/features/exceptions.prf \
		/usr/lib/qt/mkspecs/features/yacc.prf \
		/usr/lib/qt/mkspecs/features/lex.prf \
		encrypt2.pro include/objects.h \
		include/t-support.h \
		mainwindow.h \
		passphrase.h src/main.cxx \
		src/sender.cxx \
		mainwindow.cpp \
		passphrase.cpp \
		src/retriever.cpp
QMAKE_TARGET  = encrypt2
DESTDIR       = #avoid trailing-slash linebreak
TARGET        = encrypt2


first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

$(TARGET): ui_mainwindow.h ui_passphrase.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: encrypt2.pro /usr/lib/qt/mkspecs/linux-g++/qmake.conf /usr/lib/qt/mkspecs/features/spec_pre.prf \
		/usr/lib/qt/mkspecs/common/shell-unix.conf \
		/usr/lib/qt/mkspecs/common/unix.conf \
		/usr/lib/qt/mkspecs/common/linux.conf \
		/usr/lib/qt/mkspecs/common/gcc-base.conf \
		/usr/lib/qt/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/qt/mkspecs/common/g++-base.conf \
		/usr/lib/qt/mkspecs/common/g++-unix.conf \
		/usr/lib/qt/mkspecs/qconfig.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_clucene_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_declarative.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_declarative_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_designer.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_designer_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_designercomponents_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_help.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_help_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_location.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_location_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_positioning.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_positioning_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_qml.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_qml_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_qmltest.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_qmltest_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_quick.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_quick_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_quickparticles_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_quickwidgets.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_quickwidgets_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_script.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_script_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_scripttools.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_scripttools_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_sensors.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_sensors_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_uitools.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_uitools_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_webchannel.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_webchannel_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_webkit.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_webkit_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_webkitwidgets.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_webkitwidgets_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_xmlpatterns.pri \
		/usr/lib/qt/mkspecs/modules/qt_lib_xmlpatterns_private.pri \
		/usr/lib/qt/mkspecs/features/qt_functions.prf \
		/usr/lib/qt/mkspecs/features/qt_config.prf \
		/usr/lib/qt/mkspecs/linux-g++/qmake.conf \
		/usr/lib/qt/mkspecs/features/spec_post.prf \
		/usr/lib/qt/mkspecs/features/exclusive_builds.prf \
		/usr/lib/qt/mkspecs/features/default_pre.prf \
		/usr/lib/qt/mkspecs/features/resolve_config.prf \
		/usr/lib/qt/mkspecs/features/default_post.prf \
		/usr/lib/qt/mkspecs/features/warn_on.prf \
		/usr/lib/qt/mkspecs/features/qt.prf \
		/usr/lib/qt/mkspecs/features/resources.prf \
		/usr/lib/qt/mkspecs/features/moc.prf \
		/usr/lib/qt/mkspecs/features/unix/opengl.prf \
		/usr/lib/qt/mkspecs/features/uic.prf \
		/usr/lib/qt/mkspecs/features/unix/thread.prf \
		/usr/lib/qt/mkspecs/features/testcase_targets.prf \
		/usr/lib/qt/mkspecs/features/exceptions.prf \
		/usr/lib/qt/mkspecs/features/yacc.prf \
		/usr/lib/qt/mkspecs/features/lex.prf \
		encrypt2.pro \
		/usr/lib/libQt5Widgets.prl \
		/usr/lib/libQt5Gui.prl \
		/usr/lib/libQt5Core.prl \
		/usr/lib/libQt5Concurrent.prl
	$(QMAKE) -o Makefile encrypt2.pro
/usr/lib/qt/mkspecs/features/spec_pre.prf:
/usr/lib/qt/mkspecs/common/shell-unix.conf:
/usr/lib/qt/mkspecs/common/unix.conf:
/usr/lib/qt/mkspecs/common/linux.conf:
/usr/lib/qt/mkspecs/common/gcc-base.conf:
/usr/lib/qt/mkspecs/common/gcc-base-unix.conf:
/usr/lib/qt/mkspecs/common/g++-base.conf:
/usr/lib/qt/mkspecs/common/g++-unix.conf:
/usr/lib/qt/mkspecs/qconfig.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_bootstrap_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_clucene_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_concurrent.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_concurrent_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_core.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_core_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_dbus.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_dbus_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_declarative.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_declarative_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_designer.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_designer_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_designercomponents_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_gui.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_gui_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_help.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_help_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_location.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_location_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_network.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_network_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_opengl.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_opengl_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_openglextensions.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_openglextensions_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_platformsupport_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_positioning.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_positioning_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_printsupport.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_printsupport_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_qml.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_qml_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_qmldevtools_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_qmltest.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_qmltest_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_quick.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_quick_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_quickparticles_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_quickwidgets.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_quickwidgets_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_script.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_script_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_scripttools.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_scripttools_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_sensors.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_sensors_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_sql.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_sql_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_testlib.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_testlib_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_uitools.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_uitools_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_webchannel.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_webchannel_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_webkit.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_webkit_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_webkitwidgets.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_webkitwidgets_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_widgets.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_widgets_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_xml.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_xml_private.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_xmlpatterns.pri:
/usr/lib/qt/mkspecs/modules/qt_lib_xmlpatterns_private.pri:
/usr/lib/qt/mkspecs/features/qt_functions.prf:
/usr/lib/qt/mkspecs/features/qt_config.prf:
/usr/lib/qt/mkspecs/linux-g++/qmake.conf:
/usr/lib/qt/mkspecs/features/spec_post.prf:
/usr/lib/qt/mkspecs/features/exclusive_builds.prf:
/usr/lib/qt/mkspecs/features/default_pre.prf:
/usr/lib/qt/mkspecs/features/resolve_config.prf:
/usr/lib/qt/mkspecs/features/default_post.prf:
/usr/lib/qt/mkspecs/features/warn_on.prf:
/usr/lib/qt/mkspecs/features/qt.prf:
/usr/lib/qt/mkspecs/features/resources.prf:
/usr/lib/qt/mkspecs/features/moc.prf:
/usr/lib/qt/mkspecs/features/unix/opengl.prf:
/usr/lib/qt/mkspecs/features/uic.prf:
/usr/lib/qt/mkspecs/features/unix/thread.prf:
/usr/lib/qt/mkspecs/features/testcase_targets.prf:
/usr/lib/qt/mkspecs/features/exceptions.prf:
/usr/lib/qt/mkspecs/features/yacc.prf:
/usr/lib/qt/mkspecs/features/lex.prf:
encrypt2.pro:
/usr/lib/libQt5Widgets.prl:
/usr/lib/libQt5Gui.prl:
/usr/lib/libQt5Core.prl:
/usr/lib/libQt5Concurrent.prl:
qmake: FORCE
	@$(QMAKE) -o Makefile encrypt2.pro

qmake_all: FORCE


all: Makefile $(TARGET)

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/
	$(COPY_FILE) --parents include/objects.h include/t-support.h mainwindow.h passphrase.h $(DISTDIR)/
	$(COPY_FILE) --parents src/main.cxx src/sender.cxx mainwindow.cpp passphrase.cpp src/retriever.cpp $(DISTDIR)/
	$(COPY_FILE) --parents mainwindow.ui passphrase.ui $(DISTDIR)/


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


####### Sub-libraries

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

check: first

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_moc_header_make_all: moc_mainwindow.cpp moc_passphrase.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_passphrase.cpp
moc_mainwindow.cpp: mainwindow.h
	/usr/lib/qt/bin/moc $(DEFINES) -I/usr/lib/qt/mkspecs/linux-g++ -I/home/dpluth/Source/encrypt2 -I/home/dpluth/Source/encrypt2 -I/home/dpluth/Source/encrypt2/include -I/usr/local/include -I/usr/include/qt -I/usr/include/qt/QtWidgets -I/usr/include/qt/QtGui -I/usr/include/qt/QtConcurrent -I/usr/include/qt/QtCore -I/usr/include/c++/4.9.2 -I/usr/include/c++/4.9.2/x86_64-unknown-linux-gnu -I/usr/include/c++/4.9.2/backward -I/usr/lib/gcc/x86_64-unknown-linux-gnu/4.9.2/include -I/usr/local/include -I/usr/lib/gcc/x86_64-unknown-linux-gnu/4.9.2/include-fixed -I/usr/include mainwindow.h -o moc_mainwindow.cpp

moc_passphrase.cpp: passphrase.h
	/usr/lib/qt/bin/moc $(DEFINES) -I/usr/lib/qt/mkspecs/linux-g++ -I/home/dpluth/Source/encrypt2 -I/home/dpluth/Source/encrypt2 -I/home/dpluth/Source/encrypt2/include -I/usr/local/include -I/usr/include/qt -I/usr/include/qt/QtWidgets -I/usr/include/qt/QtGui -I/usr/include/qt/QtConcurrent -I/usr/include/qt/QtCore -I/usr/include/c++/4.9.2 -I/usr/include/c++/4.9.2/x86_64-unknown-linux-gnu -I/usr/include/c++/4.9.2/backward -I/usr/lib/gcc/x86_64-unknown-linux-gnu/4.9.2/include -I/usr/local/include -I/usr/lib/gcc/x86_64-unknown-linux-gnu/4.9.2/include-fixed -I/usr/include passphrase.h -o moc_passphrase.cpp

compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_passphrase.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_passphrase.h
ui_mainwindow.h: mainwindow.ui
	/usr/lib/qt/bin/uic mainwindow.ui -o ui_mainwindow.h

ui_passphrase.h: passphrase.ui
	/usr/lib/qt/bin/uic passphrase.ui -o ui_passphrase.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

main.o: src/main.cxx include/objects.h \
		mainwindow.h \
		passphrase.h \
		include/t-support.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o src/main.cxx

sender.o: src/sender.cxx include/objects.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sender.o src/sender.cxx

mainwindow.o: mainwindow.cpp mainwindow.h \
		ui_mainwindow.h \
		include/objects.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

passphrase.o: passphrase.cpp passphrase.h \
		ui_passphrase.h \
		include/objects.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o passphrase.o passphrase.cpp

retriever.o: src/retriever.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o retriever.o src/retriever.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_passphrase.o: moc_passphrase.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_passphrase.o moc_passphrase.cpp

####### Install

install_target: first FORCE
	@test -d $(INSTALL_ROOT)/home/dpluth/encrypt2 || mkdir -p $(INSTALL_ROOT)/home/dpluth/encrypt2
	-$(INSTALL_PROGRAM) "$(QMAKE_TARGET)" "$(INSTALL_ROOT)/home/dpluth/encrypt2/$(QMAKE_TARGET)"
	-$(STRIP) "$(INSTALL_ROOT)/home/dpluth/encrypt2/$(QMAKE_TARGET)"

uninstall_target: FORCE
	-$(DEL_FILE) "$(INSTALL_ROOT)/home/dpluth/encrypt2/$(QMAKE_TARGET)"
	-$(DEL_DIR) $(INSTALL_ROOT)/home/dpluth/encrypt2/ 


install:  install_target  FORCE

uninstall: uninstall_target   FORCE

FORCE:

