#-------------------------------------------------
#
# Project created by QtCreator 2016-10-31T21:31:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TutorialNeuralNetMiller
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    neural/net.cpp \
    neural/neuron.cpp \
    neural/trainingdata.cpp

HEADERS  += widget.h \
    neural/net.h \
    neural/neuron.h \
    neural/trainingdata.h
