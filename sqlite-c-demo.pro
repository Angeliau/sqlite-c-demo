TEMPLATE = app
#TEMPLATE = lib
TARGET = SQLITE3JNATEST
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS+=$$PWD/libsqlite3.so

SOURCES += \
    main.cpp \
    sqlite3test.cpp

HEADERS += \
    sqlite3test.h \
    sqlite3.h \
    base.h
