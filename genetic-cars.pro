QT += widgets

TEMPLATE = app
CONFIG += console c++11
CONFIG += c++11
CONFIG += gnu++11
QMAKE_CXXFLAGS += -std=c++11
CONFIG -= app_bundle
#CONFIG -= qt


TARGET = genetic_car
CONFIG -= app_bundle
TEMPLATE = app

CONFIG += console c++11
CONFIG += c++11
CONFIG += gnu++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    car.cpp \
    preprocessing.cpp \
    windows.cpp \
    strategy.cpp \
    Moteur.cpp \
    decision_tree.cpp \
    decision_tree_cell.cpp \
    firstLearner.cpp \
    learner.cpp

HEADERS += \
    car.h \
    windows.h \
    strategy.h \
    Moteur.h \
    decision_tree.h \
    decision_tree_cell.h \
    firstLearner.h \
    learner.h
