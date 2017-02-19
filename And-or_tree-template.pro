#-------------------------------------------------
#
# Project created by QtCreator 2017-02-18T20:37:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = And-or_tree-template
TEMPLATE = app


SOURCES += src/logic/main.cpp \
    src/ui/mainwindow.cpp \
    src/models/andortree.cpp \
    src/models/lexicaltree.cpp \
    src/ui/mainmenu.cpp \
    src/models/content.cpp \
    src/models/joke.cpp \
    src/models/task.cpp \
    src/models/contenttemplate.cpp \
    src/models/joketemplate.cpp \
    src/models/tasktemplate.cpp \
    src/logic/contenttemplateprototype.cpp \
    src/logic/joketemplateprototype.cpp \
    src/logic/tasktemplateprototype.cpp \
    src/logic/contentbuilder.cpp \
    src/ui/templatemenu.cpp \
    src/logic/taskbuilder.cpp \
    src/logic/jokebuilder.cpp

HEADERS  += src/ui/mainwindow.h \
    src/models/andortree.h \
    src/models/lexicaltree.h \
    src/ui/mainmenu.h \
    src/models/content.h \
    src/models/joke.h \
    src/models/task.h \
    src/models/contenttemplate.h \
    src/models/joketemplate.h \
    src/models/tasktemplate.h \
    src/logic/contenttemplateprototype.h \
    src/logic/joketemplateprototype.h \
    src/logic/tasktemplateprototype.h \
    src/logic/contentbuilder.h \
    src/ui/templatemenu.h \
    src/logic/taskbuilder.h \
    src/logic/jokebuilder.h

RESOURCES += \
    res/default_jokes.qrc \
    res/images.qrc
