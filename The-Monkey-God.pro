#-------------------------------------------------
#
# Project created by QtCreator 2013-05-27T17:33:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = The-Monkey-God
TEMPLATE = app


SOURCES		+=	main.cpp\
				mainwindow.cpp \
				model/treenode.cpp \
    model/matrix.cpp

HEADERS		+=	mainwindow.h \
				model/treenode.h \
    model/matrix.h

FORMS    += mainwindow.ui
