# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux-x86
TARGET = MapEditor
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
QT = core gui
SOURCES += src/MapInfo.cpp qtforms/MainForm.cpp src/main.cpp src/MapArea.cpp qtforms/DialogNew.cpp
HEADERS += src/MapInfo.h qtforms/DialogNew.h qtforms/MainForm.h qtforms/ui_MainForm.h src/MapArea.h qtforms/ui_DialogNew.h
FORMS += qtforms/DialogNew.ui qtforms/MainForm.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux-x86
MOC_DIR = qtforms
RCC_DIR = qtforms
UI_DIR = qtforms
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += src qtforms ../include_common 
LIBS += 
