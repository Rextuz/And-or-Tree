#-------------------------------------------------
#
# Project created by QtCreator 2017-02-18T20:37:15
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = And-or_tree-template
TEMPLATE = app


SOURCES += src/logic/main.cpp \
    src/ui/mainwindow.cpp \
    src/models/andortree.cpp \
    src/models/lexicaltree.cpp \
    src/ui/mainmenu.cpp \
    src/models/content.cpp \
    src/models/contenttemplate.cpp \
    src/models/joketemplate.cpp \
    src/models/tasktemplate.cpp \
    src/ui/templatemenu.cpp \
    src/models/node.cpp \
    src/logic/storage.cpp \
    src/logic/joketemplatecreator.cpp \
    src/logic/tasktemplatecreator.cpp

HEADERS  += src/ui/mainwindow.h \
    src/models/andortree.h \
    src/models/lexicaltree.h \
    src/ui/mainmenu.h \
    src/models/content.h \
    src/models/contenttemplate.h \
    src/models/joketemplate.h \
    src/models/tasktemplate.h \
    src/ui/templatemenu.h \
    src/models/node.h \
    src/logic/storage.h \
    src/logic/ctcreator.h \
    src/logic/joketemplatecreator.h \
    src/logic/tasktemplatecreator.h

RESOURCES += \
    res/default_jokes.qrc \
    res/images.qrc
