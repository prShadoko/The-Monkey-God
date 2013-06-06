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
				model/matrix.cpp \
				model/solver.cpp \
				view/mainwindow.cpp

HEADERS		+=	model/matrix.h \
				model/solver.h \
				view/mainwindow.h

FORMS		+=	view/mainwindow.ui
