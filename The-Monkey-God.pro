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
				model/matrix.cpp \
				model/solver.cpp

HEADERS		+=	mainwindow.h \
				model/matrix.h \
				model/solver.h

FORMS		+=	mainwindow.ui
