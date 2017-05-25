#-------------------------------------------------
#
# Project created by QtCreator 2017-02-18T20:37:15
#
#-------------------------------------------------

QT       += core gui xml

QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = And-or_tree-template
TEMPLATE = app


SOURCES += src/logic/main.cpp \
    src/ui/mainwindow.cpp \
    src/ui/mainmenu.cpp \
    src/models/content.cpp \
    src/models/contenttemplate.cpp \
    src/models/joketemplate.cpp \
    src/models/tasktemplate.cpp \
    src/ui/templatemenu.cpp \
    src/logic/storage.cpp \
    src/logic/joketemplatecreator.cpp \
    src/logic/tasktemplatecreator.cpp \
    src/ui/savemenu.cpp \
    src/models/serializer.cpp \
    src/ui/visualizator.cpp

HEADERS  += src/ui/mainwindow.h \
    src/models/andortree.h \
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
    src/logic/tasktemplatecreator.h \
    src/models/lexicalpair.h \
    src/ui/savemenu.h \
    src/models/serializer.h \
    src/ui/visualizator.h \
    src/ui/customitem.h

RESOURCES += \
    res/images.qrc \
    res/templates.qrc
