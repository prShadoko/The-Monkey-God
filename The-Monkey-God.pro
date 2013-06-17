#-------------------------------------------------
#
# Project created by QtCreator 2013-05-27T17:33:26
#
#-------------------------------------------------

QT			+=	core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET		=	The-Monkey-God
TEMPLATE	=	app


SOURCES		+=	main.cpp\
				model/matrix.cpp \
				view/mainwindow.cpp \
				model/solver.cpp

HEADERS		+=	model/matrix.h \
				view/mainwindow.h \
				model/solver.h

FORMS		+=	view/mainwindow.ui

RESOURCES	+=	resources.qrc
