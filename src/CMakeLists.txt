include_directories(../include)
include_directories(../src_gui)
set(HEADER_FILES ../include/objects.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")


find_path(GPGME_INCLUDE_DIR gpgme.h)
find_library(GPGME_LIBRARY gpgme)
if(NOT GPGME_INCLUDE_DIR)
    message(SEND_ERROR "Failed to find gpgme.h")
endif()
if(NOT GPGME_LIBRARY)
    message(SEND_ERROR "Failed to find gpgme library")
endif()

find_path(SQLITE3_INCLUDE_DIR sqlite3.h)
find_library(SQLITE3_LIBRARY sqlite3)
if(NOT SQLITE3_INCLUDE_DIR)
    message(SEND_ERROR "Failed to find sqlite3.h")
endif()
if(NOT SQLITE3_LIBRARY)
    message(SEND_ERROR "Failed to find the sqlite3 library")
endif()

add_library(telecharger telecharger.cpp )
add_library(conversation conversation.cpp ../include/conversation.h )
add_library(sql sql.cpp)
add_library(encrypt encrypter.cpp )
add_library(sha1 sha1.cpp ../include/sha1.h )

# Qt5 requirements
include_directories(${CMAKE_CURRENT_BINARY_DIR})
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5Concurrent)

QT5_WRAP_UI(UIS_HDRS
    ../form_gui/mainwindow.ui
    ../form_gui/passphraseform.ui
    ../form_gui/passphrase.ui
    ../form_gui/settings.ui
    )

SET(SRC
    ../src_gui/mainwindow.cpp
    ../src_gui/passphraseform.cpp
    ../src_gui/passphrase.cpp
    ../src_gui/qrecorder.cpp
    ../src_gui/settings.cpp
    )


qt5_wrap_cpp(gui_SRC 
    ../include/mainwindow.h
    ../include/passphraseform.h
    ../include/passphrase.h
    ../include/settings.h
    )


add_executable(encrypt2  main.cxx ../include/objects.h ${UIS_HDRS} ${SRC} ${gui_SRC})
target_link_libraries(encrypt2 Qt5::Widgets)
target_link_libraries(encrypt2 encrypt ${GPGME_LIBRARY})
target_link_libraries(encrypt2 sha1)
target_link_libraries(encrypt2 telecharger)
target_link_libraries(encrypt2 conversation)
target_link_libraries(encrypt2 sql ${SQLITE3_LIBRARY})
###

install(TARGETS encrypt2
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)

